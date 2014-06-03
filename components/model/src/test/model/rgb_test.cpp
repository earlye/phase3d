#include <model/rgb.hpp>

#include <cassert>
#include <iostream>

void test_rgb_default_ctor() 
{
  std::cout << "test " << __func__ << std::endl;
  phase3d::model::rgb<double> rgbdbl;

  assert(rgbdbl.red() == 0.0);
  assert(rgbdbl.green() == 0.0);
  assert(rgbdbl.blue() == 0.0);
}

void test_rgb_color_ctor()
{
  std::cout << "test " << __func__ << std::endl;
  phase3d::model::rgb<double> rgbdbl(0.25,0.5,1);

  assert(rgbdbl.red()==0.25);
  assert(rgbdbl.green()==0.5);
  assert(rgbdbl.blue()==1.0);
}

void test_setters()
{
  std::cout << "test " << __func__ << std::endl;
  phase3d::model::rgb<double> rgbdbl;

  rgbdbl.red(0.25).green(0.5).blue(1.0);
  
  assert(rgbdbl.red()==0.25);
  assert(rgbdbl.green()==0.5);
  assert(rgbdbl.blue()==1.0);
}

void test_unary_negative()
{
  std::cout << "test " << __func__ << std::endl;
  phase3d::model::rgb<double> rgbdbl(0.25,0.5,1);

  rgbdbl = -rgbdbl;

  assert(rgbdbl.red() == -0.25);
  assert(rgbdbl.green() == -0.5);
  assert(rgbdbl.blue() == -1.0);
}

void test_scalar_multiplication()
{
  std::cout << "test " << __func__ << std::endl;
  phase3d::model::rgb<double> rgbdbl(0.25,0.5,1);

  rgbdbl = 2.0 * rgbdbl;

  assert(rgbdbl.red() == 0.5);
  assert(rgbdbl.green() == 1.0);
  assert(rgbdbl.blue() == 2.0);

  rgbdbl = rgbdbl * 2.0;

  assert(rgbdbl.red() == 1.0);
  assert(rgbdbl.green() == 2.0);
  assert(rgbdbl.blue() == 4.0);
}

