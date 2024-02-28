#include "../ClipperUtils.hpp"
<<<<<<< HEAD
#include "../PolylineCollection.hpp"
=======
#include "../ShortestPath.hpp"
>>>>>>> origin/merill-merge
#include "../Surface.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

#include "FillGyroid.hpp"

namespace Slic3r {

<<<<<<< HEAD


=======
>>>>>>> origin/merill-merge
static inline double f(double x, double z_sin, double z_cos, bool vertical, bool flip)
{
    if (vertical) {
        double phase_offset = (z_cos < 0 ? M_PI : 0) + M_PI;
        double a   = sin(x + phase_offset);
        double b   = - z_cos;
        double res = z_sin * cos(x + phase_offset + (flip ? M_PI : 0.));
<<<<<<< HEAD
        double r   = sqrt(a*a + b*b);
        return asin(a/r) + asin(res/r) + M_PI;
    }
    else {
=======
        double r   = sqrt(sqr(a) + sqr(b));
        return asin(a/r) + asin(res/r) + M_PI;
    } else {
>>>>>>> origin/merill-merge
        double phase_offset = z_sin < 0 ? M_PI : 0.;
        double a   = cos(x + phase_offset);
        double b   = - z_sin;
        double res = z_cos * sin(x + phase_offset + (flip ? 0 : M_PI));
<<<<<<< HEAD
        double r   = sqrt(a*a + b*b);
=======
        double r   = sqrt(sqr(a) + sqr(b));
>>>>>>> origin/merill-merge
        return (asin(a/r) + asin(res/r) + 0.5 * M_PI);
    }
}

static inline Polyline make_wave(
<<<<<<< HEAD
    const std::vector<Pointf>& one_period, double width, double height, double offset, double scaleFactor,
    double z_cos, double z_sin, bool vertical)
{
    std::vector<Pointf> points = one_period;
    double period = points.back().x;
    points.pop_back();
    int n = points.size();
    do {
        points.emplace_back(Pointf(points[points.size()-n].x + period, points[points.size()-n].y));
    } while (points.back().x < width);
    points.back().x = width;

    // and construct the final polyline to return:
    Polyline polyline;
    for (Pointf& point : points) {
        point.y += offset;
        point.y = std::max(0., std::min(height, point.y));
        if (vertical)
            std::swap(point.x, point.y);
        polyline.points.emplace_back(Point(coord_t(point.x * scaleFactor), coord_t(point.y * scaleFactor)));
=======
    const std::vector<Vec2d>& one_period, double width, double height, double offset, double scaleFactor,
    double z_cos, double z_sin, bool vertical, bool flip)
{
    std::vector<Vec2d> points = one_period;
    double period = points.back()(0);
    if (width != period) // do not extend if already truncated
    {
        points.reserve(one_period.size() * size_t(floor(width / period)));
        points.pop_back();

        size_t n = points.size();
        do {
            points.emplace_back(points[points.size()-n].x() + period, points[points.size()-n].y());
        } while (points.back()(0) < width - EPSILON);

        points.emplace_back(Vec2d(width, f(width, z_sin, z_cos, vertical, flip)));
    }

    // and construct the final polyline to return:
    Polyline polyline;
    polyline.points.reserve(points.size());
    for (auto& point : points) {
        point(1) += offset;
        point(1) = clamp(0., height, double(point(1)));
        if (vertical)
            std::swap(point(0), point(1));
        polyline.points.emplace_back((point * scaleFactor).cast<coord_t>());
>>>>>>> origin/merill-merge
    }

    return polyline;
}

<<<<<<< HEAD

static bool sortPointf (Pointf& lfs,Pointf& rhs) { return lfs.x < rhs.x || (lfs.x == rhs.x && lfs.y < rhs.y); }

static std::vector<Pointf> make_one_period(double width, double scaleFactor, double z_cos, double z_sin, bool vertical, bool flip)
{
    std::vector<Pointf> points;
    double dx = M_PI_4; // very coarse spacing to begin with
    double limit = std::min(2*M_PI, width);
    for (double x = 0.; x < limit + EPSILON; x += dx) {  // so the last point is there too
        x = std::min(x, limit);
        points.emplace_back(Pointf(x,f(x, z_sin,z_cos, vertical, flip)));
    }

    // now we will check all internal points and in case some are too far from the line connecting its neighbours,
    // we will add one more point on each side:
    const double tolerance = .1;
    for (unsigned int i=1;i<points.size()-1;++i) {
        Pointf& lp = points[i-1]; // left point
        Pointf& tp = points[i];   // this point
        Pointf& rp = points[i+1]; // right point
        // calculate distance of the point to the line:
        double dist_mm = unscale(scaleFactor * std::abs( (rp.y - lp.y)*tp.x + (lp.x - rp.x)*tp.y + (rp.x*lp.y - rp.y*lp.x) ) / std::hypot((rp.y - lp.y),(lp.x - rp.x)));

        if (dist_mm > tolerance) {                               // if the difference from straight line is more than this
            double x = 0.5f * (points[i-1].x + points[i].x);
            points.emplace_back(Pointf(x, f(x, z_sin, z_cos, vertical, flip)));
            x = 0.5f * (points[i+1].x + points[i].x);
            points.emplace_back(Pointf(x, f(x, z_sin, z_cos, vertical, flip)));
            std::sort(points.begin(), points.end(), sortPointf);            // we added the points to the end, but need them all in order
            --i;                                                // decrement i so we also check the first newly added point
        }
    }
    return points;
}

static Polylines make_gyroid_waves(double gridZ, double density_adjusted, double line_spacing, double width, double height)
{
    const double scaleFactor = scale_(line_spacing) / density_adjusted;
 //scale factor for 5% : 8 712 388
 // 1z = 10^-6 mm ?
=======
static std::vector<Vec2d> make_one_period(double width, double scaleFactor, double z_cos, double z_sin, bool vertical, bool flip, double tolerance)
{
    std::vector<Vec2d> points;
    double dx = M_PI_2; // exact coordinates on main inflexion lobes
    double limit = std::min(2*M_PI, width);
    points.reserve(size_t(ceil(limit / tolerance / 3)));

    for (double x = 0.; x < limit - EPSILON; x += dx) {
        points.emplace_back(Vec2d(x, f(x, z_sin, z_cos, vertical, flip)));
    }
    points.emplace_back(Vec2d(limit, f(limit, z_sin, z_cos, vertical, flip)));

    // piecewise increase in resolution up to requested tolerance
    for(;;)
    {
        size_t size = points.size();
        for (unsigned int i = 1;i < size; ++i) {
            auto& lp = points[i-1]; // left point
            auto& rp = points[i];   // right point
            double x = lp(0) + (rp(0) - lp(0)) / 2;
            double y = f(x, z_sin, z_cos, vertical, flip);
            Vec2d ip = {x, y};
            if (std::abs(cross2(Vec2d(ip - lp), Vec2d(ip - rp))) > sqr(tolerance)) {
                points.emplace_back(std::move(ip));
            }
        }

        if (size == points.size())
            break;
        else
        {
            // insert new points in order
            std::sort(points.begin(), points.end(),
                      [](const Vec2d &lhs, const Vec2d &rhs) { return lhs(0) < rhs(0); });
        }
    }

    return points;
}

static Polylines make_gyroid_waves(coordf_t gridZ, coordf_t scaleFactor, double width, double height, double tolerance)
{

    //scale factor for 5% : 8 712 388
    // 1z = 10^-6 mm ?
>>>>>>> origin/merill-merge
    const double z     = gridZ / scaleFactor;
    const double z_sin = sin(z);
    const double z_cos = cos(z);

    bool vertical = (std::abs(z_sin) <= std::abs(z_cos));
    double lower_bound = 0.;
    double upper_bound = height;
    bool flip = true;
    if (vertical) {
        flip = false;
        lower_bound = -M_PI;
        upper_bound = width - M_PI_2;
        std::swap(width,height);
    }

<<<<<<< HEAD
    std::vector<Pointf> one_period = make_one_period(width, scaleFactor, z_cos, z_sin, vertical, flip); // creates one period of the waves, so it doesn't have to be recalculated all the time
    Polylines result;

    for (double y0 = lower_bound; y0 < upper_bound+EPSILON; y0 += 2*M_PI)           // creates odd polylines
            result.emplace_back(make_wave(one_period, width, height, y0, scaleFactor, z_cos, z_sin, vertical));

    flip = !flip;                                                                   // even polylines are a bit shifted
    one_period = make_one_period(width, scaleFactor, z_cos, z_sin, vertical, flip); // updates the one period sample
    for (double y0 = lower_bound + M_PI; y0 < upper_bound+EPSILON; y0 += 2*M_PI)    // creates even polylines
            result.emplace_back(make_wave(one_period, width, height, y0, scaleFactor, z_cos, z_sin, vertical));
=======
    std::vector<Vec2d> one_period_odd = make_one_period(width, scaleFactor, z_cos, z_sin, vertical, flip, tolerance); // creates one period of the waves, so it doesn't have to be recalculated all the time
    flip = !flip;                                                                   // even polylines are a bit shifted
    std::vector<Vec2d> one_period_even = make_one_period(width, scaleFactor, z_cos, z_sin, vertical, flip, tolerance);
    Polylines result;

    for (double y0 = lower_bound; y0 < upper_bound + EPSILON; y0 += M_PI) {
        // creates odd polylines
        result.emplace_back(make_wave(one_period_odd, width, height, y0, scaleFactor, z_cos, z_sin, vertical, flip));
        // creates even polylines
        y0 += M_PI;
        if (y0 < upper_bound + EPSILON) {
            result.emplace_back(make_wave(one_period_even, width, height, y0, scaleFactor, z_cos, z_sin, vertical, flip));
        }
    }
>>>>>>> origin/merill-merge

    return result;
}

<<<<<<< HEAD
void FillGyroid::_fill_surface_single( 
    unsigned int                     thickness_layers,
    const std::pair<float, Point>   &direction, 
    ExPolygon                       &expolygon, 
    Polylines                       *polylines_out)
{
    // no rotation is supported for this infill pattern (yet)
    BoundingBox bb = expolygon.contour.bounding_box();
    // Density adjusted to have a good %of weight.
    double      density_adjusted = std::max(0., density * 2.);
    // Distance between the gyroid waves in scaled coordinates.
    coord_t     distance = coord_t(scale_(this->spacing()) / density_adjusted);

    // align bounding box to a multiple of our grid module
    bb.min.align_to_grid(Point(2*M_PI*distance, 2*M_PI*distance));

    // generate pattern
    Polylines   polylines = make_gyroid_waves(
        scale_(this->z),
        density_adjusted,
        this->spacing(),
        ceil(bb.size().x / distance) + 1.,
        ceil(bb.size().y / distance) + 1.);
    
    // move pattern in place
    for (Polyline &polyline : polylines)
        polyline.translate(bb.min.x, bb.min.y);

    // clip pattern to boundaries
    polylines = intersection_pl(polylines, (Polygons)expolygon);

    // connect lines
    if (! dont_connect && ! polylines.empty()) { // prevent calling leftmost_point() on empty collections
        ExPolygon expolygon_off;
        {
            ExPolygons expolygons_off = offset_ex(expolygon, (float)SCALED_EPSILON);
            if (! expolygons_off.empty()) {
                // When expanding a polygon, the number of islands could only shrink. Therefore the offset_ex shall generate exactly one expanded island for one input island.
                assert(expolygons_off.size() == 1);
                std::swap(expolygon_off, expolygons_off.front());
            }
        }
        Polylines chained = PolylineCollection::chained_path_from(
            std::move(polylines), 
            PolylineCollection::leftmost_point(polylines), false); // reverse allowed
        bool first = true;
        for (Polyline &polyline : chained) {
            if (! first) {
                // Try to connect the lines.
                Points &pts_end = polylines_out->back().points;
                const Point &first_point = polyline.points.front();
                const Point &last_point = pts_end.back();
                // TODO: we should also check that both points are on a fill_boundary to avoid 
                // connecting paths on the boundaries of internal regions
                // TODO: avoid crossing current infill path
                if (first_point.distance_to(last_point) <= 5 * distance && 
                    expolygon_off.contains(Line(last_point, first_point))) {
                    // Append the polyline.
                    pts_end.insert(pts_end.end(), polyline.points.begin(), polyline.points.end());
                    continue;
                }
            }
            // The lines cannot be connected.
            polylines_out->emplace_back(std::move(polyline));
            first = false;
=======
// FIXME: needed to fix build on Mac on buildserver
constexpr double FillGyroid::PatternTolerance;

void FillGyroid::_fill_surface_single(
    const FillParams                &params, 
    unsigned int                     thickness_layers,
    const std::pair<float, Point>   &direction, 
    ExPolygon                        expolygon, 
    Polylines                       &polylines_out) const
{
    float infill_angle = float(this->angle + (CorrectionAngle * 2 * M_PI) / 360.f);
    if(std::abs(infill_angle) >= EPSILON)
        expolygon.rotate(-infill_angle);

    BoundingBox bb = expolygon.contour.bounding_box();
    // Density adjusted to have a good %of weight.
    double      density_adjusted = std::max(0., params.density * DensityAdjust);
    // Distance between the gyroid waves in scaled coordinates.
    coord_t     distance = coord_t(scale_(this->get_spacing()) / density_adjusted);

    // align bounding box to a multiple of our grid module
    bb.merge(_align_to_grid(bb.min, Point(2*M_PI*distance, 2*M_PI*distance)));

    // tolerance in scaled units. clamp the maximum tolerance as there's
    // no processing-speed benefit to do so beyond a certain point
    const coordf_t scaleFactor = scale_d(this->get_spacing()) / density_adjusted;
    const double tolerance_old = std::min(this->get_spacing() / 2, FillGyroid::PatternTolerance) / unscaled(scaleFactor);
    const double tolerance_old2 = std::min(this->get_spacing() / 2, FillGyroid::PatternTolerance) * density_adjusted  / this->get_spacing();
    const double tolerance = params.config->get_computed_value("resolution_internal") * density_adjusted / this->get_spacing();

    // generate pattern
    Polylines polylines = make_gyroid_waves(
        scale_d(this->z),
        scaleFactor,
        ceil(bb.size()(0) / distance) + 1.,
        ceil(bb.size()(1) / distance) + 1.,
        tolerance);

    // shift the polyline to the grid origin
    for (Polyline &pl : polylines)
        pl.translate(bb.min);

    polylines = intersection_pl(polylines, to_polygons(expolygon));

    if (! polylines.empty()) {
        // Remove very small bits, but be careful to not remove infill lines connecting thin walls!
        // The infill perimeter lines should be separated by around a single infill line width.
        const coordf_t minlength = scale_d(0.8 * this->get_spacing());
        polylines.erase(
            std::remove_if(polylines.begin(), polylines.end(), [minlength](const Polyline &pl) { return pl.length() < minlength; }),
            polylines.end());
    }

    if (! polylines.empty()) {
        // connect lines
        size_t polylines_out_first_idx = polylines_out.size();
        if (params.connection == icNotConnected){
            append(polylines_out, chain_polylines(polylines));
        } else {
            this->connect_infill(chain_polylines(polylines), expolygon, polylines_out, this->get_spacing(), params);
        }
        // new paths must be rotated back
        if (std::abs(infill_angle) >= EPSILON) {
            for (auto it = polylines_out.begin() + polylines_out_first_idx; it != polylines_out.end(); ++ it)
                it->rotate(infill_angle);
>>>>>>> origin/merill-merge
        }
    }
}

<<<<<<< HEAD

=======
>>>>>>> origin/merill-merge
} // namespace Slic3r
