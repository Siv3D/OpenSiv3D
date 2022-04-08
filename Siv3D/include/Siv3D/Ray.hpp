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
# include "Optional.hpp"
# include "SIMD_Float4.hpp"
# include "Triangle3D.hpp"

namespace s3d
{
	struct Triangle3D;
	struct Sphere;
	struct Plane;
	struct InfinitePlane;
	struct Box;
	struct OrientedBox;
	class ViewFrustum;
	struct Cylinder;
	struct Cone;

	/// @brief レイ
	struct Ray
	{
		/// @brief 始点
		SIMD_Float4 origin;

		/// @brief 方向（正規化ベクトル）
		SIMD_Float4 direction;

		SIV3D_NODISCARD_CXX20
		Ray() = default;

		SIV3D_NODISCARD_CXX20
		Ray(Float3 _origin, Float3 normalizedDirection) noexcept;

		template <class X, class Y, class Z>
		SIV3D_NODISCARD_CXX20
		Ray(X ox, Y oy, Z oz, Float3 normalizedDirection) noexcept;

		template <class X, class Y, class Z>
		SIV3D_NODISCARD_CXX20
		Ray(Float3 _origin, X ndx, Y ndy, Z ndz) noexcept;

		/// @brief レイの始点を返します。
		/// @return レイの始点
		[[nodiscard]]
		Float3 SIV3D_VECTOR_CALL getOrigin() const noexcept;

		/// @brief レイの始点を設定します。
		/// @param _origin 新しいレイの始点
		/// @return *this
		Ray& SIV3D_VECTOR_CALL setOrigin(Float3 _origin) noexcept;

		/// @brief レイの方向（正規化ベクトル）を返します。
		/// @return レイの方向（正規化ベクトル）
		[[nodiscard]]
		Float3 SIV3D_VECTOR_CALL getDirection() const noexcept;

		/// @brief レイの方向（正規化ベクトル）を設定します。
		/// @param _direction 新しいレイの方向（正規化ベクトル）
		/// @return *this
		Ray& SIV3D_VECTOR_CALL setDirection(Float3 _direction) noexcept;

		/// @brief 始点からの距離を指定して、レイ上の点の座標を計算します。
		/// @param distance 始点からの距離
		/// @return レイ上の点の座標
		[[nodiscard]]
		Float3 SIV3D_VECTOR_CALL point_at(float distance) const noexcept;

		/// @brief 始点からの距離を指定して、レイ上の点の座標を計算します。
		/// @param distance 始点からの距離
		/// @return レイ上の点の座標
		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Vec3 SIV3D_VECTOR_CALL point_at(Arithmetic distance) const noexcept;

		/// @brief レイが交差するかを調べます。
		/// @param triangle 交差判定する相手の形状
		/// @return 交差する場合、視点からの距離。それ以外の場合は none
		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Triangle3D& triangle) const;

		/// @brief レイが交差するかを調べます。
		/// @param sphere 交差判定する相手の形状
		/// @return 交差する場合、視点からの距離。それ以外の場合は none
		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Sphere& sphere) const;

		/// @brief レイが交差するかを調べます。
		/// @param plane 交差判定する相手の形状
		/// @return 交差する場合、視点からの距離。それ以外の場合は none
		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Plane& plane) const;

		/// @brief レイが交差するかを調べます。
		/// @param plane 交差判定する相手の形状
		/// @return 交差する場合、視点からの距離。それ以外の場合は none
		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const InfinitePlane& plane) const;

		/// @brief レイが交差するかを調べます。
		/// @param aabb 交差判定する相手の形状
		/// @return 交差する場合、視点からの距離。それ以外の場合は none
		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Box& aabb) const;

		/// @brief レイが交差するかを調べます。
		/// @param obb 交差判定する相手の形状
		/// @return 交差する場合、視点からの距離。それ以外の場合は none
		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const OrientedBox& obb) const;

		/// @brief レイが交差するかを調べます。
		/// @param frustum 交差判定する相手の形状
		/// @return 交差する場合、視点からの距離。それ以外の場合は none
		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const ViewFrustum& frustum) const;

		/// @brief レイが交差するかを調べます。
		/// @param cylinder 交差判定する相手の形状
		/// @return 交差する場合、視点からの距離。それ以外の場合は none
		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Cylinder& cylinder) const;

		/// @brief レイが交差するかを調べます。
		/// @param cone 交差判定する相手の形状
		/// @return 交差する場合、視点からの距離。それ以外の場合は none
		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Cone& cone) const;


		[[nodiscard]]
		Optional<Float3> SIV3D_VECTOR_CALL intersectsAt(const Triangle3D& triangle) const;

		[[nodiscard]]
		Optional<Float3> SIV3D_VECTOR_CALL intersectsAt(const Sphere& sphere) const;

		[[nodiscard]]
		Optional<Float3> SIV3D_VECTOR_CALL intersectsAt(const Plane& plane) const;

		[[nodiscard]]
		Optional<Float3> SIV3D_VECTOR_CALL intersectsAt(const InfinitePlane& plane) const;

		[[nodiscard]]
		Optional<Float3> SIV3D_VECTOR_CALL intersectsAt(const Box& aabb) const;

		[[nodiscard]]
		Optional<Float3> SIV3D_VECTOR_CALL intersectsAt(const OrientedBox& obb) const;

		[[nodiscard]]
		Optional<Float3> SIV3D_VECTOR_CALL intersectsAt(const ViewFrustum& frustum) const;

		[[nodiscard]]
		Optional<Float3> SIV3D_VECTOR_CALL intersectsAt(const Cylinder& cylinder) const;

		[[nodiscard]]
		Optional<Float3> SIV3D_VECTOR_CALL intersectsAt(const Cone& cone) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Ray& value)
		{
			return output << CharType('(')
				<< value.origin.xyz() << CharType(',') << CharType(' ')
				<< value.direction.xyz() << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Ray& value)
		{
			CharType unused;
			Float3 origin, direction;
			input >> unused
				>> origin >> unused
				>> direction >> unused;
			value.origin = SIMD_Float4{ origin, 0.0f };
			value.direction = SIMD_Float4{ direction, 0.0f };
			return input;
		}

		friend void Formatter(FormatData& formatData, const Ray& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Ray, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Ray& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {})", value.origin.xyz(), value.direction.xyz());
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.origin.xyz(), value.direction.xyz());
		}
	}
};

# include "detail/Ray.ipp"
