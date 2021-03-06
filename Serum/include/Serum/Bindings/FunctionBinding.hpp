/// @file FunctionBinding.hpp
/// Defines a type which resolves a binding as the result of a function.

#ifndef SERUM_BINDINGS_FUNCTION_BINDING_HPP
#define SERUM_BINDINGS_FUNCTION_BINDING_HPP

#include "Serum/Internal/Common.hpp"
#include "Serum/Bindings/Binding.hpp"

namespace Serum::Bindings
{
    /// Type alias for a function that resolves a TRequest instance.
    /// @tparam TRequest The type of the requested object.
    template <typename TRequest>
    using ResolutionFunction = std::function<TRequest(ResolutionContext&)>;

    /// Resolves a binding as the result of a function.
    /// @tparam TRequest The type of the requested object.
    template <typename TRequest>
    class FunctionBinding final : public Binding<TRequest>
    {

        public:
            /// Initializes a new instance of the FunctionBinding class.
            /// @param resolveFunction The resolve function. This function is moved.
            /// @param name Optionally, the name.
            explicit FunctionBinding(
                ResolutionFunction<TRequest> const& resolveFunction,
                std::string const& name = "") noexcept
                : Binding<TRequest>(BindingType::Function, name),
                  resolveFunction(std::move(resolveFunction))
            {
            }

            [[nodiscard]] std::shared_ptr<Binding<TRequest>> Clone() const override
            {
                return std::make_shared<FunctionBinding>(*this);
            }

        protected:
            TRequest ResolveCore(ResolutionContext& resolutionContext) override
            {
                return resolveFunction(resolutionContext);
            }

        private:
            ResolutionFunction<TRequest> resolveFunction;
    };
}

#endif // SERUM_BINDINGS_FUNCTION_BINDING_HPP
