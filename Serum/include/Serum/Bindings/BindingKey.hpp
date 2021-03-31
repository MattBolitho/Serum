/// @file BindingKey.hpp
/// Defines a key type for bindings which allows them to be stored in maps.

#ifndef SERUM_BINDINGS_BINDING_KEY_HPP
#define SERUM_BINDINGS_BINDING_KEY_HPP

#include <iomanip>
#include <ostream>
#include <string>
#include <typeindex>

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
				const std::type_index& requestType,
				const std::string& name) noexcept
				: requestType(requestType),
				  name(name)
			{
			}

			/// Copy constructor.
			/// @param key The key.
			BindingKey(const BindingKey& key) = default;

			/// Copy assignment operator.
			/// @param key The key.
			BindingKey& operator=(const BindingKey& key) = default;

			/// Equality operator for binding keys.
			/// @param otherKey The other binding key.
			/// @returns True if the keys are the same and false otherwise.
			bool operator==(const BindingKey& otherKey) const noexcept
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

	/// Overload of the stream operator for string functionality.
	/// @param stream The stream.
	/// @param bindingKey The binding key.
	/// @returns The stream.
	inline std::ostream& operator <<(std::ostream& stream, const BindingKey& bindingKey)
	{
		stream << "[" << bindingKey.GetRequestType().name() << ", " << std::quoted(bindingKey.GetName()) << "]";
		return stream;
	}
}

namespace std
{
	// Injects a template specialization for Serum::Bindings::BindingKey into the standard
	// namespace so it can be used in maps.
	// See: https://en.cppreference.com/w/cpp/utility/hash

	template <>
	struct hash<Serum::Bindings::BindingKey>
	{
		std::size_t operator()(const Serum::Bindings::BindingKey& key) const noexcept
		{
			return std::hash<std::string>{}(key.GetName()) ^ std::hash<std::type_index>{}(key.GetRequestType());
		}
	};
}

#endif // SERUM_BINDINGS_BINDING_KEY_HPP
