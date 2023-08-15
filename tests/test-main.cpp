#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string>
#include "../lib/big_integer.h"


big_integer* diget_new()
{
	return new big_integer();
}

TEST_CASE( "Test functions dig_init, to_str of class big_integer.", "[big-integer-functions]" ){
	SECTION("big_integer init")
	{
		CHECK(big_integer().to_str() == "0");
	}

	List* list = list_with_val();
	SECTION("list size")
	{
		CHECK(list->Size() == 3);
	}

	SECTION("list clear")
	{
		list->Clear();
		CHECK(list->Size() == 0);
	}
}