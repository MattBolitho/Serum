/// @file SerumContainerTests.cpp
/// Unit tests for the SerumContainer type.

#include "catch.hpp"
#include "Serum/SerumContainer.hpp"
#include "Serum.Tests/TestType.hpp"
#include "Serum.Tests/TestResolver.hpp"

namespace Serum::SerumContainerTests
{
	TEST_CASE("SerumContainer_GetNumberOfBindings")
	{
		constexpr auto expected = 4;
		const auto container = SerumContainer().BindConstant<std::string>(std::string("hello"))
											   .BindConstant<int>(0)
											   .BindConstant<float>(0.f)
											   .BindConstant<double>(0.0);

		const auto actual = container.GetNumberOfBindings();

		REQUIRE(expected == actual);
	}

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
	}

	TEST_CASE("SerumContainer_BindResolver")
	{
		SECTION("DefaultInstance_WhenBindingDoesNotExist_CorrectlyBinds")
		{
			auto expected = double();
			auto container = SerumContainer();

			container.BindResolver<double, TestResolver<double>>();

			REQUIRE(expected == container.Get<double>());
		}

		SECTION("DefaultInstance_WhenBindingExists_Throws")
		{
			auto container = SerumContainer();

			container.BindResolver<double, TestResolver<double>>();

			REQUIRE_THROWS(container.BindResolver<double, TestResolver<double>>());
		}
	}

	TEST_CASE("BindingMethods_CanBeChained")
	{
		auto container = SerumContainer()
								.BindConstant<int>(7)
								.BindFunction<std::string>([]() { return "Hello World"; })
								.BindResolver<TestType, TestResolver<TestType>>();
	}
}
