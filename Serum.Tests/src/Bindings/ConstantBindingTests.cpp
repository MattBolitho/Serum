/// @file ConstantBindingTests.cpp
/// Unit tests for the ConstantBinding type.

#include "catch.hpp"
#include "Serum/Bindings/ConstantBinding.hpp"

namespace Serum::Bindings::ConstantBindingTests
{
	struct TestType final
	{
		int intValue = 0;
		bool boolValue = false;
		std::string stringValue = "";

		bool operator==(const TestType& other) const
		{
			return intValue == other.intValue
				&& boolValue == other.boolValue
				&& stringValue == other.stringValue;
		}
	};

	TEST_CASE("ConstantBinding_ConstructorCorrectlyIntializesMembers")
	{
		const std::string name = "Test Name";

		auto binding = ConstantBinding<int>(4, name);

		REQUIRE(binding.GetName() == name);
		REQUIRE(binding.GetBindingType() == BindingType::Constant);
		REQUIRE(binding.GetTypeIndex() == typeid(int));
	}

	TEST_CASE("ConstantBinding_ResolvesCorrectly")
	{
		const TestType testValue = { 4, true, "test" };
		auto binding = ConstantBinding<TestType>(testValue);

		auto result = binding.Resolve();

		REQUIRE(testValue == result);
	}
}
