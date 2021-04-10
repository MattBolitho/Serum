/// @file SerumContainer.hpp
/// Defines a type that allows bindings to be registered and resolved.

#ifndef SERUM_SERUM_CONTAINER_HPP
#define SERUM_SERUM_CONTAINER_HPP

#include <sstream>
#include <unordered_map>
#include <any>
#include <type_traits>
#include <optional>
#include "Serum/SerumException.hpp"
#include "Serum/Internal/AnyBindingWrapper.hpp"
#include "Serum/Bindings/BindingKey.hpp"
#include "Serum/Bindings/ConstantBinding.hpp"
#include "Serum/Bindings/FunctionBinding.hpp"
#include "Serum/Bindings/ResolverBinding.hpp"

namespace Serum
{
	/// The type used to store the bindings in the kernel.
	using BindingCollection = std::unordered_map<Bindings::BindingKey, Internal::AnyBindingWrapper>;

	/// Allows bindings to be registered and resolved.
	class SerumContainer
	{
		public:
			/// Initializes a new instance of the SerumContainer class.
			SerumContainer() = default;

			/// Resolves a bound service from the container.
			/// @tparam TRequest The type of the service to request.
			/// @param name Optionally, the name of the binding.
			/// @returns The resolved service.
			/// @throws SerumException If no matching bindings exist.
			template <typename TRequest>
			[[nodiscard]] TRequest Get(const std::string& name = "") const
			{
				const auto key = Bindings::BindingKey(typeid(TRequest), name);
				const auto optionalBinding = GetBinding(key);

				if (!optionalBinding.has_value())
				{
					std::stringstream errorMessageStream;
					errorMessageStream << "No binding registered for " << key << ".";
					throw SerumException(errorMessageStream.str());
				}

				const auto& binding = optionalBinding.value();
				switch (binding.GetBindingType())
				{
					case Bindings::BindingType::Constant:
						return binding.AsConstantBinding<TRequest>().Resolve();

					case Bindings::BindingType::Function:
						return binding.AsFunctionBinding<TRequest>().Resolve();

					case Bindings::BindingType::Resolver:
						return binding.AsResolverBinding<TRequest>().Resolve();

					case Bindings::BindingType::Construct:
						throw SerumException("Currently unsupported.");

					case Bindings::BindingType::Unknown:
					default:
						throw SerumException("Could not resolve binding. Binding type was unknown or invalid.");
				}
			}

			/// Gets the number of bindings that have been registered to the container.
			/// @returns The number of bindings that have been registered to the container.
			[[nodiscard]] BindingCollection::size_type GetNumberOfBindings() const noexcept
			{
				return bindings.size();
			}

			/// Checks whether a binding has been registered.
			/// @tparam TRequest The type of the service to request.
			/// @param name Optionally, the name of the binding.
			/// @returns Whether or not a binding of the request type and name exists.
			template <typename TRequest>
			[[nodiscard]] bool HasBinding(const std::string& name = "") const
			{
				const auto key = Bindings::BindingKey(typeid(TRequest), name);
				return bindings.find(key) != bindings.end();
			}

			/// Binds the type to a constant value. When the type is requested, the container
			/// will return a copy of the value.
			/// @tparam TRequest The type of the requested object.
			/// @tparam TResolve The type of the constant to resolve. This must be convertible from TRequest.
			/// @param value The value to return.
			/// @param name Optionally, a name for the binding.
			/// @returns This instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest, typename TResolve = TRequest>
			SerumContainer& BindConstant(const TResolve& value, const std::string& name = "")
			{
				static_assert(
					std::is_copy_assignable<TResolve>::value,
					"Cannot bind constant - the resolution type must be copy assignable.");

				static_assert(
					std::is_convertible<TRequest, TResolve>::value,
					"Cannot bind constant - the resolution type must be convertible from the request type.");

				auto binding = Bindings::ConstantBinding<TRequest>(value, name);
				auto key = binding.GetBindingKey();
				this->ThrowIfBindingExists(key);
				bindings[key] = Internal::AnyBindingWrapper::FromConstantBinding(binding);

				return *this;
			}

			/// Binds the type to the result of a function. When the type is requested, the container will invoke
			/// the function and return the result.
			/// @tparam TRequest The type of the requested object.
			/// @param function The function.
			/// @param name Optionally, a name for the binding.
			/// @returns This instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest>
			SerumContainer& BindFunction(const std::function<TRequest()>& function, const std::string& name = "")
			{
				auto binding = Bindings::FunctionBinding<TRequest>(function, name);
				auto key = binding.GetBindingKey();
				this->ThrowIfBindingExists(key);
				bindings[key] = Internal::AnyBindingWrapper::FromFunctionBinding(binding);

				return *this;
			}

			/// Binds the type to a resolver. When the type is requested, the return value of the given resolver's
			/// Resolve method will be returned.
			/// @tparam TRequest The type of the requested object.
			/// @tparam TResolver The type of the resolver.
			/// @param name Optionally, a name for the binding.
			template <typename TRequest, typename TResolver>
			SerumContainer& BindResolver(const std::string& name = "")
			{
				static_assert(
					std::is_default_constructible<TResolver>::value,
					"Cannot bind resolver - resolver type must be default constructible. Did you mean to pass an instance?");

				auto resolverInstance = std::make_shared<TResolver>();
				auto upcastResolvedInstance = std::dynamic_pointer_cast<SerumResolver<TRequest>>(resolverInstance);
				auto binding = Bindings::ResolverBinding<TRequest>(upcastResolvedInstance, name);
				auto key = binding.GetBindingKey();
				this->ThrowIfBindingExists(key);
				bindings[key] = Internal::AnyBindingWrapper::FromResolverBinding(binding);

				return *this;
			}

		private:
			[[nodiscard]] std::optional<Internal::AnyBindingWrapper> GetBinding(const Bindings::BindingKey& key) const
			{
				const auto iterator = bindings.find(key);

				return iterator == bindings.end()
					? std::nullopt
					: std::optional<Internal::AnyBindingWrapper>(iterator->second);
			}

			void ThrowIfBindingExists(const Bindings::BindingKey& key) const
			{
				const auto existingBinding = GetBinding(key);

				if (existingBinding.has_value())
				{
					std::stringstream errorMessage;
					errorMessage << "A binding already exists for " << key << ".\n";

					throw SerumException(errorMessage.str());
				}
			}

			/// The bindings, keyed by binding type and name.
			std::unordered_map<Bindings::BindingKey, Internal::AnyBindingWrapper> bindings{};
	};
}

#endif // SERUM_SERUM_CONTAINER_HPP
