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
# include "2DShapes.hpp"

namespace s3d
{
	struct Mat3x3
	{
		using value_type = float;

	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				value_type _11, _12, _13;
			};

			Float3 _11_12_13;
		};

		union
		{
			struct
			{
				value_type _21, _22, _23;
			};

			Float3 _21_22_23;
		};

		union
		{
			struct
			{
				value_type _31, _32, _33;
			};

			Float3 _31_32_33;
		};

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		SIV3D_NODISCARD_CXX20
		Mat3x3() = default;

		SIV3D_NODISCARD_CXX20
		constexpr Mat3x3(float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Mat3x3& lhs, const Mat3x3& rhs) noexcept
		{
			return (lhs._11 == rhs._11) && (lhs._12 == rhs._12) && (lhs._13 == rhs._13)
				&& (lhs._21 == rhs._21) && (lhs._22 == rhs._22) && (lhs._23 == rhs._23)
				&& (lhs._31 == rhs._31) && (lhs._32 == rhs._32) && (lhs._33 == rhs._33);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Mat3x3& lhs, const Mat3x3& rhs) noexcept
		{
			return (lhs._11 != rhs._11) || (lhs._12 != rhs._12) || (lhs._13 != rhs._13)
				|| (lhs._21 != rhs._21) || (lhs._22 != rhs._22) || (lhs._23 != rhs._23)
				|| (lhs._31 != rhs._31) || (lhs._32 != rhs._32) || (lhs._33 != rhs._33);
		}

		[[nodiscard]]
		constexpr float determinant() const noexcept;

		[[nodiscard]]
		Mat3x3 inverse() const noexcept;

		[[nodiscard]]
		constexpr Float2 transformPoint(Point pos) const noexcept;

		[[nodiscard]]
		constexpr Float2 transformPoint(Float2 pos) const noexcept;

		[[nodiscard]]
		constexpr Vec2 transformPoint(Vec2 pos) const noexcept;

		[[nodiscard]]
		constexpr Quad transformRect(const RectF& rect) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		[[nodiscard]]
		static constexpr Mat3x3 Identity() noexcept;

		[[nodiscard]]
		static Mat3x3 Homography(const Quad& to);

		[[nodiscard]]
		static Mat3x3 Homography(const Quad& from, const Quad& to);

		template <class CharType>
		friend inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Mat3x3& value)
		{
			return output << CharType('(')
				<< Float3{ value._11, value._12, value._13 } << CharType(',')
				<< Float3{ value._21, value._22, value._23 } << CharType(',')
				<< Float3{ value._31, value._32, value._33 } << CharType(')');
		}

		template <class CharType>
		friend inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Mat3x3& value)
		{
			CharType unused;
			Float3 r1, r2, r3;

			input >> unused
				>> r1 >> unused
				>> r2 >> unused
				>> r3 >> unused;

			value._11 = r1.x;
			value._12 = r1.y;
			value._13 = r1.z;
			value._21 = r2.x;
			value._22 = r2.y;
			value._23 = r2.z;
			value._31 = r3.x;
			value._32 = r3.y;
			value._33 = r3.z;

			return input;
		}

		friend void Formatter(FormatData& formatData, const Mat3x3& value);
	};
}

# include "detail/Mat3x3.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Mat3x3, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Mat3x3& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"(({}, {}, {}), ({}, {}, {}), ({}, {}, {}))",
				value._11, value._12, value._13, value._21, value._22, value._23, value._31, value._32, value._33);
		}
		else
		{
			const std::u32string format
				= (U"(({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}), ({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}), ({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}))");
			return format_to(ctx.out(), format, value._11, value._12, value._13, value._21, value._22, value._23, value._31, value._32, value._33);
		}
	}
};

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::Mat3x3>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Mat3x3& value) const noexcept
	{
		return value.hash();
	}
};
