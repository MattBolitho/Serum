/// @file Binding.hpp
/// Defines a type for storing information for a binding.

#ifndef SERUM_BINDINGS_BINDING_HPP
#define SERUM_BINDINGS_BINDING_HPP

#include <string>
#include <typeindex>
#include "Serum/Bindings/BindingType.hpp"

namespace Serum::Bindings
{
	/// Stores information about a binding.
	/// @tparam TRequest The type used to request the service in the binding.
	template <typename TRequest>
	class Binding
	{
		public:
			/// Deleted default constructor.
			Binding() = delete;

			/// Copy constructor.
			/// @param binding The binding to copy.
			Binding(const Binding& binding) noexcept = default;

			/// Move constructor.
			/// @param binding The binding to move.
			Binding(Binding&& binding) noexcept = default;

			/// Public virtual destructor.
			virtual ~Binding() = default;

			/// Copy assignment operator.
			/// @param binding The binding to copy.
			Binding& operator=(const Binding& binding) = default;

			/// Move assignment operator.
			/// @param binding The binding to move.
			Binding& operator=(Binding&& binding) = default;

			/// Resolves the binding.
			/// @returns The resolved service.
			virtual TRequest Resolve() = 0;

			/// Gets the binding type.
			/// @returns The binding type.
			[[nodiscard]] BindingType GetBindingType() const noexcept
			{
				return bindingType;
			}

			/// Gets the type index for the request type.
			/// @returns The type index for the request type.
			[[nodiscard]] std::type_index GetTypeIndex() const noexcept
			{
				return requestType;
			}

			/// Gets the name of the binding.
			/// @returns The name of the binding.
			[[nodiscard]] std::string GetName() const noexcept
			{
				return name;
			}

		protected:
			/// Initializes a new instance of the Binding class.
			/// @param bindingType The binding type.
			/// @param name Optionally, a name for the binding.
			explicit Binding(
				const BindingType bindingType,
				const std::string& name = "") noexcept
				: bindingType(bindingType),
				  requestType(typeid(TRequest)),
				  name(name)
			{
			}

		private:
			BindingType bindingType;
			std::type_index requestType;
			std::string name;
	};
}

#endif // SERUM_BINDINGS_BINDING_HPP
