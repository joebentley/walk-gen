#ifndef DLA_H_
#define DLA_H_

// http://paulbourke.net/fractals/dla/

// 2-dimensional DLAs

#include <vector>

#include "Vector.h"
#include "Walk.h"

/**
 * Base class of all Diffusion Limited Aggregations.
 *
 * Do a random walk until a particle comes close to ("sticks" to) any of the
 * current seeds, then we set it as a new seed, so that further particles we
 * introduce can "stick" to it.
 *
 * By doing this multiple times and then coloring all the seeds "black" on an
 * output image we can build up a diffusion limited aggregation.
 */
class DLA {
 public:
 DLA() : width(1000), height(1000), stickiness(1) { }
 DLA(double stickiness) : stickiness(stickiness) { } 
 DLA(int width, int height) : width(width), height(height), stickiness(1) { }
 DLA(int width, int height, double stickiness) : width(width), height(height), stickiness(stickiness) { }

    int getHeight() { return height; }
    void setHeight(int height) { this->height = height; }

    int getWidth() { return width; }
    void setWidth(int width) { this->width = width; }

    /* Return true if the point is within 1 pixel (cardinally or diagonally) of any seed */
    bool closeToSeed(Vector<2> point);

    /* Return all the current seeds of the DLA */
    std::vector<Vector<2> > getSeeds() { return seeds; }
    void addSeed(Vector<2> seed) { seeds.push_back(seed); }

    /*
     * Simulate once, returning Vector<2> of new seed, wrapping if particle leaves
     * x_boundary / 2 or y_boundary / 2 in either direction, assuming centered about (0, 0)
     *
     * Returns (0, 0) if there are no seeds currently
     */
    Vector<2> simulate(Vector<2> initial, Walk<2> &walk, int x_boundary, int y_boundary);
   
    // Same as above but using width as x_boundary and height as y_boundary
    Vector<2> simulate(Vector<2> initial, Walk<2> &walk);

    /* Use random Vector<2> in boundaries assuming centered at (0, 0)
     * Returns (0, 0) if there are no seeds currently */
    Vector<2> simulate(Walk<2> &walk);

 private:
    int width, height;

    std::vector<Vector<2> > seeds;

 protected:
    double stickiness;
};

/**
 * Class of DLAs with initial point seed at (0, 0)
 */
class PointDLA : public DLA {
 public:
 PointDLA() : DLA(), init_radius(10), furthest_radius(0) { addSeed(Vector<2>(0, 0)); }
 PointDLA(double stickiness)
     : DLA(stickiness), init_radius(10), furthest_radius(0) { addSeed(Vector<2>(0, 0)); }
 PointDLA(int init_radius, double stickiness)
     : DLA(stickiness), init_radius(init_radius), furthest_radius(0) { addSeed(Vector<2>(0, 0)); }

    // Get radius of structure by calculating directly (SLOWER)
    double getStructureRadius();

    /**
     * Get the furthest outwards radius, like getStructureRadius(), but instead
     * keeping a running total that is updated by simulateInRadius(Walk<2>, int) */
    double getFurthestRadius() { return furthest_radius; }

    /**
     * Use random Vector<2> on a circle with radius `init_radius`
     * Update furthest_radius if this new point is further away
     */
    Vector<2> simulateInRadius(Walk<2> &walk, int init_radius);

    /**
     * Same as above, with the radius `init_radius` set to getFurthestRadius() + 50
     * or this->init_radius + 50, whichever is larger */
    Vector<2> simulateInRadius(Walk<2> &walk);

 private:
    int init_radius;
    double furthest_radius;
};


/**
 * Class of DLAs with line seeds at y = 0 from x = -width to width
 *
 * So (badly named) width is actually half width
 */
class LineDLA : public DLA {
 public:
 LineDLA() : DLA(200, 0), min_y(0) { init(); }
 LineDLA(double stickiness) : DLA(200, 0, stickiness), min_y(0) { init(); }
 LineDLA(int width, double stickiness) : DLA(width, 0, stickiness), min_y(0) { init(); }

    /**
     * Add initial line of seeds */
    void init();

    /**
     * Get seed with minimum y value */
    int getHighestPoint() { return min_y; }

    /**
     * Simulate once, if the new seed is less than the current highest point,
     * set min_y */
    Vector<2> simulate(Walk<2> &walk);
 private:
    int min_y;
};

#endif /* DLA_H_ */
