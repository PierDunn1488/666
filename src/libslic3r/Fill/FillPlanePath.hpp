#ifndef slic3r_FillPlanePath_hpp_
#define slic3r_FillPlanePath_hpp_

#include <map>

#include "../libslic3r.h"

<<<<<<< HEAD
#include "Fill.hpp"
=======
#include "FillBase.hpp"
>>>>>>> origin/merill-merge

namespace Slic3r {

// The original Perl code used path generators from Math::PlanePath library:
// http://user42.tuxfamily.org/math-planepath/
// http://user42.tuxfamily.org/math-planepath/gallery.html

class FillPlanePath : public Fill
{
public:
<<<<<<< HEAD
    virtual ~FillPlanePath() {}

protected:
    virtual void _fill_surface_single(
        unsigned int                     thickness_layers,
        const direction_t               &direction, 
        ExPolygon                       &expolygon, 
        Polylines*                      polylines_out);

    virtual float _layer_angle(size_t idx) const { return 0.f; }
    virtual bool  _centered() const = 0;
    virtual Pointfs _generate(coord_t min_x, coord_t min_y, coord_t max_x, coord_t max_y) = 0;
=======
    ~FillPlanePath() override = default;

protected:
    void _fill_surface_single(
        const FillParams                &params, 
        unsigned int                     thickness_layers,
        const std::pair<float, Point>   &direction, 
        ExPolygon                        expolygon, 
        Polylines                       &polylines_out) const override;

    float _layer_angle(size_t idx) const override { return 0.f; }
    virtual bool  _centered() const = 0;
    virtual Pointfs _generate(coord_t min_x, coord_t min_y, coord_t max_x, coord_t max_y) const = 0;
>>>>>>> origin/merill-merge
};

class FillArchimedeanChords : public FillPlanePath
{
public:
<<<<<<< HEAD
    virtual Fill* clone() const { return new FillArchimedeanChords(*this); };
    virtual ~FillArchimedeanChords() {}
    virtual bool can_solid() const { return true; };

protected:
    virtual bool  _centered() const { return true; }
    virtual Pointfs _generate(coord_t min_x, coord_t min_y, coord_t max_x, coord_t max_y);
=======
    Fill* clone() const override { return new FillArchimedeanChords(*this); };
    ~FillArchimedeanChords() override = default;

protected:
    bool  _centered() const override { return true; }
    Pointfs _generate(coord_t min_x, coord_t min_y, coord_t max_x, coord_t max_y) const override;
>>>>>>> origin/merill-merge
};

class FillHilbertCurve : public FillPlanePath
{
public:
<<<<<<< HEAD
    virtual Fill* clone() const { return new FillHilbertCurve(*this); };
    virtual ~FillHilbertCurve() {}
    virtual bool can_solid() const { return true; };

protected:
    virtual bool  _centered() const { return false; }
    virtual Pointfs _generate(coord_t min_x, coord_t min_y, coord_t max_x, coord_t max_y);
=======
    Fill* clone() const override { return new FillHilbertCurve(*this); };
    ~FillHilbertCurve() override = default;

protected:
    bool  _centered() const override { return false; }
    Pointfs _generate(coord_t min_x, coord_t min_y, coord_t max_x, coord_t max_y) const override;
>>>>>>> origin/merill-merge
};

class FillOctagramSpiral : public FillPlanePath
{
public:
<<<<<<< HEAD
    virtual Fill* clone() const { return new FillOctagramSpiral(*this); };
    virtual ~FillOctagramSpiral() {}
    virtual bool can_solid() const { return true; };

protected:
    virtual bool  _centered() const { return true; }
    virtual Pointfs _generate(coord_t min_x, coord_t min_y, coord_t max_x, coord_t max_y);
=======
    Fill* clone() const override { return new FillOctagramSpiral(*this); };
    ~FillOctagramSpiral() override = default;

protected:
    bool  _centered() const override { return true; }
    Pointfs _generate(coord_t min_x, coord_t min_y, coord_t max_x, coord_t max_y) const override;
>>>>>>> origin/merill-merge
};

} // namespace Slic3r

#endif // slic3r_FillPlanePath_hpp_
