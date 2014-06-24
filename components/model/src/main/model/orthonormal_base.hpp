#ifndef h5FBB52D6_952D_4048_BC7F_8E80E0C13B4B
#define h5FBB52D6_952D_4048_BC7F_8E80E0C13B4B

#include "vector_3d.hpp"

#include <cmath>

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class orthonormal_base
    {
    public:
      typedef SCALAR scalar;
      typedef orthonormal_base<scalar> this_type;
      typedef phase3d::model::vector_3d<scalar> vector_3d;

      orthonormal_base()
	: u_(vector_3d::x_)
	, v_(vector_3d::y_)
	, w_(vector_3d::z_)
      { }

      static orthonormal_base from_uv( vector_3d a , vector_3d b )
      {
	vector_3d u = a.normalize();
	vector_3d w = a.cross_product(b).normalize();
	vector_3d v = w.cross_product(u);
	return orthonormal_base(u,v,w);
      }

      static orthonormal_base from_w( vector_3d a )
      {
	vector_3d w = a.normalize();
	vector_3d v = v_from_w(w);
	vector_3d u = v.cross_product(w);
      }

    private:

      static vector_3d v_from_w( vector_3d const& w )
      {
	scalar absx = fabs(w.x());
	scalar absy = fabs(w.y());
	scalar absz = fabs(w.z());
	if ( absx < absy && absx < absz )
	  return vector_3d(0,w.z(),-w.y()).normalize();
	else if ( absy < absz )
	  return vector_3d(w.z(),0,-w.x()).normalize();
	else
	  return vector_3d(w.y(),-w.x(),0);
      }

      orthonormal_base( vector_3d u , vector_3d v , vector_3d w )
	: u_(u)
	, v_(v)
	, w_(w)
      { }


    private:
      vector_3d u_;
      vector_3d v_;
      vector_3d w_;
    };
  }
}

#endif

