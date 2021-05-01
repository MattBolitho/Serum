/// @file AnyBindingWrapperTests.cpp
/// Unit tests for the AnyBindingWrapper type.

#include "catch.hpp"
#include "Serum/Serum.hpp"

namespace Serum::Internal::AnyBindingWrapperTests
{
	TEST_CASE("AnyBindingWrapper_FromFunctionBinding")
	{
		SECTION("CanBeConvertedToFunctionBinding")
		{
			auto expected = []() { return 1; };
			auto context = ResolutionContext();
			auto constantBinding = Bindings::FunctionBinding<int>(expected);
			auto const wrapper = AnyBindingWrapper::FromFunctionBinding(constantBinding);

			auto convertedBinding = wrapper.AsFunctionBinding<int>();

			REQUIRE(constantBinding.Resolve(context) == convertedBinding.Resolve(context));
		}
	}
}
