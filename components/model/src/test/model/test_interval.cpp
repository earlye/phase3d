#include <model/interval.hpp>

#include <libede/ASSERT_EQUAL.hpp>
#include <libede/ASSERT_FALSE.hpp>
#include <libede/ASSERT_TRUE.hpp>

namespace test_interval
{
  typedef phase3d::model::interval< double > dbl_interval;

  void test_ctor()
  {
    dbl_interval test(0,2);    

    ASSERT_EQUAL(test.low(),0);
    ASSERT_EQUAL(test.high(),2);
  }

  void test_stream()
  {
    dbl_interval value(0,2);
    std::stringstream check;
    check << value;
    ASSERT_EQUAL(check.str(),"[0 .. 2]");
  }


  void test_empty()
  {
    ASSERT_FALSE(dbl_interval(0,1).empty());
    ASSERT_TRUE(dbl_interval(1,0).empty());
  }

  void test_equal()
  {
    // testing operator== - don't use ASSERT_EQUAL
    ASSERT_TRUE(dbl_interval(0,1) == dbl_interval(0,1));
    ASSERT_FALSE(dbl_interval(0,1) == dbl_interval(1,2));
    ASSERT_TRUE(dbl_interval(1,0) == dbl_interval(2,1));
    ASSERT_TRUE(dbl_interval(1,0) == dbl_interval(2,0)); // empty intervals are equal, even if they're empty for different reasons.
  }

  void test_unequal()
  {
    // testing operator!= - don't use ASSERT_EQUAL
    ASSERT_FALSE(dbl_interval(0,1) != dbl_interval(0,1));
    ASSERT_TRUE(dbl_interval(0,1) != dbl_interval(1,2));
    ASSERT_FALSE(dbl_interval(1,0) != dbl_interval(2,1));
    ASSERT_FALSE(dbl_interval(1,0) != dbl_interval(2,0)); // empty intervals are equal, even if they're empty for different reasons.
  }

  void test_intersect()
  {
    dbl_interval a(1,3);
    dbl_interval b(2,7);
    dbl_interval c = a.intersect(b);
    dbl_interval d = b.intersect(a);
    dbl_interval e = b.intersect(dbl_interval(0,1));

    dbl_interval expected(2,3);

    ASSERT_EQUAL(c,expected);
    ASSERT_EQUAL(d,expected);
    ASSERT_TRUE(e.empty());
  }
}
