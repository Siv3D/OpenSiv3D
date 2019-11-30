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
	struct Ray
	{
		Vec3 origin;

		Vec3 direction;

		Ray() = default;

		Ray(const Ray&) = default;

		Ray& operator=(const Ray&) = default;

		Ray(Ray&&) = default;

		Ray& operator=(Ray&&) = default;

		constexpr Ray(const Vec3& _origin, const Vec3& normalizedDirection) noexcept
			: origin(_origin)
			, direction(normalizedDirection) {}

		constexpr Ray(double ox, double oy, double oz, const Vec3& normalizedDirection) noexcept
			: origin(ox, oy, oz)
			, direction(normalizedDirection) {}

		constexpr Vec3 point_at(double distance) const noexcept
		{
			return Vec3(
				origin.x + distance * direction.x,
				origin.y + distance * direction.y,
				origin.z + distance * direction.z
				);
		}

		constexpr Ray& setOrigin(const Vec3& _origin) noexcept
		{
			origin.set(_origin);
			return *this;
		}

		constexpr Ray& setDirection(const Vec3& _direction) noexcept
		{
			direction.set(_direction);
			return *this;
		}

		[[nodiscard]] Optional<float> intersects(const Triangle3D& triangle) const;

		[[nodiscard]] Optional<float> intersects(const Sphere& sphere) const;

		[[nodiscard]] Optional<float> intersects(const AABB& aabb) const;

		[[nodiscard]] Optional<float> intersects(const OBB& obb) const;
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Ray& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Ray& value)
	{
		return output << CharType('(')
			<< value.origin << CharType(',') << CharType(' ')
			<< value.direction << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Ray& value)
	{
		CharType unused;
		return input >> unused
			>> value.origin >> unused
			>> value.direction >> unused;
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
	struct hash<s3d::Ray>
	{
		[[nodiscard]] size_t operator ()(const s3d::Ray& value) const noexcept
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
	struct formatter<s3d::Ray, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Ray& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.origin, value.direction);
		}
	};
}
