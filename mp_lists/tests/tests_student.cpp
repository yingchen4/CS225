#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case 1", "[Student]") {
List<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertBack(4);

    List<int> slist = list.split(0);
    stringstream s1, s2;

    list.print(s1);
    slist.print(s2);

    REQUIRE( "< >" == s1.str() );
    REQUIRE( "< 1 2 3 4 >" == s2.str() );
}
 
TEST_CASE("My Test Case 2", "[Student]") {
    List<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertBack(4);

    List<int> slist = list.split(4);
    stringstream s1, s2;

    list.print(s1);
    slist.print(s2);

    REQUIRE( "< 1 2 3 4 >" == s1.str() );
    REQUIRE( "< >" == s2.str() );
}

 
TEST_CASE("My Test Case 3", "[Student]") {
    List<int> list;

    List<int> slist = list.split(2);
    stringstream s1, s2;

    list.print(s1);
    slist.print(s2);

    REQUIRE( "< >" == s1.str() );
    REQUIRE( "< >" == s2.str() );
}


TEST_CASE("My Test Case 4", "[Student]") {
    List<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertBack(4);

    List<int> slist = list.split(6);
    stringstream s1, s2;

    list.print(s1);
    slist.print(s2);

    REQUIRE( "< 1 2 3 4 >" == s1.str() );
    REQUIRE( "< >" == s2.str() );
}