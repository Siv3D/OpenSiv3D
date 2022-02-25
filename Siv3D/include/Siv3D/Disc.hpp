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
# include "ColorHSV.hpp"

namespace s3d
{
	class Texture;
	struct Quaternion;
	struct Mat4x4;
	struct PhongMaterial;

	struct Disc
	{
		using position_type = Vec3;

		using size_type = position_type::value_type;

		using value_type = position_type::value_type;

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

	SIV3D_DISABLE_MSVC_WARNINGS_POP()
		
		size_type r;

		SIV3D_NODISCARD_CXX20
		Disc() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Disc(double _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Disc(double cx, double cy, double cz, double _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Disc(const Vec3& _center, double _r) noexcept;


		constexpr Disc& setPos(value_type cx, value_type cy, value_type cz) noexcept;

		constexpr Disc& setPos(position_type _center) noexcept;

		constexpr Disc& setR(size_type _r) noexcept;


		[[nodiscard]]
		constexpr Disc movedBy(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		constexpr Disc movedBy(position_type v) const noexcept;

		constexpr Disc& moveBy(value_type _x, value_type _y, value_type _z) noexcept;

		constexpr Disc& moveBy(position_type v) noexcept;


		[[nodiscard]]
		constexpr Disc stretched(value_type _r) const noexcept;


		[[nodiscard]]
		constexpr Disc scaled(double s) const noexcept;


		[[nodiscard]]
		constexpr bool hasArea() const noexcept;

		[[nodiscard]]
		constexpr Disc lerp(const Disc& other, double f) const noexcept;


		const Disc& draw(const ColorF& color = Palette::White) const;

		const Disc& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Disc& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Disc& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Disc& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Disc& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;


		const Disc& draw(const PhongMaterial& material) const;

		const Disc& draw(const Texture& texture, const PhongMaterial& material) const;

		const Disc& draw(const Quaternion& rotation, const PhongMaterial& material) const;

		const Disc& draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const;

		const Disc& draw(const Mat4x4& mat, const PhongMaterial& material) const;

		const Disc& draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const;

	};
}

# include "detail/Disc.ipp"
