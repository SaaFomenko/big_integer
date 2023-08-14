#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <string>
#include "../lib/two_link_list.h"
#include "../lib/list_to_string.h"


List* list_new()
{
	return new List();
}

List* list_with_val(int val1 = 1, int val2 = 2, int val3 = 3)
{
	List* list1 = list_new();
	list1->PushFront(val1);
	list1->PushBack(val2);
	list1->PushBack(val3);

	return list1;
}

TEST_CASE( "Test functions Empty, Size, Clear of class List.", "[list-functions]" ){
	SECTION("list is empty")
	{
		CHECK(list_new()->Empty() == true);
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

TEST_CASE( "Test push and pop functions in class List.", "[list-push-pop]" ){

	List* list = list_new();
	list->PushBack(3);
	SECTION("push to back value in list")
	{
		CHECK(list->Size() == 1);
	}

	list->PushFront(2);
	SECTION("push to front value in list")
	{
		CHECK(list->Size() == 2);
	}

	int val = list->PopBack();
	SECTION("pop of back value in list")
	{
		CHECK(val == 3);
		CHECK(list->Size() == 1);
	}

	val = list->PopFront();
	SECTION("pop of front value in list")
	{
		CHECK(val == 2);
		CHECK(list->Size() == 0);
	}

	SECTION("pop back in empty list")
	{
		CHECK_THROWS_AS(list->PopBack(), std::runtime_error);
	}

	SECTION("pop front in empty list")
	{
			CHECK_THROWS_AS(list->PopFront(), std::runtime_error);
	}
}

TEST_CASE( "Test function list to string.", "[list-to-string]" ){

	List* list = list_new();
	const int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	const int size = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < size; ++i)
	{
		list->PushBack(arr[i]);
	}

	const std::string list_front = list_to_string(list);
	CHECK(list_front == "1 2 3 4 5 6 7 ");

	const std::string list_back = list_to_string(list, false);
	CHECK(list_back == "7 6 5 4 3 2 1 ");
}

int main(int argc, char* argv[])
{
	return Catch::Session().run(argc, argv);
}
