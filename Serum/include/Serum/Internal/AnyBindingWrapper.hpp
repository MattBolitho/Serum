/// @file AnyBindingWrapper.hpp
/// Defines a type that wraps bindings which allows
/// them to be resolved dynamically at runtime.

#ifndef SERUM_INTERNAL_ANY_BINDING_WRAPPER_HPP
#define SERUM_INTERNAL_ANY_BINDING_WRAPPER_HPP

#include "Serum/Internal/Common.hpp"
#include "Serum/Bindings/BindingType.hpp"
#include "Serum/Bindings/FunctionBinding.hpp"
#include "Serum/Bindings/ResolverBinding.hpp"
#include "Serum/Bindings/SingletonBinding.hpp"

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

			/// Initializes a new instance of the AnyBindingWrapper type.
			/// @param functionBinding The function binding.
			template <typename TRequest>
			explicit AnyBindingWrapper(Bindings::FunctionBinding<TRequest> const& functionBinding) noexcept
				: bindingType(Bindings::BindingType::Function),
				  binding(std::any(functionBinding))
			{
			}

			/// Initializes a new instance of the AnyBindingWrapper type.
			/// @param resolverBinding The resolver binding.
			template <typename TRequest>
			explicit AnyBindingWrapper(Bindings::ResolverBinding<TRequest> const& resolverBinding) noexcept
				: bindingType(Bindings::BindingType::Resolver),
				  binding(std::any(resolverBinding))
			{
			}

			/// Initializes a new instance of the AnyBindingWrapper type.
			/// @param singletonBinding The resolver binding.
			template <typename TRequest>
			explicit AnyBindingWrapper(Bindings::SingletonBinding<TRequest> const& singletonBinding) noexcept
				: bindingType(singletonBinding.GetBindingType()),
				  binding(std::any(singletonBinding))
			{
			}

			/// Gets the underlying binding type.
			/// @returns The underlying binding type.
			[[nodiscard]] Bindings::BindingType GetBindingType() const noexcept
			{
				return bindingType;
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

			/// Gets the wrapped binding as a singleton binding.
			/// @tparam TRequest The type of the request.
			/// @returns The wrapped binding as a singleton binding.
			/// @throws SerumException If the underlying type is not a singleton binding.
			template <typename TRequest>
			[[nodiscard]] Bindings::SingletonBinding<TRequest> AsSingletonBinding() const
			{
				VerifyBindingType(Bindings::BindingType::Singleton);
				return this->CastBinding<Bindings::SingletonBinding<TRequest>>();
			}

		private:
			Bindings::BindingType bindingType;
			std::any binding;

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
	};
}

#endif // SERUM_BINDINGS_ANY_BINDING_WRAPPER_HPP
