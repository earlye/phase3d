#ifndef hDAFB1789_AFA9_4F8B_920B_6811764A82B0
#define hDAFB1789_AFA9_4F8B_920B_6811764A82B0

#include "interval.hpp"
#include "rgb.hpp"
#include "surface.hpp"
#include "basic_write_channel.hpp"

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class camera
    {
    public:
      typedef SCALAR scalar;
      typedef camera<scalar> this_type;
      typedef typename phase3d::model::interval< scalar > interval;
      typedef typename phase3d::model::rgb< scalar > rgb;
      typedef typename phase3d::model::surface< scalar > surface;
      typedef typename phase3d::model::basic_write_channel<rgb> basic_write_channel;

      virtual ~camera() { }
      virtual void render_tile( basic_write_channel& destination,
                                interval const& horizontal_range,
                                interval const& vertical_range,
                                surface const& source_surface ) = 0;
    };

  }
}

#endif
