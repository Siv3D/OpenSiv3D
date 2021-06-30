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
# include "ColorHSV.hpp"

namespace s3d
{
	class Texture;
	struct Quaternion;

	struct Sphere
	{
		Vec3 center;

		double r;

		Sphere() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Sphere(double _r) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr Sphere(Arithmetic _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Sphere(double _x, double _y, double _z, double _r) noexcept;

		template <class X, class Y, class Z, class R>
		SIV3D_NODISCARD_CXX20
		constexpr Sphere(X _x, Y _y, Z _z, R _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Sphere(const Vec3& _center, double _r) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Sphere(const Vec3& _center, Arithmetic _r) noexcept;


		void draw(const ColorF& color = Palette::White) const;

		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;
	};
}

# include "detail/Sphere.ipp"
