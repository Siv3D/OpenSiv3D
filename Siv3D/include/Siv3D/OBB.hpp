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
# include "Quaternion.hpp"

namespace s3d
{
	struct OBB
	{
		Vec3 center;

		Vec3 size;

		Quaternion orientation;

		OBB() = default;

		OBB(const OBB&) = default;

		OBB& operator=(const OBB&) = default;

		OBB(OBB&&) = default;

		OBB& operator=(OBB&&) = default;

		constexpr OBB(const Vec3& _center, const Vec3& _size) noexcept
			: center(_center)
			, size(_size)
			, orientation(Quaternion::Identity()) {}

		constexpr OBB(const Vec3& _center, const Vec3& _size, const Quaternion& _orientation) noexcept
			: center(_center)
			, size(_size)
			, orientation(_orientation) {}

		void getCorners(std::array<Float3, 8>& corners) const;

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
	void Formatter(FormatData& formatData, const OBB& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const OBB& value)
	{
		return output << CharType('(')
			<< value.center << CharType(',') << CharType(' ')
			<< value.size << CharType(',') << CharType(' ')
			<< value.orientation << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, OBB& value)
	{
		CharType unused;
		return input >> unused
			>> value.center >> unused
			>> value.size >> unused
			>> value.orientation >> unused;
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
	struct hash<s3d::OBB>
	{
		[[nodiscard]] size_t operator ()(const s3d::OBB& value) const noexcept
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
	struct formatter<s3d::OBB, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::OBB& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.center, value.size, value.orientation);
		}
	};
}

