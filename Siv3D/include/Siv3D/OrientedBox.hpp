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
# include "Box.hpp"
# include "Quaternion.hpp"

namespace s3d
{
	struct OrientedBox
	{
		Vec3 center;

		Vec3 size;

		Quaternion orientation;

		SIV3D_NODISCARD_CXX20
		OrientedBox() = default;

		SIV3D_NODISCARD_CXX20
		explicit OrientedBox(double _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit OrientedBox(Arithmetic _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		OrientedBox(double _w, double _h, double _d, Quaternion _orientation = Quaternion::Identity()) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		explicit OrientedBox(W _w, H _h, D _d, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit OrientedBox(const Vec3& _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		OrientedBox(double cx, double cy, double cz, double _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic S>
	# else
		template <class X, class Y, class Z, class S, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<S>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		OrientedBox(X cx, Y cy, Z cz, S _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		OrientedBox(double cx, double cy, double cz, double _w, double _h, double _d, Quaternion _orientation = Quaternion::Identity()) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class X, class Y, class Z, class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		OrientedBox(X cx, Y cy, Z cz, W _w, H _h, D _d, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		OrientedBox(double cx, double cy, double cz, const Vec3& _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z>
	# else
		template <class X, class Y, class Z, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		OrientedBox(X cx, Y cy, Z cz, const Vec3& _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		OrientedBox(const Vec3& _center, double _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		OrientedBox(const Vec3& _center, Arithmetic _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		OrientedBox(const Vec3& _center, double _w, double _h, double _d, Quaternion _orientation = Quaternion::Identity()) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		OrientedBox(const Vec3& _center, W _w, H _h, D _d, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		OrientedBox(const Vec3& _center, const Vec3& _size, Quaternion _orientation = Quaternion::Identity()) noexcept;


		SIV3D_NODISCARD_CXX20
		OrientedBox(Arg::bottomCenter_<Vec3> bottomCenter, double _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		OrientedBox(Arg::bottomCenter_<Vec3> bottomCenter, Arithmetic _size, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		OrientedBox(Arg::bottomCenter_<Vec3> bottomCenter, double _w, double _h, double _d, Quaternion _orientation = Quaternion::Identity()) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		OrientedBox(Arg::bottomCenter_<Vec3> bottomCenter, W _w, H _h, D _d, Quaternion _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		OrientedBox(Arg::bottomCenter_<Vec3> bottomCenter, const Vec3& _size, Quaternion _orientation = Quaternion::Identity()) noexcept;


		SIV3D_NODISCARD_CXX20
		OrientedBox(const Box& box, Quaternion _orientation = Quaternion::Identity()) noexcept;


		[[nodiscard]]
		std::array<Vec3, 8> getCorners() const noexcept;


		OrientedBox& setPos(double cx, double cy, double cz) noexcept;

		OrientedBox& setPos(const Vec3& _center) noexcept;

		OrientedBox& setSize(double w, double h, double d) noexcept;

		OrientedBox& setSize(const Vec3& _size) noexcept;

		OrientedBox& setOrientation(const Quaternion& _orientation) noexcept;


		[[nodiscard]]
		OrientedBox stretched(double xyz) const noexcept;

		[[nodiscard]]
		OrientedBox stretched(double x, double y, double z) const noexcept;

		[[nodiscard]]
		OrientedBox stretched(Vec3 xyz) const noexcept;


		[[nodiscard]]
		bool intersects(const Vec3& point) const noexcept;

		[[nodiscard]]
		bool intersects(const Triangle3D& triangle) const noexcept;

		[[nodiscard]]
		bool intersects(const Sphere& sphere) const noexcept;

		[[nodiscard]]
		bool intersects(const Box& box) const noexcept;

		[[nodiscard]]
		bool intersects(const OrientedBox& box) const noexcept;

		[[nodiscard]]
		bool intersects(const ViewFrustum& frustum) const noexcept;

		[[nodiscard]]
		Optional<float> intersects(const Ray& ray) const noexcept;

		[[nodiscard]]
		bool contains(const Vec3& point) const noexcept;

		[[nodiscard]]
		bool contains(const Triangle3D& triangle) const noexcept;

		[[nodiscard]]
		bool contains(const Sphere& sphere) const noexcept;

		[[nodiscard]]
		bool contains(const Box& box) const noexcept;

		[[nodiscard]]
		bool contains(const OrientedBox& box) const noexcept;

		[[nodiscard]]
		bool contains(const ViewFrustum& frustum) const noexcept;


		const OrientedBox& draw(const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Texture & texture, const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Quaternion & rotation, const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Quaternion & rotation, const Texture & texture, const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Mat4x4 & mat, const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Mat4x4 & mat, const Texture & texture, const ColorF & color = Palette::White) const;


		const OrientedBox& drawFrame(const ColorF & color = Palette::White) const;



		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const OrientedBox& value)
		{
			return output << CharType('(')
				<< value.center << CharType(',') << CharType(' ')
				<< value.size << CharType(',') << CharType(' ')
				<< value.orientation << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, OrientedBox& value)
		{
			CharType unused;
			return input >> unused
				>> value.center >> unused
				>> value.size >> unused
				>> value.orientation >> unused;
		}

		friend void Formatter(FormatData& formatData, const OrientedBox& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const OrientedBox& value);
	};
}

# include "detail/OrientedBox.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::OrientedBox, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::OrientedBox& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {})", value.center, value.size, value.orientation);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.center, value.size, value.orientation);
		}
	}
};
