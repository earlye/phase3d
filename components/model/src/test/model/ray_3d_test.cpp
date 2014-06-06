#include "model/ray_3d.hpp"

#include <stdexcept>

typedef phase3d::model::ray_3d<double> ray_3d;
typedef phase3d::model::vector_3d<double> vector_3d;

void test_r3d_default_constructor()
{
  ray_3d ray;

  if (ray.origin_.data_[0] != 0) throw std::runtime_error( "default ray_3d ctor doesn't init to zeroes" );
  if (ray.origin_.data_[1] != 0) throw std::runtime_error( "default ray_3d ctor doesn't init to zeroes" );
  if (ray.origin_.data_[2] != 0) throw std::runtime_error( "default ray_3d ctor doesn't init to zeroes" );
  if (ray.direction_.data_[0] != 0) throw std::runtime_error( "default ray_3d ctor doesn't init to zeroes" );
  if (ray.direction_.data_[1] != 0) throw std::runtime_error( "default ray_3d ctor doesn't init to zeroes" );
  if (ray.direction_.data_[2] != 0) throw std::runtime_error( "default ray_3d ctor doesn't init to zeroes" );
}

void test_r3d_initializing_constructor()
{
  ray_3d ray(vector_3d(1,2,3),vector_3d(4,5,6));

  if (ray.origin_.data_[0] != 1) throw std::runtime_error( "default ray_3d ctor doesn't init correctly" );
  if (ray.origin_.data_[1] != 2) throw std::runtime_error( "default ray_3d ctor doesn't init correctly" );
  if (ray.origin_.data_[2] != 3) throw std::runtime_error( "default ray_3d ctor doesn't init correctly" );
  if (ray.direction_.data_[0] != 4) throw std::runtime_error( "default ray_3d ctor doesn't init correctly" );
  if (ray.direction_.data_[1] != 5) throw std::runtime_error( "default ray_3d ctor doesn't init correctly" );
  if (ray.direction_.data_[2] != 6) throw std::runtime_error( "default ray_3d ctor doesn't init correctly" );
}


void test_r3d_point_at_parameter()
{
  ray_3d ray(vector_3d(1,2,3),vector_3d(4,5,6));
  vector_3d point = ray.point_at_parameter(2);


  if (point.data_[0] != 1 + 2*4) throw std::runtime_error( "point_at_parameter is broken" );
  if (point.data_[1] != 2 + 2*5) throw std::runtime_error( "point_at_parameter is broken" ); 
  if (point.data_[2] != 3 + 2*6) throw std::runtime_error( "point_at_parameter is broken" );
}
