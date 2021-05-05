/// @file Binding.hpp
/// Defines a type for storing information for a binding.

#ifndef SERUM_BINDINGS_BINDING_HPP
#define SERUM_BINDINGS_BINDING_HPP

#include "Serum/Internal/Common.hpp"
#include "Serum/Bindings/BindingType.hpp"
#include "Serum/Bindings/BindingKey.hpp"
#include "Serum/ResolutionContext.hpp"

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
			Binding(Binding const& binding) noexcept = default;

			/// Move constructor.
			/// @param binding The binding to move.
			Binding(Binding&& binding) noexcept = default;

			/// Public virtual destructor.
			virtual ~Binding() = default;

			/// Copy assignment operator.
			/// @param binding The binding to copy.
			Binding& operator=(Binding const& binding) = default;

			/// Move assignment operator.
			/// @param binding The binding to move.
			Binding& operator=(Binding&& binding) = default;

			/// Resolves the binding.
			/// @param context The resolution context.
			/// @returns The resolved service.
			TRequest Resolve(ResolutionContext& context)
			{
				context.resolutionPath.emplace_back(key);

				auto result = ResolveCore(context);

				context.resolutionPath.pop_back();

				return result;
			}

			/// Deep clones the binding.
			/// @returns A clone of the binding.
			virtual std::shared_ptr<Binding<TRequest>> Clone() const = 0;

			/// Gets the binding type.
			/// @returns The binding type.
			[[nodiscard]] BindingType GetBindingType() const noexcept
			{
				return bindingType;
			}

			/// Gets a type index for the binding.
			/// @returns The type index for the binding.
			[[nodiscard]] BindingKey GetBindingKey() const noexcept
			{
				return key;
			}

		protected:
			/// Initializes a new instance of the Binding class.
			/// @param bindingType The binding type.
			/// @param name Optionally, a name for the binding.
			explicit Binding(
				BindingType const bindingType,
				std::string const& name = "") noexcept
				: bindingType(bindingType),
				  key(BindingKey(typeid(TRequest), name))
			{
			}

			/// Resolves the binding.
			/// @param resolutionContext The resolution context.
			/// @returns The resolved service.
			virtual TRequest ResolveCore(ResolutionContext& resolutionContext) = 0;

		private:
			BindingType bindingType;
			BindingKey key;
	};
}

#endif // SERUM_BINDINGS_BINDING_HPP
