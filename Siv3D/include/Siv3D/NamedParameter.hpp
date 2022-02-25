//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <type_traits>
# include <tuple>
# include <functional>
# include <memory>
# include <utility>

namespace s3d
{
	/// @brief 名前付き変数作成クラス
	/// @tparam Tag タグ名
	/// @tparam Type 変数の値の型
	template <class Tag, class Type>
	class NamedParameter
	{
	public:

		NamedParameter() = default;

		constexpr NamedParameter(const Type& value)
			: m_value(value) {}

		template <class U, class V = Type, std::enable_if_t<std::is_convertible_v<U, V>>* = nullptr>
		constexpr NamedParameter(const NamedParameter<Tag, U>& other)
			: m_value(other.value()) {}

		template <class... Args, class V = Type, std::enable_if_t<std::is_constructible_v<V, Args...>>* = nullptr>
		constexpr NamedParameter(const NamedParameter<Tag, std::tuple<Args...>>& tuple)
			: m_value(std::make_from_tuple<Type>(tuple.value())) {}

		constexpr const Type* operator ->() const noexcept
		{
			return std::addressof(m_value);
		}

		[[nodiscard]]
		constexpr const Type& operator *() const noexcept
		{
			return m_value;
		}

		[[nodiscard]]
		constexpr const Type& value() const noexcept
		{
			return m_value;
		}

	private:

		Type m_value;
	};

	template <class Tag, class Type>
	class NamedParameter<Tag, Type&>
	{
	public:

		NamedParameter() = default;

		constexpr NamedParameter(Type& value) noexcept
			: m_ref(std::addressof(value)) {}

		constexpr Type* operator ->() const noexcept
		{
			return m_ref;
		}

		[[nodiscard]]
		constexpr Type& operator *() const noexcept
		{
			return *m_ref;
		}

		[[nodiscard]]
		constexpr Type& value() const noexcept
		{
			return *m_ref;
		}

	private:

		Type* m_ref = nullptr;
	};

	template <class Tag>
	struct NamedParameterHelper
	{
		template <class Type>
		using named_argument_type = NamedParameter<Tag, Type>;

		template <class Type>
		[[nodiscard]]
		constexpr NamedParameter<Tag, std::decay_t<Type>> operator =(Type&& value) const
		{
			return NamedParameter<Tag, std::decay_t<Type>>(std::forward<Type>(value));
		}

		template <class... Args>
		[[nodiscard]]
		constexpr NamedParameter<Tag, std::tuple<std::decay_t<Args >...>> operator ()(Args&&... args) const
		{
			return NamedParameter<Tag, std::tuple<std::decay_t<Args >...>>(std::make_tuple(std::forward<Args>(args)...));
		}

		template <class Type>
		[[nodiscard]]
		constexpr NamedParameter<Tag, Type&> operator =(std::reference_wrapper<Type> value) const
		{
			return NamedParameter<Tag, Type&>(value.get());
		}

		template <class Type>
		[[nodiscard]]
		constexpr NamedParameter<Tag, Type&> operator ()(std::reference_wrapper<Type> value) const
		{
			return NamedParameter<Tag, Type&>(value.get());
		}
	};
}

# define SIV3D_NAMED_PARAMETER(name) \
inline constexpr auto name = s3d::NamedParameterHelper<struct name##_tag>{};\
template <class Type> using name##_ = s3d::NamedParameter<struct name##_tag, Type>
