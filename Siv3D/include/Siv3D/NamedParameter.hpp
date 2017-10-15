//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <type_traits>
# include <tuple>

namespace s3d
{
	template <class Tag, class Type>
	class NamedParameter
	{
	private:

		Type m_value;

	public:

		constexpr NamedParameter()
			: m_value() {}

		explicit constexpr NamedParameter(Type value)
			: m_value(value) {}

		template <class U, class V = Type, std::enable_if_t<std::is_convertible_v<U, V>>* = nullptr>
		constexpr NamedParameter(const NamedParameter<Tag, U>& other)
			: m_value(other.value()) {}

		template <class... Args, class V = Type, std::enable_if_t<std::is_constructible_v<V, Args...>>* = nullptr>
		constexpr NamedParameter(const NamedParameter<Tag, std::tuple<Args...>>& tuple)
			: m_value(std::make_from_tuple<Type>(tuple.value())) {}

		constexpr const Type* operator-> () const
		{
			return std::addressof(m_value);
		}

		constexpr const Type& operator* () const
		{
			return m_value;
		}

		constexpr const Type& value() const
		{
			return m_value;
		}
	};

	template <class Tag, class Type>
	class NamedParameter<Tag, Type&>
	{
	private:

		Type* m_ref;

	public:

		constexpr NamedParameter() noexcept
			: m_ref(nullptr) {}

		constexpr NamedParameter(Type& value) noexcept
			: m_ref(std::addressof(value)) {}

		constexpr Type* operator-> () const
		{
			return m_ref;
		}

		constexpr Type& operator* () const
		{
			return *m_ref;
		}

		constexpr Type& value() const
		{
			return *m_ref;
		}
	};

	template <class Tag>
	struct NamedParameterHelper
	{
		template <class Type>
		using named_argument_type = NamedParameter<Tag, Type>;

		template <class Type>
		constexpr NamedParameter<Tag, std::decay_t<Type>> operator= (Type&& value) const
		{
			return NamedParameter<Tag, std::decay_t<Type>>(std::forward<Type>(value));
		}

		template <class... Args>
		constexpr NamedParameter<Tag, std::tuple<Args...>> operator() (const Args&... args) const
		{
			return NamedParameter<Tag, std::tuple<Args...>>(std::make_tuple(args...));
		}

		template <class Type>
		constexpr NamedParameter<Tag, Type&> operator= (std::reference_wrapper<Type> value) const
		{
			return NamedParameter<Tag, Type&>(value.get());
		}

		template <class Type>
		constexpr NamedParameter<Tag, Type&> operator() (std::reference_wrapper<Type> value) const
		{
			return NamedParameter<Tag, Type&>(value.get());
		}
	};

	# define SIV3D_NAMED_PARAMETER(name) \
	constexpr auto name = NamedParameterHelper<struct name##_tag>{};\
	template <class Type> using name##_ = NamedParameterHelper<struct name##_tag>::named_argument_type<Type>
}

namespace s3d
{
	namespace Arg
	{
		SIV3D_NAMED_PARAMETER(generator);
		SIV3D_NAMED_PARAMETER(generator0_1);
		SIV3D_NAMED_PARAMETER(radix);
		SIV3D_NAMED_PARAMETER(upperCase);
		SIV3D_NAMED_PARAMETER(r);
		SIV3D_NAMED_PARAMETER(theta);
		SIV3D_NAMED_PARAMETER(phi);
		SIV3D_NAMED_PARAMETER(y);
		SIV3D_NAMED_PARAMETER(center);
		SIV3D_NAMED_PARAMETER(topLeft);
		SIV3D_NAMED_PARAMETER(topRight);
		SIV3D_NAMED_PARAMETER(bottomLeft);
		SIV3D_NAMED_PARAMETER(bottomRight);
		SIV3D_NAMED_PARAMETER(left);
		SIV3D_NAMED_PARAMETER(right);
		SIV3D_NAMED_PARAMETER(top);
		SIV3D_NAMED_PARAMETER(bottom);
		SIV3D_NAMED_PARAMETER(topCenter);
		SIV3D_NAMED_PARAMETER(bottomCenter);
		SIV3D_NAMED_PARAMETER(leftCenter);
		SIV3D_NAMED_PARAMETER(rightCenter);
		SIV3D_NAMED_PARAMETER(source);
		SIV3D_NAMED_PARAMETER(loop);
		SIV3D_NAMED_PARAMETER(loopBegin);
		SIV3D_NAMED_PARAMETER(loopEnd);
		SIV3D_NAMED_PARAMETER(code);
	}
}
