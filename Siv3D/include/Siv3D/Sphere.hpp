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
	class Texture;
	struct Quaternion;
	struct Mat4x4;

	struct Sphere
	{
		Vec3 center;

		double r;

		Sphere() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Sphere(double _r) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr Sphere(Arithmetic _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Sphere(double _x, double _y, double _z, double _r) noexcept;

		template <class X, class Y, class Z, class R>
		SIV3D_NODISCARD_CXX20
		constexpr Sphere(X _x, Y _y, Z _z, R _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Sphere(const Vec3& _center, double _r) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Sphere(const Vec3& _center, Arithmetic _r) noexcept;


		const Sphere& draw(const ColorF& color = Palette::White) const;

		const Sphere& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Sphere& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Sphere& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Sphere& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Sphere& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;


		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Sphere& value)
		{
			return output << CharType('(')
				<< value.center << CharType(',') << CharType(' ')
				<< value.r << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Sphere& value)
		{
			CharType unused;
			return input >> unused
				>> value.center >> unused
				>> value.r >> unused;
		}

		friend void Formatter(FormatData& formatData, const Sphere& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Sphere& value);
	};
}

# include "detail/Sphere.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Sphere, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Sphere& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {})", value.center, value.r);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.center, value.r);
		}
	}
};
