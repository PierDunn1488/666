#ifndef slic3r_FillGyroid_hpp_
#define slic3r_FillGyroid_hpp_

#include "../libslic3r.h"

<<<<<<< HEAD
#include "Fill.hpp"
=======
#include "FillBase.hpp"
>>>>>>> origin/merill-merge

namespace Slic3r {

class FillGyroid : public Fill
{
public:
<<<<<<< HEAD

    FillGyroid(){}
    virtual Fill* clone() const { return new FillGyroid(*this); };
    virtual ~FillGyroid() {}

    /// require bridge flow since most of this pattern hangs in air
	// but it's not useful as most of it is on the previous layer.
	// it's just slowing it down => set it to false!
    virtual bool use_bridge_flow() const { return false; }

protected:

    virtual void _fill_surface_single(
        unsigned int                     thickness_layers,
        const std::pair<float, Point>   &direction, 
        ExPolygon                       &expolygon, 
        Polylines                       *polylines_out);
=======
    FillGyroid() {}
    Fill* clone() const override { return new FillGyroid(*this); }

    // Correction applied to regular infill angle to maximize printing
    // speed in default configuration (degrees)
    static constexpr float CorrectionAngle = -45.;

    // Density adjustment to have a good %of weight.
    static constexpr double DensityAdjust = 2.44;

    // Gyroid upper resolution tolerance (mm^-2)
    static constexpr double PatternTolerance = 0.2;


protected:
    void _fill_surface_single(
        const FillParams                &params, 
        unsigned int                     thickness_layers,
        const std::pair<float, Point>   &direction, 
        ExPolygon                        expolygon, 
        Polylines                       &polylines_out) const override;
>>>>>>> origin/merill-merge
};

} // namespace Slic3r

#endif // slic3r_FillGyroid_hpp_
