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
# include "Quaternion.hpp"

namespace s3d
{
	class Texture;
	struct Mat4x4;

	struct Cylinder
	{
		Vec3 center;

		double r;

		double h;

		Quaternion orientation;

		SIV3D_NODISCARD_CXX20
		Cylinder() = default;

		SIV3D_NODISCARD_CXX20
		Cylinder(double _r, double _h, const Quaternion& _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		Cylinder(double cx, double cy, double cz, double _r, double _h, const Quaternion& _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		Cylinder(const Vec3& _center, double _r, double _h, const Quaternion& _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		Cylinder(const Vec3& from, const Vec3& to, double _r) noexcept;

		SIV3D_NODISCARD_CXX20
		Cylinder(const Vec3& from, const Vec3& to, double _r, const Quaternion& _orientation) noexcept;



		const Cylinder& draw(const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;
	};
}

# include "detail/Cylinder.ipp"
