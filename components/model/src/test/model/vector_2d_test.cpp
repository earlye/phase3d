#include <model/vector_2d.hpp>

#include <libede/ASSERT_EQUAL.hpp>

#include <stdexcept>

typedef phase3d::model::vector_2d<double> double_vector_2d;

void test_v2d_length()
{
  double_vector_2d v2d(3,4);

  ASSERT_EQUAL(v2d.length() , 5);
}

void test_v2d_unary_negation()
{
  double_vector_2d v2d(1,2);

  v2d = -v2d;

  ASSERT_EQUAL( v2d.data[0] , -1 );
  ASSERT_EQUAL( v2d.data[1] , -2 );
}

void test_v2d_scalar_multiply()
{
  double_vector_2d v2d(1,2);

  v2d = 2 * v2d;

  ASSERT_EQUAL( v2d.data[0] , 2 );
  ASSERT_EQUAL( v2d.data[1] , 4 );
  
  v2d = v2d * 2;

  ASSERT_EQUAL( v2d.data[0] , 4 );
  ASSERT_EQUAL( v2d.data[1] , 8 );
}

void test_v2d_scalar_divide()
{
  double_vector_2d v2d(4,8);

  v2d = v2d / 2;

  ASSERT_EQUAL( v2d.data[0] , 2 );
  ASSERT_EQUAL( v2d.data[1] , 4 );
}

void test_v2d_add()
{
  double_vector_2d v2d_1(2,3);
  double_vector_2d v2d_2(4,6);

  double_vector_2d result = v2d_1 + v2d_2;

  ASSERT_EQUAL( result.data[0] , 6 );
  ASSERT_EQUAL( result.data[1] , 9 );

  result = v2d_2 - v2d_1;

  ASSERT_EQUAL( result.data[0] , 2 );
  ASSERT_EQUAL( result.data[1] , 3 );
}

void test_v2d_dot_product()
{
  double_vector_2d v2d_1(2,3);
  double_vector_2d v2d_2(4,6);

  double dot = v2d_1.dot_product(v2d_2);

  ASSERT_EQUAL( dot , (2*4 + 3*6) );
}
