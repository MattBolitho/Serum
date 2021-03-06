/// @file SerumContainer.hpp
/// Defines a type that allows bindings to be registered and resolved.

#ifndef SERUM_SERUM_CONTAINER_HPP
#define SERUM_SERUM_CONTAINER_HPP

#include "Serum/Internal/Common.hpp"
#include "Serum/Internal/AnyBindingWrapper.hpp"
#include "Serum/Internal/TypeTraits.hpp"
#include "Serum/Bindings/BindingKey.hpp"

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
			[[nodiscard]] auto Get(std::string const& name = "")
			{
				auto resolutionContext = ResolutionContext();

				return this->GetCore<TRequest>(resolutionContext, name);
			}

			/// Resolves a bound service from the container.
			/// @tparam TRequest The type of the service to request.
			/// @param resolutionContext The resolution context.
			/// @param name Optionally, the name of the binding.
			/// @returns The resolved service.
			/// @throws SerumException If no matching bindings exist.
			template <typename TRequest>
			[[nodiscard]] auto Get(ResolutionContext& resolutionContext, std::string const& name = "")
			{
				return this->GetCore<TRequest>(resolutionContext, name);
			}

            /// Convenience function that calls Get with std::shared_ptr<TRequest>.
            /// @tparam TRequest The type of the shared pointer to request.
            /// @param name Optionally, the name of the binding.
            /// @returns The resolved service.
            /// @throws SerumException If no matching bindings exist.
            template <typename TRequest>
            [[nodiscard]] auto GetSharedPointer(std::string const& name = "")
            {
                auto resolutionContext = ResolutionContext();

                return this->GetCore<std::shared_ptr<TRequest>>(resolutionContext, name);
            }

            /// Convenience function that calls Get with std::shared_ptr<TRequest>.
            /// @tparam TRequest The type of the shared pointer to request.
            /// @param resolutionContext The resolution context.
            /// @param name Optionally, the name of the binding.
            /// @returns The resolved shared pointer service.
            /// @throws SerumException If no matching bindings exist.
            template <typename TRequest>
            [[nodiscard]] auto GetSharedPointer(ResolutionContext& resolutionContext, std::string const& name = "")
            {
                return this->GetCore<std::shared_ptr<TRequest>>(resolutionContext, name);
            }

			/// Gets the number of bindings that have been registered to the container.
			/// @returns The number of bindings that have been registered to the container.
			[[nodiscard]] auto GetNumberOfBindings() const noexcept
			{
				return bindings.size();
			}

			/// Checks whether a binding has been registered.
			/// @tparam TRequest The type of the service to request.
			/// @param name Optionally, the name of the binding.
			/// @returns Whether or not a binding of the request type and name exists.
			template <typename TRequest>
			[[nodiscard]] auto HasBinding(std::string const& name = "") const
			{
				auto const key = Bindings::BindingKey(typeid(TRequest), name);
				return bindings.find(key) != bindings.end();
			}

			/// Binds the type to a constant value. When the type is requested, the container
			/// will return a copy of the value.
			/// @tparam TRequest The type of the requested object.
			/// @tparam TResolve The type of the constant to resolve. This must be convertible from TRequest.
			/// @param value The value to return.
			/// @param name Optionally, a name for the binding.
			/// @returns The container instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest, typename TResolve = TRequest>
			auto& BindConstant(TResolve const& value, std::string const& name = "")
			{
				static_assert(
					std::is_copy_assignable<TResolve>::value,
					"Cannot bind constant - the resolution type must be copy assignable.");

				static_assert(
					std::is_convertible<TRequest, TResolve>::value,
					"Cannot bind constant - the resolution type must be convertible from the request type.");

				auto function = [value](ResolutionContext&) { return value; };
				auto const binding = Bindings::FunctionBinding<TRequest>(function, name);

				return this->BindCore(binding, name);
			}

			/// Binds the type to the result of a function. When the type is requested, the container will invoke
			/// the function and return the result.
			/// @tparam TRequest The type of the requested object.
			/// @param function The function.
			/// @param name Optionally, a name for the binding.
			/// @returns The container instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest>
			auto& BindFunction(Bindings::ResolutionFunction<TRequest> const& function, std::string const& name = "")
			{
				auto const binding = Bindings::FunctionBinding<TRequest>(function, name);

				return this->BindCore(binding, name);
			}

			/// Binds the type to a resolver. When the type is requested, the return value of the given resolver's
			/// Resolve method will be returned.
			/// @tparam TRequest The type of the requested object.
			/// @tparam TResolver The type of the resolver.
			/// @param name Optionally, a name for the binding.
			/// @returns The container instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest, typename TResolver>
			auto& BindResolver(std::string const& name = "")
			{
				static_assert(
					std::is_convertible<std::shared_ptr<TResolver>, std::shared_ptr<SerumResolver<TRequest>>>::value,
					"Cannot bind resolver - TResolver is not convertible to SerumResolver.");

				static_assert(
					std::is_default_constructible<TResolver>::value,
					"Cannot bind resolver - resolver type must be default constructible. Did you mean to pass a SerumResolver instance?");

				auto const resolver = std::make_shared<TResolver>();
				auto const binding = Bindings::ResolverBinding<TRequest>(resolver, name);

				return this->BindCore(binding, name);
			}

			/// Binds the type to a resolver. When the type is requested, the return value of the given resolver's
			/// Resolve method will be returned.
			/// @tparam TRequest The type of the requested object.
			/// @tparam TResolver The type of the resolver.
			/// @param resolverInstance The resolver instance.
			/// @param name Optionally, a name for the binding.
			/// @returns The container instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest, typename TResolver>
			auto& BindResolver(TResolver const& resolverInstance, std::string const& name = "")
			{
				static_assert(
					std::is_convertible<std::shared_ptr<TResolver>, std::shared_ptr<SerumResolver<TRequest>>>::value,
					"Cannot bind resolver - TResolver is not convertible to SerumResolver.");

				static_assert(
					std::is_copy_constructible<TResolver>::value,
					"Cannot bind resolver - type of resolver instance is not copy constructible.");

				auto const resolver = std::make_shared<TResolver>(resolverInstance);
				auto const binding = Bindings::ResolverBinding<TRequest>(resolver, name);

				return this->BindCore(binding, name);
			}

			/// Binds the type to itself. When the type is requested, the resolver will return a new default instance
			/// of the given type.
			/// @param name Optionally, a name for the binding.
			/// @returns The container instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest>
			auto& BindToSelf(std::string const& name = "")
			{
				static_assert(
					std::is_default_constructible<TRequest>::value,
					"Could not bind type to self - Type must be default constructable.");

				if constexpr (Internal::HasSerumConstructor<TRequest>::value)
				{
					auto const function = [this](ResolutionContext& context) { return *TRequest::SerumConstructor(*this, context); };
					auto const binding = Bindings::FunctionBinding<TRequest>(function, name);
					return this->BindCore(binding, name);
				}
				else
				{
					auto const function = [](ResolutionContext&) { return TRequest(); };
					auto const binding = Bindings::FunctionBinding<TRequest>(function, name);
					return this->BindCore(binding, name);
				}
			}

			/// Binds the type to a raw pointer. When the type is requested, the container will construct a new heap-allocated
			/// instance of the resolution type and return it. The container does not manage the allocated pointer - this must
			/// later be deleted by the consumer.
			/// @tparam TRequest The type of the requested object.
			/// @tparam TResolve The type to resolve to. This must be convertible from TRequest.
			/// @param name Optionally, a name for the binding.
			/// @returns The container instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest, typename TResolve = TRequest>
			auto& BindRawPointer(std::string const& name = "")
			{
				static_assert(
					std::is_convertible<TResolve*, TRequest*>::value,
					"Could not bind pointer - The resolution pointer type is not convertible to the request pointer type.");

				if constexpr (Internal::HasSerumConstructor<TResolve>::value)
				{
					auto const function = [this](ResolutionContext& context) { return TResolve::SerumConstructor(*this, context); };
					auto const binding = Bindings::FunctionBinding<TRequest*>(function, name);
					return this->BindCore(binding, name);
				}
				else
				{
					auto const function = [](ResolutionContext&) { return new TResolve; };
					auto const binding = Bindings::FunctionBinding<TRequest*>(function, name);
					return this->BindCore(binding, name);
				}
			}

			/// Binds the type to a std::shared_ptr instance. When the type is requested, the container will make a shared pointer
			/// of the resolution type and return it.
			/// @tparam TRequest The type of the requested object.
			/// @tparam TResolve The type to resolve to. This must be convertible from TRequest.
			/// @param name Optionally, a name for the binding.
			/// @returns The container instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest, typename TResolve = TRequest>
			auto& BindSharedPointer(std::string const& name = "")
			{
				static_assert(
					std::is_convertible<std::shared_ptr<TResolve>, std::shared_ptr<TRequest>>::value,
					"Could not bind shared pointer - The resolution pointer type is not convertible to the request pointer type.");

				if constexpr (Internal::HasSerumConstructor<TResolve>::value)
				{
					auto const function = [this](ResolutionContext& context)
					{
					    return std::shared_ptr<TRequest>(TResolve::SerumConstructor(*this, context));
					};
					auto const binding = Bindings::FunctionBinding<std::shared_ptr<TRequest>>(function, name);
					return this->BindCore(binding, name);
				}
				else
				{
					auto const function = [](ResolutionContext&) { return std::make_shared<TResolve>(); };
					auto const binding = Bindings::FunctionBinding<std::shared_ptr<TRequest>>(function, name);
					return this->BindCore(binding, name);
				}
			}

			/// Binds the type to a raw pointer as a singleton. When the type is first requested, the container will construct a
			/// new heap-allocated instance of the resolution type and return it. In every subsequent request, the same pointer
			/// will be returned. The container does not manage the allocated pointer - this must later be deleted by the consumer.
			/// @tparam TRequest The type of the requested object.
			/// @tparam TResolve The type to resolve to. This must be convertible from TRequest.
			/// @param name Optionally, a name for the binding.
			/// @returns The container instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest, typename TResolve = TRequest>
			auto& BindSingletonRawPointer(std::string const& name = "")
			{
				static_assert(
					std::is_convertible<TResolve*, TRequest*>::value,
					"Could not bind pointer - The resolution pointer type is not convertible to the request pointer type.");

				if constexpr (Internal::HasSerumConstructor<TResolve>::value)
				{
					auto const function = [this](ResolutionContext& context) { return TResolve::SerumConstructor(*this, context); };
					auto const innerBinding = Bindings::FunctionBinding<TRequest*>(function, name);
					auto const binding = Bindings::SingletonBinding<TRequest*>(innerBinding);
					return this->BindCore(binding, name);
				}
				else
				{
					auto const function = [](ResolutionContext&) { return new TResolve; };
					auto const innerBinding = Bindings::FunctionBinding<TRequest*>(function, name);
					auto const binding = Bindings::SingletonBinding<TRequest*>(innerBinding);
					return this->BindCore(binding, name);
				}
			}

			/// Binds the type to a std::shared_ptr instance as a singleton. When the type is first requested, the container will
			/// construct a new heap-allocated instance of the resolution type and return it. In every subsequent request, the
			/// same pointer will be returned.
			/// @tparam TRequest The type of the requested object.
			/// @tparam TResolve The type to resolve to. This must be convertible from TRequest.
			/// @param name Optionally, a name for the binding.
			/// @returns The container instance.
			/// @throws SerumException If a binding of type TRequest with the given name already exists.
			template <typename TRequest, typename TResolve = TRequest>
			auto& BindSingletonSharedPointer(std::string const& name = "")
			{
				static_assert(
					std::is_convertible<std::shared_ptr<TResolve>, std::shared_ptr<TRequest>>::value,
					"Could not bind shared pointer - The resolution pointer type is not convertible to the request pointer type.");

				if constexpr (Internal::HasSerumConstructor<TResolve>::value)
				{
					auto const function = [this](ResolutionContext& context)
					{
						return std::shared_ptr<TRequest>(TResolve::SerumConstructor(*this, context));
					};
					auto const innerBinding = Bindings::FunctionBinding<std::shared_ptr<TRequest>>(function, name);
					auto const binding = Bindings::SingletonBinding<std::shared_ptr<TRequest>>(innerBinding);
					return this->BindCore(binding, name);
				}
				else
				{
					auto const function = [](ResolutionContext&) { return std::make_shared<TResolve>(); };
					auto const innerBinding = Bindings::FunctionBinding<std::shared_ptr<TRequest>>(function, name);
					auto const binding = Bindings::SingletonBinding<std::shared_ptr<TRequest>>(innerBinding);
					return this->BindCore(binding, name);
				}
			}

		private:
			[[nodiscard]] std::optional<Internal::AnyBindingWrapper> GetBinding(Bindings::BindingKey const& key) const
			{
				auto const iterator = bindings.find(key);

				return iterator == bindings.end()
					? std::nullopt
					: std::optional<Internal::AnyBindingWrapper>(iterator->second);
			}

			void ThrowIfBindingExists(Bindings::BindingKey const& key) const
			{
				auto const existingBinding = GetBinding(key);

				if (existingBinding.has_value())
				{
					std::stringstream errorMessage;
					errorMessage << "A binding already exists for " << key << ".\n";

					throw SerumException(errorMessage.str());
				}
			}

			template <typename TBinding>
			auto& BindCore(TBinding const& binding, std::string const& name)
			{
				auto const key = binding.GetBindingKey();
				this->ThrowIfBindingExists(key);
				bindings[key] = Internal::AnyBindingWrapper(binding);

				return *this;
			}

			template <typename TRequest>
			[[nodiscard]] auto GetCore(ResolutionContext& resolutionContext, std::string const& name)
			{
				auto const key = Bindings::BindingKey(typeid(TRequest), name);
				auto const optionalBinding = GetBinding(key);

				if (!optionalBinding.has_value())
				{
					std::stringstream errorMessageStream;
					errorMessageStream << "No binding registered for " << key << ".";
					throw SerumException(errorMessageStream.str());
				}

				const auto& binding = optionalBinding.value();
				switch (binding.GetBindingType())
				{
					case Bindings::BindingType::Function:
						return binding.AsFunctionBinding<TRequest>().Resolve(resolutionContext);

					case Bindings::BindingType::Resolver:
						return binding.AsResolverBinding<TRequest>().Resolve(resolutionContext);

					case Bindings::BindingType::Singleton:
					{
						// This is currently a bit of a hack around the fact that the underlying bindings
						// are returned by value. To make sure that the correct 'isResolved' value is set
						// in the singleton binding we can just overwrite it here.

						auto singletonBinding = binding.AsSingletonBinding<TRequest>();
						auto result = singletonBinding.Resolve(resolutionContext);
						bindings[key] = Internal::AnyBindingWrapper(singletonBinding);
						return result;
					}


					case Bindings::BindingType::Unknown:
					default:
						throw SerumException("Could not resolve binding. Binding type was unknown or invalid.");
				}
			}

			/// Stores the bindings.
			BindingCollection bindings{};
	};
}

#endif // SERUM_SERUM_CONTAINER_HPP
