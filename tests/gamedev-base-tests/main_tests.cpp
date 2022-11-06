//
// Created by robin on 26.10.22.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "Do nothing - Expect 42", "[test][nothing]" )
{
    int expected = 42;
    REQUIRE(expected == 42);
}