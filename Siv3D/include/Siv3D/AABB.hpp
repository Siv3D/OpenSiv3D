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

namespace s3d
{
	struct AABB
	{
		Vec3 center;

		Vec3 size;

		AABB() = default;

		AABB(const AABB&) = default;

		AABB& operator=(const AABB&) = default;

		AABB(AABB&&) = default;

		AABB& operator=(AABB&&) = default;

		constexpr AABB(double _size) noexcept
			: center(0, 0, 0)
			, size(_size, _size, _size) {}

		constexpr AABB(double sx, double sy, double sz) noexcept
			: center(0, 0, 0)
			, size(sx, sy, sz) {}

		constexpr AABB(const Vec3& _size) noexcept
			: center(0, 0, 0)
			, size(_size) {}

		constexpr AABB(double x, double y, double z, double _size) noexcept
			: center(x, y, z)
			, size(_size, _size, _size) {}

		constexpr AABB(double x, double y, double z, double sx, double sy, double sz) noexcept
			: center(x, y, z)
			, size(sx, sy, sz) {}

		constexpr AABB(const Vec3& _center, double _size) noexcept
			: center(_center)
			, size(_size, _size, _size) {}

		constexpr AABB(const Vec3& _center, double sx, double sy, double sz) noexcept
			: center(_center)
			, size(sx, sy, sz) {}

		constexpr AABB(const Vec3& _center, const Vec3& _size) noexcept
			: center(_center)
			, size(_size) {}

		constexpr AABB& setPos(double x, double y, double z) noexcept
		{
			center.set(x, y, z);
			return *this;
		}

		constexpr AABB& setPos(const Vec3& pos) noexcept
		{
			center.set(pos);
			return *this;
		}

		constexpr AABB& setSize(double sx, double sy, double sz) noexcept
		{
			size.set(sx, sy, sz);
			return *this;
		}

		constexpr AABB& setSize(const Vec3& _size) noexcept
		{
			size.set(_size);
			return *this;
		}

		constexpr AABB& set(double _size) noexcept
		{
			center.set(0, 0, 0);
			size.set(_size, _size, _size);
			return *this;
		}

		constexpr AABB& set(double sx, double sy, double sz) noexcept
		{
			center.set(0, 0, 0);
			size.set(sx, sy, sz);
			return *this;
		}

		constexpr AABB& set(const Vec3& _size) noexcept
		{
			center.set(0, 0, 0);
			size.set(_size);
			return *this;
		}

		constexpr AABB& set(double x, double y, double z, double _size) noexcept
		{
			center.set(x, y, z);
			size.set(_size, _size, _size);
			return *this;
		}

		constexpr AABB& set(double x, double y, double z, double sx, double sy, double sz) noexcept
		{
			center.set(x, y, z);
			size.set(sx, sy, sz);
			return *this;
		}

		constexpr AABB& set(const Vec3& _center, double _size) noexcept
		{
			center.set(_center);
			size.set(_size, _size, _size);
			return *this;
		}

		constexpr AABB& set(const Vec3& _center, double sx, double sy, double sz) noexcept
		{
			center.set(_center);
			size.set(sx, sy, sz);
			return *this;
		}

		constexpr AABB& set(const Vec3& _center, const Vec3& _size) noexcept
		{
			center.set(_center);
			size.set(_size);
			return *this;
		}

		constexpr AABB& set(const AABB& aabb) noexcept
		{
			center.set(aabb.center);
			size.set(aabb.size);
			return *this;
		}

		[[nodiscard]] constexpr AABB movedBy(double x, double y, double z) const noexcept
		{
			return{ center.movedBy(x, y, z), size };
		}

		[[nodiscard]] constexpr AABB movedBy(const Vec3& v) const noexcept
		{
			return{ center.movedBy(v), size };
		}

		constexpr AABB& moveBy(double x, double y, double z) noexcept
		{
			center.moveBy(x, y, z);
			return *this;
		}

		constexpr AABB& moveBy(const Vec3& v) noexcept
		{
			center.moveBy(v);
			return *this;
		}

		[[nodiscard]] constexpr AABB stretched(double xyz) const noexcept
		{
			return stretched({ xyz, xyz, xyz });
		}

		[[nodiscard]] constexpr AABB stretched(double _x, double _y, double _z) const noexcept
		{
			return stretched({ _x, _y, _z });
		}

		[[nodiscard]] constexpr AABB stretched(const Vec3& xyz) const noexcept
		{
			return{ center, size + xyz * 2 };
		}

		[[nodiscard]] constexpr AABB scaled(double s) const noexcept
		{
			return scaled({ s, s, s });
		}

		[[nodiscard]] constexpr AABB scaled(double sx, double sy, double sz) const noexcept
		{
			return scaled({ sx, sy, sz });
		}

		[[nodiscard]] constexpr AABB scaled(const Vec3& s) const noexcept
		{
			return{ center, size * s };
		}

		[[nodiscard]] OBB rotated(const Quaternion& rotation) const noexcept;

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
	void Formatter(FormatData& formatData, const AABB& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const AABB& value)
	{
		return output << CharType('(')
			<< value.center << CharType(',') << CharType(' ')
			<< value.size << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, AABB& value)
	{
		CharType unused;
		return input >> unused
			>> value.center >> unused
			>> value.size >> unused;
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
	struct hash<s3d::AABB>
	{
		[[nodiscard]] size_t operator ()(const s3d::AABB& value) const noexcept
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
	struct formatter<s3d::AABB, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::AABB& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.center, value.size);
		}
	};
}
