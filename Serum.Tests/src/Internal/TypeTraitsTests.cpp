/// @file TypeTraitsTests.cpp
/// Unit tests for the type traits header.

#include "catch.hpp"
#include "Serum/Serum.hpp"

namespace Serum::Internal::TypeTraitsTests
{
	struct WithSerumConstructor final
	{
		static WithSerumConstructor* SerumConstructor(SerumContainer& container, ResolutionContext& resolutionContext)
		{
			return new WithSerumConstructor();
		}
	};

	struct WithoutSerumConstructor final {};

	TEST_CASE("TypeTraits_HasSerumConstructor")
	{
		SECTION("WhenTypeHasSerumConstructor_ValueIsTrue")
		{
			REQUIRE(HasSerumConstructor<WithSerumConstructor>::value);
		}

		SECTION("WhenTypeDoesNotHaveSerumConstructor_ValueIsFalse")
		{
			REQUIRE_FALSE(HasSerumConstructor<WithoutSerumConstructor>::value);
		}
	}
}
