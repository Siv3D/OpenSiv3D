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
# include "Box.hpp"
# include "Quaternion.hpp"

namespace s3d
{
	struct OrientedBox
	{
		using position_type = Vec3;

		using size_type = Vec3;

		using value_type = size_type::value_type;

	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			position_type center;

			struct
			{
				value_type x;

				value_type y;

				value_type z;
			};
		};

		union
		{
			position_type size;

			struct
			{
				value_type w;

				value_type h;

				value_type d;
			};
		};

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

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



		OrientedBox& setPos(value_type cx, value_type cy, value_type cz) noexcept;

		OrientedBox& setPos(position_type _center) noexcept;

		OrientedBox& setSize(value_type _w, value_type _h, value_type _d) noexcept;

		OrientedBox& setSize(size_type _size) noexcept;

		OrientedBox& setOrientation(Quaternion _orientation) noexcept;


		[[nodiscard]]
		OrientedBox movedBy(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		OrientedBox movedBy(size_type v) const noexcept;

		OrientedBox& moveBy(value_type _x, value_type _y, value_type _z) noexcept;

		OrientedBox& moveBy(size_type v) noexcept;


		[[nodiscard]]
		OrientedBox stretched(double xyz) const noexcept;

		[[nodiscard]]
		OrientedBox stretched(double _x, double _y, double _z) const noexcept;

		[[nodiscard]]
		OrientedBox stretched(Vec3 xyz) const noexcept;


		[[nodiscard]]
		OrientedBox scaled(double s) const noexcept;

		[[nodiscard]]
		OrientedBox scaled(double sx, double sy, double sz) const noexcept;

		[[nodiscard]]
		OrientedBox scaled(Vec3 s) const noexcept;


		[[nodiscard]]
		bool hasVolume() const noexcept;

		[[nodiscard]]
		std::array<Vec3, 8> getCorners() const noexcept;


		[[nodiscard]]
		OrientedBox lerp(const OrientedBox& other, double f) const noexcept;


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


		const OrientedBox& draw(const ColorF& color = Palette::White) const;

		const OrientedBox& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const OrientedBox& draw(const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		const OrientedBox& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const OrientedBox& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const OrientedBox& draw(const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		const OrientedBox& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const OrientedBox& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;

		const OrientedBox& draw(const Mat4x4& mat, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;


		const OrientedBox& draw(const PhongMaterial& material) const;

		const OrientedBox& draw(const Texture& texture, const PhongMaterial& material) const;

		const OrientedBox& draw(const TextureRegion& textureRegion, const PhongMaterial& material) const;

		const OrientedBox& draw(const Quaternion& rotation, const PhongMaterial& material) const;

		const OrientedBox& draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const;

		const OrientedBox& draw(const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		const OrientedBox& draw(const Mat4x4& mat, const PhongMaterial& material) const;

		const OrientedBox& draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const;

		const OrientedBox& draw(const Mat4x4& mat, const TextureRegion& textureRegion, const PhongMaterial& material) const;



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

		friend void Formatter(FormatData& formatData, const OrientedBox& value);
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
