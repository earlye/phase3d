#include <iostream>

#include <boost/program_options.hpp>
#include <model/ppm_write_channel.hpp>
#include <model/ray_3d.hpp>
#include <model/surface.hpp>

namespace po = boost::program_options;

class stupid_surface
  : public phase3d::model::surface<double>
{
public:
  scalar intersect( ray_3d const& r )
  {
    //    std::clog << r.direction_.x() << std::endl;
    if (r.direction_.y() >= 0.0)
      return 1;
    return -1;
  }
};

int main(int argc,char**argv)
{
  std::string model;
  std::string output;
  long width;
  long height;

  po::options_description desc( "Available Options" );
  desc.add_options()
    ("help,?", "produce help message")
    ("version,v" , "display version")
    ("model,m" , po::value< std::string >( &model ) , "input file")
    ("width,w" , po::value< long >( &width ), "output image width")
    ("height,h" , po::value< long >( &height ), "output image height")
    ("output,o" , po::value< std::string>( &output ) , "output file" )
    ;
  po::variables_map vm;
  /* po::positional_options_description p;
     p.add("site", -1); */

  po::store(po::command_line_parser(argc,argv).options(desc)./*positional(p).*/run(),vm);
  po::notify(vm);

  std::cout << "Phase 3d" << std::endl;
  std::cout << "Input file:" << model << std::endl;
  std::cout << "Output file:" << output << std::endl;

  phase3d::model::ppm_write_channel output_buffer(output);
  output_buffer.set_width( width )
    .set_height( height );

  boost::shared_ptr< phase3d::model::surface<double> > surf(new stupid_surface);

  for ( double u = 0; u < 1.0 ; u += 1.0 / (double)width )
    {
      for ( double v = 0 ; v < 1.0 ; v += 1.0 / (double)height )
        {
          phase3d::model::rgb<double> color( u , v , 0 );
          
          phase3d::model::ray_3d<double> ray( phase3d::model::vector_3d<double>( 0.5 , 0.5 , -1.0 ),
                                              phase3d::model::vector_3d<double>( 0.5 - u , 0.5 - v , 1.0 ) );

          if ( surf )
            {
              double distance = surf->intersect( ray );
              if ( distance >= 0 ) {
                color = phase3d::model::rgb<double>( u , v , 1 );
              }
            }

          long x = u * width;
          long y = v * height;
          output_buffer.at(x,y,color);
        }
    }

}
