#include <model/interval.hpp>
#include <stdexcept>

namespace test_interval
{
  typedef phase3d::model::interval< double > dbl_interval;

  void test_ctor()
  {
    dbl_interval test(0,1);

    if (test.low() != 0) throw std::runtime_error( "test.low() should be 0");
    if (test.high() != 1) throw std::runtime_error( "test.high() should be 1");
  }

  void test_empty()
  {
    if (dbl_interval(0,1).empty()) throw std::runtime_error( "interval [0,1] should not be empty." );
    if (!dbl_interval(1,0).empty()) throw std::runtime_error( "interval [1,0] should be empty." );
  }

  void test_equal()
  {
    if (!(dbl_interval(0,1) == dbl_interval(0,1))) throw std::runtime_error( "[0,1] should == [0,1]" );
    if (dbl_interval(0,1) == dbl_interval(1,2)) throw std::runtime_error( "[0,1] should not == [1,2]" );
    if (!(dbl_interval(1,0) == dbl_interval(2,1))) throw std::runtime_error( "[1,0] should == [2,1]" );
  }

  void test_unequal()
  {
    if (dbl_interval(0,1) != dbl_interval(0,1)) throw std::runtime_error( "[0,1] should == [0,1]" );
    if (!(dbl_interval(0,1) != dbl_interval(1,2))) throw std::runtime_error( "[0,1] should not == [1,2]" );
    if (dbl_interval(1,0) != dbl_interval(2,1)) throw std::runtime_error( "[1,0] should == [2,1]" );
  }

  void test_intersect()
  {
    dbl_interval a(1,3);
    dbl_interval b(2,7);
    dbl_interval c = a.intersect(b);
    dbl_interval d = b.intersect(a);

    dbl_interval expected(2,3);

    if (!(c==expected)) throw std::runtime_error("intersect broken");
    if (!(d==expected)) throw std::runtime_error("intersect broken");
  }
}
