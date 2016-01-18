#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstdarg>
#include <iostream>
#include <cmath>
#include <stdexcept>

/* This is implemented in the header since it is a template class
 * and hence we wouldn't be able to access N in the cpp file */

/* N-dimensional Vector class */
template<unsigned int N>
class Vector {
 private:
    double x[N]; // Components of N-dimensional vector
 public:
    /* Initialize components to zero by default */
    Vector() {
	for (int i = 0; i < N; ++i)
	    x[i] = 0.0;
    }

    /**
     * Set the first n components of the vector to the first n varargs
     * Throw out_of_range error if n > N */
    Vector(int n, ...) {
	if (n > N)
	    throw std::out_of_range("input n is greater than number of dimensions");
	
	std::va_list arg_list;
	va_start(arg_list, n);

	for (int i = 0; i < n; ++i)
	    x[i] = va_arg(arg_list, double);

	va_end(arg_list);
    }

    /**
     * Get the i-th component of the vector
     * throw out_of_range error if i > N */
    double get(unsigned int i) {
	if (i >= N)
	    throw std::out_of_range("");
    
	return x[i];
    }

    /**
     * Set the i-th component of the vector to v
     * throw out_of_range error if i > N */
    void set(unsigned int i, double v) {
	if (i >= N)
	    throw std::out_of_range("");

	x[i] = v;
    }

    /**
     * Return magnitude of the vector, i.e. sqrt(sum_{i=1}^N of x_i^2) */
    double getMagnitude() const {
	double magnitude = 0.0;

	for (int i = 0; i < N; ++i)
	    magnitude += x[i] * x[i];

	return std::sqrt(magnitude);
    }

    /**
     * Is the magnitude of this vector within 0.1 of the other vector? */
    bool approxEqual(const Vector<N>& other) const {
	return (*this - other).getMagnitude() < 0.1;
    }

    /**
     * Add two vectors component-wise */
    friend Vector<N> operator+(const Vector<N>& lhs, const Vector<N>& rhs) {
	Vector<N> v;

	for (int i = 0; i < N; ++i)
	    v.x[i] = lhs.x[i] + rhs.x[i];

	return v;
    }

    /**
     * Subtract two vectors component-wise */
    friend Vector<N> operator-(const Vector<N>& lhs, const Vector<N>& rhs) {
	Vector<N> v;

	for (int i = 0; i < N; ++i)
	    v.x[i] = lhs.x[i] - rhs.x[i];

	return v;
    }

    /**
     * Component-wise equality check */
    friend bool operator==(const Vector<N>& lhs, const Vector<N>& rhs) {
	for (int i = 0; i < N; ++i)
	    if (lhs.x[i] != rhs.x[i])
		return false;

	return true;
    }

    /**
     * Component-wise multiplication */
    friend Vector<N> operator*(const Vector<N>& lhs, const Vector<N>& rhs) {
	Vector<N> v;

	for (int i = 0; i < N; ++i)
	    v.x[i] = lhs.x[i] * rhs.x[i];

	return v;
    }

    /**
     * Print to output stream as comma seperated components */
    friend std::ostream& operator<<(std::ostream &os, const Vector<N> &vec) {
	for (int i = 0; i < N - 1; ++i)
	    os << vec.x[i] << ", ";

	os << vec.x[N - 1];
	return os;
    }

    /**
     * Compound operators
     */
    Vector<N>& operator+=(const Vector<N> &v2) {
	*this = *this + v2;
	return *this;
    }

    Vector<N>& operator-=(Vector<N> &v2) {
	*this = *this - v2;
	return *this;
    }

    Vector<N>& operator*=(Vector<N> &v2) {
	*this = *this * v2;
	return *this;
    }
};


#endif /* VECTOR_H_ */
