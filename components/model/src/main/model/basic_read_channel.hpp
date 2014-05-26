#ifndef hFA5FB6B6_105A_445C_9912_A0644AE2AC0A
#define hFA5FB6B6_105A_445C_9912_A0644AE2AC0A

namespace phase3d
{
  namespace model
  {
    /**
     *
     * A channel is a "subset" of an image. Each channel can store various 
     * information - object id, depth, focus, rgb, transparency, etc.
     *
     * An image is a collection of channels.
     *
     * We can think of a channel as a two-dimensional vector which
     * returns a value_type given an x,y value. Implementations might
     * include an in-memory vector with x,y -> index mapping, a
     * database descriptor (e.g., table, index, column names), a url
     * reference, a procedural texture (noise), etc.
     *
     */
    template< class VALUE_TYPE >
    class basic_read_channel
    {
    public:
      typedef VALUE_TYPE value_type;
      typedef basic_read_channel<value_type> this_type;

      virtual ~basic_read_channel() { }

      virtual value_type& at( long x , long y ) const = 0;
    };
  }
}

#endif
