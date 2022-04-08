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
# include "SIMD_Float4.hpp"
# include "Quaternion.hpp"
# include "InfinitePlane.hpp"

namespace s3d
{
	/// @brief 4x4 行列クラス
	struct alignas(16) Mat4x4
	{
		DirectX::XMMATRIX value;

		SIV3D_NODISCARD_CXX20
		Mat4x4() = default;

		SIV3D_NODISCARD_CXX20
		Mat4x4(DirectX::XMMATRIX m) noexcept;

		SIV3D_NODISCARD_CXX20
		Mat4x4(SIMD_Float4 r0, SIMD_Float4 r1, SIMD_Float4 r2, SIMD_Float4 r3) noexcept;

		SIV3D_NODISCARD_CXX20
		Mat4x4(Float4 r0, Float4 r1, Float4 r2, Float4 r3) noexcept;

		SIV3D_NODISCARD_CXX20
		Mat4x4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit Mat4x4(Quaternion q) noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL operator +() const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL operator -() const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL operator +(Mat4x4 m) const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL operator -(Mat4x4 m) const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL operator *(float s) const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL operator *(Mat4x4 m) const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL operator /(float s) const noexcept;

		Mat4x4& SIV3D_VECTOR_CALL operator +=(Mat4x4 m) noexcept;

		Mat4x4& SIV3D_VECTOR_CALL operator -=(Mat4x4 m) noexcept;

		Mat4x4& SIV3D_VECTOR_CALL operator *=(float s) noexcept;

		Mat4x4& SIV3D_VECTOR_CALL operator *=(Mat4x4 m) noexcept;

		Mat4x4& SIV3D_VECTOR_CALL operator /=(float s) noexcept;

		[[nodiscard]]
		friend bool operator ==(const Mat4x4& lhs, const Mat4x4& rhs) noexcept
		{
			return DirectX::XMVector4Equal(lhs.value.r[0], rhs.value.r[0])
				&& DirectX::XMVector4Equal(lhs.value.r[1], rhs.value.r[1])
				&& DirectX::XMVector4Equal(lhs.value.r[2], rhs.value.r[2])
				&& DirectX::XMVector4Equal(lhs.value.r[3], rhs.value.r[3]);
		}

		[[nodiscard]]
		friend bool operator !=(const Mat4x4& lhs, const Mat4x4& rhs) noexcept
		{
			return DirectX::XMVector4NotEqual(lhs.value.r[0], rhs.value.r[0])
				|| DirectX::XMVector4NotEqual(lhs.value.r[1], rhs.value.r[1])
				|| DirectX::XMVector4NotEqual(lhs.value.r[2], rhs.value.r[2])
				|| DirectX::XMVector4NotEqual(lhs.value.r[3], rhs.value.r[3]);
		}

		[[nodiscard]]
		friend Mat4x4 SIV3D_VECTOR_CALL operator *(float s, const Mat4x4& v) noexcept
		{
			return (s * v.value);
		}

		[[nodiscard]]
		SIV3D_VECTOR_CALL operator DirectX::XMMATRIX() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL hasNaN() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL isIdentity() const noexcept;

		bool SIV3D_VECTOR_CALL decompose(Float3& scale, Quaternion& quaternion, Float3& translate) const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL transposed() const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL inverse() const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL inverse(float& determinant) const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL determinant() const noexcept;

		template <class X, class Y, class Z>
		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL translated(X x, Y y, Z z) const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL translated(Float3 v) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL scaled(Arithmetic s) const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL scaled(Float3 s) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL rotatedX(Arithmetic angle) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL rotatedY(Arithmetic angle) const noexcept;
		
		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL rotatedZ(Arithmetic angle) const noexcept;

		template <class X, class Y, class Z>
		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL rollPitchYaw(X pitch, Y yaw, Z roll) const noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL rotated(Float3 axis, Arithmetic angle) const noexcept;

		[[nodiscard]]
		Mat4x4 SIV3D_VECTOR_CALL rotated(Quaternion quaternion) const noexcept;

		[[nodiscard]]
		Float3 SIV3D_VECTOR_CALL transformPoint(Float3 pos) const noexcept;

		void SIV3D_VECTOR_CALL transformPoints(Float3* pOutputStream, const Float3* pInputStream, size_t vectorCount) const noexcept;

		void SIV3D_VECTOR_CALL transformPoints(Float3* pOutputStream, size_t outputStrideBytes,
			const Float3* pInputStream, size_t inputStrideBytes, size_t vectorCount) const noexcept;

		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Identity() noexcept;

		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Set(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33) noexcept;

		template <class X, class Y, class Z>
		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Translate(X x, Y y, Z z) noexcept;

		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Translate(Float3 v) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Scale(Arithmetic s) noexcept;

		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Scale(Float3 s) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Scale(Arithmetic s, Float3 center) noexcept;

		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Scale(Float3 s, Float3 center) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL RotateX(Arithmetic angle) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL RotateY(Arithmetic angle) noexcept;
		
		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL RotateZ(Arithmetic angle) noexcept;

		template <class X, class Y, class Z>
		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL RollPitchYaw(X pitch, Y yaw, Z roll) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Rotate(Float3 axis, Arithmetic angle) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Rotate(Float3 axis, Arithmetic angle, Float3 center) noexcept;

		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Rotate(Quaternion quaternion) noexcept;

		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Rotate(Quaternion quaternion, Float3 center) noexcept;

		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Reflect(InfinitePlane plane) noexcept;

		[[nodiscard]]
		static Mat4x4 SIV3D_VECTOR_CALL Shadow(InfinitePlane plane, Float3 lightPos) noexcept;

		template <class CharType>
		friend inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Mat4x4& value)
		{
			return output << CharType('(')
				<< SIMD_Float4{ value.value.r[0] } << CharType(',')
				<< SIMD_Float4{ value.value.r[1] } << CharType(',')
				<< SIMD_Float4{ value.value.r[2] } << CharType(',')
				<< SIMD_Float4{ value.value.r[3] } << CharType(')');
		}

		template <class CharType>
		friend inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Mat4x4& value)
		{
			CharType unused;
			Float4 r1, r2, r3, r4;

			input >> unused
				>> r1 >> unused
				>> r2 >> unused
				>> r3 >> unused
				>> r4 >> unused;

			value = Mat4x4{ r1, r2, r3, r4 };

			return input;
		}

		friend void Formatter(FormatData& formatData, const Mat4x4& value);
	};
}

# include "detail/Mat4x4.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Mat4x4, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Mat4x4& value, FormatContext& ctx)
	{
		const s3d::Float4 r0 = s3d::SIMD_Float4{ value.value.r[0] }.toFloat4();
		const s3d::Float4 r1 = s3d::SIMD_Float4{ value.value.r[1] }.toFloat4();
		const s3d::Float4 r2 = s3d::SIMD_Float4{ value.value.r[2] }.toFloat4();
		const s3d::Float4 r3 = s3d::SIMD_Float4{ value.value.r[3] }.toFloat4();

		if (tag.empty())
		{
			return format_to(ctx.out(), U"(({}, {}, {}, {}), ({}, {}, {}, {}), ({}, {}, {}, {}), ({}, {}, {}, {}))",
				r0.x, r0.y, r0.z, r0.w, r1.x, r1.y, r1.z, r1.w, r2.x, r2.y, r2.z, r2.w, r3.x, r3.y, r3.z, r3.w);
		}
		else
		{
			const std::u32string format
				= (U"(({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}), ({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}), ({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}), ({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}))");
			return format_to(ctx.out(), format, r0.x, r0.y, r0.z, r0.w, r1.x, r1.y, r1.z, r1.w, r2.x, r2.y, r2.z, r2.w, r3.x, r3.y, r3.z, r3.w);
		}
	}
};
