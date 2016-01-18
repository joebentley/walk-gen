walkrun
=======

This program can generate random walks on multiple different lattices, as well
as printing out the distances (from start and end of the walk). It can also
generate point and line Diffusion Limited Aggregations with the --DLA option, as
well as outputting (with --fractal) the number of seeds N versus the radius of
the structure. Finally a probability of sticking can be used, so the new seed
doesn't always stick. For more info see report.

The built-in lattice types are:

2d
--

* Triangular
* Square

3d
--

* Cubic (Square with (0, 0, 1), (0, 0, -1) vectors)
* Hexagonal (Triangular with (0, 0, 1), (0, 0, -1) vectors)


New lattices can be added in the Lattice.h file, which is quite easy, although
unfortunately the program isn't general enough to know this from walkrun.cpp, so
you will have to add your own command line argument to tell the program to use
the lattice, sorry!


Usage string:

 walkrun [length] -a -s --3D --hex -d [num-distances] --GSL --DLA --lineDLA
 --linewidth [width] --fractal --stickiness [s] --silent

For documentation of the command line arguments, see the short user guide in the
report.