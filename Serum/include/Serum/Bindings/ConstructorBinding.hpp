/// @file ConstructorBinding.hpp
/// Defines a binding that resolves requests recursively using constrctors.

#ifndef SERUM_BINDINGS_CONSTRUCTOR_BINDING_HPP
#define SERUM_BINDINGS_CONSTRUCTOR_BINDING_HPP

#include <string>
#include <functional>
#include "Serum/Bindings/Binding.hpp"

namespace Serum::Bindings 
{
    /// A binding that resolves requests recursively using constrctors.
    /// @tparam TRequest The type of the requested object.
    template <typename TRequest>
    class ConstructorBinding final : public Binding<TRequest>
    {
        public:
            /// Deleted default constructor - use FromDefaultConstructor instead.
            ConstructorBinding() = delete;

            /// Creates a ConstructorBinding instance using TRequest's default constructor.
            /// @param name Optionally, the name of the binding.
            /// @returns A ConstructorBinding instance using TRequest's default constructor.
            static ConstructorBinding<TRequest> FromDefaultConstructor(std::string const& name = "")
            {
                return ConstructorBinding<TRequest>(
                    [](){ return TRequest(); },
                    name);
            }

            TRequest Resolve() override
            {
                return constructFunction();
            }

        private:
            ConstructorBinding(
                std::function<TRequest()> const& constructFunction,
                std::string const& name = "")
                : Binding<TRequest>(BindingType::Construct, name),
                  constructFunction(constructFunction)
            {
            }

            std::function<TRequest()> constructFunction;
    };
}

#endif // SERUM_BINDINGS_CONSTRUCTOR_BINDING_HPP