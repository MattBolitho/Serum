/// @file ResolverBindingTests.cpp
/// Unit tests for the ResolverBinding type.

#include "catch.hpp"
#include "Serum/Bindings/ResolverBinding.hpp"
#include "Serum.Tests/TestResolver.hpp"

namespace Serum::Bindings::ResolverBindingTests
{
    TEST_CASE("ResolverBinding_ResolvesCorrectly")
    {
    	auto exporter = std::string();
        auto resolver = TestResolver<std::string>();

    	auto actual = resolver.Resolve();

    	REQUIRE(exporter == actual);
    }
}