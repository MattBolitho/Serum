/// @file FunctionBinding.hpp
/// Defines a type which resolves a binding as the result of a function.

#ifndef SERUM_BINDINGS_FUNCTION_BINDING_HPP
#define SERUM_BINDINGS_FUNCTION_BINDING_HPP

#include "Serum/Internal/Common.hpp"
#include "Serum/Bindings/Binding.hpp"

namespace Serum::Bindings
{
	/// Resolves a binding as the result of a function.
	/// @tparam TRequest The type of the constant value.
	template <typename TRequest>
	class FunctionBinding final : public Binding<TRequest>
	{
		public:
			/// Initializes a new instance of the FunctionBinding class.
			/// @param resolveFunction The resolve function. This function is moved.
			/// @param name Optionally, the name.
			explicit FunctionBinding(
				std::function<TRequest()> const& resolveFunction,
				std::string const& name = "") noexcept
				: Binding<TRequest>(BindingType::Function, name),
				  resolveFunction(std::move(resolveFunction))
			{
			}

			TRequest Resolve() override
			{
				return resolveFunction();
			}

		private:
			std::function<TRequest()> resolveFunction;
	};
}

#endif // SERUM_BINDINGS_FUNCTION_BINDING_HPP
