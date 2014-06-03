#include <model/vector_2d.hpp>
#include <stdexcept>

typedef phase3d::model::vector_2d<double> double_vector_2d;

void test_v2d_length()
{
  double_vector_2d v2d(3,4);

  if (v2d.length() != 5) throw std::runtime_error( "expected v2d.length() == 5" );
}

void test_v2d_unary_negation()
{
  double_vector_2d v2d(1,2);

  v2d = -v2d;

  if ( v2d.data[0] != -1 ) throw std::runtime_error( "expected v2d[0] == -1" );
  if ( v2d.data[1] != -2 ) throw std::runtime_error( "expected v2d[1] == -2" );
}

void test_v2d_scalar_multiply()
{
  double_vector_2d v2d(1,2);

  v2d = 2 * v2d;

  if ( v2d.data[0] != 2 ) throw std::runtime_error( "expected v2d[0] == 2" );
  if ( v2d.data[1] != 4 ) throw std::runtime_error( "expected v2d[1] == 4" );
  
  v2d = v2d * 2;

  if ( v2d.data[0] != 4 ) throw std::runtime_error( "expected v2d[0] == 4" );
  if ( v2d.data[1] != 8 ) throw std::runtime_error( "expected v2d[1] == 8" );
}

void test_v2d_scalar_divide()
{
  double_vector_2d v2d(4,8);

  v2d = v2d / 2;

  if ( v2d.data[0] != 2 ) throw std::runtime_error( "expected v2d[0] == 2" );
  if ( v2d.data[1] != 4 ) throw std::runtime_error( "expected v2d[1] == 4" );
}

void test_v2d_add()
{
  double_vector_2d v2d_1(2,3);
  double_vector_2d v2d_2(4,6);

  double_vector_2d result = v2d_1 + v2d_2;

  if ( result.data[0] != 6 ) throw std::runtime_error( "expected result[0] == 6" );
  if ( result.data[1] != 9 ) throw std::runtime_error( "expected result[1] == 9" );

  result = v2d_2 - v2d_1;

  if ( result.data[0] != 2 ) throw std::runtime_error( "expected result[0] == 2" );
  if ( result.data[1] != 3 ) throw std::runtime_error( "expected result[1] == 3" );
}
