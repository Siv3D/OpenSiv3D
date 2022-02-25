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
# include "Quaternion.hpp"

namespace s3d
{
	class Texture;
	struct Mat4x4;
	struct PhongMaterial;

	/// @brief 円柱
	struct Cylinder
	{
		using position_type = Vec3;

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

		value_type r;

		value_type h;

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


		Cylinder& setPos(value_type cx, value_type cy, value_type cz) noexcept;

		Cylinder& setPos(position_type _center) noexcept;

		Cylinder& setSize(value_type _r, value_type _h) noexcept;

		Cylinder& setOrientation(Quaternion _orientation) noexcept;


		[[nodiscard]]
		Cylinder movedBy(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		Cylinder movedBy(position_type v) const noexcept;

		Cylinder& moveBy(value_type _x, value_type _y, value_type _z) noexcept;

		Cylinder& moveBy(position_type v) noexcept;


		[[nodiscard]]
		Cylinder stretched(double _r, double _h) const noexcept;


		[[nodiscard]]
		Cylinder scaled(double sr, double sh) const noexcept;


		[[nodiscard]]
		bool hasVolume() const noexcept;


		[[nodiscard]]
		Cylinder lerp(const Cylinder& other, double f) const noexcept;


		[[nodiscard]]
		Vec3 vector() const noexcept;

		[[nodiscard]]
		position_type topCenter() const noexcept;

		[[nodiscard]]
		position_type bottomCenter() const noexcept;


		const Cylinder& draw(const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Cylinder& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;



		const Cylinder& draw(const PhongMaterial & material) const;

		const Cylinder& draw(const Texture& texture, const PhongMaterial& material) const;

		const Cylinder& draw(const Quaternion& rotation, const PhongMaterial& material) const;

		const Cylinder& draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const;

		const Cylinder& draw(const Mat4x4& mat, const PhongMaterial& material) const;

		const Cylinder& draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const;

	};
}

# include "detail/Cylinder.ipp"
