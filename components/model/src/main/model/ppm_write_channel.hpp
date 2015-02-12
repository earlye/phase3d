#ifndef hD38C8782_A42D_46D9_89DC_B217F206379D
#define hD38C8782_A42D_46D9_89DC_B217F206379D

#include "basic_write_channel.hpp"
#include "rgb.hpp"

#include <boost/format.hpp>

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class ppm_write_channel
      : public basic_write_channel< rgb<SCALAR> >
    {
    public:
      typedef SCALAR scalar;
      typedef rgb<SCALAR> value_type;
      typedef basic_write_channel< rgb<SCALAR> > base_type;
      typedef ppm_write_channel< scalar > this_type; 
      
      ppm_write_channel( std::string const& filename )
        : width_(0)
        , height_(0)
        , filename_(filename)
      { }

      ~ppm_write_channel( )
      {
        std::ofstream of(filename_);
        of << "P3\n";
        of << width_ << " " << height_ << "\n";
        of << "255\n";

        for( int i = 0; i != pixels_.size() ; ++i )
          {
            rgb< double > pixel = pixels_[i];
            of << int(pixel.red() * 255) << " "
               << int(pixel.green() * 255) << " "
               << int(pixel.blue() * 255) << " ";
            if ( (i + 1) % width_ == 0 )
              of << "\n";              
          }
      }

      long get_height() const {
        return height_;
      }

      long get_width() const {
        return width_;
      }
      
      ppm_write_channel& set_width( long width ) {
        width_ = width;
        reallocate();
        return *this;
      }

      ppm_write_channel& set_height( long height ) {
        height_ = height;
        reallocate();
        return *this;
      }

      ppm_write_channel& at( long x, long y , value_type const& value ) {
        long index = (height_ - y - 1) * width_ + x;
        assert( index < pixels_.size() );
        pixels_[index] = value;
      }

    private:

      void reallocate( ) {
        if (width_ * height_) {
          pixels_.resize(width_*height_);
        }
      }

      long width_;
      long height_;
      std::string filename_;
      std::vector< value_type > pixels_;
    };
  }
}

#endif
