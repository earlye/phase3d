#ifndef h620BA860_BF38_41F4_8063_EBBBAC51BAB1
#define h620BA860_BF38_41F4_8063_EBBBAC51BAB1

#include "vector_3d.hpp"

namespace phase3d 
{
  namespace model
  {

    template< typename STORAGE >
    class ray_3d
    {
    public:
      typedef STORAGE storage;
      typedef ray_3d<storage> this_type;
      typedef vector_3d< storage > v3d;

      
      v3d origin_;
      v3d direction_;

      ray_3d() { }

      ray_3d(v3d origin, v3d direction)
	: origin_(origin)
	, direction_(direction)
      { }

      v3d point_at_parameter( storage t )
      {
	return origin_ + t * direction_;
      }
    };

  }
}

#endif
