
#include <iostream>

#include <cstring>
#include <cstdlib>
#include <ctime>

#include "DLA.h"
#include "Walk.h"
#include "Lattice.h"

#define DEFAULT_LENGTH 200000 // default walk length

const std::string USAGE = "walkrun [length] -a -s --3D --hex"
    " -d [num-distances] --DLA "
    " --lineDLA --linewidth [width] --fractal --stickiness [s] --silent";


int main(int argc, char *argv[])
{
    int walk_length = DEFAULT_LENGTH;

    bool accumulate = false;

    bool distance = false;
    int distance_count = 10;

    bool square = false;

    bool simplecubic = false;
    bool hexagonal = false;

    bool pointDLA = false;
    bool lineDLA = false;

    int line_width = 100;

    double stickiness = 1;

    bool fractal_dimension = false;

    bool suppress_output = false;

    /* Parse all the command-line args */
    for (int n = 1; n < argc; ++n) {
        if (!std::strcmp(argv[n], "-a")) {
            accumulate = true;
        } else if (!std::strcmp(argv[n], "-s")) {
            square = true;
	} else if (!std::strcmp(argv[n], "--3D")) {
	    simplecubic = true;
	} else if (!std::strcmp(argv[n], "--hex")) {
	    hexagonal = true;
        } else if (!std::strcmp(argv[n], "-d")) {
            distance = true;

	    /* If not on last arg */
	    if (n != argc - 1)
		distance_count = std::atof(argv[++n]);
        } else if (!std::strcmp(argv[n], "--DLA")) {
            pointDLA = true;
        } else if (!std::strcmp(argv[n], "--lineDLA")) {
            lineDLA = true;
	} else if (!std::strcmp(argv[n], "--linewidth")) {
	    line_width = std::atof(argv[++n]);
        } else if (!std::strcmp(argv[n], "--stickiness")) {
            stickiness = std::atof(argv[++n]);
        } else if (!std::strcmp(argv[n], "--fractal")) {
            fractal_dimension = true;
	} else if (!std::strcmp(argv[n], "--silent")) {
	    suppress_output = true;
        } else if (!(walk_length = std::atoi(argv[n]))) {
            std::cout << USAGE << std::endl;
            return -1;
        }
    }

    // Use 3D lattice
    if (simplecubic || hexagonal) {
	Lattice<3> lattice;

	if (simplecubic)
	    lattice = SimpleCubic();
	else if (hexagonal)
	    lattice = Hexagonal();

	/* Generate the random walk, applying the basis set */
	Walk<3> random_walk = Walk<3>(lattice).generate(walk_length).applyBasis();

	// TODO: Currently just copied from below...move it
	// Calculate and print the distance between the start and end point of the walk
	if (distance) {
	    // invariant: i random walk distances have been calculated
	    for (int i = 0; i < distance_count; ++i) {
		int distance = random_walk.getDistance();

		if (!suppress_output)
		    std::cout << distance << std::endl;

            random_walk.generate(walk_length).applyBasis();
	    }

	// Accumulate the vectors at each step
	} else if (accumulate) {
	    if (!suppress_output)
		std::cout << random_walk.accumulateVectors().toCSV() << std::endl;
	// Print out the vectors without accumulating them
	} else {
	    if (!suppress_output)
		std::cout << random_walk.toCSV() << std::endl;
	}

	return 0;
    } else {
	/* Use a 2D lattice */
	Lattice<2> lattice;

	if (square) {
	    lattice = SquareLattice();
	} else {
	    lattice = TriLattice();
	}

	// Generate a diffusion limited aggregation
	if (pointDLA) {
	    Walk<2> walk(lattice);
	    PointDLA dla(stickiness);

	    /* Generate until user manually stops it */
	    for (;;) {
		if (fractal_dimension) {
		    dla.simulateInRadius(walk);

		    // Output N vs. R
		    auto N = dla.getSeeds().size();
		    double R = dla.getFurthestRadius();

		    if (!suppress_output)
			std::cout << N << ", " << R << std::endl;
		} else {
		    Vector<2> point = dla.simulateInRadius(walk);

		    if (!suppress_output)
			std::cout << point << std::endl;
		}
	    }

	    return 0;
	}

	if (lineDLA) {
	    Walk<2> walk(lattice);

	    LineDLA dla(line_width, stickiness);

	    // Output the initial seeds (TODO: Don't do this here...)
	    for (int x = -line_width; x <= line_width; ++x) {
		if (!suppress_output)
		    std::cout << Vector<2>(2, (double)x, 0.0) << std::endl;
	    }

	    /* Generate until user manually stops it */
	    for (;;) {
		Vector<2> point = dla.simulate(walk);
		if (!suppress_output)
		    std::cout << point << std::endl;
	    }

	    return 0;
	}

	/* Generate the random walk, applying the basis set */
	Walk<2> random_walk = Walk<2>(lattice).generate(walk_length).applyBasis();

	// Calculate and print the distance between the start and end point of the walk
	if (distance) {
	    // invariant: i random walk distances have been calculated
	    for (int i = 0; i < distance_count; ++i) {
		int distance = random_walk.getDistance();

		if (!suppress_output)
		    std::cout << distance << std::endl;

		random_walk.generate(walk_length).applyBasis();
	    }
	// Accumulate the vectors at each step
	} else if (accumulate) {
	    if (!suppress_output)
		std::cout << random_walk.accumulateVectors().toCSV() << std::endl;
	// Print out the vectors without accumulating them
	} else {
	    if (!suppress_output)
		std::cout << random_walk.toCSV() << std::endl;
	}
    }

    return 0;
}
