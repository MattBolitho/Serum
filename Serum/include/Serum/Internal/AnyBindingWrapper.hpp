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
#include "Serum/Bindings/FunctionBinding.hpp"
#include "Serum/Bindings/ResolverBinding.hpp"
#include "Serum/Bindings/ConstructorBinding.hpp"

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
			static AnyBindingWrapper FromConstantBinding(Bindings::ConstantBinding<TRequest>const& binding) noexcept
			{
				return AnyBindingWrapper(Bindings::BindingType::Constant, binding);
			}

			/// Creates an AnyBindingWrapper instance for the given function binding.
			/// @tparam TRequest The type of the request.
			/// @param binding The binding.
			/// @returns An AnyBindingWrapper instance for the given function binding.
			template <typename TRequest>
			static AnyBindingWrapper FromFunctionBinding(Bindings::FunctionBinding<TRequest> const& binding) noexcept
			{
				return AnyBindingWrapper(Bindings::BindingType::Function, binding);
			}

			/// Creates an AnyBindingWrapper instance for the given resolver binding.
			/// @tparam TRequest The type of the request.
			/// @param binding The binding.
			/// @returns An AnyBindingWrapper instance for the given resolver binding.
			template <typename TRequest>
			static AnyBindingWrapper FromResolverBinding(Bindings::ResolverBinding<TRequest> const& binding) noexcept
			{
				return AnyBindingWrapper(Bindings::BindingType::Resolver, binding);
			}

			/// Creates an AnyBindingWrapper instance for the given constructor binding.
			/// @tparam TRequest The type of the request.
			/// @param binding The binding.
			/// @returns An AnyBindingWrapper instance for the given constructor binding.
			template <typename TRequest>
			static AnyBindingWrapper FromConstructorBinding(Bindings::ConstructorBinding<TRequest> const& binding) noexcept
			{
				return AnyBindingWrapper(Bindings::BindingType::Construct, binding);
			}

			/// Gets the underlying binding type.
			/// @returns The underlying binding type.
			[[nodiscard]] Bindings::BindingType GetBindingType() const noexcept
			{
				return bindingType;
			}

			/// Gets the wrapped binding as a constant binding.
			/// @tparam TRequest The type of the request.
			/// @returns The wrapped binding as a constant binding.
			/// @throws SerumException If the underlying type is not a constant binding.
			template <typename TRequest>
			[[nodiscard]] Bindings::ConstantBinding<TRequest> AsConstantBinding() const
			{
				VerifyBindingType(Bindings::BindingType::Constant);
				return this->CastBinding<Bindings::ConstantBinding<TRequest>>();
			}

			/// Gets the wrapped binding as a function binding.
			/// @tparam TRequest The type of the request.
			/// @returns The wrapped binding as a function binding.
			/// @throws SerumException If the underlying type is not a function binding.
			template <typename TRequest>
			[[nodiscard]] Bindings::FunctionBinding<TRequest> AsFunctionBinding() const
			{
				VerifyBindingType(Bindings::BindingType::Function);
				return this->CastBinding<Bindings::FunctionBinding<TRequest>>();
			}

			/// Gets the wrapped binding as a resolver binding.
			/// @tparam TRequest The type of the request.
			/// @returns The wrapped binding as a resolver binding.
			/// @throws SerumException If the underlying type is not a resolver binding.
			template <typename TRequest>
			[[nodiscard]] Bindings::ResolverBinding<TRequest> AsResolverBinding() const
			{
				VerifyBindingType(Bindings::BindingType::Resolver);
				return this->CastBinding<Bindings::ResolverBinding<TRequest>>();
			}

			/// Gets the wrapped binding as a constructor binding.
			/// @tparam TRequest The type of the request.
			/// @returns The wrapped binding as a constructor binding.
			/// @throws SerumException If the underlying type is not a constructor binding.
			template <typename TRequest>
			[[nodiscard]] Bindings::ConstructorBinding<TRequest> AsConstructorBinding() const
			{
				VerifyBindingType(Bindings::BindingType::Construct);
				return this->CastBinding<Bindings::ConstructorBinding<TRequest>>();
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

			template <typename TBinding>
			[[nodiscard]] TBinding CastBinding() const
			{
				try
				{
					return std::any_cast<TBinding>(binding);
				}
				catch (std::bad_any_cast const&)
				{
					throw SerumException("Failed to cast underlying binding.");
				}
			}


			Bindings::BindingType bindingType;
			std::any binding;
	};
}

#endif // SERUM_BINDINGS_ANY_BINDING_WRAPPER_HPP
