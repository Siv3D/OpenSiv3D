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
# include "Optional.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"

namespace s3d
{
	class Texture;
	struct Quaternion;
	struct Mat4x4;
	struct Triangle3D;
	struct OrientedBox;
	class ViewFrustum;
	struct Ray;
	struct PhongMaterial;

	struct Sphere
	{
		using position_type	= Vec3;

		using size_type		= position_type::value_type;

		using value_type	= position_type::value_type;

	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			/// @brief 球の中心座標
			position_type center;

			struct
			{
				/// @brief 球の中心の X 座標
				value_type x;

				/// @brief 球の中心の Y 座標
				value_type y;

				/// @brief 球の中心の Z 座標
				value_type z;
			};
		};

		/// @brief 球の半径
		size_type r;

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		Sphere() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Sphere(double _r) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		explicit constexpr Sphere(Arithmetic _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Sphere(double _x, double _y, double _z, double _r) noexcept;

		template <class X, class Y, class Z, class R>
		SIV3D_NODISCARD_CXX20
		constexpr Sphere(X _x, Y _y, Z _z, R _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Sphere(const Vec3& _center, double _r) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		constexpr Sphere(const Vec3& _center, Arithmetic _r) noexcept;


		[[nodiscard]]
		friend constexpr bool operator ==(const Sphere& lhs, const Sphere& rhs) noexcept
		{
			return (lhs.center == rhs.center)
				&& (lhs.r == rhs.r);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Sphere& lhs, const Sphere& rhs) noexcept
		{
			return (lhs.center != rhs.center)
				|| (lhs.r != rhs.r);
		}

		constexpr Sphere& set(value_type _x, value_type _y, size_type _z, size_type _r) noexcept;

		constexpr Sphere& set(position_type _center, size_type _r) noexcept;

		constexpr Sphere& set(const Sphere& sphere) noexcept;

		constexpr Sphere& setPos(value_type _x, value_type _y, value_type _z) noexcept;

		constexpr Sphere& setPos(position_type _center) noexcept;

		constexpr Sphere& setR(value_type _r) noexcept;


		[[nodiscard]]
		constexpr Sphere movedBy(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		constexpr Sphere movedBy(position_type v) const noexcept;

		constexpr Sphere& moveBy(value_type _x, value_type _y, value_type _z) noexcept;

		constexpr Sphere& moveBy(position_type v) noexcept;


		[[nodiscard]]
		constexpr Sphere stretched(value_type size) const noexcept;

		[[nodiscard]]
		constexpr Sphere scaled(double s) const noexcept;


		[[nodiscard]]
		constexpr position_type top() const noexcept;

		[[nodiscard]]
		constexpr position_type bottom() const noexcept;

		[[nodiscard]]
		constexpr position_type left() const noexcept;

		[[nodiscard]]
		constexpr position_type right() const noexcept;

		[[nodiscard]]
		constexpr position_type forward() const noexcept;

		[[nodiscard]]
		constexpr position_type backward() const noexcept;


		[[nodiscard]]
		constexpr Sphere lerp(const Sphere& other, double f) const noexcept;


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




		const Sphere& draw(const ColorF& color = Palette::White) const;

		const Sphere& draw(const Texture& texture, const ColorF& color = Palette::White) const;

		const Sphere& draw(const Quaternion& rotation, const ColorF& color = Palette::White) const;

		const Sphere& draw(const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		const Sphere& draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;

		const Sphere& draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;


		const Sphere& draw(const PhongMaterial& material) const;

		const Sphere& draw(const Texture& texture, const PhongMaterial& material) const;

		const Sphere& draw(const Quaternion& rotation, const PhongMaterial& material) const;

		const Sphere& draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const;

		const Sphere& draw(const Mat4x4& mat, const PhongMaterial& material) const;

		const Sphere& draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const;



		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Sphere& value)
		{
			return output << CharType('(')
				<< value.center << CharType(',') << CharType(' ')
				<< value.r << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Sphere& value)
		{
			CharType unused;
			return input >> unused
				>> value.center >> unused
				>> value.r >> unused;
		}

		friend void Formatter(FormatData& formatData, const Sphere& value);
	};
}

# include "detail/Sphere.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Sphere, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Sphere& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {})", value.center, value.r);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.center, value.r);
		}
	}
};
