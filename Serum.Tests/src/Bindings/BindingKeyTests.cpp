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

	TEST_CASE("BindingKey_ostreamOperator<<_StreamsCorrectValue")
	{
		std::stringstream stringStream;
		std::stringstream expectedStringStream;
		const std::string expected = "[int, \"test\"]";
		expectedStringStream << "[" << typeid(int).name() << ", \"test\"]";
		const auto bindingKey = BindingKey(typeid(int), "test");

		stringStream << bindingKey;

		REQUIRE(expectedStringStream.str() == stringStream.str());
	}
}
