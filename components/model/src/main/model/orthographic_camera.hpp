#ifndef hFA672904_AA4F_4D45_8189_FF2FB09908A5
#define hFA672904_AA4F_4D45_8189_FF2FB09908A5

#include "camera.hpp"

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR>
    class orthographic_camera
      : public camera< SCALAR >
    {
    public:
      typedef SCALAR scalar;
      typedef camera< scalar > base_type;
      typedef orthographic_camera< scalar > this_type;
      typedef typename phase3d::model::intersection< scalar > intersection;
      typedef typename phase3d::model::interval< scalar > interval;
      typedef typename phase3d::model::ray_3d< scalar > ray_3d;
      typedef typename phase3d::model::rgb< scalar > rgb;
      typedef typename phase3d::model::surface< scalar > surface;
      typedef typename phase3d::model::vector_3d< scalar > vector_3d;
      typedef typename phase3d::model::basic_write_channel< rgb > basic_write_channel;

      virtual void render_tile( basic_write_channel& destination,
                                interval const& horizontal_range,
                                interval const& vertical_range,
                                surface const& source_surface )
      {
        for ( int y = horizontal_range.low(); y < horizontal_range.high() ; ++y )
          {
            for ( int x = horizontal_range.low(); x < horizontal_range.high() ; ++x )
              {
                ray_3d ray( vector_3d( x , y , 0 ),
                            vector_3d( 0 , 0 , -1.0 ) );

                boost::shared_ptr< intersection > intersect = source_surface.get_intersection(
                  ray , interval(0,std::numeric_limits<scalar>::max()) );

                rgb color;

                if ( intersect.get() )
                  color = intersect->color_;
                else
                  color = phase3d::model::rgb<scalar>(0,0,0);

                destination.at(x,y,color);
              }
          }
      }

    };
  }
}
#endif
