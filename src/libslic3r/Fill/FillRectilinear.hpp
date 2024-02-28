#ifndef slic3r_FillRectilinear_hpp_
#define slic3r_FillRectilinear_hpp_

#include "../libslic3r.h"

<<<<<<< HEAD
#include "Fill.hpp"

namespace Slic3r {

class FillRectilinear : public Fill
{
public:
    virtual Fill* clone() const { return new FillRectilinear(*this); };
    virtual ~FillRectilinear() {}
    virtual bool can_solid() const { return true; };

protected:
	virtual void _fill_surface_single(
	    unsigned int                     thickness_layers,
	    const direction_t               &direction, 
	    ExPolygon                       &expolygon, 
	    Polylines*                      polylines_out);
    
	void _fill_single_direction(ExPolygon expolygon, const direction_t &direction,
	    coord_t x_shift, Polylines* out);
};

class FillAlignedRectilinear : public FillRectilinear
{
public:
    virtual Fill* clone() const { return new FillAlignedRectilinear(*this); };
    virtual ~FillAlignedRectilinear() {};
    virtual bool can_solid() const { return false; };

protected:
	// Keep the angle constant in all layers.
    virtual float _layer_angle(size_t idx) const { return 0.f; };
=======
#include "FillBase.hpp"

namespace Slic3r {

class Surface;
struct SegmentedIntersectionLine;
struct ExPolygonWithOffset;

class FillRectilinear : public Fill
{
public:
    Fill* clone() const override { return new FillRectilinear(*this); };
    ~FillRectilinear() override = default;
    virtual void init_spacing(double spacing, const FillParams& params) override;
    Polylines fill_surface(const Surface* surface, const FillParams& params) const override;

protected:
    virtual std::vector<SegmentedIntersectionLine> _vert_lines_for_polygon(const ExPolygonWithOffset& poly_with_offset, const BoundingBox& bounding_box, const FillParams& params, coord_t line_spacing) const;

    // Fill by single directional lines, interconnect the lines along perimeters.
    bool fill_surface_by_lines(const Surface* surface, const FillParams& params, float angleBase, float pattern_shift, Polylines& polylines_out) const;

    // Fill by multiple sweeps of differing directions.
    struct SweepParams {
        float angle_base;
        float pattern_shift;
    };
    bool fill_surface_by_multilines(const Surface* surface, FillParams params, const std::initializer_list<SweepParams>& sweep_params, Polylines& polylines_out) const;
};

class FillMonotonic : public FillRectilinear
{
public:
    Fill* clone() const override { return new FillMonotonic(*this); };
    ~FillMonotonic() override = default;
    Polylines fill_surface(const Surface* surface, const FillParams& params) const override;
    bool no_sort() const override { return true; }
>>>>>>> origin/merill-merge
};

class FillGrid : public FillRectilinear
{
public:
<<<<<<< HEAD
    virtual Fill* clone() const { return new FillGrid(*this); };
    virtual ~FillGrid() {}
    virtual bool can_solid() const { return false; };

protected:
	// The grid fill will keep the angle constant between the layers,; see the implementation of Slic3r::Fill.
    virtual float _layer_angle(size_t idx) const { return 0.f; }
	
	virtual void _fill_surface_single(
	    unsigned int                     thickness_layers,
	    const std::pair<float, Point>   &direction, 
	    ExPolygon                       &expolygon, 
	    Polylines*                      polylines_out);
=======
    Fill* clone() const override { return new FillGrid(*this); };
    ~FillGrid() override = default;
    Polylines fill_surface(const Surface* surface, const FillParams& params) const override;

protected:
    // The grid fill will keep the angle constant between the layers, see the implementation of Slic3r::Fill.
    float _layer_angle(size_t idx) const override { return 0.f; }
>>>>>>> origin/merill-merge
};

class FillTriangles : public FillRectilinear
{
public:
<<<<<<< HEAD
    virtual Fill* clone() const { return new FillTriangles(*this); };
    virtual ~FillTriangles() {}
    virtual bool can_solid() const { return false; };

protected:
	// The grid fill will keep the angle constant between the layers,; see the implementation of Slic3r::Fill.
    virtual float _layer_angle(size_t idx) const { return 0.f; }
	
	virtual void _fill_surface_single(
	    unsigned int                     thickness_layers,
	    const std::pair<float, Point>   &direction, 
	    ExPolygon                       &expolygon, 
	    Polylines*                      polylines_out);
=======
    Fill* clone() const override { return new FillTriangles(*this); };
    ~FillTriangles() override = default;
    Polylines fill_surface(const Surface* surface, const FillParams& params) const override;

protected:
    // The grid fill will keep the angle constant between the layers, see the implementation of Slic3r::Fill.
    float _layer_angle(size_t idx) const override { return 0.f; }
>>>>>>> origin/merill-merge
};

class FillStars : public FillRectilinear
{
public:
<<<<<<< HEAD
    virtual Fill* clone() const { return new FillStars(*this); };
    virtual ~FillStars() {}
    virtual bool can_solid() const { return false; };

protected:
	// The grid fill will keep the angle constant between the layers,; see the implementation of Slic3r::Fill.
    virtual float _layer_angle(size_t idx) const { return 0.f; }
	
	virtual void _fill_surface_single(
	    unsigned int                     thickness_layers,
	    const std::pair<float, Point>   &direction, 
	    ExPolygon                       &expolygon, 
	    Polylines*                      polylines_out);
=======
    Fill* clone() const override { return new FillStars(*this); };
    ~FillStars() override = default;
    Polylines fill_surface(const Surface* surface, const FillParams& params) const override;

protected:
    // The grid fill will keep the angle constant between the layers, see the implementation of Slic3r::Fill.
    float _layer_angle(size_t idx) const override { return 0.f; }
>>>>>>> origin/merill-merge
};

class FillCubic : public FillRectilinear
{
public:
<<<<<<< HEAD
    virtual Fill* clone() const { return new FillCubic(*this); };
    virtual ~FillCubic() {}
    virtual bool can_solid() const { return false; };

protected:
	// The grid fill will keep the angle constant between the layers,; see the implementation of Slic3r::Fill.
    virtual float _layer_angle(size_t idx) const { return 0.f; }
	
	virtual void _fill_surface_single(
	    unsigned int                     thickness_layers,
	    const std::pair<float, Point>   &direction, 
	    ExPolygon                       &expolygon, 
	    Polylines*                      polylines_out);
};

=======
    Fill* clone() const override { return new FillCubic(*this); };
    ~FillCubic() override = default;
    Polylines fill_surface(const Surface* surface, const FillParams& params) const override;

protected:
    // The grid fill will keep the angle constant between the layers, see the implementation of Slic3r::Fill.
    float _layer_angle(size_t idx) const override { return 0.f; }
};

class FillRectilinearPeri : public FillRectilinear
{
public:
    Fill* clone() const override { return new FillRectilinearPeri(*this); };
    ~FillRectilinearPeri() override = default;
    //Polylines fill_surface(const Surface *surface, const FillParams &params);
    void fill_surface_extrusion(const Surface* surface, const FillParams& params, ExtrusionEntitiesPtr& out) const override;

};


class FillScatteredRectilinear : public FillRectilinear
{
public:
    Fill* clone() const override { return new FillScatteredRectilinear(*this); };
    ~FillScatteredRectilinear() override = default;
    Polylines fill_surface(const Surface* surface, const FillParams& params) const override;

protected:
    float _layer_angle(size_t idx) const override;
    std::vector<SegmentedIntersectionLine> _vert_lines_for_polygon(const ExPolygonWithOffset& poly_with_offset, const BoundingBox& bounding_box, const FillParams& params, coord_t line_spacing) const override;
    coord_t _line_spacing_for_density(float density) const override;
};

class FillRectilinearSawtooth : public FillRectilinear {
public:

    Fill* clone() const override { return new FillRectilinearSawtooth(*this); };
    ~FillRectilinearSawtooth() override = default;
    void fill_surface_extrusion(const Surface* surface, const FillParams& params, ExtrusionEntitiesPtr& out) const override;

};

class FillRectilinearWGapFill : public FillRectilinear
{
public:
    Fill* clone() const override { return new FillRectilinearWGapFill(*this); };
    ~FillRectilinearWGapFill() override = default;
    void fill_surface_extrusion(const Surface* surface, const FillParams& params, ExtrusionEntitiesPtr& out) const override;
    static void split_polygon_gap_fill(const Surface& surface, const FillParams& params, ExPolygons& rectilinear, ExPolygons& gapfill);
protected:
    virtual bool is_monotonic() const { return false;  }
};

class FillMonotonicWGapFill : public FillRectilinearWGapFill
{
public:

    Fill* clone() const override { return new FillMonotonicWGapFill(*this); };
    ~FillMonotonicWGapFill() override = default;
protected:
    virtual bool is_monotonic() const override { return true; }
};


>>>>>>> origin/merill-merge
}; // namespace Slic3r

#endif // slic3r_FillRectilinear_hpp_
