#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string>
#include "../lib/big_integer.h"


// big_integer* diget_new()
// {
// 	return new big_integer();
// }

TEST_CASE( "Test functions dig_init, to_str of class big_integer.", "[big-integer-functions]" ){
	SECTION("big_integer init default to null")
	{
		CHECK(big_integer().to_str() == "0");
	}

	SECTION("Init big_integer and return how text")
	{
		CHECK(big_integer("1234567").to_str() == "1234567");
	}
}