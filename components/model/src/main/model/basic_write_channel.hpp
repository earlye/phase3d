#ifndef h6B66878C_1944_489A_B48B_F7C99EE0B227
#define h6B66878C_1944_489A_B48B_F7C99EE0B227

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
     * stores a value_type given an x,y value. Implementations might
     * include an in-memory vector with x,y -> index mapping, a
     * database descriptor (e.g., table, index, column names), a url
     * reference, a procedural texture (noise), etc.
     *
     */
    template< class VALUE_TYPE >
    class basic_write_channel
    {
    public:
      typedef VALUE_TYPE value_type;
      typedef basic_write_channel<value_type> this_type;

      virtual ~basic_write__channel() { }

      virtual this_type& at( long x , long y , value_type const& value ) = 0;
    };
  }
}

#endif
