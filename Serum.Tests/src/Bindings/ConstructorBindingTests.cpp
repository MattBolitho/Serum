/// @file ConstructorBindingTests.cpp
/// Unit tests for the ConstructorBinding type.

#include "catch.hpp"
#include "Serum/Serum.hpp"
#include "Serum.Tests/TestType.hpp"

namespace Serum::Bindings::ConstructorBindingTests
{
    TEST_CASE("ConstructorBinding_ResolvesCorrectly")
    {
        auto expected = TestType();
        auto binding = ConstructorBinding<TestType>::FromDefaultConstructor<TestType>();

        auto actual = binding.Resolve();

        REQUIRE(expected == actual);
    }
}