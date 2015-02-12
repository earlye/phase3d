#ifndef h3F65C00C_6A97_4AD0_995C_6A14C25690FA
#define h3F65C00C_6A97_4AD0_995C_6A14C25690FA

#include "surface.hpp"

namespace phase3d
{
  namespace model
  {
    template< typename SCALAR >
    class triangle_3d
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

      triangle_3d( vector_3d p0 , vector_3d p1, vector_3d p2 )
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

  }
}

#endif
