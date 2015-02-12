#ifndef h3AD34450_C3AA_4693_B4AD_B87A719246EB
#define h3AD34450_C3AA_4693_B4AD_B87A719246EB

#include "surface.hpp"

#include <boost/shared_ptr.hpp>

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class group
      : public phase3d::model::surface<SCALAR>
    {
    public:
      typedef SCALAR scalar;
      typedef phase3d::model::surface<scalar> base_type;
      typedef base_type surface_type;
      typedef typename base_type::intersection intersection;
      typedef typename base_type::interval interval;
      typedef typename base_type::ray_3d ray_3d;

      group& push_back( boost::shared_ptr< surface_type > surface )
      {
        surfaces_.push_back(surface);
        return *this;
      }

      boost::shared_ptr<intersection> get_intersection( ray_3d const& ray , interval const& original_range ) const
      {
        boost::shared_ptr<intersection> result;
        interval range(original_range);

        for( int i = 0; i < surfaces_.size() ; ++i )
          {
            boost::shared_ptr<intersection> check = surfaces_[i]->get_intersection( ray, range );
            if ( check.get() )
              {
                range = interval(range.low(), check->t_ );
                result = check;
              }
          }
        return result;
      }

    private:
      std::vector< boost::shared_ptr< surface_type > > surfaces_;
    };

  }
}

#endif
