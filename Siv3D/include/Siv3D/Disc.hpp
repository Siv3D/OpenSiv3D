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

	struct Disc
	{
		Vec3 center;
		
		double r;

		SIV3D_NODISCARD_CXX20
		Disc() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Disc(double _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Disc(double cx, double cy, double cz, double _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Disc(const Vec3& _center, double _r) noexcept;


		const Disc& draw(const ColorF& color = Palette::White) const;

		const Disc& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Disc& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Disc& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Disc& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Disc& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;
	};
}

# include "detail/Disc.ipp"
