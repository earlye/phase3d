#include <model/ppm_write_channel.hpp>
#include <model/basic_write_channel.hpp>
#include <model/ray_3d.hpp>
#include <model/surface.hpp>

#include <boost/format.hpp>
#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;
typedef double scalar;

template< typename SCALAR >
class sphere
  : public phase3d::model::surface<SCALAR>
{
public:
  typedef SCALAR scalar;
  typedef phase3d::model::surface<SCALAR> base_type;
  typedef typename base_type::intersection intersection;
  typedef typename base_type::ray_3d ray_3d;
  typedef typename base_type::interval interval;
  typedef typename base_type::vector_2d vector_2d;
  
  boost::shared_ptr<intersection> get_intersection( ray_3d const& ray , interval const& range )
  {
    boost::shared_ptr<intersection> result;
    //    std::clog << r.direction_.x() << std::endl;
    if (ray.direction_.y() >= 0.0)
      {
        result.reset( new intersection( scalar(1), ray, ray_3d(), vector_2d() ) );
      }
    return result;
  }
};

template< typename SCALAR >
class camera
{
public:
  typedef SCALAR scalar;
  typedef camera<scalar> this_type;
  virtual ~camera() { }
  virtual void render_image( phase3d::model::basic_write_channel<scalar>& destination ) = 0;
};

int main(int argc,char**argv)
{
  typedef phase3d::model::intersection<scalar> intersection;
  typedef phase3d::model::interval<scalar> interval;
  
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
  std::cout << boost::format("width x height: %d x %d\n") % width % height;
  assert( width );
  assert( height );

  phase3d::model::ppm_write_channel<scalar> output_buffer(output);
  output_buffer.set_width( width )
    .set_height( height );

  boost::shared_ptr< phase3d::model::surface<scalar> > surf(new sphere<scalar>);

  for ( scalar u = 0; u < 1.0 ; u += 1.0 / (scalar)width )
    {
      for ( scalar v = 0 ; v < 1.0 ; v += 1.0 / (scalar)height )
        {
          phase3d::model::rgb<scalar> color( u , v , 0 );
          
          phase3d::model::ray_3d<scalar> ray( phase3d::model::vector_3d<scalar>( 0.5 , 0.5 , -1.0 ),
                                              phase3d::model::vector_3d<scalar>( 0.5 - u , 0.5 - v , 1.0 ) );

          if ( surf )
            {
              boost::shared_ptr< intersection > intersect = surf->get_intersection( ray , interval() );
              if ( intersect ) {
                color = phase3d::model::rgb<scalar>( u , v , 1 );
              }
            }

          long x = u * width;
          long y = v * height;
          output_buffer.at(x,y,color);
        }
    }

}
