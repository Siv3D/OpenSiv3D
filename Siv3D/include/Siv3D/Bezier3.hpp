//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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

		[[nodiscard]] Vec2 getPos(double t) const noexcept;

		[[nodiscard]] Vec2 getTangent(double t) const noexcept;

		[[nodiscard]] LineString getLineString(uint32 quality = 24) const;

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
	
		const Bezier3& draw(const ColorF& color = Palette::White) const;

		const Bezier3& draw(double thickness, const ColorF& color = Palette::White) const;
	};

	struct Bezier3Path
	{
	private:

		Vec2 m_v0, m_v1, m_v2;

		double m_t = 0.0;

	public:

		Bezier3Path() = default;

		explicit Bezier3Path(const Bezier3& bezier) noexcept;

		void setT(const double t) noexcept
		{
			m_t = t;
		}

		[[nodiscard]] double getT() const noexcept
		{
			return m_t;
		}

		double advance(double distance, int32 quality = 8) noexcept;
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

namespace fmt_s3d
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
