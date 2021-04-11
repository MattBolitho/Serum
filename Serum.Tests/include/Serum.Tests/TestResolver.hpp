/// @file TestResolver.hpp
/// Defines a test resolver type which just returns a default instance.

#ifndef SERUM_TESTS_TEST_RESOLVER_HPP
#define SERUM_TESTS_TEST_RESOLVER_HPP

#include <optional>
#include "Serum/SerumResolver.hpp"

namespace Serum
{
    template <typename T>
    class TestResolver final : public SerumResolver<T>
    {
        public:
            explicit TestResolver(std::optional<T> const& value = std::nullopt)
                : SerumResolver<T>(), value(value.has_value() ? value.value() : T())
            {
            }

            T Resolve() override
            {
                return value;
            }

		private:
    		T value;
    };
}

#endif // SERUM_TESTS_TEST_RESOLVER_HPP