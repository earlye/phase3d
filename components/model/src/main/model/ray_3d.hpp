#ifndef h620BA860_BF38_41F4_8063_EBBBAC51BAB1
#define h620BA860_BF38_41F4_8063_EBBBAC51BAB1

#include "vector_3d.hpp"

namespace phase3d 
{
  namespace model
  {

    template< typename SCALAR >
    class ray_3d
    {
    public:
      typedef SCALAR scalar;
      typedef ray_3d<scalar> this_type;
      typedef typename phase3d::model::vector_3d< scalar > vector_3d;
      
      vector_3d origin_;
      vector_3d direction_;

      ray_3d() { }

      ray_3d(vector_3d origin, vector_3d direction)
	: origin_(origin)
	, direction_(direction)
      { }

      vector_3d point_at_parameter( scalar t ) const
      {
	return origin_ + t * direction_;
      }
    };

  }
}

#endif
