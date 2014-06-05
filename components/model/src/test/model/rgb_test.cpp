#include <model/rgb.hpp>

#include <stdexcept>

void test_rgb_default_ctor() 
{
  phase3d::model::rgb<double> rgbdbl;

  if (rgbdbl.red() != 0.0) throw std::runtime_error( "expected rgbdbl.red() == 0.0");
  if (rgbdbl.green() != 0.0) throw std::runtime_error( "expected rgbdbl.green() == 0.0");
  if (rgbdbl.blue() != 0.0) throw std::runtime_error( "expected rgbdbl.blue() == 0.0" );
}

void test_rgb_color_ctor()
{
  phase3d::model::rgb<double> rgbdbl(0.25,0.5,1);

  if(rgbdbl.red()!=0.25) throw std::runtime_error( "expected rgbdbl.red() == 0.25");
  if(rgbdbl.green()!=0.5) throw std::runtime_error( "expected green==0.5" );
  if(rgbdbl.blue()!=1.0) throw std::runtime_error( "expected blue==1.0" );
}

void test_rgb_setters()
{
  phase3d::model::rgb<double> rgbdbl;

  rgbdbl.red(0.25).green(0.5).blue(1.0);
  
  if(rgbdbl.red()!=0.25) throw std::runtime_error("expected red==0.25");
  if(rgbdbl.green()!=0.5) throw std::runtime_error("expected green==0.5");
  if(rgbdbl.blue()!=1.0) throw std::runtime_error("expected blue==1.0");
}

void test_rgb_unary_negative()
{
  phase3d::model::rgb<double> rgbdbl(0.25,0.5,1);

  rgbdbl = -rgbdbl;

  if(rgbdbl.red() != -0.25) throw std::runtime_error("expected red== -0.25");
  if(rgbdbl.green() != -0.5) throw std::runtime_error("expected green== -0.5");
  if(rgbdbl.blue() != -1.0) throw std::runtime_error("expected blue== -1.0");
}

void test_rgb_scalar_multiplication()
{
  phase3d::model::rgb<double> rgbdbl(0.25,0.5,1);

  rgbdbl = 2.0 * rgbdbl;

  if(rgbdbl.red() != 0.5) throw std::runtime_error("expected red==0.5");
  if(rgbdbl.green() != 1.0) throw std::runtime_error("expected green==1.0");
  if(rgbdbl.blue() != 2.0) throw std::runtime_error("expected blue==2.0");

  rgbdbl = rgbdbl * 2.0;

  if(rgbdbl.red() != 1.0) throw std::runtime_error("expected red==1.0");
  if(rgbdbl.green() != 2.0) throw std::runtime_error("expected green==2.0");
  if(rgbdbl.blue() != 4.0) throw std::runtime_error("expected blue==4.0");
}

