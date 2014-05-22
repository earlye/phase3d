#ifndef h5A5BE40275AB421B9F80E8871D15C17D
#define h5A5BE40275AB421B9F80E8871D15C17D

namespace phase3d 
{
  namespace model
  {
    template< typename STORAGE >
    class rgb
    {
    private:
      typedef STORAGE storage;

      storage red_;
      storage green_;
      storage blue_;

    public:
      rgb( )
	: red_(0)
	, green_(0)
	, blue_(0)
      { }

      rgb( storage red, storage green, storage blue )
	: red_(red)
	, green_(green)
	, blue_(blue)
      { }

      storage red() const
      { return red_; }

      storage green() const
      { return green_; }

      storage blue() const
      { return blue_; }

      rgb& red( storage value )
      { red_ = value; return *this; }

      rgb& green( storage value )
      { green_ = value; return *this; }

      rgb& blue( storage value )
      { blue_ = value; return *this; }

      rgb operator-() const
      {
	return rgb(-red_,-green_,-blue_);
      }      
    };

    template<typename STORAGE, typename SCALAR>
    rgb<STORAGE> operator*(SCALAR k, rgb<STORAGE> a)
    { return rgb<STORAGE>(k*a.red(),k*a.green(),k*a.blue()); }

    template<typename STORAGE, typename SCALAR>
    rgb<STORAGE> operator*(rgb<STORAGE> a,SCALAR k)
    { return rgb<STORAGE>(k*a.red(),k*a.green(),k*a.blue()); }
  }
}

#endif
