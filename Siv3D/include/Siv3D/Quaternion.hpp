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

namespace s3d
{
	struct Mat4x4;

	/// @brief クォータニオン
	struct alignas(16) Quaternion
	{
		SIMD_Float4 value = { 0.0f, 0.0f, 0.0f, 1.0f };

		SIV3D_NODISCARD_CXX20
		Quaternion() = default;

		SIV3D_NODISCARD_CXX20
		Quaternion(const Quaternion&) = default;

		SIV3D_NODISCARD_CXX20
		Quaternion(float x, float y, float z, float w) noexcept;

		template <class X, class Y, class Z, class W>
		SIV3D_NODISCARD_CXX20
		Quaternion(X x, Y y, Z z, W w) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		Quaternion(const Float3& axis, Arithmetic angle) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit Quaternion(const Mat4x4& m) noexcept;
		
		SIV3D_NODISCARD_CXX20
		explicit Quaternion(Float4 _vec) noexcept;

		SIV3D_NODISCARD_CXX20
		Quaternion(aligned_float4 _vec) noexcept;

		Quaternion& operator =(const Quaternion&) = default;

		Quaternion& SIV3D_VECTOR_CALL operator =(aligned_float4 other) noexcept;

		Quaternion& SIV3D_VECTOR_CALL operator =(SIMD_Float4 other) noexcept;

		[[nodiscard]]
		Quaternion SIV3D_VECTOR_CALL operator *(Quaternion q) const noexcept;

		Quaternion& SIV3D_VECTOR_CALL operator *=(Quaternion q) noexcept;

		[[nodiscard]]
		Float3 SIV3D_VECTOR_CALL operator *(Float3 v) const noexcept;

		[[nodiscard]]
		friend Float3 SIV3D_VECTOR_CALL operator *(Float3 v, Quaternion q) noexcept
		{
			return (q * v);
		}

		[[nodiscard]]
		SIV3D_VECTOR_CALL operator aligned_float4() const noexcept;

		[[nodiscard]]
		Float4 SIV3D_VECTOR_CALL toFloat4() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL elem(size_t index) const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL getX() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL getY() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL getZ() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL getW() const noexcept;

		void SIV3D_VECTOR_CALL setX(float x) noexcept;

		void SIV3D_VECTOR_CALL setY(float y) noexcept;

		void SIV3D_VECTOR_CALL setZ(float z) noexcept;

		void SIV3D_VECTOR_CALL setW(float w) noexcept;

		void SIV3D_VECTOR_CALL set(float x, float y, float z, float w) noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL isZero() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL isIdentity() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL hasNaN() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL hasInf() const noexcept;

		Quaternion& SIV3D_VECTOR_CALL normalize() noexcept;

		[[nodiscard]]
		Quaternion SIV3D_VECTOR_CALL normalized() const noexcept;

		Quaternion& SIV3D_VECTOR_CALL conjugate() noexcept;

		[[nodiscard]]
		Quaternion SIV3D_VECTOR_CALL conjugated() const noexcept;

		[[nodiscard]]
		Quaternion SIV3D_VECTOR_CALL inverse() const noexcept;

		SIV3D_CONCEPT_FLOATING_POINT
		[[nodiscard]]
		Quaternion SIV3D_VECTOR_CALL slerp(Quaternion q, Float t) const noexcept;

		[[nodiscard]]
		std::pair<Float3, float> SIV3D_VECTOR_CALL toAxisAngle() const noexcept;

		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL Identity() noexcept;

		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL Zero() noexcept;

		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL FromUnitVectors(const Vec3& from, const Vec3& to) noexcept;

		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL FromUnitVectorPairs(const std::pair<Vec3, Vec3>& from, const std::pair<Vec3, Vec3>& to) noexcept;

		template <class X, class Y, class Z>
		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL RollPitchYaw(X pitch, Y yaw, Z roll) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL RotationNormal(Float3 normalAxis, Arithmetic angle) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL RotationAxis(Float3 axis, Arithmetic angle) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL RotateX(Arithmetic angle) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL RotateY(Arithmetic angle) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL RotateZ(Arithmetic angle) noexcept;

		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL Rotate(const Mat4x4& m) noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Quaternion& value)
		{
			return output << value.toFloat4();
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Quaternion& value)
		{
			Float4 t;
			input >> t;
			value = SIMD_Float4{ t };
			return input;
		}

		friend void Formatter(FormatData& formatData, const Quaternion& value);
	};
}

# include "detail/Quaternion.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Quaternion, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Quaternion& value, FormatContext& ctx)
	{
		const s3d::Float4 v = value.toFloat4();

		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", v.x, v.y, v.z, v.w);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, v.x, v.y, v.z, v.w);
		}
	}
};
