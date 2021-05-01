/// @file ResolutionContext.hpp
/// Defines a type used to store contextual information about a binding as it is resolved.

#ifndef SERUM_RESOLUTION_CONTEXT_HPP
#define SERUM_RESOLUTION_CONTEXT_HPP

#include "Serum/Internal/Common.hpp"
#include "Bindings/BindingKey.hpp"

namespace Serum
{
	namespace Bindings
	{
		template <typename TRequest>
		class Binding;
	}

	/// Stores contextual information about a binding as it is resolved.
	class ResolutionContext final
	{
		template <typename TRequest>
		friend class Bindings::Binding;

		public:
			/// Initializes a new instance of the resolution context class.
			explicit ResolutionContext() = default;

			/// Gets the key of the binding that is making the request (i.e. the previous request in the resolution path).
			/// @returns The key of the binding that is making the request.
			[[nodiscard]] auto GetRequestingBinding() const
			{
				if (resolutionPath.empty())
				{
					throw SerumException("Cannot get requesting type - resolution path is empty.");
				}

				return resolutionPath.back();
			}

			/// Checks whether or not the resolution path contains a key with the given type.
			/// @returns true if the resolution path contains a key with the given type, false otherwise.
			[[nodiscard]] auto ResolutionPathContainsType(std::type_info const& type) const
			{
				auto const key = Bindings::BindingKey(type, "");

				return std::find(resolutionPath.begin(), resolutionPath.end(), key) != resolutionPath.end();
			}

			/// Checks whether or not the resolution path contains the given key.
			/// @returns true if the resolution path contains the given key, false otherwise.
			[[nodiscard]] auto ResolutionPathContainsKey(Bindings::BindingKey const& key) const
			{
				return std::find(resolutionPath.begin(), resolutionPath.end(), key) != resolutionPath.end();
			}

		private:
			std::vector<Bindings::BindingKey> resolutionPath{};
	};
}

#endif // SERUM_RESOLUTION_CONTEXT_HPP
