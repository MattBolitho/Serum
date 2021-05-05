/// @file SingletonBinding.hpp
/// Defines a binding that wraps another binding such that it is only
/// resolved once and the same instance is always returned.

#ifndef SERUM_BINDINGS_SINGLETON_BINDING_HPP
#define SERUM_BINDINGS_SINGLETON_BINDING_HPP

#include "Serum/Internal/Common.hpp"
#include "Serum/Bindings/Binding.hpp"

namespace Serum::Bindings
{
	/// Wraps another binding such that it is only
	/// resolved once and the same instance is always returned.
	/// @tparam TRequest The type of the service to request.
	template <typename TRequest>
	class SingletonBinding final : public Binding<TRequest>
	{
		public:
			/// Initializes a new instance of the SingletonBinding class.
			/// @param binding The binding to wrap.
			explicit SingletonBinding(Binding<TRequest> const& binding) noexcept
				: Binding<TRequest>(BindingType::Singleton, binding.GetBindingKey().GetName()),
				  isResolved(false),
				  innerBinding(binding.Clone())
			{
			}

			[[nodiscard]] std::shared_ptr<Binding<TRequest>> Clone() const override
			{
				return std::make_shared<SingletonBinding>(*this);
			}

		protected:
			TRequest ResolveCore(ResolutionContext& resolutionContext) override
			{
				if (isResolved)
				{
					return resolvedValue;
				}

				auto result = innerBinding->Resolve(resolutionContext);
				resolvedValue = result;
				isResolved = true;

				return resolvedValue;
			}

		private:
			bool isResolved;
			TRequest resolvedValue;
			std::shared_ptr<Binding<TRequest>> innerBinding = nullptr;
	};
}

#endif // SERUM_BINDINGS_SINGLETON_BINDING_HPP
