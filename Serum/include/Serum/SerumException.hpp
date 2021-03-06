/// @file SerumException.hpp
/// Defines an exception type for the Serum library.

#ifndef SERUM_SERUM_EXCEPTION_HPP
#define SERUM_SERUM_EXCEPTION_HPP

#include "Serum/Internal/Common.hpp"

namespace Serum
{
	/// An exception type for the Serum library.
	class SerumException final : public std::runtime_error
	{
		public:
			/// Initializes a new instance of the SerumException class.
			/// @param message The message.
			explicit SerumException(const char* message)
				: std::runtime_error(message)
			{
			}

			/// Initializes a new instance of the SerumException class.
			/// @param message The message.
			explicit SerumException(std::string const& message)
				: std::runtime_error(message)
			{
			}
	};
}

#endif // SERUM_SERUM_EXCEPTION_HPP
