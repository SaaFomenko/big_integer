#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <cstring>
#include "../lib/big_integer.h"


static const char* null_str = "0";
static const char* a_str = "114575"; 
static const char* b_str = "78524"; 
static const char* sum_str = "193099"; 
static const char* mult_str = "8996887300"; 

TEST_CASE( "Test functions dig_init, to_str of class big_integer.", "[big-integer-functions]" ){
	SECTION("big_integer init default to null")
	{
		auto a = big_integer();
		bool equal = strncmp(
			a.to_str(), 
			null_str, 
			a.len()
		) == 0;
		CHECK(equal);
	}

	SECTION("Init big_integer and return how text")
	{
		auto b = big_integer(b_str);
		bool equal = strncmp(
			b.to_str(), 
			b_str,
			b.len()
		) == 0;
		CHECK(equal);
	}
}

TEST_CASE("Test operators +, * of class big_integer.", "[big-integer-operators]"){
	SECTION("test operator +")
	{
		big_integer a(a_str);
		big_integer b(b_str);
		big_integer result = a + b;

		bool equal = strncmp(result.to_str(), sum_str, result.len()) == 0;
		CHECK(equal);
	}

	SECTION("test operator *")
	{
		big_integer a(a_str);
		big_integer b(b_str);
		big_integer result = a * b;

		bool equal = strncmp(result.to_str(), mult_str, result.len()) == 0;
		CHECK(equal);
	}

}