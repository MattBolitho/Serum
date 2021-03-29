/// @file ConstantBinding.hpp
/// Defines a binding type where the same value is always resolved.

#ifndef SERUM_BINDINGS_CONSTANT_BINDING_HPP
#define SERUM_BINDINGS_CONSTANT_BINDING_HPP

#include <string>
#include "Serum/Bindings/Binding.hpp"

namespace Serum::Bindings
{
	/// A binding type where the same value is always resolved.
	/// @tparam T The type of the constant value.
	template <typename T>
	class ConstantBinding final : public Binding<T>
	{
		public:
			/// Initializes a new instance of the ConstantBinding class.
			/// @param value The value.
			/// @param name The name.
			explicit ConstantBinding(
				const T& value,
				const std::string& name = "") noexcept
				: Binding<T>(BindingType::Constant, name), value(value)
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

#endif // SERUM_BINDINGS_CONSTANT_BINDING_HPP
