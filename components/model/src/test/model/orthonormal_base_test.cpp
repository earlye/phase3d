#include <model/orthonormal_base.hpp>

typedef phase3d::model::orthonormal_base<double> orthonormal_base;
typedef phase3d::model::vector_3d<double> vector_3d;

namespace test_orthonormal_base
{

  void test_canonical()
  {
    orthonormal_base base;
  }

  void test_from_uv()
  {
    orthonormal_base base = orthonormal_base::from_uv( vector_3d::x_ , vector_3d::y_ );
  }

  void test_from_w()
  {
    orthonormal_base base = orthonormal_base::from_w( vector_3d::z_ );
  }

}
