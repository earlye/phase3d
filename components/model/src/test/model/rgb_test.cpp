#include <model/rgb.hpp>

#include <libede/ASSERT_EQUAL.hpp>

#include <stdexcept>

void test_rgb_default_ctor() 
{
  phase3d::model::rgb<double> rgbdbl;

  ASSERT_EQUAL(rgbdbl.red(),0.0);
  ASSERT_EQUAL(rgbdbl.green() , 0.0);
  ASSERT_EQUAL(rgbdbl.blue() , 0.0);
}

void test_rgb_color_ctor()
{
  phase3d::model::rgb<double> rgbdbl(0.25,0.5,1);

  ASSERT_EQUAL(rgbdbl.red(),0.25);
  ASSERT_EQUAL(rgbdbl.green(),0.5);
  ASSERT_EQUAL(rgbdbl.blue(),1.0);
}

void test_rgb_setters()
{
  phase3d::model::rgb<double> rgbdbl;

  rgbdbl.red(0.25).green(0.5).blue(1.0);
  
  ASSERT_EQUAL(rgbdbl.red(),0.25);
  ASSERT_EQUAL(rgbdbl.green(),0.5);
  ASSERT_EQUAL(rgbdbl.blue(),1.0);
}

void test_rgb_unary_negative()
{
  phase3d::model::rgb<double> rgbdbl(0.25,0.5,1);

  rgbdbl = -rgbdbl;

  ASSERT_EQUAL(rgbdbl.red() , -0.25);
  ASSERT_EQUAL(rgbdbl.green() , -0.5);
  ASSERT_EQUAL(rgbdbl.blue() , -1.0);
}

void test_rgb_scalar_multiplication()
{
  phase3d::model::rgb<double> rgbdbl(0.25,0.5,1);

  rgbdbl = 2.0 * rgbdbl;

  ASSERT_EQUAL(rgbdbl.red() , 0.5);
  ASSERT_EQUAL(rgbdbl.green() , 1.0);
  ASSERT_EQUAL(rgbdbl.blue() , 2.0);

  rgbdbl = rgbdbl * 2.0;

  ASSERT_EQUAL(rgbdbl.red() , 1.0);
  ASSERT_EQUAL(rgbdbl.green() , 2.0);
  ASSERT_EQUAL(rgbdbl.blue() , 4.0);
}

