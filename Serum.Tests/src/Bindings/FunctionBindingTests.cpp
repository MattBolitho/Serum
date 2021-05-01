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

		REQUIRE(binding.GetBindingKey() == BindingKey(typeid(int), name));
		REQUIRE(binding.GetBindingType() == BindingType::Function);
	}

	TEST_CASE("FunctionBinding_ResolvesCorrectly")
	{
		TestType testValue = { 4, true, "test" };
		auto binding = FunctionBinding<TestType>([&]() { return testValue; });
		auto context = ResolutionContext();

		auto result = binding.Resolve(context);

		REQUIRE(testValue == result);
	}
}
