/// @file BindingType.hpp
/// Defines an enumeration for the different types of bindings.

#ifndef SERUM_BINDINGS_BINDING_TYPE_HPP
#define SERUM_BINDINGS_BINDING_TYPE_HPP

#include "Serum/Internal/Common.hpp"

namespace Serum::Bindings
{
	/// An enumeration for the different types of bindings.
	enum class BindingType
	{
		/// An unknown binding type.
		Unknown,

		/// The type is bound to a function which resolves the instance.
		Function,

		/// The type is bound to the result of a method call on a SerumResolver instance.
		Resolver,

		/// The type is bound such that it is resolved only once.
		Singleton
	};

	/// Overload of the stream operator for string functionality.
	inline std::ostream& operator <<(std::ostream& stream, BindingType const binding)
	{
		switch (binding)
		{
			case BindingType::Unknown:
				stream << "Unknown";
				break;

			case BindingType::Function:
				stream << "Function";
				break;

			case BindingType::Resolver:
				stream << "Resolver";
				break;

			case BindingType::Singleton:
				stream << "Singleton";
				break;

			default:
				stream << "Unknown binding type";
				break;
		}

		return stream;
	}
}

#endif // SERUM_BINDINGS_BINDING_TYPE_HPP
