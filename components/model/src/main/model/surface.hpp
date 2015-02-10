#ifndef h8AABB0FF_875F_4D19_AA98_3DA69B8DF2B6
#define h8AABB0FF_875F_4D19_AA98_3DA69B8DF2B6

#include "ray_3d.hpp"

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class surface
    {
    public:
      typedef SCALAR scalar;
      typedef surface<scalar> this_type;
      typedef typename phase3d::model::ray_3d<scalar> ray_3d;

      // Check if "ray" intersects "this" where range.low() <= t < range.high().
      virtual boost::shared_ptr<intersection> get_intersection( ray_3d const& ray, interval<scalar> float range ) = 0;
    };
  }
}

#endif
