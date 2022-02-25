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
# include "Common.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"

namespace s3d
{
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

		union
		{
			/// @brief 楕円の X 軸 Y 軸に沿った半径
			position_type axes;

			struct
			{
				/// @brief 楕円の X 軸上の半径
				value_type a;

				/// @brief 楕円の Y 軸上の半径
				value_type b;
			};
		};

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		/// @brief 
		SIV3D_NODISCARD_CXX20
		Ellipse() = default;

		/// @brief 
		/// @param r 
		SIV3D_NODISCARD_CXX20
		explicit constexpr Ellipse(size_type r) noexcept;

		/// @brief 
		/// @param _a 
		/// @param _b 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(size_type _a, size_type _b) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param r 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(value_type _x, value_type _y, size_type r) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param _a 
		/// @param _b 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(value_type _x, value_type _y, size_type _a, size_type _b) noexcept;

		/// @brief 
		/// @param _center 
		SIV3D_NODISCARD_CXX20
		explicit constexpr Ellipse(position_type _center) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(const position_type& _center, size_type r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _a 
		/// @param _b 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(const position_type& _center, size_type _a, size_type _b) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param _axes 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(value_type _x, value_type _y, const Vec2& _axes) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _axes 
		SIV3D_NODISCARD_CXX20
		constexpr Ellipse(const position_type& _center, const Vec2& _axes) noexcept;

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

		constexpr Ellipse& set(value_type _x, value_type _y, size_type _a, size_type _b) noexcept;

		constexpr Ellipse& set(value_type _x, value_type _y, size_type _r) noexcept;

		constexpr Ellipse& set(const position_type& _center, size_type _r) noexcept;

		constexpr Ellipse& set(const position_type& _center, size_type _a, size_type _b) noexcept;

		constexpr Ellipse& set(value_type _x, value_type _y, const Vec2& _axes) noexcept;

		constexpr Ellipse& set(const position_type& _center, const Vec2& _axes) noexcept;

		constexpr Ellipse& set(const Circle& circle) noexcept;

		constexpr Ellipse& set(const RectF& rect) noexcept;

		constexpr Ellipse& set(const Ellipse& ellipse) noexcept;

		constexpr Ellipse& setCenter(value_type _x, value_type _y) noexcept;

		constexpr Ellipse& setCenter(const position_type& _center) noexcept;

		constexpr Ellipse& setPos(value_type _x, value_type _y) noexcept;

		constexpr Ellipse& setPos(const position_type& _center) noexcept;

		constexpr Ellipse& setAxes(value_type _r) noexcept;

		constexpr Ellipse& setAxes(size_type _a, size_type _b) noexcept;

		constexpr Ellipse& setAxes(const Vec2& _axes) noexcept;

		[[nodiscard]]
		constexpr Ellipse movedBy(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr Ellipse movedBy(const position_type& v) const noexcept;

		constexpr Ellipse& moveBy(value_type _x, value_type _y) noexcept;

		constexpr Ellipse& moveBy(const position_type& v) noexcept;

		[[nodiscard]]
		constexpr Ellipse stretched(value_type size) const noexcept;

		[[nodiscard]]
		constexpr Ellipse stretched(double _x, double _y) const noexcept;

		[[nodiscard]]
		constexpr Ellipse scaled(double s) const noexcept;

		[[nodiscard]]
		constexpr Ellipse scaled(double sx, double sy) const noexcept;

		[[nodiscard]]
		constexpr position_type top() const noexcept;

		[[nodiscard]]
		constexpr position_type right() const noexcept;

		[[nodiscard]]
		constexpr position_type bottom() const noexcept;

		[[nodiscard]]
		constexpr position_type left() const noexcept;

		[[nodiscard]]
		constexpr Line horizontalDiameter() const noexcept;

		[[nodiscard]]
		constexpr Line verticalDiameter() const noexcept;

		[[nodiscard]]
		constexpr value_type area() const noexcept;

		[[nodiscard]]
		constexpr Circle boundingCircle() const noexcept;

		[[nodiscard]]
		constexpr RectF boundingRect() const noexcept;

		[[nodiscard]]
		Polygon asPolygon(uint32 quality = 24) const;

		[[nodiscard]]
		constexpr Ellipse lerp(const Ellipse& other, double f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		bool contains(const Shape2DType& other) const;

		[[nodiscard]]
		bool leftClicked() const noexcept;

		[[nodiscard]]
		bool leftPressed() const noexcept;

		[[nodiscard]]
		bool leftReleased() const noexcept;

		[[nodiscard]]
		bool rightClicked() const noexcept;

		[[nodiscard]]
		bool rightPressed() const noexcept;

		[[nodiscard]]
		bool rightReleased() const noexcept;

		[[nodiscard]]
		bool mouseOver() const noexcept;

		const Ellipse& paint(Image& dst, const Color& color) const;

		const Ellipse& overwrite(Image& dst, const Color& color) const;

		const Ellipse& draw(const ColorF& color = Palette::White) const;

		const Ellipse& draw(const ColorF& innerColor, const ColorF& outerColor) const;

		const Ellipse& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Ellipse& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

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

		friend void Formatter(FormatData& formatData, const Ellipse& value);
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
	size_t operator ()(const s3d::Ellipse& value) const noexcept
	{
		return value.hash();
	}
};
