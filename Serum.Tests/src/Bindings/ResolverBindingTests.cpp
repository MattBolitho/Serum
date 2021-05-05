/// @file ResolverBindingTests.cpp
/// Unit tests for the ResolverBinding type.

#include "catch.hpp"
#include "Serum/Serum.hpp"
#include "Serum.Tests/TestResolver.hpp"

namespace Serum::Bindings::ResolverBindingTests
{
    TEST_CASE("ResolverBinding_ResolvesCorrectly")
    {
        auto context = ResolutionContext();
    	auto exporter = std::string();
        auto resolver = TestResolver<std::string>();

    	auto actual = resolver.Resolve(context);

    	REQUIRE(exporter == actual);
    }
}