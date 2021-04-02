/// @file AnyBindingWrapper.hpp
/// Defines a type that wraps bindings which allows
/// them to be resolved dynamically at runtime.

#ifndef SERUM_INTERNAL_ANY_BINDING_WRAPPER_HPP
#define SERUM_INTERNAL_ANY_BINDING_WRAPPER_HPP

#include <sstream>
#include <utility>
#include <any>
#include "Serum/SerumException.hpp"
#include "Serum/Bindings/BindingType.hpp"
#include "Serum/Bindings/ConstantBinding.hpp"

namespace Serum::Internal
{
	/// Wraps bindings such that they can be resolved dynamically at runtime.
	class AnyBindingWrapper final
	{
		public:
			/// Initializes a new instance of the AnyBindingWrapper type.
			AnyBindingWrapper() noexcept
				: bindingType(Bindings::BindingType::Unknown), binding(std::any())
			{
			}

			/// Creates an AnyBindingWrapper instance for the given constant binding.
			/// @tparam TRequest The type of the request.
			/// @param binding The binding.
			/// @returns An AnyBindingWrapper instance for the given constant binding.
			template <typename TRequest>
			static AnyBindingWrapper FromConstantBinding(const Bindings::ConstantBinding<TRequest>& binding) noexcept
			{
				return AnyBindingWrapper(Bindings::BindingType::Constant, binding);
			}

			/// Gets the wrapped binding as a constant binding.
			/// @tparam TRequest The type of the request.
			/// @returns The wrapped binding as a constant binding.
			/// @throws SerumException If the underlying type is not a constant binding.
			template <typename TRequest>
			[[nodiscard]] Bindings::ConstantBinding<TRequest> AsConstantBinding() const
			{
				VerifyBindingType(Bindings::BindingType::Constant);

				try
				{
					return std::any_cast<Bindings::ConstantBinding<TRequest>>(binding);
				}
				catch (const std::bad_any_cast&)
				{
					throw SerumException("Failed to cast underlying binding to ConstantBinding.");
				}
			}

			/// Gets the underlying binding type.
			/// @returns The underlying binding type.
			[[nodiscard]] Bindings::BindingType GetBindingType() const noexcept
			{
				return bindingType;
			}

		private:
			AnyBindingWrapper(const Bindings::BindingType bindingType, std::any binding) noexcept
				: bindingType(bindingType), binding(std::move(binding))
			{
			}

			void VerifyBindingType(const Bindings::BindingType expected) const
			{
				if (bindingType != expected)
				{
					std::stringstream errorMessageStream;
					errorMessageStream << "Could not convert binding. Expected binding type was "
									   << expected
									   << " but actual binding type was "
									   << bindingType
									   << ".";

					throw SerumException(errorMessageStream.str());
				}
			}

			Bindings::BindingType bindingType;
			std::any binding;
	};
}

#endif // SERUM_BINDINGS_ANY_BINDING_WRAPPER_HPP