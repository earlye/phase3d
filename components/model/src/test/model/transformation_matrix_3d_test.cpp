#include <model/transformation_matrix_3d.hpp>

#include <libede/ASSERT_EQUAL.hpp>

namespace test_transformation_matrix_3d
{

  typedef phase3d::model::transformation_matrix_3d<double> xfm;

  void test_initializer()
  {
    xfm matrix = { 1.0 , 2.0 , 3.0 , 4.0,
		   5.0 , 6.0 , 7.0 , 8.0,
		   9.0 , 10.0, 11.0, 12.0,
		   13.0, 14.0, 15.0, 16.0 };

    ASSERT_EQUAL( 1.0 , matrix.get(0,0) );
    ASSERT_EQUAL( 2.0 , matrix.get(1,0) );
    ASSERT_EQUAL( 3.0 , matrix.get(2,0) );
    ASSERT_EQUAL( 4.0 , matrix.get(3,0) );
    ASSERT_EQUAL( 5.0 , matrix.get(0,1) );
    ASSERT_EQUAL( 6.0 , matrix.get(1,1) );
    ASSERT_EQUAL( 7.0 , matrix.get(2,1) );
    ASSERT_EQUAL( 8.0 , matrix.get(3,1) );
    ASSERT_EQUAL( 9.0 , matrix.get(0,2) );
    ASSERT_EQUAL( 10.0 , matrix.get(1,2) );
    ASSERT_EQUAL( 11.0 , matrix.get(2,2) );
    ASSERT_EQUAL( 12.0 , matrix.get(3,2) );
    ASSERT_EQUAL( 13.0 , matrix.get(0,3) );
    ASSERT_EQUAL( 14.0 , matrix.get(1,3) );
    ASSERT_EQUAL( 15.0 , matrix.get(2,3) );
    ASSERT_EQUAL( 16.0 , matrix.get(3,3) );
  }

  void test_default_constructor()
  {
    xfm matrix;

    ASSERT_EQUAL(1.0 , matrix.get(0,0));
    ASSERT_EQUAL(0.0 , matrix.get(1,0));
    ASSERT_EQUAL(0.0 , matrix.get(2,0));
    ASSERT_EQUAL(0.0 , matrix.get(3,0));
    ASSERT_EQUAL(0.0 , matrix.get(0,1));
    ASSERT_EQUAL(1.0 , matrix.get(1,1));
    ASSERT_EQUAL(0.0 , matrix.get(2,1));
    ASSERT_EQUAL(0.0 , matrix.get(3,1));
    ASSERT_EQUAL(0.0 , matrix.get(0,2));
    ASSERT_EQUAL(0.0 , matrix.get(1,2));
    ASSERT_EQUAL(1.0 , matrix.get(2,2));
    ASSERT_EQUAL(0.0 , matrix.get(3,2));
    ASSERT_EQUAL(0.0 , matrix.get(0,3));
    ASSERT_EQUAL(0.0 , matrix.get(1,3));
    ASSERT_EQUAL(0.0 , matrix.get(2,3));
    ASSERT_EQUAL(1.0 , matrix.get(3,3));
  }

}
