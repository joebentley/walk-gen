#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Vector.h"

TEST_CASE( "2-vectors work", "[Vector<2>]" ) {
    Vector<2> v(2, 1.0 , 2.0);
    Vector<2> v2(2, 3.0, 4.0);

    REQUIRE( v.get(0) == 1.0 );
    REQUIRE( v.get(1) == 2.0 );

    SECTION( "setting and getting components" ) {
	v.set(0, 4.0);
	v.set(1, 2.3);

	REQUIRE( v.get(0) == 4.0);
	REQUIRE( v.get(1) == 2.3);
    }

    SECTION( "calculating magnitude" ) {
	REQUIRE( v2.getMagnitude() == 5.0 );
    }

    SECTION( "adding and subtracting vectors" ) {
	Vector<2> v3 = v + v2;
	Vector<2> v4 = v - v2;

	REQUIRE( v3.get(0) == 4.0 );
	REQUIRE( v3.get(1) == 6.0 );
	REQUIRE( v4.get(0) == -2.0 );
	REQUIRE( v4.get(1) == -2.0 );
    }

    SECTION( "multiplication" ) {
	Vector<2> v3 = v * v2;
	REQUIRE( v3.get(0) == 3.0 );
	REQUIRE( v3.get(1) == 8.0 );
    }

    SECTION( "equality" ) {
	Vector<2> v3(2, 1.0, 2.0);

	REQUIRE( v == v3 );
    }

    SECTION( "compound operators" ) {
	v += v2;
	REQUIRE( v.get(0) == 4.0 );
	REQUIRE( v.get(1) == 6.0 );
	v -= v2;
	REQUIRE( v.get(0) == 1.0 );
	REQUIRE( v.get(1) == 2.0 );
	v *= v2;
	REQUIRE( v.get(0) == 3.0 );
	REQUIRE( v.get(1) == 8.0 );
    }

    SECTION( "test approx equal" ) {
	Vector<2> v3(2, 1.03, 1.98);

	REQUIRE( v3.approxEqual(v) );
	REQUIRE( v.approxEqual(v3) );
	REQUIRE( !v.approxEqual(v2) );
    }

}

TEST_CASE( "3-vectors work", "[Vector<3>]" ) {
    Vector<3> v(3, 1.0 , 2.0, 8.0);
    Vector<3> v2(3, 3.0, 4.0, 0.0);

    REQUIRE( v.get(0) == 1.0 );
    REQUIRE( v.get(1) == 2.0 );
    REQUIRE( v.get(2) == 8.0 );

    SECTION( "setting and getting components" ) {
	v.set(0, 4.0);
	v.set(1, 2.3);
	v.set(2, 2.9);

	REQUIRE( v.get(0) == 4.0 );
	REQUIRE( v.get(1) == 2.3 );
	REQUIRE( v.get(2) == 2.9 );
    }

    SECTION( "calculating magnitude" ) {
	REQUIRE( v2.getMagnitude() == 5.0 );
    }

    SECTION( "adding and subtracting vectors" ) {
	Vector<3> v3 = v + v2;
	Vector<3> v4 = v - v2;

	REQUIRE( v3.get(0) == 4.0 );
	REQUIRE( v3.get(1) == 6.0 );
	REQUIRE( v3.get(2) == 8.0 );
	REQUIRE( v4.get(0) == -2.0 );
	REQUIRE( v4.get(1) == -2.0 );
	REQUIRE( v4.get(2) == 8.0 );
    }

    SECTION( "multiplication" ) {
	Vector<3> v3 = v * v2;
	REQUIRE( v3.get(0) == 3.0 );
	REQUIRE( v3.get(1) == 8.0 );
	REQUIRE( v3.get(2) == 0.0 );
    }

    SECTION( "equality" ) {
	Vector<3> v3(3, 1.0, 2.0, 8.0);

	REQUIRE( v == v3 );
    }

    SECTION( "compound operators" ) {
	v += v2;
	REQUIRE( v.get(0) == 4.0 );
	REQUIRE( v.get(1) == 6.0 );
	REQUIRE( v.get(2) == 8.0 );
	v -= v2;
	REQUIRE( v.get(0) == 1.0 );
	REQUIRE( v.get(1) == 2.0 );
	REQUIRE( v.get(2) == 8.0 );
	v *= v2;
	REQUIRE( v.get(0) == 3.0 );
	REQUIRE( v.get(1) == 8.0 );
	REQUIRE( v.get(2) == 0.0 );
    }

    SECTION( "test approx equal" ) {
	Vector<3> v3(3, 1.03, 1.98, 8.04);

	REQUIRE( v3.approxEqual(v) );
	REQUIRE( v.approxEqual(v3) );
	REQUIRE( !v.approxEqual(v2) );
    }

}
