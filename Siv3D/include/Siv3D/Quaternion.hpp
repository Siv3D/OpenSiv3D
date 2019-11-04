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
		__m128 vec;

		Quaternion() = default;

		Quaternion(const Quaternion&) = default;

		Quaternion& operator=(const Quaternion&) = default;

		Quaternion(Quaternion&&) = default;

		Quaternion& operator=(Quaternion&&) = default;

		explicit Quaternion(float _xyzw) noexcept
			: vec(SIMD::SetAll(_xyzw)) {}

		Quaternion(float _x, float _y, float _z, float _w) noexcept
			: vec(SIMD::Set(_x, _y, _z, _w)) {}

		template <class X, class Y, class Z, class W>
		Quaternion(X _x, Y _y, Z _z, W _w) noexcept
			: Quaternion(static_cast<float>(_x), static_cast<float>(_y), static_cast<float>(_z), static_cast<float>(_w)) {}

		template <class U, class V>
		Quaternion(const Vector2D<U> & xy, const Vector2D<V> & zw) noexcept
			: Quaternion(static_cast<float>(xy.x), static_cast<float>(xy.y), static_cast<float>(zw.x), static_cast<float>(zw.y)) {}

		template <class U, class W>
		Quaternion(const Vector3D<U> & xyz, W w) noexcept
			: Quaternion(static_cast<float>(xyz.x), static_cast<float>(xyz.y), static_cast<float>(xyz.z), static_cast<float>(w)) {}

		template <class U>
		Quaternion(const Vector4D<U> & v) noexcept
			: Quaternion(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z), static_cast<float>(v.w)) {}

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

		void SIV3D_VECTOR_CALL setX(float x) noexcept
		{
			vec = SIMD::SetX(vec, x);
		}

		void SIV3D_VECTOR_CALL setY(float y) noexcept
		{
			vec = SIMD::SetY(vec, y);
		}

		void SIV3D_VECTOR_CALL setZ(float z) noexcept
		{
			vec = SIMD::SetZ(vec, z);
		}

		void SIV3D_VECTOR_CALL setW(float w) noexcept
		{
			vec = SIMD::SetW(vec, w);
		}

		//[[nodiscard]] bool SIV3D_VECTOR_CALL isNaN() const;

		//[[nodiscard]] bool SIV3D_VECTOR_CALL isInfinite() const;

		//[[nodiscard]] bool SIV3D_VECTOR_CALL isIdentity() const;

		[[nodiscard]] Quaternion SIV3D_VECTOR_CALL inverse() const
		{
			return SIMD::QuaternionInverse(*this);
		}

		template <class Float>
		[[nodiscard]] Quaternion SIV3D_VECTOR_CALL slerp(Quaternion q, Float t) const
		{
			return SIMD::QuaternionSlerpV(*this, q, SIMD::SetAll(t));
		}

		[[nodiscard]] static constexpr Quaternion SIV3D_VECTOR_CALL Identity() noexcept
		{
			return SIMD::constants::m128_MIdentityR3;
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

		//[[nodiscard]] std::pair<Float3, float> SIV3D_VECTOR_CALL toAxisAngle() const
		//{

		//}
	};
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
		value = Quaternion(t);
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