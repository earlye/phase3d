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

      virtual scalar intersect( ray_3d const& ray ) = 0;
    };
  }
}

#endif
