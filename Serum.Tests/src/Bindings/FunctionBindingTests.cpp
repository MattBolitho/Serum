/// @file FunctionBindingTests.cpp
/// Unit tests for the FunctionBinding type.

#include "catch.hpp"
#include "Serum/Serum.hpp"
#include "Serum.Tests/TestType.hpp"

namespace Serum::Bindings::FunctionBindingTests
{
	TEST_CASE("FunctionBinding_ConstructorCorrectlyIntializesMembers")
	{
		std::string const name = "Test Name";

		auto binding = FunctionBinding<int>([]() { return 3; }, name);

		REQUIRE(binding.GetName() == name);
		REQUIRE(binding.GetBindingType() == BindingType::Function);
		REQUIRE(binding.GetTypeIndex() == typeid(int));
	}

	TEST_CASE("FunctionBinding_ResolvesCorrectly")
	{
		TestType testValue = { 4, true, "test" };
		auto binding = FunctionBinding<TestType>([&]() { return testValue; });

		auto result = binding.Resolve();

		REQUIRE(testValue == result);
	}
}
