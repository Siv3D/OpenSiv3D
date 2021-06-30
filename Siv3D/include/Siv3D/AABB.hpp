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

	struct AABB
	{
		Vec3 center;

		Vec3 size;

		SIV3D_NODISCARD_CXX20
		AABB() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr AABB(double _size) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr AABB(Arithmetic _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr AABB(double _w, double _h, double _d) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		explicit constexpr AABB(W _w, H _h, D _d) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr AABB(const Vec3& _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr AABB(double cx, double cy, double cz, double _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic S>
	# else
		template <class X, class Y, class Z, class S, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<S>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr AABB(X cx, Y cy, Z cz, S _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr AABB(double cx, double cy, double cz, double _w, double _h, double _d) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class X, class Y, class Z, class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		constexpr AABB(X cx, Y cy, Z cz, W _w, H _h, D _d) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr AABB(double cx, double cy, double cz, const Vec3& _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z>
	# else
		template <class X, class Y, class Z, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr AABB(X cx, Y cy, Z cz, const Vec3& _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr AABB(const Vec3& _center, double _size) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr AABB(const Vec3& _center, Arithmetic _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr AABB(const Vec3& _center, double _w, double _h, double _d) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr AABB(const Vec3& _center, W _w, H _h, D _d) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr AABB(const Vec3& _center, const Vec3& _size) noexcept;


		void draw(const ColorF& color = Palette::White) const;
		
		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;
	};
}

# include "detail/AABB.ipp"
