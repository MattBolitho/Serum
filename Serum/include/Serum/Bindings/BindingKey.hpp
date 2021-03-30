/// @file BindingKey.hpp
/// Defines a key type for bindings which allows them to be stored in maps.

#ifndef SERUM_BINDINGS_BINDING_KEY_HPP
#define SERUM_BINDINGS_BINDING_KEY_HPP

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

			/// Compares 2 keys.
			/// @param key The other key.
			/// @returns A comparison of the keys.
			bool operator <(const BindingKey& key) const noexcept
			{
				// todo - add names
				return requestType < key.GetRequestType();
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
		stream << "[" << bindingKey.GetRequestType().name() << ", " << bindingKey.GetName() << "]";
		return stream;
	}
}

#endif // SERUM_BINDINGS_BINDING_KEY_HPP
