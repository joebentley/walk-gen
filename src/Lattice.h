#ifndef LATTICE_H_
#define LATTICE_H_

#include <cmath>
#include <map>
#include <vector>
#include "Vector.h"

/* N-dimensional lattice */
template<unsigned int N>
class Lattice {
public:
    Lattice() { ndimensions = N; }
    
    /* An N-dimensional lattice basis vector expressed in cartesian coordinates */
    typedef Vector<N> Basis;

    Basis getBasis() { return basis; }
    std::vector<Basis> getTranslationSet() { return translations; }

    /**
     * Apply basis set to given vector to transform it into the lattice
     */
    Basis applyBasis(Vector<N> vector) {
		return vector * getBasis();
    }
protected:
    // Number of dimensions of basis
    int ndimensions;
    
    // Basis set
    Basis basis;

    // Expressed in units of basis
    std::vector<Basis> translations;
};

class TriLattice : public Lattice<2> {
public:
    TriLattice() { ndimensions = 2; init(); }

private:
    void init() {
		basis = Vector<2>(2, 1.0, std::sqrt(3) / 2.);

		translations.push_back(Vector<2>(2, -0.5, 1.0));     //  a
		translations.push_back(Vector<2>(2, 0.5, -1.0));     // -a
		translations.push_back(Vector<2>(2, 0.5, 1.0));      //  b
		translations.push_back(Vector<2>(2, -0.5, -1.0));    // -b
		translations.push_back(Vector<2>(2, 1.0, 0.0));      //  c
		translations.push_back(Vector<2>(2, -1.0, 0.0));     // -c
    }
};

class SquareLattice : public Lattice<2> {
public:
    SquareLattice() { ndimensions = 2; init(); }

private:
    void init() {
		basis = Vector<2>(2, 1.0, 1.0);

		translations.push_back(Vector<2>(2, 0.0, 1.0));     //  a
		translations.push_back(Vector<2>(2, 0.0, -1.0));    // -a
		translations.push_back(Vector<2>(2, 1.0, 0.0));     //  b
		translations.push_back(Vector<2>(2, -1.0, 0.0));    // -b
    }
};

class SimpleCubic : public Lattice<3> {
public:
    SimpleCubic() { ndimensions = 3; init(); }

private:
    void init() {
		basis = Vector<3>(3, 1.0, 1.0, 1.0);

		translations.push_back(Vector<3>(3, 0.0, 1.0, 0.0));     //  a
		translations.push_back(Vector<3>(3, 0.0, -1.0, 0.0));    // -a
		translations.push_back(Vector<3>(3, 1.0, 0.0, 0.0));     //  b
		translations.push_back(Vector<3>(3, -1.0, 0.0, 0.0));    // -b
		translations.push_back(Vector<3>(3, 0.0, 0.0, 1.0));     //  c
		translations.push_back(Vector<3>(3, 0.0, 0.0, -1.0));    // -c
    }
};

class Hexagonal : public Lattice<3> {
public:
    Hexagonal() { ndimensions = 3; init(); }

private:
    void init() {
		basis = Vector<3>(3, 1.0, std::sqrt(3) / 2.0, 1.0);

		translations.push_back(Vector<3>(3, -0.5, 1.0, 0.0));     //  a
		translations.push_back(Vector<3>(3, 0.5, -1.0, 0.0));     // -a
		translations.push_back(Vector<3>(3, 0.5, 1.0, 0.0));      //  b
		translations.push_back(Vector<3>(3, -0.5, -1.0, 0.0));    // -b
		translations.push_back(Vector<3>(3, 1.0, 0.0, 0.0));      //  c
		translations.push_back(Vector<3>(3, -1.0, 0.0, 0.0));     // -c
		translations.push_back(Vector<3>(3, 0.0, 0.0, 1.0));      //  d
		translations.push_back(Vector<3>(3, 0.0, 0.0, -1.0));     // -d
    }
};

#endif /* LATTICE_H_ */

