#ifndef h199A1ED3_8E95_435B_9976_AD9F400159F1
#define h199A1ED3_8E95_435B_9976_AD9F400159F1

#include "vector_3d.hpp"

namespace phase3d
{
  namespace model
  {
    
    template< typename SCALAR >
    class intersection
    {
    public:
      typedef SCALAR scalar;
      typedef vector_3d<scalar> vector_3d;

      scalar t_;
      vector_3d normal_;
      vector_2d uv_;
    };
    
  }
}

#endif
