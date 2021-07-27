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
# include "Optional.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"

namespace s3d
{
	class Texture;
	struct Quaternion;
	struct Mat4x4;
	struct Triangle3D;
	struct Sphere;
	struct OrientedBox;
	class ViewFrustum;
	struct Ray;

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


		SIV3D_NODISCARD_CXX20
		constexpr Box(Arg::bottomCenter_<Vec3> _center, double _size) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Box(Arg::bottomCenter_<Vec3> _center, Arithmetic _size) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Box(Arg::bottomCenter_<Vec3> _center, double _w, double _h, double _d) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic D>
	# else
		template <class W, class H, class D, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<D>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Box(Arg::bottomCenter_<Vec3> _center, W _w, H _h, D _d) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Box(Arg::bottomCenter_<Vec3> _center, const Vec3& _size) noexcept;



		constexpr Box& setPos(double cx, double cy, double cz) noexcept;

		constexpr Box& setPos(const Vec3& _center) noexcept;

		constexpr Box& setSize(double w, double h, double d) noexcept;

		constexpr Box& setSize(const Vec3& _size) noexcept;


		[[nodiscard]]
		constexpr Box stretched(double xyz) const noexcept;

		[[nodiscard]]
		constexpr Box stretched(double x, double y, double z) const noexcept;

		[[nodiscard]]
		constexpr Box stretched(Vec3 xyz) const noexcept;


		[[nodiscard]]
		std::array<Vec3, 8> getCorners() const noexcept;


		[[nodiscard]]
		bool intersects(const Vec3& point) const noexcept;

		[[nodiscard]]
		bool intersects(const Triangle3D& triangle) const noexcept;

		[[nodiscard]]
		bool intersects(const Sphere& sphere) const noexcept;

		[[nodiscard]]
		bool intersects(const Box& box) const noexcept;

		[[nodiscard]]
		bool intersects(const OrientedBox& box) const noexcept;

		[[nodiscard]]
		bool intersects(const ViewFrustum& frustum) const noexcept;

		[[nodiscard]]
		Optional<float> intersects(const Ray& ray) const noexcept;

		[[nodiscard]]
		bool contains(const Vec3& point) const noexcept;

		[[nodiscard]]
		bool contains(const Triangle3D& triangle) const noexcept;

		[[nodiscard]]
		bool contains(const Sphere& sphere) const noexcept;

		[[nodiscard]]
		bool contains(const Box& box) const noexcept;

		[[nodiscard]]
		bool contains(const OrientedBox& box) const noexcept;

		[[nodiscard]]
		bool contains(const ViewFrustum& frustum) const noexcept;




		const Box& draw(const ColorF& color = Palette::White) const;
		
		const Box& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Box& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Box& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Box& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Box& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;


		const Box& drawFrame(const ColorF& color = Palette::White) const;


		[[nodiscard]]
		static constexpr Box FromTwoPoints(const Vec3& a, const Vec3& b) noexcept;


		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Box& value)
		{
			return output << CharType('(')
				<< value.center << CharType(',') << CharType(' ')
				<< value.size << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Box& value)
		{
			CharType unused;
			return input >> unused
				>> value.center >> unused
				>> value.size >> unused;
		}

		friend void Formatter(FormatData& formatData, const Box& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Box& value);
	};
}

# include "detail/Box.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Box, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Box& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {})", value.center, value.size);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.center, value.size);
		}
	}
};
