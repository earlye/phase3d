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
class triangle
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
  typedef typename phase3d::model::rgb<scalar> rgb;

public:

  triangle( vector_3d p0 , vector_3d p1, vector_3d p2 )
    : p0_(p0)
    , p1_(p1)
    , p2_(p2)
  { }

  boost::shared_ptr<intersection> get_intersection( ray_3d const& ray , interval const& range ) const
  {
    scalar A = p0_.x() - p1_.x();
    scalar B = p0_.y() - p1_.y();
    scalar C = p0_.z() - p1_.z();

    scalar D = p0_.x() - p2_.x();
    scalar E = p0_.y() - p2_.y();
    scalar F = p0_.z() - p2_.z();

    scalar G = ray.direction_.x();
    scalar H = ray.direction_.y();
    scalar I = ray.direction_.z();

    scalar J = p0_.x() - ray.origin_.x();
    scalar K = p0_.y() - ray.origin_.y();
    scalar L = p0_.z() - ray.origin_.z();

    scalar EIHF = E*I - H*F;
    scalar GFDI = G*F - D*I;
    scalar DHEG = D*H - E*G;

    scalar denom = A*EIHF + B*GFDI + C*DHEG;
    scalar beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

    if (beta <= scalar(0) || beta >= scalar(1))
      {
        return boost::shared_ptr<intersection>();
      }

    scalar AKJB = A*K - J*B;
    scalar JCAL = J*K - A*L;
    scalar BLKC = B*L - K*C;

    scalar gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;

    if (gamma <= scalar(0) || (beta+gamma) >= scalar(1))
      return boost::shared_ptr<intersection>();

    scalar t = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    if (!range.contains(t))
      {
        return boost::shared_ptr<intersection>();
      }


    vector_3d p = ray.point_at_parameter(t);
    vector_3d n = p0_.cross_product(p1_);
    ray_3d normal_ray(p,n);
    vector_2d uv;

    return boost::shared_ptr<intersection>(new intersection(t, ray, normal_ray , uv , rgb(t/2000.0,0,0) ));
  }

private:
  vector_3d p0_;
  vector_3d p1_;
  vector_3d p2_;
};

template< typename SCALAR >
class group
  : public phase3d::model::surface<SCALAR>
{
public:
  typedef SCALAR scalar;
  typedef phase3d::model::surface<scalar> base_type;
  typedef base_type surface_type;
  typedef typename base_type::intersection intersection;
  typedef typename base_type::interval interval;
  typedef typename base_type::ray_3d ray_3d;

  group& push_back( boost::shared_ptr< surface_type > surface )
  {
    surfaces_.push_back(surface);
    return *this;
  }

  boost::shared_ptr<intersection> get_intersection( ray_3d const& ray , interval const& original_range ) const
  {
    boost::shared_ptr<intersection> result;
    interval range(original_range);

    for( int i = 0; i < surfaces_.size() ; ++i )
      {
        boost::shared_ptr<intersection> check = surfaces_[i]->get_intersection( ray, range );
        if ( check.get() )
          {
            range = interval(range.low(), check->t_ );
            result = check;
          }
      }
    return result;
  }

private:
  std::vector< boost::shared_ptr< surface_type > > surfaces_;
};


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
  typedef typename phase3d::model::rgb<scalar> rgb;

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

    scalar t = (-b - sqrt_discriminant ) / (scalar(2)*a);
    if (t < range.low() )
      t = ( -b + sqrt_discriminant ) / (scalar(2)*a);

    if ( !range.contains(t) )
      return result;

    vector_3d p( ray.point_at_parameter(t) );
    vector_3d n = scalar(2) * (p - center_);
    ray_3d normal_ray(p,n);
    vector_2d uv;

    result.reset( new intersection( t, ray, normal_ray , uv , rgb(0,0,t/2000.0)  ) );
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


  boost::shared_ptr< group<scalar> > scene(new group<scalar>());

  scene->push_back(boost::shared_ptr< phase3d::model::surface<scalar> >(
    new sphere<scalar>(
      phase3d::model::vector_3d<scalar>(250,250,-1000) , 150 ) ));

  scene->push_back(boost::shared_ptr< phase3d::model::surface<scalar> >(
    new triangle<scalar>( phase3d::model::vector_3d<scalar>(300,600,-800),
                          phase3d::model::vector_3d<scalar>(0,100,-1000),
                          phase3d::model::vector_3d<scalar>(450,20,-1000) )));

  boost::shared_ptr< camera<scalar> > camera( new orthographic_camera<scalar> );

  camera->render_tile( output_buffer,
                       phase3d::model::interval<scalar>(0, output_buffer.get_width()),
                       phase3d::model::interval<scalar>(0, output_buffer.get_height()),
                       *scene );


}
