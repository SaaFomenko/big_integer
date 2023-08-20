#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <cstring>
#include "../lib/big_integer.h"


static const char* null_str = "0";
static const char* big_int_test = "1234567" 

TEST_CASE( "Test functions dig_init, to_str of class big_integer.", "[big-integer-functions]" ){
	SECTION("big_integer init default to null")
	{
		bool equal = strncmp(
			big_integer().to_str(), 
			null_str, 
			big_integer.str_size()
		) == 0;
		CHECK(equal);
	}

	SECTION("Init big_integer and return how text")
	{
		bool equal = strncmp(
			big_integer(big_int_test).to_str(), 
			big_int_test,
			big_integer.str_size()
		) == 0;
		CHECK(equal);
	}
}