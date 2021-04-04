/// @file AnyBindingWrapperTests.cpp
/// Unit tests for the AnyBindingWrapper type.

#include "catch.hpp"
#include "Serum/Internal/AnyBindingWrapper.hpp"

namespace Serum::Internal::AnyBindingWrapperTests
{
	TEST_CASE("AnyBindingWrapper_FromConstantBinding")
	{
		SECTION("CanBeConvertedToConstantBinding")
		{
			constexpr auto expected = 2;
			auto constantBinding = Bindings::ConstantBinding<int>(expected);
			const auto wrapper = AnyBindingWrapper::FromConstantBinding(constantBinding);

			auto convertedBinding = wrapper.AsConstantBinding<int>();

			REQUIRE(constantBinding.Resolve() == convertedBinding.Resolve());
		}
	}

	TEST_CASE("AnyBindingWrapper_FromFunctionBinding")
	{
		SECTION("CanBeConvertedToFunctionBinding")
		{
			auto expected = []() { return 1; };
			auto constantBinding = Bindings::FunctionBinding<int>(expected);
			const auto wrapper = AnyBindingWrapper::FromFunctionBinding(constantBinding);

			auto convertedBinding = wrapper.AsFunctionBinding<int>();

			REQUIRE(constantBinding.Resolve() == convertedBinding.Resolve());
		}
	}
}
