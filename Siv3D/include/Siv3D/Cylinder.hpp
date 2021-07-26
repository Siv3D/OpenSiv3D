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
	struct Mat4x4;

	struct Cylinder
	{
		Vec3 center;

		double r;

		double h;

		const Cylinder& draw(const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;
	};
}
