/// @file TestType.hpp
/// Defines a POD type for use in tests.

#ifndef SERUM_TESTS_TEST_TYPE_HPP
#define SERUM_TESTS_TEST_TYPE_HPP

#include <string>

namespace Serum
{
	struct TestType
	{
		int intValue = 0;
		bool boolValue = false;
		std::string stringValue = "";

		bool operator==(const TestType& other) const
		{
			return intValue == other.intValue
				&& boolValue == other.boolValue
				&& stringValue == other.stringValue;
		}
	};
}

#endif // SERUM_TESTS_TEST_TYPE_HPP
