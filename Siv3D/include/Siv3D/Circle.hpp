//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
	struct Line;
	struct Ellipse;
	class Polygon;

	/// @brief 円
	struct Circle
	{
		using position_type	= Vec2;

		using size_type		= position_type::value_type;

		using value_type	= position_type::value_type;

	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			/// @brief 円の中心座標
			position_type center;

			struct
			{
				/// @brief 円の中心の X 座標
				value_type x;

				/// @brief 円の中心の Y 座標
				value_type y;
			};
		};

		/// @brief 円の半径
		size_type r;

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		/// @brief 
		SIV3D_NODISCARD_CXX20
		Circle() = default;

		/// @brief 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		explicit constexpr Circle(size_type _r) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(value_type _x, value_type _y, size_type _r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(position_type _center, size_type _r) noexcept;
		
		/// @brief 
		/// @param _center 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::center_<position_type> _center, size_type _r) noexcept;

		/// @brief 
		/// @param topLeft 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::topLeft_<position_type> topLeft, size_type _r) noexcept;

		/// @brief 
		/// @param topCenter 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::topCenter_<position_type> topCenter, size_type _r) noexcept;

		/// @brief 
		/// @param topRight 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::topRight_<position_type> topRight, size_type _r) noexcept;

		/// @brief 
		/// @param rightCenter 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::rightCenter_<position_type> rightCenter, size_type _r) noexcept;

		/// @brief 
		/// @param bottomRight 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::bottomRight_<position_type> bottomRight, size_type _r) noexcept;

		/// @brief 
		/// @param bottomCenter 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::bottomCenter_<position_type> bottomCenter, size_type _r) noexcept;

		/// @brief 
		/// @param bottomLeft 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::bottomLeft_<position_type> bottomLeft, size_type _r) noexcept;

		/// @brief 
		/// @param leftCenter 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr Circle(Arg::leftCenter_<position_type> leftCenter, size_type _r) noexcept;

		/// @brief 
		/// @param p0 
		/// @param p1 
		SIV3D_NODISCARD_CXX20
		Circle(position_type p0, position_type p1) noexcept;

		/// @brief 
		/// @param p0 
		/// @param p1 
		/// @param p2 
		SIV3D_NODISCARD_CXX20
		Circle(const position_type& p0, const position_type& p1, const position_type& p2) noexcept;

		/// @brief 
		/// @param diameter 
		SIV3D_NODISCARD_CXX20
		explicit Circle(const Line& diameter) noexcept;

		/// @brief 
		/// @param _center 
		/// @param p 
		SIV3D_NODISCARD_CXX20
		Circle(Arg::center_<position_type> _center, const position_type& p) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Circle& lhs, const Circle& rhs) noexcept
		{
			return (lhs.center == rhs.center)
				&& (lhs.r == rhs.r);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Circle& lhs, const Circle& rhs) noexcept
		{
			return (lhs.center != rhs.center)
				|| (lhs.r != rhs.r);
		}

		constexpr Circle& set(value_type _x, value_type _y, size_type _r) noexcept;

		constexpr Circle& set(const position_type& _center, size_type _r) noexcept;

		constexpr Circle& set(Arg::center_<position_type> _center, size_type _r) noexcept;

		constexpr Circle& set(Arg::topLeft_<position_type> topLeft, size_type _r) noexcept;

		constexpr Circle& set(Arg::topCenter_<position_type> topCenter, size_type _r) noexcept;

		constexpr Circle& set(Arg::topRight_<position_type> topRight, size_type _r) noexcept;

		constexpr Circle& set(Arg::rightCenter_<position_type> rightCenter, size_type _r) noexcept;

		constexpr Circle& set(Arg::bottomRight_<position_type> bottomRight, size_type _r) noexcept;

		constexpr Circle& set(Arg::bottomCenter_<position_type> bottomCenter, size_type _r) noexcept;

		constexpr Circle& set(Arg::bottomLeft_<position_type> bottomLeft, size_type _r) noexcept;

		constexpr Circle& set(Arg::leftCenter_<position_type> leftCenter, size_type _r) noexcept;

		constexpr Circle& set(const Circle& circle) noexcept;

		constexpr Circle& setCenter(value_type _x, value_type _y) noexcept;

		constexpr Circle& setCenter(const position_type& _center) noexcept;

		constexpr Circle& setPos(value_type _x, value_type _y) noexcept;

		constexpr Circle& setPos(const position_type& _center) noexcept;

		constexpr Circle& setPos(Arg::center_<position_type> _center) noexcept;

		constexpr Circle& setPos(Arg::topLeft_<position_type> topLeft) noexcept;

		constexpr Circle& setPos(Arg::topCenter_<position_type> topCenter) noexcept;

		constexpr Circle& setPos(Arg::topRight_<position_type> topRight) noexcept;

		constexpr Circle& setPos(Arg::rightCenter_<position_type> rightCenter) noexcept;

		constexpr Circle& setPos(Arg::bottomRight_<position_type> bottomRight) noexcept;

		constexpr Circle& setPos(Arg::bottomCenter_<position_type> bottomCenter) noexcept;

		constexpr Circle& setPos(Arg::bottomLeft_<position_type> bottomLeft) noexcept;

		constexpr Circle& setPos(Arg::leftCenter_<position_type> leftCenter) noexcept;

		constexpr Circle& setR(value_type _r) noexcept;

		[[nodiscard]]
		constexpr Circle movedBy(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr Circle movedBy(position_type v) const noexcept;

		constexpr Circle& moveBy(value_type _x, value_type _y) noexcept;

		constexpr Circle& moveBy(position_type v) noexcept;

		[[nodiscard]]
		constexpr Circle stretched(value_type size) const noexcept;

		[[nodiscard]]
		constexpr Ellipse stretched(double _x, double _y) const noexcept;

		[[nodiscard]]
		constexpr Circle scaled(double s) const noexcept;

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
		constexpr value_type perimeter() const noexcept;

		[[nodiscard]]
		constexpr RectF boundingRect() const noexcept;

		[[nodiscard]]
		Polygon asPolygon(uint32 quality = 24) const;

		[[nodiscard]]
		constexpr Circle lerp(const Circle& other, double f) const noexcept;

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

		/*
		const Circle& paint(Image& dst, const Color& color, bool antialiased = true) const;

		const Circle& overwrite(Image& dst, const Color& color, bool antialiased = true) const;

		const Circle& paintFrame(Image& dst, double innerThickness, double outerThickness, const Color& color, bool antialiased = true) const;

		const Circle& overwriteFrame(Image& dst, double innerThickness, double outerThickness, const Color& color, bool antialiased = true) const;

		//const Circle& paintPie(Image& dst, double startAngle, double angle, const Color& color) const;

		//const Circle& overwritePie(Image& dst, double startAngle, double angle, const Color& color) const;

		//const Circle& paintArc(Image& dst, double startAngle, double angle, double innerThickness, double outerThickness, const Color& color) const;

		//const Circle& overwriteArc(Image& dst, double startAngle, double angle, double innerThickness, double outerThickness, const Color& color) const;
		*/

		const Circle& draw(const ColorF& color = Palette::White) const;

		const Circle& draw(const ColorF& innerColor, const ColorF& outerColor) const;

		const Circle& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Circle& drawFrame(double thickness, const ColorF& innerColor, const ColorF& outerColor) const;

		const Circle& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		const Circle& drawFrame(double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const;
		
		const Circle& drawPie(double startAngle, double angle, const ColorF& color = Palette::White) const;

		const Circle& drawPie(double startAngle, double angle, const ColorF& innerColor, const ColorF& outerColor) const;

		const Circle& drawArc(double startAngle, double angle, double innerThickness = 1.0, double outerThickness = 0.0, const ColorF& color = Palette::White) const;

		const Circle& drawArc(double startAngle, double angle, double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const;

		//const Circle& drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF(0.0, 0.5)) const;

		//[[nodiscard]] TexturedCircle operator ()(const Texture& texture) const;

		//[[nodiscard]] TexturedCircle operator ()(const TextureRegion& textureRegion) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Circle& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.r << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Circle& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.r >> unused;
		}

		friend void Formatter(FormatData& formatData, const Circle& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Circle& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Circle, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Circle& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {})", value.x, value.y, value.r);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y, value.r);
		}
	}
};

template <>
struct std::hash<s3d::Circle>
{
	[[nodiscard]]
	size_t operator()(const s3d::Circle& value) const noexcept
	{
		return value.hash();
	}
};
