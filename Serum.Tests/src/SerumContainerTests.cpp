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

	TEST_CASE("SerumContainer_HasKey")
	{
		constexpr auto bindingName = "test-binding";
		const auto container = SerumContainer().BindConstant<double>(1.2345, bindingName)
											   .BindConstant<int>(4);

		SECTION("WhenNamedKeyExists_ReturnsTrue")
		{
			REQUIRE(container.HasBinding<double>(bindingName));
		}

		SECTION("WhenNamedKeyDoesNotExist_ReturnsFalse")
		{
			REQUIRE_FALSE(container.HasBinding<double>());
		}

		SECTION("WhenUnamedKeyExists_ReturnsTrue")
		{
			REQUIRE(container.HasBinding<int>());
		}

		SECTION("WhenUnamedKeyDoesNotExist_ReturnsFalse")
		{
			REQUIRE_FALSE(container.HasBinding<float>());
		}
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

		SECTION("WithInstance_WhenBindingDoesNotExist_CorrectlyBinds")
		{
			constexpr auto expected = "test-value";
			auto resolver = TestResolver<std::string>(expected);
			auto container = SerumContainer();

			container.BindResolver<std::string>(resolver);

			REQUIRE(expected == container.Get<std::string>());
		}

		SECTION("WithInstance_WhenBindingExists_Throws")
		{
			constexpr auto expected = "test-value";
			auto resolver = TestResolver<std::string>(expected);
			auto container = SerumContainer();

			container.BindResolver<std::string>(resolver);

			REQUIRE_THROWS(container.BindResolver<std::string>(resolver));
		}
	}

	TEST_CASE("SerumContainer_BindToSelf")
	{
		SECTION("WhenBindingDoesNotExist_CorrectlyBinds")
		{
			auto container = SerumContainer();

			container.BindToSelf<TestType>();

			REQUIRE(TestType() == container.Get<TestType>());
		}

		SECTION("WhenBindingExists_Throws")
		{
			auto container = SerumContainer();

			container.BindToSelf<TestType>();

			REQUIRE_THROWS(container.BindToSelf<TestType>());
		}
	}

	TEST_CASE("SerumContainer_BindRawPointer")
	{
		SECTION("WhenBindingDoesNotExist_CorrectlyBinds")
		{
			auto container = SerumContainer();

			container.BindRawPointer<TestType>();

			auto resolvedPointer = container.Get<TestType*>();
			CHECK(TestType() == *resolvedPointer);
			delete resolvedPointer;
		}

		SECTION("WhenBindingExists_Throws")
		{
			auto container = SerumContainer();

			container.BindRawPointer<TestType>();

			REQUIRE_THROWS(container.BindRawPointer<TestType>());
		}
	}

	TEST_CASE("SerumContainer_BindSharedPointer")
	{
		SECTION("WhenBindingDoesNotExist_CorrectlyBinds")
		{
			auto container = SerumContainer();

			container.BindSharedPointer<TestType>();

			auto resolvedPointer = container.Get<std::shared_ptr<TestType>>();
			REQUIRE(TestType() == *resolvedPointer);
		}

		SECTION("WhenBindingExists_Throws")
		{
			auto container = SerumContainer();

			container.BindSharedPointer<TestType>();

			REQUIRE_THROWS(container.BindSharedPointer<TestType>());
		}
	}

	TEST_CASE("SerumContainer_BindingMethods_CanBeChained")
	{
		auto container = SerumContainer()
								.BindConstant<int>(7)
								.BindFunction<std::string>([]() { return "Hello World"; })
								.BindResolver<TestType, TestResolver<TestType>>()
								.BindToSelf<TestType>("self-binding")
								.BindRawPointer<double>()
								.BindSharedPointer<float>();

		REQUIRE(6 == container.GetNumberOfBindings());
	}
}
