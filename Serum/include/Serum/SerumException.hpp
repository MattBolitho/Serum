/// @file SerumException.hpp
/// Defines an exception type for the Serum library.

#ifndef SERUM_SERUM_EXCEPTION_HPP
#define SERUM_SERUM_EXCEPTION_HPP

#include <string>
#include <stdexcept>

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
			explicit SerumException(const std::string& message)
				: std::runtime_error(message)
			{
			}
	};
}

#endif // SERUM_SERUM_EXCEPTION_HPP
