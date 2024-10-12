#ifndef WALK_H_
#define WALK_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Lattice.h"

// Global used just in this file
namespace WalkRNG {
    // Whether or not we've generated a new random seed since program start
    extern bool random_seeded;
};


/* Class to perform a random walk on an N-dimensional lattice */
template<unsigned int N>
class Walk : public std::vector<Vector<N> > {
public:
    Walk(Lattice<N> lattice) : lattice(lattice) {
        /* If we haven't seeded the RNG yet... */
        if (!WalkRNG::random_seeded) {
            std::srand((unsigned int)std::time(0));
            WalkRNG::random_seeded = true;
        }
    }

    /**
     * Generate random walk on the lattice of length `length` modifying in place
     * with non-basis transformed vectors and also returning the walk.
     * Clears the current walk.
     */
    Walk<N> &generate(int length) {
        this->clear();

        /* Get the new translation set for this lattice */
        std::vector<Vector<N> > translation_set = this->lattice.getTranslationSet();

        for (int i = 0; i < length; ++i) {
            /* Get random index for the translation_set */
            size_t random_index;
            random_index = std::rand() % translation_set.size();

            /* Get the element */
            Vector<N> random_element = translation_set.at(random_index);

            /* Add it to the walk */
            this->push_back(random_element);
        }

        return *this;
    }

    /**
     * Step walk for one iteration, returning single vector and adding to Walk.
     * Same as generate(int length) with a length == 1, and doesn't clear the walk.
     * Returns the generated Vector<N>
     */
    Vector<N> step() {
        std::vector<Vector<N> > translation_set = this->lattice.getTranslationSet();

        size_t random_index = std::rand() % translation_set.size();
        
        Vector<N> random_element = translation_set.at(random_index);

        this->push_back(random_element);

        return random_element;
    }

    /**
     * Apply this->lattice's basis to each vector in the walk
     */
    Walk &applyBasis() {
        for (size_t i = 0; i < this->size(); ++i) {
            this->at(i) = this->lattice.applyBasis(this->at(i));
        }

        return *this;
    }


    /**
     * Get distance between start and end points of walk
     */
    double getDistance() {
	    return this->getDistanceBetween(0, this->size());
    }

    /**
     * Get distance between inclusive point `start` and
     * exclusive point `end` of walk
     */
    double getDistanceBetween(size_t start, size_t end) {
        Vector<N> res;

        for (size_t i = start; i < end; ++i) {
            res += this->at(i);
        }

        return res.getMagnitude();
    }

    /**
     * Return new walk with each step added, so each step corresponds to the
     * current position on the lattice.
     */
    Walk<N> accumulateVectors()
    {
        Walk<N> walk(this->lattice);
        Vector<N> running_total = this->at(0);

        // Initial value 
        walk.push_back(running_total);

        /* Accumulate each vector to the running total, and push it
        * to the walk */
        for (size_t i = 1; i < this->size(); ++i) {
            running_total += this->at(i);
            walk.push_back(running_total);
        }

        return walk;
    }

    /**
     * Return as string of newline-seperated comma seperated rows
     * with first column as x-component, second column as y-component, etc.
     */
    std::string toCSV() {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    // Display each vector in walk, one on each line
    friend std::ostream& operator<<(std::ostream& os, const Walk<N> &walk) {
        for (size_t i = 0; i < walk.size(); ++i)
            os << walk.at(i) << std::endl;

        return os;
    }

private:
    Lattice<N> lattice;
};

#endif /* WALK_H_ */
