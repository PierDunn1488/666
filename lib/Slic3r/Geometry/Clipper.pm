package Slic3r::Geometry::Clipper;
use strict;
use warnings;

require Exporter;
our @ISA = qw(Exporter);
<<<<<<< HEAD
<<<<<<< HEAD
our @EXPORT_OK = qw(offset offset_ex
    diff_ex diff union_ex intersection_ex JT_ROUND JT_MITER
    JT_SQUARE is_counter_clockwise union_pt offset2 offset2_ex
    intersection intersection_pl diff_pl union CLIPPER_OFFSET_SCALE
    union_pt_chained intersection_ppl);
=======
=======
>>>>>>> origin/merill-merge
our @EXPORT_OK = qw(
	offset offset2 
	offset_ex offset2_ex
    diff_ex diff union_ex intersection_ex 
    JT_ROUND JT_MITER JT_SQUARE 
    intersection intersection_pl diff_pl union);
<<<<<<< HEAD
>>>>>>> origin/merill-merge
=======
>>>>>>> origin/merill-merge

1;
