//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <xmmintrin.h>
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "SIMDMath.hpp"
# include "SIMD_Float4.hpp"
# include "Mat4x4.hpp"

namespace s3d
{
	struct alignas(16) Quaternion
	{
		__m128 vec = SIMD::constants::m128_MIdentityR3;

		constexpr Quaternion() = default;

		Quaternion(const Quaternion&) = default;

		Quaternion& operator=(const Quaternion&) = default;

		Quaternion(Quaternion&&) = default;

		Quaternion& operator=(Quaternion&&) = default;

		Quaternion(float _x, float _y, float _z, float _w) noexcept
			: vec(SIMD::Set(_x, _y, _z, _w)) {}

		template <class X, class Y, class Z, class W>
		Quaternion(X _x, Y _y, Z _z, W _w) noexcept
			: Quaternion(static_cast<float>(_x), static_cast<float>(_y), static_cast<float>(_z), static_cast<float>(_w)) {}

		template <class Float, std::enable_if_t<std::is_convertible_v<Float, float>>* = nullptr>
		Quaternion(const Float3& axis, Float angle) noexcept
			: vec{ SIMD::QuaternionRotationAxis(SIMD_Float4(axis, 0.0f), static_cast<float>(angle)) } {}

		explicit Quaternion(Mat4x4 m) noexcept
			: vec{ SIMD::QuaternionRotationMatrix(m) } {}

		constexpr Quaternion(__m128 _vec) noexcept
			: vec(_vec) {}

		[[nodiscard]] constexpr SIV3D_VECTOR_CALL operator __m128() const noexcept
		{
			return vec;
		}

		[[nodiscard]] Float4 SIV3D_VECTOR_CALL toFloat4() const noexcept
		{
			Float4 result;

			SIMD::StoreFloat4(&result, vec);

			return result;
		}

		[[nodiscard]] float elem(size_t index) const noexcept
		{
			return SIMD::GetByIndex(vec, index);
		}

		[[nodiscard]] float getX() const noexcept
		{
			return SIMD::GetX(vec);
		}

		[[nodiscard]] float getY() const noexcept
		{
			return SIMD::GetY(vec);
		}

		[[nodiscard]] float getZ() const noexcept
		{
			return SIMD::GetZ(vec);
		}

		[[nodiscard]] float getW() const noexcept
		{
			return SIMD::GetW(vec);
		}

		const Quaternion& SIV3D_VECTOR_CALL setX(float x) noexcept
		{
			vec = SIMD::SetX(vec, x);
			return *this;
		}

		const Quaternion& SIV3D_VECTOR_CALL setY(float y) noexcept
		{
			vec = SIMD::SetY(vec, y);
			return *this;
		}

		const Quaternion& SIV3D_VECTOR_CALL setZ(float z) noexcept
		{
			vec = SIMD::SetZ(vec, z);
			return *this;
		}

		const Quaternion& SIV3D_VECTOR_CALL setW(float w) noexcept
		{
			vec = SIMD::SetW(vec, w);
			return *this;
		}

		constexpr Quaternion& SIV3D_VECTOR_CALL set(const Quaternion& q) noexcept
		{
			vec = q.vec;
			return *this;
		}

		void SIV3D_VECTOR_CALL multiply(const Quaternion& q) noexcept
		{
			vec = SIMD::QuaternionMultiply(vec, q);
		}

		Quaternion& SIV3D_VECTOR_CALL operator *=(const Quaternion& q) noexcept
		{
			multiply(q);
			return *this;
		}

		[[nodiscard]] Quaternion SIV3D_VECTOR_CALL operator *(const Quaternion& q) const noexcept
		{
			return SIMD::QuaternionMultiply(vec, q);
		}

		[[nodiscard]] Float3 operator *(const Float3& v) const noexcept
		{
			Float3 result;
			SIMD::StoreFloat3(&result, SIMD::Vector3Rotate(SIMD_Float4(v, 0.0f), vec));
			return result;
		}

		[[nodiscard]] bool SIV3D_VECTOR_CALL isIdentity() const noexcept
		{
			return SIMD::Vector4Equal(vec, SIMD::constants::m128_MIdentityR3);
		}

		[[nodiscard]] bool SIV3D_VECTOR_CALL isZero() const noexcept
		{
			return SIMD::Vector4Equal(vec, SIMD::constants::m128_Zero);
		}

		[[nodiscard]] bool SIV3D_VECTOR_CALL isNaN() const noexcept
		{
			return SIMD::Vector4IsNaN(vec);
		}

		[[nodiscard]] bool SIV3D_VECTOR_CALL isInfinite() const noexcept
		{
			return SIMD::Vector4IsInfinite(vec);
		}

		Quaternion& SIV3D_VECTOR_CALL normalize() noexcept
		{
			vec = SIMD::QuaternionNormalize(vec);
			return *this;
		}

		[[nodiscard]] Quaternion SIV3D_VECTOR_CALL normalized() const noexcept
		{
			return SIMD::QuaternionNormalize(vec);
		}

		Quaternion& SIV3D_VECTOR_CALL conjugate() noexcept
		{
			vec = SIMD::QuaternionConjugate(vec);
			return *this;
		}

		[[nodiscard]] Quaternion SIV3D_VECTOR_CALL conjugated() const noexcept
		{
			return SIMD::QuaternionConjugate(vec);
		}

		[[nodiscard]] Quaternion SIV3D_VECTOR_CALL inverse() const noexcept
		{
			return SIMD::QuaternionInverse(*this);
		}

		template <class Float>
		[[nodiscard]] Quaternion SIV3D_VECTOR_CALL slerp(Quaternion q, Float t) const noexcept
		{
			return SIMD::QuaternionSlerp(*this, q, static_cast<float>(t));
		}

		[[nodiscard]] std::pair<Float3, float> SIV3D_VECTOR_CALL toAxisAngle() const noexcept
		{
			Float3 axis;
			SIMD::StoreFloat3(&axis, SIMD::Vector3Normalize(vec));
			return{ axis, SIMD::ScalarACos(SIMD::GetW(vec)) * 2.0f };
		}

		[[nodiscard]] static constexpr Quaternion SIV3D_VECTOR_CALL Identity() noexcept
		{
			return SIMD::constants::m128_MIdentityR3;
		}

		[[nodiscard]] static constexpr Quaternion SIV3D_VECTOR_CALL Zero() noexcept
		{
			return SIMD::constants::m128_Zero;
		}

		template <class X, class Y, class Z>
		[[nodiscard]] static Quaternion SIV3D_VECTOR_CALL RollPitchYaw(X pitch, Y yaw, Z roll) noexcept
		{
			return SIMD::QuaternionRotationRollPitchYawFromVector(SIMD_Float4(pitch, yaw, roll, 0.0f));
		}

		[[nodiscard]] static Quaternion SIV3D_VECTOR_CALL RollPitchYawFromVector(const Float3& angles) noexcept
		{
			return SIMD::QuaternionRotationRollPitchYawFromVector(SIMD_Float4(angles, 0.0f));
		}

		template <class Float>
		[[nodiscard]] static Quaternion SIV3D_VECTOR_CALL RotationNormal(const Float3& normalAxis, Float angle)
		{
			return SIMD::QuaternionRotationNormal(SIMD_Float4(normalAxis, 0.0f), static_cast<float>(angle));
		}

		template <class Float>
		[[nodiscard]] static Quaternion SIV3D_VECTOR_CALL RotationAxis(const Float3& axis, Float angle)
		{
			return SIMD::QuaternionRotationAxis(SIMD_Float4(axis, 0.0f), static_cast<float>(angle));
		}

		[[nodiscard]] static Quaternion SIV3D_VECTOR_CALL RotationMatrix(Mat4x4 m)
		{
			return SIMD::QuaternionRotationMatrix(m);
		}
	};

	inline Mat4x4::Mat4x4(Quaternion q) noexcept
	{
		*this = SIMD::MatrixRotationQuaternion(q.vec);
	}
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Quaternion& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Quaternion& value)
	{
		return output << value.toFloat4();
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Quaternion& value)
	{
		Float4 t;
		CharType unused;
		input >> t;
		value = Quaternion(SIMD_Float4(t));
		return input;
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::Quaternion>
	{
		[[nodiscard]] size_t operator ()(const s3d::Quaternion& value) const noexcept
		{
			return s3d::Hash::FNV1a(value);
		}
	};
}

//////////////////////////////////////////////////
//
//	fmt
//
//////////////////////////////////////////////////

namespace fmt_s3d
{
	template <>
	struct formatter<s3d::Quaternion, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Quaternion& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			const s3d::Float4 v = value.toFloat4();

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), v.x, v.y, v.z, v.w);
		}
	};
}