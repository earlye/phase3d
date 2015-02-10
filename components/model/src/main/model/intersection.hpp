#ifndef h199A1ED3_8E95_435B_9976_AD9F400159F1
#define h199A1ED3_8E95_435B_9976_AD9F400159F1

#include "vector_3d.hpp"
#include "vector_2d.hpp"

namespace phase3d
{
  namespace model
  {
    
    template< typename SCALAR >
    class intersection
    {
    public:
      typedef SCALAR scalar;
      typedef typename phase3d::model::ray_3d<scalar> ray_3d;
      typedef typename phase3d::model::vector_2d<scalar> vector_2d;

      scalar t_;
      ray_3d incident_ray_;
      ray_3d normal_;
      vector_2d uv_;

      intersection( scalar t , ray_3d incident_ray, ray_3d normal, vector_2d uv )
        : t_(t)
        , incident_ray_(incident_ray)
        , normal_(normal)
        , uv_(uv)
      { }
    };
    
  }
}

#endif
