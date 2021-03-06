/// @file SerumResolver.hpp
/// Defines a base type for allowing custom resolution logic
/// to be bound into the container.

#ifndef SERUM_SERUM_RESOLVER
#define SERUM_SERUM_RESOLVER

#include "Serum/ResolutionContext.hpp"

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
            SerumResolver(SerumResolver const& resolver) noexcept = default;

            /// Move constructor.
            /// @param resolver The resolver.
            SerumResolver(SerumResolver&& resolver) noexcept = default;

            /// Copy assignment operator.
            /// @param resolver The resolver.
            SerumResolver& operator=(SerumResolver const& resolver) = default;

            /// Move assignment operator.
            /// @param resolver The resolver.
            SerumResolver& operator=(SerumResolver&& resolver) = default;

            /// Resolves the binding.
            /// @param resolutionContext The resolution context.
            /// @returns The resolved binding.
            virtual TResolve Resolve(ResolutionContext& resolutionContext) = 0;

        protected:
            /// Default constructor.
            SerumResolver() = default;
    };
}

#endif // SERUM_BINDINGS_SERUM_RESOLVER