/// @file ConstantBindingTests.cpp
/// Unit tests for the ConstantBinding type.

#include "catch.hpp"
#include "Serum/Serum.hpp"
#include "Serum.Tests/TestType.hpp"

namespace Serum::Bindings::ConstantBindingTests
{
	TEST_CASE("ConstantBinding_ConstructorCorrectlyIntializesMembers")
	{
		std::string const name = "Test Name";

		auto binding = ConstantBinding<int>(4, name);

		REQUIRE(binding.GetName() == name);
		REQUIRE(binding.GetBindingType() == BindingType::Constant);
		REQUIRE(binding.GetTypeIndex() == typeid(int));
	}

	TEST_CASE("ConstantBinding_ResolvesCorrectly")
	{
		TestType const testValue = { 4, true, "test" };
		auto binding = ConstantBinding<TestType>(testValue);

		auto result = binding.Resolve();

		REQUIRE(testValue == result);
	}
}
