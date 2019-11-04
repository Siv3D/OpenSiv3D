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
# include "SIMD_Float4.hpp"

namespace s3d
{
	struct Line3D
	{
		Vec3 begin, end;

		Line3D() = default;

		Line3D(const Line3D&) = default;

		Line3D& operator=(const Line3D&) = default;

		Line3D(Line3D&&) = default;

		Line3D& operator=(Line3D&&) = default;

		constexpr Line3D(double bx, double by, double bz, double ex, double ey, double ez) noexcept
			: begin(bx, by, bz)
			, end(ex, ey, ez) {}

		constexpr Line3D(double bx, double by, double bz, const Vec3& _end) noexcept
			: begin(bx, by, bz)
			, end(_end) {}

		constexpr Line3D(const Vec3& _begin, double ex, double ey, double ez) noexcept
			: begin(_begin)
			, end(ex, ey, ez) {}

		constexpr Line3D(const Vec3& _begin, const Vec3& _end) noexcept
			: begin(_begin)
			, end(_end) {}

		void draw(const Mat4x4& vp, const ColorF& color = Palette::White) const;
	};


	struct alignas(16) SIMD_Line3D
	{
		SIMD_Float4 vec[2];

		SIMD_Line3D() = default;

		SIMD_Line3D(const SIMD_Line3D&) = default;

		SIMD_Line3D& operator=(const SIMD_Line3D&) = default;

		SIMD_Line3D(SIMD_Line3D&&) = default;

		SIMD_Line3D& operator=(SIMD_Line3D&&) = default;

		constexpr SIMD_Line3D(SIMD_Float4 _begin, SIMD_Float4 _end) noexcept
			: vec{ _begin, _end } {}

		SIMD_Line3D(const Float3& _begin, const Float3& _end) noexcept
			: vec{ { _begin, 0.0f }, { _end, 0.0f } } {}

		void draw(const Mat4x4& vp, const ColorF& color = Palette::White) const;
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Line3D& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Line3D& value)
	{
		return output << CharType('(')
			<< value.begin << CharType(',') << CharType(' ')
			<< value.end << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Line3D& value)
	{
		CharType unused;
		return input >> unused
			>> value.begin >> unused
			>> value.end >> unused;
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
	struct hash<s3d::Line3D>
	{
		[[nodiscard]] size_t operator ()(const s3d::Line3D& value) const noexcept
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
	struct formatter<s3d::Line3D, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Line3D& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.begin, value.end);
		}
	};
}
