/// @file SerumExceptionTests.cpp
/// Unit tests for the SerumException type.

#include <cstring>
#include "catch.hpp"
#include "Serum/Serum.hpp"

namespace Serum::SerumExceptionTests
{
	TEST_CASE("SerumException_Constructor")
	{
		SECTION("CharPointer_SetsCorrectMessage")
		{
			constexpr auto* message = "Test message.";

			auto exception = SerumException(message);

			REQUIRE(strcmp(message, exception.what()) == 0);
		}

		SECTION("String_SetsCorrectMessage")
		{
			std::string const message = "Test message.";

			auto exception = SerumException(message);

			REQUIRE(message == exception.what());
		}
	}
}
