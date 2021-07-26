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
		OrientedBox(const Box& box, Quaternion _orientation = Quaternion::Identity()) noexcept;


		OrientedBox& setPos(double cx, double cy, double cz) noexcept;

		OrientedBox& setPos(const Vec3& _center) noexcept;

		OrientedBox& setSize(double w, double h, double d) noexcept;

		OrientedBox& setSize(const Vec3& _size) noexcept;

		OrientedBox& setOrientation(const Quaternion& _orientation) noexcept;

		[[nodiscard]]
		std::array<Vec3, 8> getCorners() const noexcept;


		const OrientedBox& draw(const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Texture & texture, const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Quaternion & rotation, const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Quaternion & rotation, const Texture & texture, const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Mat4x4 & mat, const ColorF & color = Palette::White) const;

		const OrientedBox& draw(const Mat4x4 & mat, const Texture & texture, const ColorF & color = Palette::White) const;


		const OrientedBox& drawFrame(const ColorF & color = Palette::White) const;

	};
}

# include "detail/OrientedBox.ipp"
