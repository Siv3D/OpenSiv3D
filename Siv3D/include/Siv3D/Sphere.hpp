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
# include "Vector3D.hpp"

namespace s3d
{
	struct Sphere
	{
		Vec3 center;

		double r;

		Sphere() = default;

		Sphere(const Sphere&) = default;

		Sphere& operator=(const Sphere&) = default;

		Sphere(Sphere&&) = default;

		Sphere& operator=(Sphere&&) = default;

		constexpr Sphere(const Vec3& _center, double _r) noexcept
			: center(_center)
			, r(_r) {}

		constexpr Sphere(double x, double y, double z, double _r) noexcept
			: center(x, y, z)
			, r(_r) {}

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
	void Formatter(FormatData& formatData, const Sphere& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Sphere& value)
	{
		return output << CharType('(')
			<< value.center << CharType(',') << CharType(' ')
			<< value.r << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Sphere& value)
	{
		CharType unused;
		return input >> unused
			>> value.center >> unused
			>> value.r >> unused;
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
	struct hash<s3d::Sphere>
	{
		[[nodiscard]] size_t operator ()(const s3d::Sphere& value) const noexcept
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
	struct formatter<s3d::Sphere, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Sphere& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.center, value.r);
		}
	};
}
