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
# include "Optional.hpp"
# include "SIMD_Float4.hpp"
# include "Triangle3D.hpp"

namespace s3d
{
	struct Triangle3D;
	struct Plane;
	struct Sphere;
	struct AABB;
	struct OBB;

	struct Ray
	{
		SIMD_Float4 origin;

		SIMD_Float4 direction;

		SIV3D_NODISCARD_CXX20
		Ray() = default;

		SIV3D_NODISCARD_CXX20
		Ray(Float3 _origin, Float3 normalizedDirection) noexcept;

		template <class X, class Y, class Z>
		SIV3D_NODISCARD_CXX20
		Ray(X ox, Y oy, Z oz, Float3 normalizedDirection) noexcept;

		template <class X, class Y, class Z>
		SIV3D_NODISCARD_CXX20
		Ray(Float3 _origin, X ndx, Y ndy, Z ndz) noexcept;

		[[nodiscard]]
		Float3 SIV3D_VECTOR_CALL getOrigin() const noexcept;

		Ray& SIV3D_VECTOR_CALL setOrigin(Float3 _origin) noexcept;

		[[nodiscard]]
		Float3 SIV3D_VECTOR_CALL getDirection() const noexcept;

		Ray& SIV3D_VECTOR_CALL setDirection(Float3 _direction) noexcept;
		
		[[nodiscard]]
		Float3 SIV3D_VECTOR_CALL point_at(float distance) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Vec3 SIV3D_VECTOR_CALL point_at(Arithmetic distance) const noexcept;

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(Triangle3D triangle) const;

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(Plane plane) const;

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Sphere& sphere) const;

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const AABB& aabb) const;

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const OBB& obb) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Ray& value)
		{
			return output << CharType('(')
				<< value.origin << CharType(',') << CharType(' ')
				<< value.direction << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Ray& value)
		{
			CharType unused;
			return input >> unused
				>> value.origin >> unused
				>> value.direction >> unused;
		}

		friend void Formatter(FormatData& formatData, const Ray& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Ray& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Ray, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Ray& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {})", value.origin, value.direction);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.origin, value.direction);
		}
	}
};

# include "detail/Ray.ipp"
