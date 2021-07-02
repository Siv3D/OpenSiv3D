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

	struct Box
	{
		Vec3 center;

		Vec3 size;

		SIV3D_NODISCARD_CXX20
		Box() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Box(double _size) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr Box(Arithmetic _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Box(double _w, double _h, double _d) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		explicit constexpr Box(W _w, H _h, D _d) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Box(const Vec3& _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Box(double cx, double cy, double cz, double _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic S>
	# else
		template <class X, class Y, class Z, class S, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<S>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Box(X cx, Y cy, Z cz, S _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Box(double cx, double cy, double cz, double _w, double _h, double _d) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z, Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class X, class Y, class Z, class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>, std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		constexpr Box(X cx, Y cy, Z cz, W _w, H _h, D _d) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Box(double cx, double cy, double cz, const Vec3& _size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic Z>
	# else
		template <class X, class Y, class Z, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<Z>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Box(X cx, Y cy, Z cz, const Vec3& _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Box(const Vec3& _center, double _size) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Box(const Vec3& _center, Arithmetic _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Box(const Vec3& _center, double _w, double _h, double _d) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Box(const Vec3& _center, W _w, H _h, D _d) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Box(const Vec3& _center, const Vec3& _size) noexcept;


		constexpr Box& setPos(double cx, double cy, double cz) noexcept;

		constexpr Box& setPos(const Vec3& _center) noexcept;

		constexpr Box& setSize(double w, double h, double d) noexcept;

		constexpr Box& setSize(const Vec3& _size) noexcept;


		[[nodiscard]]
		bool intersects(const Box& box) const noexcept;


		void draw(const ColorF& color = Palette::White) const;
		
		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;
	};
}

# include "detail/Box.ipp"
