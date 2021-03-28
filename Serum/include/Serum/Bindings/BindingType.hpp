/// @file BindingType.hpp
/// Defines an enumeration for the different types of bindings.

#ifndef SERUM_BINDINGS_BINDING_TYPE_HPP
#define SERUM_BINDINGS_BINDING_TYPE_HPP

#include <string>
#include <ostream>

namespace Serum::Bindings
{
	/// An enumeration for the different types of bindings.
	enum class BindingType
	{
		/// The types are bound such that the container
		/// constructs the instance.
		Construct,

		/// The types are bound such that a constant value
		/// is always resolved.
		Constant,

		/// The types are bound such that the container calls
		/// a given function to resolve the instance.
		Function
	};

	/// Overload of the stream operator for string functionality.
	inline std::ostream& operator <<(std::ostream& stream, const BindingType binding)
	{
		switch (binding)
		{
			case BindingType::Construct:
				stream << "Construct";
				break;

			case BindingType::Constant:
				stream << "Constant";
				break;

			case BindingType::Function:
				stream << "Function";
				break;

			default:
				stream << "Unknown binding type";
				break;
		}

		return stream;
	}
}

#endif // SERUM_BINDINGS_BINDING_TYPE_HPP
