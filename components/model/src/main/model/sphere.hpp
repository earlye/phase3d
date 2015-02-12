#ifndef h0427C5AD_6082_42BD_A956_B96694A9E890
#define h0427C5AD_6082_42BD_A956_B96694A9E890

#include "surface.hpp"

namespace phase3d
{
  namespace model
  {
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

  }
}

#endif
