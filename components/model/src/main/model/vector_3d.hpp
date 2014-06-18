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

      storage data_[3] = {0,0,0};

      vector_3d( storage x = 0 , storage y = 0 , storage z = 0 )
      {
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
      }

      storage length() const
      {
	return std::sqrt(length_squared());
      }

      this_type operator-() const
      {
	return this_type(-data_[0],-data_[1],-data_[2]);
      }

      bool operator==(this_type const& other) const
      {
	return data_[0] == other.data_[0]
	  && data_[1] == other.data_[1]
	  && data_[2] == other.data_[2];
      }

      bool operator!=(this_type const& other) const
      {
	return !(operator==(other));
      }


      template< typename SCALAR >
      this_type operator*( SCALAR other ) const
      {
	return this_type(data_[0]*other,data_[1]*other,data_[2]*other);
      }

      template< typename SCALAR >
      this_type operator/( SCALAR other ) const
      {
	return this_type(data_[0]/other,data_[1]/other,data_[2]/other);
      }

      template< typename OTHER_STORAGE >
      this_type operator+(vector_3d<OTHER_STORAGE> const& other ) const
      {
	return this_type(data_[0] + other.data_[0], data_[1] + other.data_[1],data_[2]+other.data_[2]);
      }

      template< typename OTHER_STORAGE >
      this_type operator-(vector_3d<OTHER_STORAGE> const& other ) const
      {
	return this_type(data_[0] - other.data_[0], data_[1] - other.data_[1],data_[2]-other.data_[2]);
      }

      template< typename OTHER_STORAGE >
      storage dot_product(vector_3d<OTHER_STORAGE> const& other ) const
      {
	return data_[0]*other.data_[0] + data_[1] * other.data_[1] + data_[2]*other.data_[2];
      }

      template< typename OTHER_STORAGE >
      this_type cross_product(vector_3d<OTHER_STORAGE> const& other ) const
      {
	return this_type( data_[1]*other.data_[2] - data_[2]*other.data_[1],
			  data_[2]*other.data_[0] - data_[0]*other.data_[2],
			  data_[0]*other.data_[1] - data_[1]*other.data_[0] );
      }

      this_type normalize() const
      {
	return *this / length();
      }

    private:
      storage length_squared() const
      {
	return data_[0]*data_[0] + data_[1]*data_[1] + data_[2]*data_[2];
      }
    };

    template< typename SCALAR , typename STORAGE >
    vector_3d<STORAGE> operator*( SCALAR const scalar, vector_3d<STORAGE> const& vec )
    {
      return vector_3d<STORAGE>(scalar * vec.data_[0], scalar * vec.data_[1], scalar * vec.data_[2]);
    }

    template< typename STREAM_TYPE , typename STORAGE >
    STREAM_TYPE& operator<<( STREAM_TYPE& stream , vector_3d<STORAGE> const& vec )
    {
      return stream << '(' << vec.data_[0] << ',' << vec.data_[1] << ',' << vec.data_[2] << ')';
    }
  }
}

#endif

