
#include "Walk.h"
#include "DLA.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>

#include <iostream>


bool DLA::closeToSeed(Vector<2> point)
{
    // Check if a seed is close to another seed
    for (size_t i = 0; i < seeds.size(); ++i) {
        if ((seeds.at(i) - point).getMagnitude() < 1.5) {
            return true;
        }
    }

    return false;
}

Vector<2> DLA::simulate(Vector<2> initial, Walk<2> &walk, int x_boundary, int y_boundary)
{
    // If there are no seeds, don't do anything, or else we'll just loop infinitely
    if (seeds.size() == 0) {
        return Vector<2>(2, 0.0, 0.0);
    }

    Vector<2> current = initial;

    // Run a random walk until it sticks
    for (;;) {
        // Add the next step in random walk
        current += walk.step();

        // Check if close to seed
        if (closeToSeed(current)) {
            // Stick immediately if stickiness == 1
            if (stickiness == 1) {
                addSeed(current);
                return current;
            }
            
            // Else use the probability
            double r = std::rand() / (double)RAND_MAX;
            // std::cout << "s = " << stickiness << " r = " << r << std::endl;

            if (r < stickiness) {
                addSeed(current);
                return current;
            }
        }

        // Wrap around if it goes outside
        if (current.get(0) > (x_boundary / 2))
            current.set(0, -x_boundary / 2);
        else if (current.get(0) < (-x_boundary / 2))
            current.set(0, x_boundary / 2);

        if (current.get(1) > (y_boundary / 2))
            current.set(1, -y_boundary / 2);
        else if (current.get(1) < (-y_boundary / 2))
            current.set(1, y_boundary / 2);
    }
}

Vector<2> DLA::simulate(Vector<2> initial, Walk<2> &walk)
{
    return simulate(initial, walk, width, height);
}

Vector<2> DLA::simulate(Walk<2> &walk)
{
    /* Generate two random points within the rectangle with width `width`
     * and height `height */
    int u1 = std::rand();
    int u2 = std::rand();
    
    int rand_x = (u1 % width) - (width / 2);
    int rand_y = (u2 % height) - (height / 2);

    // Generate
    return simulate(Vector<2>(2, (double)rand_x, (double)rand_y), walk);
}


double PointDLA::getStructureRadius()
{
    /* Loop through all of the seeds finding the max distance from center */
    double max_distance = 0;

    Vector<2> initial(2, 0.0, 0.0);

    for (size_t i = 0; i < getSeeds().size(); ++i) {
        Vector<2> seed = getSeeds().at(i);

        double radius = (initial - seed).getMagnitude();
        if (radius > max_distance) {
            max_distance = radius;
        }
    }

    return max_distance;
}

Vector<2> PointDLA::simulateInRadius(Walk<2> &walk, int init_radius)
{
    /* Generate new point on the radius of a circle with init_radius */
    double angle = ((double)std::rand() / RAND_MAX) * (2 * M_PI);

    int x = (int)(init_radius * std::cos(angle));
    int y = (int)(init_radius * std::sin(angle));

    // Calculate boundary distance based on hypotenuse of triangle
    // with opposite and adjacent of the radius (plus a fudge factor)
    int boundary_distance = (int)(std::sqrt(2) * (init_radius + 50));

    Vector<2> current(2, (double)x, (double)y);

    Vector<2> newSeed = simulate(current, walk, boundary_distance, boundary_distance);

    // Check if new furthest seed
    if (newSeed.getMagnitude() > furthest_radius)
        furthest_radius = newSeed.getMagnitude();

    return newSeed;
}

Vector<2> PointDLA::simulateInRadius(Walk<2> &walk)
{
    /* Use whichever is greater out of the initial buffer radius,
     * and the current furthest radius */
    int init = (double)getFurthestRadius() > init_radius ?
	getFurthestRadius() : init_radius;

    return simulateInRadius(walk, init + 50);
}


void LineDLA::init()
{
    // Draw an initial straight line at (x, 0) for a range of x values from
    // -width to width
    for (int x = -getWidth(); x <= getWidth(); ++x)
        addSeed(Vector<2>(2, (double)x, 0.0));
}

Vector<2> LineDLA::simulate(Walk<2> &walk)
{
    const int width = getWidth();

    int x = (std::rand() % (width * 2)) - width;

    //int y = -std::abs(std::rand() % (std::abs(min_y) + 50));
    int y = min_y - 50;

    Vector<2> current(2, (double)x, (double)y);

    /* We reimplement the simulate function here because we need to alter
     * the way that we calculated the boundaries. */

    // Generate until we hit another particle
    for (;;) {
        current += walk.step();

        // Check if close to seed
        if (closeToSeed(current)) {
            // Stick immediately if stickiness == 1
            if (stickiness == 1) {
                addSeed(current);

                // See if the new seed is the highest yet
                if (current.get(1) < min_y)
                    min_y = current.get(1);

                return current;
            }
            
            // Else use the probability
            double r = std::rand() / RAND_MAX;
            
            if (r < stickiness) {
                addSeed(current);

                // See if the new seed is the highest yet
                if (current.get(1) < min_y)
                    min_y = current.get(1);

                return current;
            }
        }


        // Wrap around if it goes outside width
	if (current.get(0) > width)
	    current.set(0, -width);
	if (current.get(0) < -width)
	    current.set(0, width);

        // "Push it back" if it gets too far
	if (current.get(1) < min_y - 50)
	    current.set(1, min_y - 10);
    }
}
