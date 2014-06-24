#ifndef h21F70988_A913_4DE6_9975_C9A97FA72CAC
#define h21F70988_A913_4DE6_9975_C9A97FA72CAC

#include <cmath>

namespace phase3d
{
  namespace model
  {
    namespace scalar
    {
      template< SCALAR >
      bool is_just_above( SCALAR value , SCALAR check , SCALAR epsilon )
      {
	SCALAR difference = check - value;
	return 0 <= difference && difference <= epsilon;
      }
      
      template< SCALAR >
      bool is_just_below( SCALAR value , SCALAR check , SCALAR epsilon )
      {
	SCALAR difference = value - check;
	return 0 <= difference && difference <= epsilon;
      }

      template< SCALAR >
      bool is_approximately( SCALAR value , SCALAR check , SCALAR epsilon )
      {
	SCALAR difference = fabs(value - check);
	return 0 <= difference && difference <= epsilon;
      }
    }    
  }
}

#endif
