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

	struct Plane
	{
		Vec3 center;
		
		Vec2 size;

		SIV3D_NODISCARD_CXX20
		Plane() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Plane(double _size) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr Plane(Arithmetic _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Plane(double _w, double _h) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H>
	# else
		template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		explicit constexpr Plane(W _w, H _h) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Plane(const Vec2& _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Plane(double cx, double cy, double cz, double _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic S>
	# else
		template <class X, class Y, class Z, class S, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<S>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Plane(X cx, Y cy, Z cz, S _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Plane(double cx, double cy, double cz, double _w, double _h) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic W, Concept::Arithmetic H>
	# else
		template <class X, class Y, class Z, class W, class H, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<W>, std::is_arithmetic<H>>>* = nullptr>
	# endif
		constexpr Plane(X cx, Y cy, Z cz, W _w, H _h) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Plane(double cx, double cy, double cz, const Vec2& _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z>
	# else
		template <class X, class Y, class Z, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Plane(X cx, Y cy, Z cz, const Vec2& _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Plane(const Vec3& _center, double _size) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Plane(const Vec3& _center, Arithmetic _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Plane(const Vec3& _center, double _w, double _h) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H>
	# else
		template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Plane(const Vec3& _center, W _w, H _h) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Plane(const Vec3& _center, const Vec2& _size) noexcept;

		void draw(const ColorF& color = Palette::White) const;

		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;
	};
}

# include "detail/Plane.ipp"
