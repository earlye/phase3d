#ifndef h5A5BE40275AB421B9F80E8871D15C17D
#define h5A5BE40275AB421B9F80E8871D15C17D

namespace phase3d 
{
  namespace model
  {
    template< typename SCALAR >
    class rgb
    {
    private:
      typedef SCALAR scalar;

      scalar red_;
      scalar green_;
      scalar blue_;

    public:
      rgb( )
	: red_(0)
	, green_(0)
	, blue_(0)
      { }

      rgb( scalar red, scalar green, scalar blue )
	: red_(red)
	, green_(green)
	, blue_(blue)
      { }

      scalar red() const
      { return red_; }

      scalar green() const
      { return green_; }

      scalar blue() const
      { return blue_; }

      rgb& red( scalar value )
      { red_ = value; return *this; }

      rgb& green( scalar value )
      { green_ = value; return *this; }

      rgb& blue( scalar value )
      { blue_ = value; return *this; }

      rgb operator-() const
      {
	return rgb(-red_,-green_,-blue_);
      }      
    };

    template<typename SCALAR>
    rgb<SCALAR> operator*(SCALAR k, rgb<SCALAR> const& a)
    { return rgb<SCALAR>(k*a.red(),k*a.green(),k*a.blue()); }

    template<typename SCALAR>
    rgb<SCALAR> operator*(rgb<SCALAR> const& a,SCALAR k)
    { return rgb<SCALAR>(k*a.red(),k*a.green(),k*a.blue()); }

    template<typename SCALAR>
    rgb<SCALAR> operator/(rgb<SCALAR> const& a,SCALAR k)
    { return rgb<SCALAR>(a.red()/k,a.green()/k,a.blue()/k); }

    template<typename SCALAR>
    rgb<SCALAR> operator+(rgb<SCALAR> const& a, rgb<SCALAR> const& b )
    { return rgb<SCALAR>(a.red()+b.red(),a.green()+b.green(),a.blue()+b.blue()); }

    template<typename SCALAR>
    rgb<SCALAR> operator-(rgb<SCALAR> const& a, rgb<SCALAR> const& b )
    { return rgb<SCALAR>(a.red()-b.red(),a.green()-b.green(),a.blue()-b.blue()); }

    template<typename SCALAR>
    rgb<SCALAR> operator*(rgb<SCALAR> const& a, rgb<SCALAR> const& b )
    { return rgb<SCALAR>(a.red()*b.red(),a.green()*b.green(),a.blue()*b.blue()); }

    template<typename SCALAR>
    rgb<SCALAR> operator/(rgb<SCALAR> const& a, rgb<SCALAR> const& b )
    { return rgb<SCALAR>(a.red()/b.red(),a.green()/b.green(),a.blue()/b.blue()); }

  }
}

#endif
