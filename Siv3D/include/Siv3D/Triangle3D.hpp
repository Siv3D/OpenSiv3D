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
	struct Triangle3D
	{
		Vec3 p0, p1, p2;

		Triangle3D() = default;

		Triangle3D(const Triangle3D&) = default;

		Triangle3D& operator=(const Triangle3D&) = default;

		Triangle3D(Triangle3D&&) = default;

		Triangle3D& operator=(Triangle3D&&) = default;

		constexpr Triangle3D(const Vec3& _p0, const Vec3& _p1, const Vec3& _p2) noexcept
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		void draw(const Mat4x4& vp, const ColorF& color = Palette::White) const;

		void drawFrame(const Mat4x4& vp, const ColorF& color = Palette::White) const;

		void drawFrame(const Mat4x4& vp, double thickness, const ColorF& color = Palette::White) const;
	};


	struct alignas(16) SIMD_Triangle3D
	{
		SIMD_Float4 vec[3];

		SIMD_Triangle3D() = default;

		SIMD_Triangle3D(const SIMD_Triangle3D&) = default;

		SIMD_Triangle3D& operator=(const SIMD_Triangle3D&) = default;

		SIMD_Triangle3D(SIMD_Triangle3D&&) = default;

		SIMD_Triangle3D& operator=(SIMD_Triangle3D&&) = default;

		constexpr SIMD_Triangle3D(SIMD_Float4 _p0, SIMD_Float4 _p1, SIMD_Float4 _p2) noexcept
			: vec{ _p0, _p1, _p2 } {}

		SIMD_Triangle3D(const Float3& _p0, const Float3& _p1, const Float3& _p2) noexcept
			: vec{ { _p0, 0.0f }, { _p1, 0.0f }, { _p2, 0.0f } } {}

		void draw(const Mat4x4& vp, const ColorF& color = Palette::White) const;

		void drawFrame(const Mat4x4& vp, const ColorF& color = Palette::White) const;

		void drawFrame(const Mat4x4& vp, double thickness = 1.0, const ColorF& color = Palette::White) const;
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Triangle3D& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Triangle3D& value)
	{
		return output << CharType('(')
			<< value.p0 << CharType(',') << CharType(' ')
			<< value.p1 << CharType(',') << CharType(' ')
			<< value.p2 << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Triangle3D& value)
	{
		CharType unused;
		return input >> unused
			>> value.p0 >> unused
			>> value.p1 >> unused
			>> value.p2 >> unused;
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
	struct hash<s3d::Triangle3D>
	{
		[[nodiscard]] size_t operator ()(const s3d::Triangle3D& value) const noexcept
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
	struct formatter<s3d::Triangle3D, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Triangle3D& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.p0, value.p1, value.p2);
		}
	};
}
