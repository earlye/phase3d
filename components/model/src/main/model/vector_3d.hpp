#ifndef h521F1744_AC9B_43DC_A29B_CD61A13FBEF3
#define h521F1744_AC9B_43DC_A29B_CD61A13FBEF3

#include <cmath>

namespace phase3d
{
  namespace model
  {
    template< typename STORAGE >
    class vector_3d
    {
    public:
      typedef STORAGE storage;
      typedef vector_3d<storage> this_type;

      storage data[3] = {0,0,0};

      vector_3d( storage x , storage y , storage z )
      {
	data[0] = x;
	data[1] = y;
	data[2] = z;
      }

      storage length() const
      {
	return std::sqrt(length_squared());
      }

      this_type operator-() const
      {
	return this_type(-data[0],-data[1],-data[2]);
      }

      bool operator==(this_type const& other) const
      {
	return data[0] == other.data[0]
	  && data[1] == other.data[1]
	  && data[2] == other.data[2];
      }

      bool operator!=(this_type const& other) const
      {
	return !(operator==(other));
      }


      template< typename SCALAR >
      this_type operator*( SCALAR other )
      {
	return this_type(data[0]*other,data[1]*other,data[2]*other);
      }

      template< typename SCALAR >
      this_type operator/( SCALAR other )
      {
	return this_type(data[0]/other,data[1]/other,data[2]/other);
      }

      template< typename OTHER_STORAGE >
      this_type operator+(vector_3d<OTHER_STORAGE> const& other )
      {
	return this_type(data[0] + other.data[0], data[1] + other.data[1],data[2]+other.data[2]);
      }

      template< typename OTHER_STORAGE >
      this_type operator-(vector_3d<OTHER_STORAGE> const& other )
      {
	return this_type(data[0] - other.data[0], data[1] - other.data[1],data[2]-other.data[2]);
      }

      template< typename OTHER_STORAGE >
      storage dot_product(vector_3d<OTHER_STORAGE> const& other )
      {
	return data[0]*other.data[0] + data[1] * other.data[1] + data[2]*other.data[2];
      }

      template< typename OTHER_STORAGE >
      this_type cross_product(vector_3d<OTHER_STORAGE> const& other )
      {
	return this_type( data[1]*other.data[2] - data[2]*other.data[1],
			  data[2]*other.data[0] - data[0]*other.data[2],
			  data[0]*other.data[1] - data[1]*other.data[0] );
      }

    private:
      storage length_squared() const
      {
	return data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
      }
    };

    template< typename SCALAR , typename STORAGE >
    vector_3d<STORAGE> operator*( SCALAR const scalar, vector_3d<STORAGE> const& vec )
    {
      return vector_3d<STORAGE>(scalar * vec.data[0], scalar * vec.data[1], scalar * vec.data[2]);
    }
  }
}

#endif

