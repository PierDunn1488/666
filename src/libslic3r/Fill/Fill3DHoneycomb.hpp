#ifndef slic3r_Fill3DHoneycomb_hpp_
#define slic3r_Fill3DHoneycomb_hpp_

#include <map>

#include "../libslic3r.h"

<<<<<<< HEAD
#include "Fill.hpp"
=======
#include "FillBase.hpp"
>>>>>>> origin/merill-merge

namespace Slic3r {

class Fill3DHoneycomb : public Fill
{
public:
<<<<<<< HEAD
    virtual Fill* clone() const { return new Fill3DHoneycomb(*this); };
    virtual ~Fill3DHoneycomb() {}

	// require bridge flow since most of this pattern hangs in air
    virtual bool use_bridge_flow() const { return true; }

protected:
	virtual void _fill_surface_single(
	    unsigned int                     thickness_layers,
	    const direction_t               &direction, 
	    ExPolygon                       &expolygon, 
	    Polylines*                      polylines_out);
=======
    Fill* clone() const override { return new Fill3DHoneycomb(*this); };
    ~Fill3DHoneycomb() override {}

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

#endif // slic3r_Fill3DHoneycomb_hpp_
