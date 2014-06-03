#ifndef hA2D386E1_6CDD_4870_8410_21DC0C60594A
#define hA2D386E1_6CDD_4870_8410_21DC0C60594A

#include <cmath>

namespace phase3d
{
  namespace model
  {
    template< typename STORAGE >
    class vector_2d
    {
    public:
      typedef STORAGE storage;
      typedef vector_2d<storage> this_type;

      storage data[2] = {0,0};

      vector_2d( storage x , storage y )
      {
	data[0] = x;
	data[1] = y;
      }

      storage length() const
      {
	return std::sqrt(length_squared());
      }

      this_type operator-() const
      {
	return this_type(-data[0],-data[1]);
      }

      template< typename SCALAR >
      this_type operator*( SCALAR other )
      {
	return this_type(data[0]*other,data[1]*other);
      }

      template< typename SCALAR >
      this_type operator/( SCALAR other )
      {
	return this_type(data[0]/other,data[1]/other);
      }

      template< typename OTHER_STORAGE >
      this_type operator+(vector_2d<OTHER_STORAGE> const& other )
      {
	return this_type(data[0] + other.data[0], data[1] + other.data[1]);
      }

      template< typename OTHER_STORAGE >
      this_type operator-(vector_2d<OTHER_STORAGE> const& other )
      {
	return this_type(data[0] - other.data[0], data[1] - other.data[1]);
      }

    private:
      storage length_squared() const
      {
	return data[0]*data[0] + data[1]*data[1];
      }
    };

    template< typename SCALAR , typename STORAGE >
    vector_2d<STORAGE> operator*( SCALAR const scalar, vector_2d<STORAGE> const& vec )
    {
      return vector_2d<STORAGE>(scalar * vec.data[0], scalar * vec.data[1]);
    }
  }
}

#endif

