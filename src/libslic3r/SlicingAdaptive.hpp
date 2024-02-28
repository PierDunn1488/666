<<<<<<< HEAD:xs/src/libslic3r/SlicingAdaptive.hpp
#ifndef slic3r_SlicingAdaptive_hpp_
#define slic3r_SlicingAdaptive_hpp_

=======
// Based on implementation by @platsch

#ifndef slic3r_SlicingAdaptive_hpp_
#define slic3r_SlicingAdaptive_hpp_

#include "Slicing.hpp"
>>>>>>> origin/merill-merge:src/libslic3r/SlicingAdaptive.hpp
#include "admesh/stl.h"

namespace Slic3r
{

<<<<<<< HEAD:xs/src/libslic3r/SlicingAdaptive.hpp
class TriangleMesh;
=======
class ModelVolume;
>>>>>>> origin/merill-merge:src/libslic3r/SlicingAdaptive.hpp

class SlicingAdaptive
{
public:
<<<<<<< HEAD:xs/src/libslic3r/SlicingAdaptive.hpp
    SlicingAdaptive() {};
    ~SlicingAdaptive() {};
    void clear();
    void add_mesh(const TriangleMesh *mesh) { m_meshes.push_back(mesh); }
    void prepare(coordf_t object_size);
    float next_layer_height(coordf_t z, coordf_t quality_factor, coordf_t min_layer_height, coordf_t max_layer_height);
    float horizontal_facet_distance(coordf_t z, coordf_t max_layer_height);

private:
    float _layer_height_from_facet(int ordered_id, float scaled_quality_factor);

protected:
    // id of the current facet from last iteration
    coordf_t                            object_size;
    int                                 current_facet;
    std::vector<const TriangleMesh*>	m_meshes;
    // Collected faces of all meshes, sorted by raising Z of the bottom most face.
    std::vector<const stl_facet*>		m_faces;
    // Z component of face normals, normalized.
    std::vector<float>					m_face_normal_z;
=======
    void  clear();
    void  set_slicing_parameters(SlicingParameters params) { m_slicing_params = params; }
    void  prepare(const ModelObject &object);
    // Return next layer height starting from the last print_z, using a quality measure
    // (quality in range from 0 to 1, 0 - highest quality at low layer heights, 1 - lowest print quality at high layer heights).
    // The layer height curve shall be centered roughly around the default profile's layer height for quality 0.5.
	float next_layer_height(const float print_z, float quality, size_t &current_facet);
    float horizontal_facet_distance(float z);

	struct FaceZ {
		std::pair<float, float> z_span;
		// Cosine of the normal vector towards the Z axis.
		float					n_cos;
		// Sine of the normal vector towards the Z axis.
		float					n_sin;
	};

protected:
	SlicingParameters 		m_slicing_params;

	std::vector<FaceZ>		m_faces;
>>>>>>> origin/merill-merge:src/libslic3r/SlicingAdaptive.hpp
};

}; // namespace Slic3r

#endif /* slic3r_SlicingAdaptive_hpp_ */
