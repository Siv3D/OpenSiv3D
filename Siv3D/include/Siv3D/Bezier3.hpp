//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "LineString.hpp"
# include "Geometry2D.hpp"

namespace s3d
{
	/// <summary>
	/// 3 次ベジェ曲線
	/// </summary>
	struct Bezier3
	{
		Vec2 p0, p1, p2, p3;

		Bezier3() = default;

		constexpr Bezier3(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2, const Vec2& _p3) noexcept
			: p0(_p0)
			, p1(_p1)
			, p2(_p2)
			, p3(_p3) {}

		[[nodiscard]] constexpr Vec2 getPos(const double t) const noexcept
		{
			return (1 - t)*(1 - t)*(1 - t)*p0 + 3 * (1 - t)*(1 - t)*t*p1 + 3 * (1 - t)*t*t*p2 + t*t*t*p3;
		}

		[[nodiscard]] Vec2 getTangent(const double t) const noexcept
		{
			return (-3 * p0*(1 - t) * (1 - t) +
				p1*(3 * (1 - t)*(1 - t) - 6 * (1 - t) *t) +
				p2*(6 * (1 - t)*t - 3 * t * t) + 3 * p3*t * t).normalized();
		}

		[[nodiscard]] LineString getLineString(const uint32 quality = 24) const
		{
			return getLineString(0.0, 1.0, quality);
		}

		[[nodiscard]] LineString getLineString(double start, double end, uint32 quality = 24) const;

		template <class Shape2DType>
		[[nodiscard]] bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape2DType>
		[[nodiscard]] Optional<Array<Vec2>> intersectsAt(const Shape2DType& shape) const
		{
			return Geometry2D::IntersectAt(*this, shape);
		}

		// paint, overpaint
	
		const Bezier3& draw(const ColorF& color = Palette::White) const
		{
			return draw(1.0, color);
		}

		const Bezier3& draw(double thickness, const ColorF& color = Palette::White) const;
	};

	struct Bezier3Path
	{
	private:

		Vec2 m_v0, m_v1, m_v2;

		double m_t = 0.0;

	public:

		Bezier3Path() = default;

		explicit constexpr Bezier3Path(const Bezier3& bezier) noexcept
			: m_v0(-3 * bezier.p0 + 9 * bezier.p1 - 9 * bezier.p2 + 3 * bezier.p3)
			, m_v1(6 * bezier.p0 - 12 * bezier.p1 + 6 * bezier.p2)
			, m_v2(-3 * bezier.p0 + 3 * bezier.p1) {}

		constexpr void setT(const double t) noexcept
		{
			m_t = t;
		}

		[[nodiscard]] constexpr double getT() const noexcept
		{
			return m_t;
		}

		double advance(double distance, int32 quality = 8) noexcept
		{
			for (int i = 0; i < quality; ++i)
			{
				m_t = m_t + (distance / quality) / (m_t * m_t * m_v0 + m_t * m_v1 + m_v2).length();
			}

			return m_t;
		}
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Bezier3& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Bezier3& value)
	{
		return	output << CharType('(')
			<< value.p0 << CharType(',') << CharType(' ')
			<< value.p1 << CharType(',') << CharType(' ')
			<< value.p2 << CharType(',') << CharType(' ')
			<< value.p3 << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Bezier3& value)
	{
		CharType unused;
		return	input >> unused
			>> value.p0 >> unused
			>> value.p1 >> unused
			>> value.p2 >> unused
			>> value.p3 >> unused;
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::Bezier3>
	{
		[[nodiscard]] size_t operator ()(const s3d::Bezier3& value) const noexcept
		{
			return s3d::Hash::FNV1a(value);
		}
	};
}

//////////////////////////////////////////////////
//
//	fmt
//
//////////////////////////////////////////////////

namespace fmt
{
	template <>
	struct formatter<s3d::Bezier3, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Bezier3& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.p0, value.p1, value.p2);
		}
	};
}
