/// @file ResolverBinding.hpp
/// Defines a type for a binding that uses a SerumResolver to resolve the binding.

#ifndef SERUM_BINDINGS_RESOLVER_BINDING_HPP
#define SERUM_BINDINGS_RESOLVER_BINDING_HPP

#include <utility>
#include <string>
#include <memory>
#include "Serum/SerumResolver.hpp"
#include "Serum/Bindings/Binding.hpp"

namespace Serum::Bindings 
{
    /// A binding that uses a SerumResolver to resolve the binding.
    /// @tparam TRequest The type of the requested object.
    template <typename TRequest>
    class ResolverBinding final : public Binding<TRequest> 
    {
        public:
            /// Initializes a new instance of the ResolverBinding class.
            /// @param resolverPointer A pointer to the resolver to use.
            /// @param name Optionally, a name for the binding.
            ResolverBinding(
                std::unique_ptr<SerumResolver<TRequest>> resolverPointer,
                const std::string& name = "") noexcept
                : Binding<TRequest>(BindingType::Resolver, name), 
                  resolver(std::move(resolver))
            {
            }

            TRequest Resolve() override
            {
                return resolver->Resolve();
            }

        private:
            std::unique_ptr<SerumResolver<TRequest>> resolver;
    };
}

#endif