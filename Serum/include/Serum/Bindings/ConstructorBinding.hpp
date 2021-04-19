/// @file ConstructorBinding.hpp
/// Defines a binding that resolves requests recursively using constrctors.

#ifndef SERUM_BINDINGS_CONSTRUCTOR_BINDING_HPP
#define SERUM_BINDINGS_CONSTRUCTOR_BINDING_HPP

#include <string>
#include <functional>
#include <utility>
#include "Serum/Bindings/Binding.hpp"

namespace Serum::Bindings
{
    /// A binding that resolves requests recursively using constrctors.
    /// @tparam TRequest The type of the requested object.
    template <typename TRequest>
    class ConstructorBinding final : public Binding<TRequest>
    {
        public:
            /// Initializes a new instance of the ConstructorBinding class.
            /// @param constructFunction
            /// @param name
            explicit ConstructorBinding(
	            std::function<TRequest()> constructFunction,
                std::string const& name = "")
                : Binding<TRequest>(BindingType::Construct, name),
                  constructFunction(std::move(constructFunction))
            {
            }

            /// Creates a ConstructorBinding instance using TRequest's default constructor.
            /// @param name Optionally, the name of the binding.
            /// @returns A ConstructorBinding instance using TRequest's default constructor.
            template <typename TResolve>
            static ConstructorBinding<TRequest> FromDefaultConstructor(std::string const& name = "")
            {
                return ConstructorBinding<TRequest>(
                    [](){ return TResolve(); },
                    name);
            }

            TRequest Resolve() override
            {
                return constructFunction();
            }

        private:

            std::function<TRequest()> constructFunction;
    };
}

#endif // SERUM_BINDINGS_CONSTRUCTOR_BINDING_HPP