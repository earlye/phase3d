#include <model/ppm_write_channel.hpp>
#include <model/basic_write_channel.hpp>
#include <model/ray_3d.hpp>
#include <model/surface.hpp>

#include <boost/format.hpp>
#include <boost/program_options.hpp>

#include <cmath>
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
  typedef typename phase3d::model::vector_3d<scalar> vector_3d;

  sphere()
    : center_(0,0,0)
    , radius_(1.0)
  {}

  sphere( vector_3d const& center, scalar radius )
    : center_(center)
    , radius_(radius)
  { }

  sphere& set_center( vector_3d const& center )
  {
    this->center_ = center;
    return *this;
  }

  sphere& set_radius( scalar const& radius )
  {
    this->radius_ = radius;
    return *this;
  }
  
  boost::shared_ptr<intersection> get_intersection( ray_3d const& ray , interval const& range ) const
  {
    boost::shared_ptr<intersection> result;

    vector_3d o_c = ray.origin_ - center_;

    scalar a = ray.direction_.dot_product(ray.direction_);
    scalar b = (scalar(2) * ray.direction_).dot_product( o_c );
    scalar c = o_c.dot_product(o_c) - radius_*radius_;

    scalar discriminant = b*b - scalar(4) * a * c;

    if ( discriminant < 0 )
      return result;

    scalar sqrt_discriminant = sqrt(discriminant);
    
    if ( discriminant == scalar(0) )
      {
        scalar t = (-b + sqrt_discriminant ) / (scalar(2)*a);
        if ( !range.contains(t) )
          return result;

        vector_3d p( ray.point_at_parameter(t) );
        vector_3d n = scalar(2) * (p - center_);

        result.reset( new intersection( scalar(t), ray, ray_3d(p,n) , vector_2d() ) );
        return result;
      }

    result.reset( new intersection( scalar(1), ray, ray_3d(), vector_2d() ) );
    return result;
  }

private:
  vector_3d center_;
  scalar radius_;
};

template< typename SCALAR >
class camera
{
public:
  typedef SCALAR scalar;
  typedef camera<scalar> this_type;
  typedef typename phase3d::model::interval< scalar > interval;
  typedef typename phase3d::model::rgb< scalar > rgb;
  typedef typename phase3d::model::surface< scalar > surface;

  virtual ~camera() { }
  virtual void render_tile( phase3d::model::basic_write_channel<rgb>& destination, interval const& horizontal_range, interval const& vertical_range, surface const& source_surface ) = 0;
};

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

  virtual void render_tile( phase3d::model::basic_write_channel< rgb >& destination, interval const& horizontal_range, interval const& vertical_range, surface const& source_surface )
  {
    for ( int y = horizontal_range.low(); y < horizontal_range.high() ; ++y )
      {
        for ( int x = horizontal_range.low(); x < horizontal_range.high() ; ++x )
          {
            ray_3d ray( vector_3d( x + 0.5 , y + 0.5 , 0 ),
                        vector_3d( 0 , 0 , -1.0 ) );

            boost::shared_ptr< intersection > intersect = source_surface.get_intersection( ray , interval() );

            rgb color;
            
            if ( intersect.get() )
              color = phase3d::model::rgb<scalar>( 0.5 , 0.5 , 0.5 );
            else
              color = phase3d::model::rgb<scalar>(0,0,0);

            destination.at(x,y,color);
          }
      }
  }

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
  std::cout << "Input-file: " << model << std::endl;
  std::cout << "Output-file: " << output << std::endl;
  std::cout << boost::format("width x height: %d x %d\n") % width % height;
  assert( width );
  assert( height );

  phase3d::model::ppm_write_channel<scalar> output_buffer(output);
  output_buffer.set_width( width )
    .set_height( height );

  boost::shared_ptr< phase3d::model::surface<scalar> > surf(new sphere<scalar>( phase3d::model::vector_3d<scalar>(250,250,-1000) , 150 ) );
  boost::shared_ptr< camera<scalar> > camera( new orthographic_camera<scalar> );

  camera->render_tile( output_buffer,
                       phase3d::model::interval<scalar>(0, output_buffer.get_width()),
                       phase3d::model::interval<scalar>(0, output_buffer.get_height()),
                       *surf );


}
