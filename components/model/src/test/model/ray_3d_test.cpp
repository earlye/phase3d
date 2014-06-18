#include "model/ray_3d.hpp"

#include <libede/ASSERT_EQUAL.hpp>

#include <stdexcept>

typedef phase3d::model::ray_3d<double> ray_3d;
typedef phase3d::model::vector_3d<double> vector_3d;

void test_r3d_default_constructor()
{
  ray_3d ray;

  ASSERT_EQUAL(ray.origin_.data_[0] , 0);
  ASSERT_EQUAL(ray.origin_.data_[1] , 0);
  ASSERT_EQUAL(ray.origin_.data_[2] , 0);
  ASSERT_EQUAL(ray.direction_.data_[0] , 0);
  ASSERT_EQUAL(ray.direction_.data_[1] , 0);
  ASSERT_EQUAL(ray.direction_.data_[2] , 0);
}

void test_r3d_initializing_constructor()
{
  ray_3d ray(vector_3d(1,2,3),vector_3d(4,5,6));

  ASSERT_EQUAL(ray.origin_.data_[0] , 1);
  ASSERT_EQUAL(ray.origin_.data_[1] , 2);
  ASSERT_EQUAL(ray.origin_.data_[2] , 3);
  ASSERT_EQUAL(ray.direction_.data_[0] , 4);
  ASSERT_EQUAL(ray.direction_.data_[1] , 5);
  ASSERT_EQUAL(ray.direction_.data_[2] , 6);
}


void test_r3d_point_at_parameter()
{
  ray_3d ray(vector_3d(1,2,3),vector_3d(4,5,6));
  vector_3d point = ray.point_at_parameter(2);


  ASSERT_EQUAL(point.data_[0] , 1 + 2*4);
  ASSERT_EQUAL(point.data_[1] , 2 + 2*5);
  ASSERT_EQUAL(point.data_[2] , 3 + 2*6);
}
