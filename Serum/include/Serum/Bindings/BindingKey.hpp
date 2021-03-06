/// @file BindingKey.hpp
/// Defines a key type for bindings which allows them to be stored in maps.

#ifndef SERUM_BINDINGS_BINDING_KEY_HPP
#define SERUM_BINDINGS_BINDING_KEY_HPP

#include "Serum/Internal/Common.hpp"

namespace Serum::Bindings
{
	/// A key type for bindings which allows them to be stored in maps.
	class BindingKey final
	{
		public:
			/// Initializes a new instance of the BindingKey class.
			/// @param requestType The request type.
			/// @param name The name of the binding.
			BindingKey(
				std::type_index const& requestType,
				std::string const& name) noexcept
				: requestType(requestType),
				  name(name)
			{
			}

			/// Copy constructor.
			/// @param key The key.
			BindingKey(BindingKey const& key) = default;

			/// Copy assignment operator.
			/// @param key The key.
			BindingKey& operator=(BindingKey const& key) = default;

			/// Overload of the stream operator.
			/// @param stream The stream.
			/// @param bindingKey The binding key.
			/// @returns The stream.
			friend std::ostream& operator <<(std::ostream& stream, BindingKey const& bindingKey)
			{
				stream << "[" << bindingKey.requestType.name() << ", \"" << bindingKey.name << "\"]";
				return stream;
			}

			/// Equality operator for binding keys.
			/// @param otherKey The other binding key.
			/// @returns True if the keys are the same and false otherwise.
			bool operator==(BindingKey const& otherKey) const noexcept
			{
				return name == otherKey.name && requestType == otherKey.requestType;
			}

			/// Gets the request type information.
			/// @returns The request type information.
			[[nodiscard]] std::type_index GetRequestType() const noexcept
			{
				return requestType;
			}

			/// Gets the name of the binding.
			/// @returns The name of the binding.
			[[nodiscard]] std::string GetName() const noexcept
			{
				return name;
			}

		private:
			std::type_index requestType;
			std::string name;
	};
}

namespace std
{
	// Injects a template specialization for Serum::Bindings::BindingKey into the standard
	// namespace so it can be used in maps.
	// See: https://en.cppreference.com/w/cpp/utility/hash

	template <>
	struct hash<Serum::Bindings::BindingKey>
	{
		std::size_t operator()(Serum::Bindings::BindingKey const& key) const noexcept
		{
			return std::hash<std::string>{}(key.GetName()) ^ std::hash<std::type_index>{}(key.GetRequestType());
		}
	};
}

#endif // SERUM_BINDINGS_BINDING_KEY_HPP
