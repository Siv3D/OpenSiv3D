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
# include "ColorHSV.hpp"
# include "NamedParameter.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	/// @brief 角丸長方形
	struct RoundRect
	{
		using position_type	= RectF::position_type;

		using size_type		= RectF::size_type;

		using value_type	= position_type::value_type;

		SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			RectF rect;

			struct
			{
				value_type x, y, w, h;
			};
		};

		value_type r;

		SIV3D_DISABLE_MSVC_WARNINGS_POP()

		SIV3D_NODISCARD_CXX20
		RoundRect() = default;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param _w 
		/// @param _h 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(value_type _x, value_type _y, value_type _w, value_type _h, value_type _r) noexcept;

		/// @brief 
		/// @param pos 
		/// @param _w 
		/// @param _h 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, value_type _w, value_type _h, value_type _r) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(value_type _x, value_type _y, size_type size, value_type _r) noexcept;

		/// @brief 
		/// @param pos 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, value_type size, value_type _r) noexcept;

		/// @brief 
		/// @param pos 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, size_type size, value_type _r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(Arg::center_<position_type> _center, value_type _w, value_type _h, value_type _r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(Arg::center_<position_type> _center, size_type size, value_type _r) noexcept;

		/// @brief 
		/// @param _rect 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(const RectF& _rect, value_type _r) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const RoundRect& lhs, const RoundRect& rhs) noexcept
		{
			return (lhs.rect == rhs.rect)
				&& (lhs.r == rhs.r);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const RoundRect& lhs, const RoundRect& rhs) noexcept
		{
			return (lhs.rect != rhs.rect)
				|| (lhs.r != rhs.r);
		}

		constexpr RoundRect& set(value_type _x, value_type _y, value_type _w, value_type _h, value_type _r) noexcept
		{
			rect.set(_x, _y, _w, _h);
			r = _r;
			return *this;
		}

		constexpr RoundRect& set(const position_type& pos, value_type _w, value_type _h, value_type _r) noexcept
		{
			return set(pos.x, pos.y, _w, _h, _r);
		}

		constexpr RoundRect& set(value_type _x, value_type _y, const size_type& size, value_type _r) noexcept
		{
			return set(_x, _y, size.x, size.y, _r);
		}

		constexpr RoundRect& set(const position_type& pos, const size_type& size, value_type _r) noexcept
		{
			return set(pos.x, pos.y, size.x, size.y, _r);
		}

		constexpr RoundRect& set(const RectF& _rect, value_type _r) noexcept
		{
			return set(_rect.x, _rect.y, _rect.w, _rect.h, _r);
		}

		constexpr RoundRect& set(const RoundRect& roundRect) noexcept
		{
			return *this = roundRect;
		}

		constexpr RoundRect& setPos(value_type _x, value_type _y) noexcept
		{
			rect.setPos(_x, _y);
			return *this;
		}

		constexpr RoundRect& setPos(const position_type& _center) noexcept
		{
			return setPos(_center.x, _center.y);
		}

		constexpr RoundRect& setCenter(value_type _x, value_type _y) noexcept
		{
			rect.setCenter(_x, _y);
			return *this;
		}

		constexpr RoundRect& setCenter(const position_type& _center) noexcept
		{
			return setCenter(_center.x, _center.y);
		}

		constexpr RoundRect& setSize(value_type _w, value_type _h) noexcept
		{
			rect.setSize(_w, _h);
			return *this;
		}

		constexpr RoundRect& setSize(const size_type& _size) noexcept
		{
			return setSize(_size.x, _size.y);
		}

		[[nodiscard]] constexpr RoundRect movedBy(value_type _x, value_type _y) const noexcept
		{
			return{ rect.movedBy(_x, _y), r };
		}

		[[nodiscard]] constexpr RoundRect movedBy(const position_type& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		constexpr RoundRect& moveBy(value_type _x, value_type _y) noexcept
		{
			rect.moveBy(_x, _y);
			return *this;
		}

		constexpr RoundRect& moveBy(const position_type& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		[[nodiscard]] constexpr RoundRect stretched(value_type size) const noexcept
		{
			return RoundRect(rect.stretched(size), r);
		}

		[[nodiscard]] constexpr RoundRect stretched(value_type _x, value_type _y) const noexcept
		{
			return RoundRect(rect.stretched(_x, _y), r);
		}

		[[nodiscard]] constexpr RoundRect stretched(const size_type& xy) const noexcept
		{
			return RoundRect(rect.stretched(xy.x, xy.y), r);
		}

		[[nodiscard]] constexpr RoundRect stretched(value_type top, value_type right, value_type bottom, value_type left) const noexcept
		{
			return RoundRect(rect.stretched(top, right, bottom, left), r);
		}

		[[nodiscard]] constexpr position_type center() const noexcept
		{
			return rect.center();
		}

		[[nodiscard]] constexpr double area() const noexcept
		{
			return rect.area() - (4 - Math::Constants::Pi) * r * r;
		}

		[[nodiscard]] constexpr double perimeter() const noexcept
		{
			return rect.perimeter() + r * (2 * Math::Constants::Pi - 8);
		}

		[[nodiscard]] Polygon asPolygon(uint32 quality = 24) const;

		[[nodiscard]]
		constexpr RoundRect lerp(const RoundRect& other, double f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		bool intersects(const Shape2DType& other) const;

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

		//const RoundRect& paint(Image& dst, const Color& color) const;

		//const RoundRect& overwrite(Image& dst, const Color& color, bool antialiased = true) const;

		//const RoundRect& paintFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color) const;

		//const RoundRect& overwriteFrame(Image& dst, int32 innerThickness, int32 outerThickness, const Color& color, bool antialiased = true) const;

		//const RoundRect& draw(const ColorF& color = Palette::White) const;

		//const RoundRect& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		//const RoundRect& drawFrame(double innerThickness, double outerThickness, const ColorF& color = Palette::White) const;

		//const RoundRect& drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF(0.0, 0.5)) const;

		//[[nodiscard]] TexturedRoundRect operator ()(const Texture& texture) const;

		//[[nodiscard]] TexturedRoundRect operator ()(const TextureRegion& textureRegion) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const RoundRect& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.w << CharType(',') << CharType(' ')
				<< value.h << CharType(',') << CharType(' ')
				<< value.r << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, RoundRect& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.w >> unused
				>> value.h >> unused
				>> value.r >> unused;
		}

		friend void Formatter(FormatData& formatData, const RoundRect& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const RoundRect& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::RoundRect, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::RoundRect& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {}, {})", value.x, value.y, value.w, value.h, value.r);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y, value.w, value.h, value.r);
		}
	}
};

template <>
struct std::hash<s3d::RoundRect>
{
	[[nodiscard]]
	size_t operator()(const s3d::RoundRect& value) const noexcept
	{
		return value.hash();
	}
};
