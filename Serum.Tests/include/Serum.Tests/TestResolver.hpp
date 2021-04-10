/// @file TestResolver.hpp
/// Defines a test resolver type which just returns a default instance.

#ifndef SERUM_TESTS_TEST_RESOLVER_HPP
#define SERUM_TESTS_TEST_RESOLVER_HPP

#include "Serum/SerumResolver.hpp"

namespace Serum 
{
    template <typename T>
    class TestResolver final : public SerumResolver<T>
    {
        public:
            explicit TestResolver()
                : SerumResolver<T>()
            {
            }

            T Resolve() override
            {
                return T();
            }
    };
}

#endif // SERUM_TESTS_TEST_RESOLVER_HPP