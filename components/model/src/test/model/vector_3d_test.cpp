#include <model/vector_3d.hpp>

#include <libede/ASSERT_EQUAL.hpp>

#include <iostream>
#include <stdexcept>
#include <sstream>

typedef phase3d::model::vector_3d<double> double_vector_3d;


namespace test_vector3d
{
  void test_length()
  {
    double_vector_3d v3d(3,4,0);
    ASSERT_EQUAL(v3d.length(),5);

    v3d = double_vector_3d(0,3,4);
    ASSERT_EQUAL(v3d.length(),5);

    v3d = double_vector_3d(3,0,4);
    ASSERT_EQUAL(v3d.length(),5);
  }

  void test_normalize()
  {
    double_vector_3d v3d(3,4,0);
    double_vector_3d check = v3d.normalize();

    ASSERT_EQUAL(check.length(),1);
  }

  void test_unary_negation()
  {
    double_vector_3d v3d(1,2,3);

    v3d = -v3d;

    ASSERT_EQUAL( v3d.data_[0] , -1 );
    ASSERT_EQUAL( v3d.data_[1] , -2 );
    ASSERT_EQUAL( v3d.data_[2] , -3 );
  }

  void test_scalar_multiply()
  {
    double_vector_3d v3d(1,2,3);

    v3d = 2 * v3d;

    ASSERT_EQUAL( v3d.data_[0] , 2 );
    ASSERT_EQUAL( v3d.data_[1] , 4 );
    ASSERT_EQUAL( v3d.data_[2] , 6 );
  
    v3d = v3d * 2;

    ASSERT_EQUAL( v3d.data_[0] , 4 );
    ASSERT_EQUAL( v3d.data_[1] , 8 );
    ASSERT_EQUAL( v3d.data_[2] , 12 );
  }

  void test_scalar_divide()
  {
    double_vector_3d v3d(4,8,12);

    v3d = v3d / 2;

    ASSERT_EQUAL( v3d.data_[0] , 2 );
    ASSERT_EQUAL( v3d.data_[1] , 4 );
    ASSERT_EQUAL( v3d.data_[2] , 6 );
  }

  void test_add()
  {
    double_vector_3d v3d_1(2,3,4);
    double_vector_3d v3d_2(4,6,8);

    double_vector_3d result = v3d_1 + v3d_2;

    ASSERT_EQUAL( result.data_[0] , 6 );
    ASSERT_EQUAL( result.data_[1] , 9 );
    ASSERT_EQUAL( result.data_[2] , 12 );

    result = v3d_2 - v3d_1;

    ASSERT_EQUAL( result.data_[0] , 2 );
    ASSERT_EQUAL( result.data_[1] , 3 );
    ASSERT_EQUAL( result.data_[2] , 4 );
  }

  void test_dot_product()
  {
    double_vector_3d v3d_1(2,3,4);
    double_vector_3d v3d_2(4,6,8);

    double dot = v3d_1.dot_product(v3d_2);

    ASSERT_EQUAL( dot , (2*4 + 3*6 + 4*8) );
  }

  void test_cross_product()
  {
    double_vector_3d x_axis(1,0,0);
    double_vector_3d y_axis(0,1,0);
    double_vector_3d z_axis(0,0,1);

    ASSERT_EQUAL(z_axis , x_axis.cross_product(y_axis));
    ASSERT_EQUAL(-z_axis , y_axis.cross_product(x_axis));
    ASSERT_EQUAL(x_axis , y_axis.cross_product(z_axis));
    ASSERT_EQUAL(-x_axis , z_axis.cross_product(y_axis));
    ASSERT_EQUAL(y_axis , z_axis.cross_product(x_axis));
    ASSERT_EQUAL(-y_axis , x_axis.cross_product(z_axis));
  }

}
