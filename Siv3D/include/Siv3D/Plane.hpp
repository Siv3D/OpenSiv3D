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

		const Plane& draw(const ColorF& color = Palette::White) const;

		const Plane& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Plane& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Plane& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Plane& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Plane& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;
	


		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Plane& value)
		{
			return output << CharType('(')
				<< value.center << CharType(',') << CharType(' ')
				<< value.size << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Plane& value)
		{
			CharType unused;
			return input >> unused
				>> value.center >> unused
				>> value.size >> unused;
		}

		friend void Formatter(FormatData& formatData, const Plane& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Plane& value);
	};
}

# include "detail/Plane.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Plane, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Plane& value, FormatContext& ctx)
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
