/// @file BindingKeyTests.cpp
/// Unit tests for the BindingKey type.

#include <sstream>
#include "catch.hpp"
#include "Serum/Serum.hpp"

namespace Serum::Bindings::BindingKeyTests
{
	TEST_CASE("BindingKey_Constructor_CorrectlyInitializesMembers")
	{
		std::type_index const requestType = typeid(int);
		std::string const name = "Test Name";

		auto bindingKey = BindingKey(requestType, name);

		REQUIRE(requestType == bindingKey.GetRequestType());
		REQUIRE(name == bindingKey.GetName());
	}

	TEST_CASE("BindingKey_ostreamOperator<<_StreamsCorrectValue")
	{
		std::stringstream stringStream;
		std::stringstream expectedStringStream;
		std::string const expected = "[int, \"test\"]";
		expectedStringStream << "[" << typeid(int).name() << ", \"test\"]";
		auto const bindingKey = BindingKey(typeid(int), "test");

		stringStream << bindingKey;

		REQUIRE(expectedStringStream.str() == stringStream.str());
	}
}
