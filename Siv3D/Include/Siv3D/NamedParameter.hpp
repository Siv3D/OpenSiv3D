//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <type_traits>
# include <tuple>

namespace s3d
{
	namespace detail
	{
		template <class Type, class Tuple, std::size_t... I>
		constexpr Type MakeFromTuple_impl(Tuple&& t, std::index_sequence<I...>)
		{
			return Type(std::get<I>(std::forward<Tuple>(t))...);
		}
	}

	template <class Type, class Tuple>
	constexpr Type MakeFromTuple(Tuple&& t)
	{
		return detail::MakeFromTuple_impl<Type>(std::forward<Tuple>(t),
			std::make_index_sequence<std::tuple_size_v<std::decay_t<Tuple>>>{});
	}

	template <class Type>
	constexpr Type MakeFromTuple(const std::tuple<>&)
	{
		return Type();
	}

	namespace Arg
	{
		namespace detail
		{
			template <class Tag, class ValueType>
			struct NamedParameter
			{
			private:

				ValueType m_value;

			public:

				constexpr NamedParameter()
					: m_value() {}

				explicit constexpr NamedParameter(ValueType value)
					: m_value(value) {}

				template <class U, class V = ValueType, std::enable_if_t<std::is_convertible<U, V>::value>* = nullptr>
				constexpr NamedParameter(const NamedParameter<Tag, U>& other)
					: NamedParameter(static_cast<ValueType>(*other)) {}

				template <class... Args, class V = ValueType, std::enable_if_t<std::is_constructible<V, Args...>::value>* = nullptr>
				constexpr NamedParameter(const NamedParameter<Tag, std::tuple<Args...>>& tuple)
					: m_value(MakeFromTuple<ValueType>(tuple.value())) {}

				constexpr ValueType const* operator-> () const
				{
					return &m_value;
				}

				constexpr ValueType const& operator* () const
				{
					return m_value;
				}

				constexpr ValueType const& value() const
				{
					return m_value;
				}
			};

			template <class Tag>
			struct NamedParameterHelper
			{
				template <class ValueType>
				using named_argument_type = NamedParameter<Tag, ValueType>;

				template <class ValueType>
				constexpr NamedParameter<Tag, ValueType> operator= (ValueType value) const
				{
					return NamedParameter<Tag, ValueType>(value);
				}

				template <class... Args>
				constexpr NamedParameter<Tag, std::tuple<Args...>> operator() (Args&&... args) const
				{
					return NamedParameter<Tag, std::tuple<Args...>>(std::make_tuple(args...));
				}
			};
		}

		# define SIV3D_MAKE_NAMED_PARAMETER(name) \
		constexpr auto name = detail::NamedParameterHelper<struct name##_tag>{};\
		template <class ValueType> using name##_ = detail::NamedParameterHelper<struct name##_tag>::named_argument_type<ValueType>

		SIV3D_MAKE_NAMED_PARAMETER(generator);
		SIV3D_MAKE_NAMED_PARAMETER(radix);
		SIV3D_MAKE_NAMED_PARAMETER(upperCase);
		SIV3D_MAKE_NAMED_PARAMETER(r);
		SIV3D_MAKE_NAMED_PARAMETER(theta);
		SIV3D_MAKE_NAMED_PARAMETER(center);
	}
}
