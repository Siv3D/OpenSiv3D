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

	struct Cone
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


		Cone& setPos(value_type cx, value_type cy, value_type cz) noexcept;

		Cone& setPos(position_type _center) noexcept;

		Cone& setSize(value_type _r, value_type _h) noexcept;

		Cone& setOrientation(Quaternion _orientation) noexcept;


		[[nodiscard]]
		Cone movedBy(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		Cone movedBy(position_type v) const noexcept;

		Cone& moveBy(value_type _x, value_type _y, value_type _z) noexcept;

		Cone& moveBy(position_type v) noexcept;


		[[nodiscard]]
		Cone stretched(double _r, double _h) const noexcept;


		[[nodiscard]]
		Cone scaled(double sr, double sh) const noexcept;


		[[nodiscard]]
		bool hasVolume() const noexcept;


		[[nodiscard]]
		Cone lerp(const Cone& other, double f) const noexcept;


		[[nodiscard]]
		Vec3 vector() const noexcept;

		[[nodiscard]]
		position_type top() const noexcept;

		[[nodiscard]]
		position_type bottomCenter() const noexcept;


		const Cone& draw(const ColorF& color = Palette::White) const;

		const Cone& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Cone& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Cone& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Cone& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Cone& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;



		const Cone& draw(const PhongMaterial & material) const;

		const Cone& draw(const Texture& texture, const PhongMaterial& material) const;

		const Cone& draw(const Quaternion& rotation, const PhongMaterial& material) const;

		const Cone& draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const;

		const Cone& draw(const Mat4x4& mat, const PhongMaterial& material) const;

		const Cone& draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const;
	};
}

# include "detail/Cone.ipp"
