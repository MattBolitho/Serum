/// @file TypeTraits.hpp
/// Defines type traits for use in Serum.

#ifndef SERUM_INTERNAL_TYPE_TRAITS_HPP
#define SERUM_INTERNAL_TYPE_TRAITS_HPP

#include "Serum/ResolutionContext.hpp"

namespace Serum
{
	class SerumContainer;

	namespace Internal
	{
		/// The expected function pointer signature of a Serum constructor.
		template <typename T>
		using SerumConstructorSignature = T* (*)(SerumContainer&, ResolutionContext&);

		/// Checks whether or not the type T has a Serum constructor.
		/// @tparam T The type to check.
		template <typename T>
		struct HasSerumConstructor final
		{
			private:
				template<typename U, SerumConstructorSignature<U>>
				struct SFINAE final {};

			    template<typename U>
				static std::true_type Test(SFINAE<U, &U::SerumConstructor>*);

			    template<typename U>
				static std::false_type Test(...);

			public:
			    static constexpr auto value = std::is_same<std::true_type, decltype(Test<T>(nullptr))>::value;
		};
	}
}

#endif // SERUM_INTERNAL_TYPE_TRAITS_HPP
