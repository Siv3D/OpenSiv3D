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

		template <class Type, class Tuple>
		constexpr Type MakeFromTuple(Tuple&& t)
		{
			return detail::MakeFromTuple_impl<Type>(std::forward<Tuple>(t),
				std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
		}

		template <class Type>
		constexpr Type MakeFromTuple(const std::tuple<>&)
		{
			return Type();
		}
	}

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
			: m_value(other.value()) {}

		template <class... Args, class V = ValueType, std::enable_if_t<std::is_constructible<V, Args...>::value>* = nullptr>
		constexpr NamedParameter(const NamedParameter<Tag, std::tuple<Args...>>& tuple)
			: m_value(detail::MakeFromTuple<ValueType>(tuple.value())) {}

		constexpr const ValueType* operator-> () const
		{
			return &m_value;
		}

		constexpr const ValueType& operator* () const
		{
			return m_value;
		}

		constexpr const ValueType& value() const
		{
			return m_value;
		}
	};

	template <class Tag, class ValueType>
	struct NamedParameter<Tag, ValueType&>
	{
	private:

		ValueType* m_ref;

	public:

		constexpr NamedParameter() noexcept
			: m_ref(nullptr) {}

		constexpr NamedParameter(ValueType& value) noexcept
			: m_ref(&value) {}

		constexpr ValueType* operator-> () const
		{
			return m_ref;
		}

		constexpr ValueType& operator* () const
		{
			return *m_ref;
		}

		constexpr ValueType& value() const
		{
			return *m_ref;
		}
	};

	template <class Tag>
	struct NamedParameterHelper
	{
		template <class ValueType>
		using named_argument_type = NamedParameter<Tag, ValueType>;

		template <class ValueType>
		constexpr NamedParameter<Tag, std::decay_t<ValueType>> operator= (ValueType&& value) const
		{
			return NamedParameter<Tag, std::decay_t<ValueType>>(std::forward<ValueType>(value));
		}

		template <class... Args>
		constexpr NamedParameter<Tag, std::tuple<Args...>> operator() (const Args&... args) const
		{
			return NamedParameter<Tag, std::tuple<Args...>>(std::make_tuple(args...));
		}

		template <class ValueType>
		constexpr NamedParameter<Tag, ValueType&> operator= (std::reference_wrapper<ValueType> value) const
		{
			return NamedParameter<Tag, ValueType&>(value.get());
		}

		template <class ValueType>
		constexpr NamedParameter<Tag, ValueType&> operator() (std::reference_wrapper<ValueType> value) const
		{
			return NamedParameter<Tag, ValueType&>(value.get());
		}
	};

	# define SIV3D_MAKE_NAMED_PARAMETER(name) \
	constexpr auto name = NamedParameterHelper<struct name##_tag>{};\
	template <class ValueType> using name##_ = NamedParameterHelper<struct name##_tag>::named_argument_type<ValueType>
}

namespace s3d
{
	namespace Arg
	{
		SIV3D_MAKE_NAMED_PARAMETER(generator);
		SIV3D_MAKE_NAMED_PARAMETER(radix);
		SIV3D_MAKE_NAMED_PARAMETER(upperCase);
		SIV3D_MAKE_NAMED_PARAMETER(r);
		SIV3D_MAKE_NAMED_PARAMETER(theta);
		SIV3D_MAKE_NAMED_PARAMETER(center);
	}
}
