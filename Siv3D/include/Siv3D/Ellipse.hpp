//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"

namespace s3d
{
	struct Circle;

	template <class SizeType> struct Rectangle;
	using Rect = Rectangle<Point>;
	using RectF = Rectangle<Vec2>;

	/// @brief 楕円
	struct Ellipse
	{
		using position_type	= Vec2;

		using size_type		= position_type::value_type;

		using value_type	= position_type::value_type;

		SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			/// @brief 楕円の中心座標
			position_type center;

			struct
			{
				/// @brief 楕円の中心の X 座標
				value_type x;

				/// @brief 楕円の中心の Y 座標
				value_type y;
			};
		};

		/// @brief 楕円の X 軸上の半径
		value_type a;

		/// @brief 楕円の Y 軸上の半径
		value_type b;

		SIV3D_DISABLE_MSVC_WARNINGS_POP()

		/// @brief 
		SIV3D_NODISCARD_CXX20
		Ellipse() = default;

		/// @brief 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		explicit constexpr Ellipse(double _r) noexcept;

		/// @brief 
		/// @param _a 
		/// @param _b 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(double _a, double _b) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(double _x, double _y, double _r) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param _a 
		/// @param _b 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(double _x, double _y, double _a, double _b) noexcept;

		/// @brief 
		/// @param _center 
		SIV3D_NODISCARD_CXX20
		explicit constexpr Ellipse(Vec2 _center) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(const Vec2& _center, double _r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _a 
		/// @param _b 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(const Vec2& _center, double _a, double _b) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param _axis 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(double _x, double _y, const Vec2& _axis) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _axis 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(const Vec2& _center, const Vec2& _axis) noexcept;

		/// @brief 
		/// @param circle 
		SIV3D_NODISCARD_CXX20
		explicit constexpr Ellipse(const Circle& circle) noexcept;

		/// @brief 
		/// @param rect 
		SIV3D_NODISCARD_CXX20
		explicit constexpr Ellipse(const RectF& rect) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Ellipse& lhs, const Ellipse& rhs) noexcept
		{
			return (lhs.center == rhs.center)
				&& (lhs.a == rhs.a)
				&& (lhs.b == rhs.b);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Ellipse& lhs, const Ellipse& rhs) noexcept
		{
			return (lhs.center != rhs.center)
				|| (lhs.a != rhs.a)
				|| (lhs.b != rhs.b);
		}



		[[nodiscard]]
		size_t hash() const noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Ellipse& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.a << CharType(',') << CharType(' ')
				<< value.b << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Ellipse& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.a >> unused
				>> value.b >> unused;
		}

		friend void Formatter(FormatData& formatData, const Ellipse& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Ellipse& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Ellipse, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Ellipse& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.x, value.y, value.a, value.b);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y, value.a, value.b);
		}
	}
};

template <>
struct std::hash<s3d::Ellipse>
{
	[[nodiscard]]
	size_t operator()(const s3d::Ellipse& value) const noexcept
	{
		return value.hash();
	}
};
