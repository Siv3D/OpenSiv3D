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

namespace s3d
{
	template <class Type>
	inline constexpr auto LessThan(const Type& right)
	{
		return [=](const auto& left) -> bool { return left < right; };
	}

	template <class Type>
	inline constexpr auto LessThanEqual(const Type& right)
	{
		return [=](const auto& left) -> bool { return left <= right; };
	}

	template <class Type>
	inline constexpr auto GreaterThanEqual(const Type& right)
	{
		return [=](const auto& left) -> bool { return left >= right; };
	}

	template <class Type>
	inline constexpr auto GreaterThan(const Type& right)
	{
		return [=](const auto& left) -> bool { return left > right; };
	}

	template <class Type>
	inline constexpr auto Equal(const Type& right)
	{
		return [=](const auto& left) -> bool { return left == right; };
	}

	template <class Type>
	inline constexpr auto NotEqual(const Type& right)
	{
		return [=](const auto& left) -> bool { return left != right; };
	}

	namespace detail
	{
		template <class MinType, class MaxType>
		struct InRange_impl
		{
			const MinType m_min;

			const MaxType m_max;

			constexpr InRange_impl(const MinType& min, const MaxType& max)
				: m_min(min)
				, m_max(max) {}

			template <class Type>
			constexpr bool operator() (const Type& value) const
			{
				return m_min <= value && value <= m_max;
			}
		};

		template <class Type = void>
		struct Odd_impl
		{
			constexpr bool operator() (const Type& value) const
			{
				return value % 2 != 0;
			}
		};

		template <>
		struct Odd_impl<void>
		{
			template <class Type>
			constexpr bool operator() (const Type& value) const
			{
				return value % 2 != 0;
			}
		};

		template <class Type = void>
		struct Even_impl
		{
			constexpr bool operator() (const Type& value) const
			{
				return value % 2 != 0;
			}
		};

		template <>
		struct Even_impl<void>
		{
			template <class Type>
			constexpr bool operator() (const Type& value) const
			{
				return value % 2 == 0;
			}
		};

		template <class Type = void>
		struct Not_impl
		{
			constexpr bool operator() (const Type& value) const
			{
				return !value;
			}
		};

		template <>
		struct Not_impl<void>
		{
			template <class Type>
			constexpr bool operator() (const Type& value) const
			{
				return !value;
			}
		};

		template <class Type = void>
		struct NotNot_impl
		{
			constexpr bool operator() (const Type& value) const
			{
				return !!value;
			}
		};

		template <>
		struct NotNot_impl<void>
		{
			template <class Type>
			constexpr bool operator() (const Type& value) const
			{
				return !!value;
			}
		};
	}

	template <class MinType, class MaxType>
	inline constexpr auto InRange(const MinType& min, const MaxType& max)
	{
		return detail::InRange_impl<MinType, MaxType>(min, max);
	}

	inline constexpr auto Odd()
	{
		return detail::Odd_impl<>();
	}

	inline constexpr auto Even()
	{
		return detail::Even_impl<>();
	}

	inline constexpr auto Not()
	{
		return detail::Not_impl<>();
	}

	inline constexpr auto NotNot()
	{
		return detail::NotNot_impl<>();
	}
}
