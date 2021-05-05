/// @file TestType.hpp
/// Defines a Serum constructable POD type for use in tests.

#ifndef SERUM_TESTS_SERUM_CONSTRUCTABLE_TEST_TYPE_HPP
#define SERUM_TESTS_SERUM_CONSTRUCTABLE_TEST_TYPE_HPP

#include "Serum/Serum.hpp"
#include "Serum.Tests/TestType.hpp"

namespace Serum
{
	struct SerumConstructableTestType final : TestType
	{
		static SerumConstructableTestType* SerumConstructor(
			SerumContainer& container,
			ResolutionContext& resolutionContext)
		{
			return new SerumConstructableTestType();
		}
	};
}

#endif // SERUM_TESTS_SERUM_CONSTRUCTABLE_TEST_TYPE_HPP