#ifndef h8AABB0FF_875F_4D19_AA98_3DA69B8DF2B6
#define h8AABB0FF_875F_4D19_AA98_3DA69B8DF2B6

#include "intersection.hpp"
#include "interval.hpp"
#include "ray_3d.hpp"

#include <boost/shared_ptr.hpp>

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
      typedef typename phase3d::model::vector_2d<scalar> vector_2d;
      typedef typename phase3d::model::intersection<scalar> intersection;
      typedef typename phase3d::model::interval<scalar> interval;

      // Check if "ray" intersects "this" where range.low() <= t < range.high().
      virtual boost::shared_ptr<intersection> get_intersection( ray_3d const& ray, interval const& range ) const = 0;
    };
  }
}

#endif
