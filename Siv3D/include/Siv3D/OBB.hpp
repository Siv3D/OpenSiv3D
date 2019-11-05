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
# include "AABB.hpp"
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

		constexpr OBB(double _size) noexcept
			: center(0, 0, 0)
			, size(_size, _size, _size) {}

		constexpr OBB(double sx, double sy, double sz) noexcept
			: center(0, 0, 0)
			, size(sx, sy, sz) {}

		constexpr OBB(const Vec3& _size) noexcept
			: center(0, 0, 0)
			, size(_size) {}

		constexpr OBB(double _size, const Quaternion& _orientation) noexcept
			: center(0, 0, 0)
			, size(_size, _size, _size)
			, orientation(_orientation) {}

		constexpr OBB(double sx, double sy, double sz, const Quaternion& _orientation) noexcept
			: center(0, 0, 0)
			, size(sx, sy, sz)
			, orientation(_orientation) {}

		constexpr OBB(const Vec3& _size, const Quaternion& _orientation) noexcept
			: center(0, 0, 0)
			, size(_size)
			, orientation(_orientation) {}

		constexpr OBB(double x, double y, double z, double _size) noexcept
			: center(x, y, z)
			, size(_size, _size, _size) {}

		constexpr OBB(double x, double y, double z, double sx, double sy, double sz) noexcept
			: center(x, y, z)
			, size(sx, sy, sz) {}

		constexpr OBB(double x, double y, double z, double _size, const Quaternion& _orientation) noexcept
			: center(x, y, z)
			, size(_size, _size, _size)
			, orientation(_orientation) {}

		constexpr OBB(double x, double y, double z, double sx, double sy, double sz, const Quaternion& _orientation) noexcept
			: center(x, y, z)
			, size(sx, sy, sz)
			, orientation(_orientation) {}

		constexpr OBB(const Vec3& _center, double _size) noexcept
			: center(_center)
			, size(_size, _size, _size) {}

		constexpr OBB(const Vec3& _center, double sx, double sy, double sz) noexcept
			: center(_center)
			, size(sx, sy, sz) {}

		constexpr OBB(const Vec3& _center, const Vec3& _size) noexcept
			: center(_center)
			, size(_size) {}

		constexpr OBB(const Vec3& _center, double _size, const Quaternion& _orientation) noexcept
			: center(_center)
			, size(_size, _size, _size)
			, orientation(_orientation) {}

		constexpr OBB(const Vec3& _center, double sx, double sy, double sz, const Quaternion& _orientation) noexcept
			: center(_center)
			, size(sx, sy, sz)
			, orientation(_orientation) {}

		constexpr OBB(const Vec3& _center, const Vec3& _size, const Quaternion& _orientation) noexcept
			: center(_center)
			, size(_size)
			, orientation(_orientation) {}

		constexpr OBB(const AABB& aabb) noexcept
			: center(aabb.center)
			, size(aabb.size) {}

		constexpr OBB(const AABB& aabb, const Quaternion& _orientation) noexcept
			: center(aabb.center)
			, size(aabb.size)
			, orientation(_orientation) {}

		constexpr OBB& setPos(double x, double y, double z) noexcept
		{
			center.set(x, y, z);
			return *this;
		}

		constexpr OBB& setPos(const Vec3& pos) noexcept
		{
			center.set(pos);
			return *this;
		}

		constexpr OBB& setSize(double sx, double sy, double sz) noexcept
		{
			size.set(sx, sy, sz);
			return *this;
		}

		constexpr OBB& setSize(const Vec3& _size) noexcept
		{
			size.set(_size);
			return *this;
		}

		constexpr OBB& setOrientation(const Quaternion& _orientation) noexcept
		{
			orientation.set(_orientation);
			return *this;
		}

		constexpr OBB& set(double _size, const Quaternion& _orientation) noexcept
		{
			center.set(0, 0, 0);
			size.set(_size, _size, _size);
			orientation.set(_orientation);
			return *this;
		}

		constexpr OBB& set(double sx, double sy, double sz, const Quaternion& _orientation) noexcept
		{
			center.set(0, 0, 0);
			size.set(sx, sy, sz);
			orientation.set(_orientation);
			return *this;
		}

		constexpr OBB& set(const Vec3& _size, const Quaternion& _orientation) noexcept
		{
			center.set(0, 0, 0);
			size.set(_size);
			orientation.set(_orientation);
			return *this;
		}

		constexpr OBB& set(double x, double y, double z, double _size, const Quaternion& _orientation) noexcept
		{
			center.set(x, y, z);
			size.set(_size, _size, _size);
			orientation.set(_orientation);
			return *this;
		}

		constexpr OBB& set(double x, double y, double z, double sx, double sy, double sz, const Quaternion& _orientation) noexcept
		{
			center.set(x, y, z);
			size.set(sx, sy, sz);
			orientation.set(_orientation);
			return *this;
		}

		constexpr OBB& set(const Vec3& _center, double _size, const Quaternion& _orientation) noexcept
		{
			center.set(_center);
			size.set(_size, _size, _size);
			orientation.set(_orientation);
			return *this;
		}

		constexpr OBB& set(const Vec3& _center, double sx, double sy, double sz, const Quaternion& _orientation) noexcept
		{
			center.set(_center);
			size.set(sx, sy, sz);
			orientation.set(_orientation);
			return *this;
		}

		constexpr OBB& set(const Vec3& _center, const Vec3& _size, const Quaternion& _orientation) noexcept
		{
			center.set(_center);
			size.set(_size);
			orientation.set(_orientation);
			return *this;
		}

		constexpr OBB& set(const AABB& aabb, const Quaternion& _orientation) noexcept
		{
			center.set(aabb.center);
			size.set(aabb.size);
			orientation.set(_orientation);
			return *this;
		}

		[[nodiscard]] constexpr OBB movedBy(double x, double y, double z) const noexcept
		{
			return{ center.movedBy(x, y, z), size };
		}

		[[nodiscard]] constexpr OBB movedBy(const Vec3& v) const noexcept
		{
			return{ center.movedBy(v), size };
		}

		constexpr OBB& moveBy(double x, double y, double z) noexcept
		{
			center.moveBy(x, y, z);
			return *this;
		}

		constexpr OBB& moveBy(const Vec3& v) noexcept
		{
			center.moveBy(v);
			return *this;
		}

		[[nodiscard]] constexpr OBB stretched(double xyz) const noexcept
		{
			return stretched({ xyz, xyz, xyz });
		}

		[[nodiscard]] constexpr OBB stretched(double _x, double _y, double _z) const noexcept
		{
			return stretched({ _x, _y, _z });
		}

		[[nodiscard]] constexpr OBB stretched(const Vec3& xyz) const noexcept
		{
			return{ center, size + xyz * 2 };
		}

		[[nodiscard]] constexpr OBB scaled(double s) const noexcept
		{
			return scaled({ s, s, s });
		}

		[[nodiscard]] constexpr OBB scaled(double sx, double sy, double sz) const noexcept
		{
			return scaled({ sx, sy, sz });
		}

		[[nodiscard]] constexpr OBB scaled(const Vec3& s) const noexcept
		{
			return{ center, size * s };
		}

		std::array<Float3, 8> getCorners() const;

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

