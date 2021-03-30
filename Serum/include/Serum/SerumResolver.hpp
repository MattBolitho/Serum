/// @file SerumResolver.hpp
/// Defines a base type for allowing custom resolution logic
/// to be bound into the container.

#ifndef SERUM_SERUM_RESOLVER
#define SERUM_SERUM_RESOLVER

namespace Serum 
{
    template <typename TResolve>
    class SerumResolver 
    {
        public:
            /// Public virtual destructor.
            virtual ~SerumResolver() = default;

            /// Copy constructor.
            /// @param resolver The resolver.
            SerumResolver(const SerumResolver& resolver) noexcept = default;

            /// Move constructor.
            /// @param resolver The resolver.
            SerumResolver(const SerumResolver&& resolver) noexcept = default;

            /// Copy assignment operator.
            /// @param resolver The resolver.
            SerumResolver& operator=(const SerumResolver& resolver) = default;

            /// Move assignment operator.
            /// @param resolver The resolver.
            SerumResolver& operator=(SerumResolver&& resolver) = default;

            /// Resolves the binding.
            /// @returns The resolved binding.
            virtual TResolve Resolve() = 0;

        protected:
            /// Default constructor.
            SerumResolver() = default;
    };
}

#endif // SERUM_BINDINGS_SERUM_RESOLVER