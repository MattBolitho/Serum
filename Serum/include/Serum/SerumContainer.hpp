/// @file SerumContainer.hpp
/// Defines a type that allows bindings to be registered and resolved.

#ifndef SERUM_SERUM_CONTAINER_HPP
#define SERUM_SERUM_CONTAINER_HPP

#include <unordered_map>
#include <typeindex>
#include <any>

namespace Serum
{
	/// Allows bindings to be registered and resolved.
	class SerumContainer
	{
		public:
			/// Initializes a new instance of the SerumContainer class.
			SerumContainer() = default;



		private:
			std::unordered_map<std::type_index, std::any> bindings{};
	};
}

#endif // SERUM_SERUM_CONTAINER_HPP
