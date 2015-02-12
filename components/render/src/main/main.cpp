#include <model/basic_write_channel.hpp>
#include <model/camera.hpp>
#include <model/group.hpp>
#include <model/orthographic_camera.hpp>
#include <model/ppm_write_channel.hpp>
#include <model/ray_3d.hpp>
#include <model/sphere.hpp>
#include <model/surface.hpp>
#include <model/triangle_3d.hpp>

#include <boost/format.hpp>
#include <boost/program_options.hpp>

#include <cmath>
#include <iostream>

namespace po = boost::program_options;
namespace p3m = phase3d::model;
typedef double scalar;

int main(int argc,char**argv)
{
  typedef p3m::intersection<scalar> intersection;
  typedef p3m::interval<scalar> interval;

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
  std::cout << "Input-file: " << model << std::endl;
  std::cout << "Output-file: " << output << std::endl;
  std::cout << boost::format("width x height: %d x %d\n") % width % height;
  assert( width );
  assert( height );

  p3m::ppm_write_channel<scalar> output_buffer(output);
  output_buffer.set_width( width )
    .set_height( height );


  boost::shared_ptr< p3m::group<scalar> > scene(new p3m::group<scalar>());

  scene->push_back(boost::shared_ptr< p3m::surface<scalar> >(
    new p3m::sphere<scalar>(
      p3m::vector_3d<scalar>(250,250,-1000) , 150 ) ));

  scene->push_back(boost::shared_ptr< p3m::surface<scalar> >(
    new p3m::triangle_3d<scalar>( p3m::vector_3d<scalar>(300,600,-800),
                                  p3m::vector_3d<scalar>(0,100,-1000),
                                  p3m::vector_3d<scalar>(450,20,-1000) )));

  boost::shared_ptr< p3m::camera<scalar> > camera( new p3m::orthographic_camera<scalar> );

  camera->render_tile( output_buffer,
                       p3m::interval<scalar>(0, output_buffer.get_width()),
                       p3m::interval<scalar>(0, output_buffer.get_height()),
                       *scene );


}
