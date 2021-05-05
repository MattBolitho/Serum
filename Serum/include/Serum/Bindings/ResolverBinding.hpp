/// @file ResolverBinding.hpp
/// Defines a type for a binding that uses a SerumResolver to resolve the binding.

#ifndef SERUM_BINDINGS_RESOLVER_BINDING_HPP
#define SERUM_BINDINGS_RESOLVER_BINDING_HPP

#include "Serum/Internal/Common.hpp"
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
            explicit ResolverBinding(
	            std::shared_ptr<SerumResolver<TRequest>> resolverPointer,
                std::string const& name = "") noexcept
                : Binding<TRequest>(BindingType::Resolver, name),
                  resolver(std::move(resolverPointer))
            {
            }

			[[nodiscard]] std::shared_ptr<Binding<TRequest>> Clone() const override
			{
				return std::make_shared<ResolverBinding>(*this);
			}

		protected:
            TRequest ResolveCore(ResolutionContext& resolutionContext) override
            {
                return resolver->Resolve();
            }

        private:
            std::shared_ptr<SerumResolver<TRequest>> resolver;
    };
}

#endif