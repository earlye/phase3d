#ifndef h5B4E037D_FE97_4220_A14C_39B037507CFC
#define h5B4E037D_FE97_4220_A14C_39B037507CFC

#include <initializer_list>
#include <algorithm>

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class transformation_matrix_3d
    {
    public:
      typedef SCALAR scalar;
      typedef transformation_matrix_3d< scalar > this_type;

      transformation_matrix_3d( std::initializer_list<scalar> args )
      { 
	std::copy( args.begin() , args.end() , matrix_ );
      }

      transformation_matrix_3d( )
	: transformation_matrix_3d
	  ( { 1,0,0,0,
	      0,1,0,0,
	      0,0,1,0,
	      0,0,0,1 } )
      { }

      SCALAR get( int x , int y ) const
      {
	return matrix_[index(x,y)];
      }

      this_type& put( int x , int y , scalar s )
      {
	matrix_[index(x,y)] = s;
	return *this;
      }
      
    private:
      int index( int x , int y ) const
      {
	return y*4 + x;
      }

      SCALAR matrix_[16];
    };
  }
}

#endif
