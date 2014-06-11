#ifndef h115B937A_3B3B_4877_8364_C2C7C8DCA57F
#define h115B937A_3B3B_4877_8364_C2C7C8DCA57F

#include <algorithm>

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class interval
    {
    public:
      typedef SCALAR scalar;
      typedef interval<scalar> this_type;

      interval( scalar low, scalar high )
        : low_(low)
        , high_(high)
      { }

      bool contains( scalar value ) const
      {
	return low_ <= value && value <= high_;
      }

      bool empty( ) const
      {
	return low_ > high_;
      }

      bool low() const
      {
	return low_;
      }

      bool high() const
      {
	return high_;
      }

      bool operator==( this_type const& other ) const
      {
	if (empty()) 
	  return other.empty();

	return (low_ == other.low_) && (high_ == other.high_);
      }

      bool operator!=( this_type const& other ) const
      {
	return !operator==(other);
      }

      interval intersect( this_type const& other ) const
      {
	return interval( std::max( low_ , other.low_ ) , std::min( high_, other.high_ ) );
      }
      
    private:
      scalar low_;
      scalar high_;
    };
  }
}

#endif
