#ifndef slic3r_CoolingBuffer_hpp_
#define slic3r_CoolingBuffer_hpp_

<<<<<<< HEAD
#include "libslic3r.h"
#include "GCode.hpp"
=======
#include "../libslic3r.h"
>>>>>>> origin/merill-merge
#include <map>
#include <string>

namespace Slic3r {

<<<<<<< HEAD
/*
A standalone G-code filter, to control cooling of the print.
The G-code is processed per layer. Once a layer is collected, fan start / stop commands are edited
and the print is modified to stretch over a minimum layer time.
*/

class CoolingBuffer {
    public:
    CoolingBuffer(GCode &gcodegen)
        : _gcodegen(&gcodegen), _elapsed_time(0.), _elapsed_time_bridges(0.),
          _elapsed_time_external(0.), _layer_id(0)
    {
        this->_min_print_speed = this->_gcodegen->config.min_print_speed * 60;
    };
    std::string append(const std::string &gcode, std::string obj_id, size_t layer_id, float print_z);
    std::string flush();
    GCode* gcodegen() { return this->_gcodegen; };
    
    private:
    GCode*                      _gcodegen;
    std::string                 _gcode;
    float                       _elapsed_time;
    float                       _elapsed_time_bridges;
    float                       _elapsed_time_external;
    size_t                      _layer_id;
    std::map<std::string,float> _last_z;
    float                       _min_print_speed;
};

#ifdef SLIC3R_TEST
void apply_speed_factor(std::string &line, float speed_factor, float min_print_speed);
#endif
=======
class GCode;
class Layer;
struct PerExtruderAdjustments;

// A standalone G-code filter, to control cooling of the print.
// The G-code is processed per layer. Once a layer is collected, fan start / stop commands are edited
// and the print is modified to stretch over a minimum layer time.
//
// The simple it sounds, the actual implementation is significantly more complex.
// Namely, for a multi-extruder print, each material may require a different cooling logic.
// For example, some materials may not like to print too slowly, while with some materials 
// we may slow down significantly.
//
class CoolingBuffer {
public:
    CoolingBuffer(GCode &gcodegen);
    void        reset();
    void        set_current_extruder(unsigned int extruder_id) { m_current_extruder = extruder_id; }
    /// process the laer :check the time and apply fan / speed change
    /// append_time_only: if he layer is only support, then you can put this at true to not process the layer but just append its time to the next one.
    std::string process_layer(const std::string &gcode, size_t layer_id, bool append_time_only = false);
    GCode* 	    gcodegen() { return &m_gcodegen; }

private:
	CoolingBuffer& operator=(const CoolingBuffer&) = delete;
    std::vector<PerExtruderAdjustments> parse_layer_gcode(const std::string &gcode, std::vector<float> &current_pos) const;
    float       calculate_layer_slowdown(std::vector<PerExtruderAdjustments> &per_extruder_adjustments);
    // Apply slow down over G-code lines stored in per_extruder_adjustments, enable fan if needed.
    // Returns the adjusted G-code.
    std::string apply_layer_cooldown(const std::string &gcode, size_t layer_id, float layer_time, std::vector<PerExtruderAdjustments> &per_extruder_adjustments);

    GCode&              m_gcodegen;
    std::string         m_gcode;
    // Internal data.
    // X,Y,Z,E,F
    std::vector<char>   m_axis;
    std::vector<float>  m_current_pos;
    unsigned int        m_current_extruder;

    //saved previous unslowed layer 
    std::map<size_t, float> saved_layer_time_support;
    std::map<size_t, float> saved_layer_time_object;


    // Old logic: proportional.
    bool                m_cooling_logic_proportional = false;
};
>>>>>>> origin/merill-merge

}

#endif
