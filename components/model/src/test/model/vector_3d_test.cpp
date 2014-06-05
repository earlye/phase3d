#include <model/vector_3d.hpp>
#include <stdexcept>

typedef phase3d::model::vector_3d<double> double_vector_3d;

void test_v3d_length()
{
  double_vector_3d v3d(3,4,0
);

  if (v3d.length() != 5) throw std::runtime_error( "expected v3d.length() == 5" );
}

void test_v3d_unary_negation()
{
  double_vector_3d v3d(1,2,3);

  v3d = -v3d;

  if ( v3d.data[0] != -1 ) throw std::runtime_error( "expected v3d[0] == -1" );
  if ( v3d.data[1] != -2 ) throw std::runtime_error( "expected v3d[1] == -2" );
  if ( v3d.data[2] != -3 ) throw std::runtime_error( "expected v3d[1] == -3" );
}

void test_v3d_scalar_multiply()
{
  double_vector_3d v3d(1,2,3);

  v3d = 2 * v3d;

  if ( v3d.data[0] != 2 ) throw std::runtime_error( "expected v3d[0] == 2" );
  if ( v3d.data[1] != 4 ) throw std::runtime_error( "expected v3d[1] == 4" );
  if ( v3d.data[2] != 6 ) throw std::runtime_error( "expected v3d[2] == 6" );
  
  v3d = v3d * 2;

  if ( v3d.data[0] != 4 ) throw std::runtime_error( "expected v3d[0] == 4" );
  if ( v3d.data[1] != 8 ) throw std::runtime_error( "expected v3d[1] == 8" );
  if ( v3d.data[2] != 12 ) throw std::runtime_error( "expected v3d[2] == 12" );
}

void test_v3d_scalar_divide()
{
  double_vector_3d v3d(4,8,12);

  v3d = v3d / 2;

  if ( v3d.data[0] != 2 ) throw std::runtime_error( "expected v3d[0] == 2" );
  if ( v3d.data[1] != 4 ) throw std::runtime_error( "expected v3d[1] == 4" );
  if ( v3d.data[2] != 6 ) throw std::runtime_error( "expected v3d[2] == 6" );
}

void test_v3d_add()
{
  double_vector_3d v3d_1(2,3,4);
  double_vector_3d v3d_2(4,6,8);

  double_vector_3d result = v3d_1 + v3d_2;

  if ( result.data[0] != 6 ) throw std::runtime_error( "expected result[0] == 6" );
  if ( result.data[1] != 9 ) throw std::runtime_error( "expected result[1] == 9" );
  if ( result.data[2] != 12 ) throw std::runtime_error( "expected result[2] == 12" );

  result = v3d_2 - v3d_1;

  if ( result.data[0] != 2 ) throw std::runtime_error( "expected result[0] == 2" );
  if ( result.data[1] != 3 ) throw std::runtime_error( "expected result[1] == 3" );
  if ( result.data[2] != 4 ) throw std::runtime_error( "expected result[1] == 4" );
}

void test_v3d_dot_product()
{
  double_vector_3d v3d_1(2,3,4);
  double_vector_3d v3d_2(4,6,8);

  double dot = v3d_1.dot_product(v3d_2);

  if ( dot != (2*4 + 3*6 + 4*8) ) throw std::runtime_error( "dot product is busted" );
}

void test_v3d_cross_product()
{
  double_vector_3d x_axis(1,0,0);
  double_vector_3d y_axis(0,1,0);
  double_vector_3d z_axis(0,0,1);

  if (z_axis != x_axis.cross_product(y_axis)) throw std::runtime_error( "cross product broken." );
  if (-z_axis != y_axis.cross_product(x_axis)) throw std::runtime_error( "cross product broken." );
  if (x_axis != y_axis.cross_product(z_axis)) throw std::runtime_error( "cross product broken." );
  if (-x_axis != z_axis.cross_product(y_axis)) throw std::runtime_error( "cross product broken." );
  if (y_axis != z_axis.cross_product(x_axis)) throw std::runtime_error( "cross product broken." );
  if (-y_axis != x_axis.cross_product(z_axis)) throw std::runtime_error( "cross product broken." );
}
