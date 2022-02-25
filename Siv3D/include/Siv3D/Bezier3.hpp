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
# include "Array.hpp"
# include "Optional.hpp"
# include "2DShapes.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief 三次ベジェ曲線
	struct Bezier3
	{
		Vec2 p0;

		Vec2 p1;

		Vec2 p2;

		Vec2 p3;

		SIV3D_NODISCARD_CXX20
		Bezier3() = default;

		SIV3D_NODISCARD_CXX20
		constexpr Bezier3(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2, const Vec2& _p3) noexcept;

		[[nodiscard]]
		constexpr Vec2& p(size_t index) noexcept;

		[[nodiscard]]
		constexpr const Vec2& p(size_t index) const noexcept;

		[[nodiscard]]
		constexpr Vec2 point(size_t index) const;

		[[nodiscard]]
		constexpr Vec2 getPos(double t) const noexcept;

		[[nodiscard]]
		Vec2 getTangent(double t) const noexcept;

		[[nodiscard]]
		LineString getLineString(int32 quality = 24) const;

		[[nodiscard]]
		LineString getLineString(double start, double end, int32 quality = 24) const;

		[[nodiscard]]
		RectF boundingRect() const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		const Bezier3& paint(Image& dst, const Color& color) const;

		const Bezier3& paint(Image& dst, int32 thickness, const Color& color) const;

		const Bezier3& overwrite(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Bezier3& overwrite(Image& dst, int32 thickness, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Bezier3& draw(const ColorF& color = Palette::White, int32 quality = 24) const;

		const Bezier3& draw(double thickness, const ColorF& color = Palette::White, int32 quality = 24) const;

		const Bezier3& draw(const LineStyle& style, double thickness, const ColorF& color = Palette::White, int32 quality = 24) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Bezier3& value)
		{
			return output << CharType('(')
				<< value.p0 << CharType(',') << CharType(' ')
				<< value.p1 << CharType(',') << CharType(' ')
				<< value.p2 << CharType(',') << CharType(' ')
				<< value.p3 << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Bezier3& value)
		{
			CharType unused;
			return input >> unused
				>> value.p0 >> unused
				>> value.p1 >> unused
				>> value.p2 >> unused
				>> value.p3 >> unused;
		}

		friend void Formatter(FormatData& formatData, const Bezier3& value);
	};

	struct Bezier3Path
	{
	public:

		Bezier3Path() = default;

		explicit constexpr Bezier3Path(const Bezier3& bezier) noexcept;

		constexpr void setT(const double t) noexcept;

		[[nodiscard]]
		constexpr double getT() const noexcept;

		double advance(double distance, int32 quality = 8) noexcept;
	
	private:

		Vec2 m_v0;
		
		Vec2 m_v1;
		
		Vec2 m_v2;

		double m_t = 0.0;
	};
}

# include "detail/Bezier3.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Bezier3, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Bezier3& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.p0, value.p1, value.p2, value.p3);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.p0, value.p1, value.p2, value.p3);
		}
	}
};

template <>
struct std::hash<s3d::Bezier3>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Bezier3& value) const noexcept
	{
		return value.hash();
	}
};
