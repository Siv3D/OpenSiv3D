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

	struct Cone
	{
		Vec3 center;

		double r;

		double h;

		Quaternion orientation;

		SIV3D_NODISCARD_CXX20
		Cone() = default;

		SIV3D_NODISCARD_CXX20
		Cone(double _r, double _h, const Quaternion& _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		Cone(double cx, double cy, double cz, double _r, double _h, const Quaternion& _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		Cone(const Vec3& _center, double _r, double _h, const Quaternion& _orientation = Quaternion::Identity()) noexcept;

		SIV3D_NODISCARD_CXX20
		Cone(const Vec3& from, const Vec3& to, double _r) noexcept;

		SIV3D_NODISCARD_CXX20
		Cone(const Vec3& from, const Vec3& to, double _r, const Quaternion& _orientation) noexcept;

		const Cone& draw(const ColorF& color = Palette::White) const;

		const Cone& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Cone& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Cone& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Cone& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Cone& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;
	};
}

# include "detail/Cone.ipp"
