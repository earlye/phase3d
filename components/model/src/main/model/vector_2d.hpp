#ifndef hA2D386E1_6CDD_4870_8410_21DC0C60594A
#define hA2D386E1_6CDD_4870_8410_21DC0C60594A

#include <cmath>

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class vector_2d
    {
    public:
      typedef SCALAR scalar;
      typedef vector_2d<scalar> this_type;

      scalar data[2] = {0,0};

      vector_2d( scalar x , scalar y )
      {
	data[0] = x;
	data[1] = y;
      }

      bool operator==(this_type const& other) const
      {
	return data[0] == other.data[0]
	  && data[1] == other.data[1];
      }

      bool operator!=(this_type const& other) const
      {
	return !(operator==(other));
      }

      scalar length() const
      {
	return std::sqrt(length_squared());
      }

      this_type operator-() const
      {
	return this_type(-data[0],-data[1]);
      }

      this_type operator*( scalar other )
      {
	return this_type(data[0]*other,data[1]*other);
      }

      this_type operator/( scalar other )
      {
	return this_type(data[0]/other,data[1]/other);
      }

      this_type operator+(this_type const& other )
      {
	return this_type(data[0] + other.data[0], data[1] + other.data[1]);
      }

      this_type operator-(this_type const& other )
      {
	return this_type(data[0] - other.data[0], data[1] - other.data[1]);
      }

      scalar dot_product(this_type const& other )
      {
	return data[0]*other.data[0] + data[1] * other.data[1];
      }

    private:
      scalar length_squared() const
      {
	return data[0]*data[0] + data[1]*data[1];
      }
    };

    template< typename OTHER_SCALAR, typename SCALAR >
    vector_2d<SCALAR> operator*( OTHER_SCALAR const scalar, vector_2d<SCALAR> const& vec )
    {
      return vector_2d<SCALAR>(scalar * vec.data[0], scalar * vec.data[1]);
    }
  }
}

#endif

