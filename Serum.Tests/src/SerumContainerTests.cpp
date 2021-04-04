/// @file SerumContainerTests.cpp
/// Unit tests for the SerumContainer type.

#include "catch.hpp"
#include "Serum/SerumContainer.hpp"

namespace Serum::SerumContainerTests
{
	TEST_CASE("SerumContainer_BindConstant")
	{
		SECTION("WhenBindingDoesNotExist_CorrectlyBinds")
		{
			auto container = SerumContainer();
			const std::string testValue = "This is a test.";

			container.BindConstant<std::string>(testValue);

			REQUIRE(testValue == container.Get<std::string>());
		}

		SECTION("WhenBindingExists_Throws")
		{
			auto container = SerumContainer();

			container.BindConstant<int>(4);

			REQUIRE_THROWS(container.BindConstant<int>(3));
		}

		SECTION("CanBeChanined")
		{
			auto container = SerumContainer()
								.BindConstant<std::string>(std::string("test"))
								.BindConstant<double, float>(5.f);
		}
	}

	TEST_CASE("SerumContainer_BindFunction")
	{
		SECTION("WhenBindingDoesNotExist_CorrectlyBinds")
		{
			auto container = SerumContainer();
			std::string testValue = "This is a test.";

			container.BindFunction<std::string>([&]() { return testValue; });

			REQUIRE(testValue == container.Get<std::string>());
		}

		SECTION("WhenBindingExists_Throws")
		{
			auto container = SerumContainer();

			container.BindFunction<int>([]() { return 4; });

			REQUIRE_THROWS(container.BindFunction<int>([]() { return 7; }));
		}

		SECTION("CanBeChanined")
		{
			auto container = SerumContainer()
								.BindFunction<int>([]() { return 7; })
								.BindFunction<std::string>([&]() { return "Hello World"; });
		}
	}
}
