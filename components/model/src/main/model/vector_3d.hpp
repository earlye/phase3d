#ifndef h521F1744_AC9B_43DC_A29B_CD61A13FBEF3
#define h521F1744_AC9B_43DC_A29B_CD61A13FBEF3

#include <cmath>

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class vector_3d
    {
    public:
      typedef SCALAR scalar;
      typedef vector_3d<scalar> this_type;

      scalar data_[3] = {0,0,0};

      static const this_type x_;
      static const this_type y_;
      static const this_type z_;

      vector_3d( scalar x = 0 , scalar y = 0 , scalar z = 0 )
      {
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
      }

      scalar length() const
      {
	return std::sqrt(length_squared());
      }

      scalar x() const
      {
	return data_[0];
      }

      scalar y() const
      {
	return data_[1];
      }

      scalar z() const
      {
	return data_[2];
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


      this_type operator*( scalar other ) const
      {
	return this_type(data_[0]*other,data_[1]*other,data_[2]*other);
      }

      this_type operator/( scalar other ) const
      {
	return this_type(data_[0]/other,data_[1]/other,data_[2]/other);
      }

      template< typename OTHER_SCALAR >
      this_type operator+(vector_3d<OTHER_SCALAR> const& other ) const
      {
	return this_type(data_[0] + other.data_[0], data_[1] + other.data_[1],data_[2]+other.data_[2]);
      }

      template< typename OTHER_SCALAR >
      this_type operator-(vector_3d<OTHER_SCALAR> const& other ) const
      {
	return this_type(data_[0] - other.data_[0], data_[1] - other.data_[1],data_[2]-other.data_[2]);
      }

      template< typename OTHER_SCALAR >
      scalar dot_product(vector_3d<OTHER_SCALAR> const& other ) const
      {
	return data_[0]*other.data_[0] + data_[1] * other.data_[1] + data_[2]*other.data_[2];
      }

      template< typename OTHER_SCALAR >
      this_type cross_product(vector_3d<OTHER_SCALAR> const& other ) const
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
      scalar length_squared() const
      {
	return data_[0]*data_[0] + data_[1]*data_[1] + data_[2]*data_[2];
      }
    };

    template< typename SCALAR >
    const vector_3d<SCALAR> vector_3d<SCALAR>::x_ = vector_3d(1,0,0);

    template< typename SCALAR >
    const vector_3d<SCALAR> vector_3d<SCALAR>::y_ = vector_3d(0,1,0);

    template< typename SCALAR >
    const vector_3d<SCALAR> vector_3d<SCALAR>::z_ = vector_3d(0,0,1);

    template< typename OTHER_SCALAR, typename SCALAR >
    vector_3d<SCALAR> operator*( OTHER_SCALAR const scalar, vector_3d<SCALAR> const& vec )
    {
      return vector_3d<SCALAR>(scalar * vec.data_[0], scalar * vec.data_[1], scalar * vec.data_[2]);
    }

    template< typename STREAM_TYPE , typename SCALAR >
    STREAM_TYPE& operator<<( STREAM_TYPE& stream , vector_3d<SCALAR> const& vec )
    {
      return stream << '(' << vec.data_[0] << ',' << vec.data_[1] << ',' << vec.data_[2] << ')';
    }
  }
}

#endif

