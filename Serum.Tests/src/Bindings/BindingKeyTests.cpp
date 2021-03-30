/// @file BindingKeyTests.cpp
/// Unit tests for the BindingKey type.

#include <sstream>
#include "catch.hpp"
#include "Serum/Bindings/BindingKey.hpp"

namespace Serum::Bindings::BindingKeyTests
{
	TEST_CASE("BindingKey_Constructor_CorrectlyInitializesMembers")
	{
		const std::type_index requestType = typeid(int);
		const std::string name = "Test Name";

		auto bindingKey = BindingKey(requestType, name);

		REQUIRE(requestType == bindingKey.GetRequestType());
		REQUIRE(name == bindingKey.GetName());
	}

	TEST_CASE("BindingKey_LessThan")
	{
		const auto key1 = BindingKey(typeid(int), "test");
		const auto key2 = BindingKey(typeid(bool), "");

		SECTION("WhenEqual_ReturnsFalseInBothCases")
		{
			REQUIRE_FALSE(key1 < key1);
			REQUIRE_FALSE(key2 < key2);
		}

		SECTION("WhenDifferent_IsStrictOrdering")
		{
			REQUIRE(key1 < key2);
			REQUIRE_FALSE(key2 < key1);
		}
	}

	TEST_CASE("BindingKey_ostreamOperator<<_StreamsCorrectValue")
	{
		std::stringstream stringStream;
		const std::string expected = "[int, test]";
		const auto bindingKey = BindingKey(typeid(int), "test");

		stringStream << bindingKey;

		REQUIRE(expected == stringStream.str());
	}
}
