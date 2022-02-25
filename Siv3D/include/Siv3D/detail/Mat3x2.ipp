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

namespace s3d
{
	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Mat3x2::Mat3x2(const Arithmetic s) noexcept
		: _11{ static_cast<value_type>(s) }, _12{ 0.0f }
		, _21{ 0.0f }, _22{ static_cast<value_type>(s) }
		, _31{ 0.0f }, _32{ 0.0f } {}

	inline constexpr Mat3x2::Mat3x2(const float m11, const float m12, const float m21, const float m22, const float m31, const float m32) noexcept
		: _11{ m11 }, _12{ m12 }
		, _21{ m21 }, _22{ m22 }
		, _31{ m31 }, _32{ m32 } {}

	inline constexpr Mat3x2 Mat3x2::Screen(const Float2 size) noexcept
	{
		return{ (2.0f / size.x), 0.0f,
				0.0f, (-2.0f / size.y),
				-1.0f, 1.0f };
	}

	inline constexpr Mat3x2 Mat3x2::translated(const Float2 v) const noexcept
	{
		Mat3x2 mat = *this;
		mat._31 += v.x;
		mat._32 += v.y;
		return mat;
	}

	template <class X, class Y>
	inline constexpr Mat3x2 Mat3x2::translated(const X x, const Y y) const noexcept
	{
		Mat3x2 mat = *this;
		mat._31 += static_cast<value_type>(x);
		mat._32 += static_cast<value_type>(y);
		return mat;
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Mat3x2 Mat3x2::scaled(const Arithmetic s, const Float2 center) const noexcept
	{
		const float b_11 = static_cast<value_type>(s);
		const float b_22 = static_cast<value_type>(s);
		const float b_31 = (1.0f - static_cast<value_type>(s)) * center.x;
		const float b_32 = (1.0f - static_cast<value_type>(s)) * center.y;

		return{ (_11 * b_11), (_12 * b_22),
				(_21 * b_11), (_22 * b_22),
				(_31 * b_11 + b_31), (_32 * b_22 + b_32) };
	}

	inline constexpr Mat3x2 Mat3x2::scaled(const Float2 scale, const Float2 center) const noexcept
	{
		const float b_11 = static_cast<value_type>(scale.x);
		const float b_22 = static_cast<value_type>(scale.y);
		const float b_31 = (1.0f - static_cast<value_type>(scale.x)) * center.x;
		const float b_32 = (1.0f - static_cast<value_type>(scale.y)) * center.y;

		return{ (_11 * b_11), (_12 * b_22),
				(_21 * b_11), (_22 * b_22),
				(_31 * b_11 + b_31), (_32 * b_22 + b_32) };
	}

	template <class X, class Y, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>>>*>
	inline constexpr Mat3x2 Mat3x2::scaled(const X sx, const Y sy, const Float2 center) const noexcept
	{
		const float b_11 = static_cast<value_type>(sx);
		const float b_22 = static_cast<value_type>(sy);
		const float b_31 = (1.0f - static_cast<value_type>(sx)) * center.x;
		const float b_32 = (1.0f - static_cast<value_type>(sy)) * center.y;

		return{ (_11 * b_11), (_12 * b_22),
				(_21 * b_11), (_22 * b_22),
				(_31 * b_11 + b_31), (_32 * b_22 + b_32) };
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat3x2 Mat3x2::rotated(const Arithmetic angle, const Float2 center) const noexcept
	{
		Mat3x2 result;
		result.setProduct(*this, Rotate(angle, center));
		return result;
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Mat3x2 Mat3x2::shearedX(const Arithmetic sx) const noexcept
	{
		const float b_21 = -static_cast<value_type>(sx);

		return{ (_11 + _12 * b_21), _12,
				(_21 + _22 * b_21), _22,
				(_31 + _32 * b_21), _32 };
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Mat3x2 Mat3x2::shearedY(const Arithmetic sy) const noexcept
	{
		const float b_12 = static_cast<value_type>(sy);

		return{ _11, (_11 * b_12 + _12),
				_21, (_21 * b_12 + _22),
				_31, (_31 * b_12 + _32) };
	}

	inline constexpr float Mat3x2::determinant() const noexcept
	{
		return (_11 * _22) - (_12 * _21);
	}

	inline Mat3x2 Mat3x2::inverse() const noexcept
	{
		const float det = determinant();
		assert(det != 0.0f);
		
		const float detInv = (1.0f / det);

		Mat3x2 result;
		result._11 = (_22 * detInv);
		result._12 = -(_12 * detInv);
		result._21 = -(_21 * detInv);
		result._22 = (_11 * detInv);
		result._31 = (_21 * _32 - _22 * _31) * detInv;
		result._32 = (_12 * _31 - _11 * _32) * detInv;
		return result;
	}

	inline constexpr void Mat3x2::setProduct(const Mat3x2& a, const Mat3x2& b) noexcept
	{
		_11 = (a._11 * b._11) + (a._12 * b._21);
		_12 = (a._11 * b._12) + (a._12 * b._22);
		_21 = (a._21 * b._11) + (a._22 * b._21);
		_22 = (a._21 * b._12) + (a._22 * b._22);
		_31 = (a._31 * b._11) + (a._32 * b._21) + b._31;
		_32 = (a._31 * b._12) + (a._32 * b._22) + b._32;
	}

	inline constexpr Mat3x2 Mat3x2::operator *(const Mat3x2& other) const noexcept
	{
		return{ (_11 * other._11 + _12 * other._21), (_11 * other._12 + _12 * other._22),
				(_21 * other._11 + _22 * other._21), (_21 * other._12 + _22 * other._22),
				(_31 * other._11 + _32 * other._21 + other._31), (_31 * other._12 + _32 * other._22 + other._32) };
	}

	inline constexpr Float2 Mat3x2::transformPoint(const Point pos) const noexcept
	{
		return
		{
			(pos.x * _11 + pos.y * _21 + _31),
			(pos.x * _12 + pos.y * _22 + _32)
		};
	}

	inline constexpr Float2 Mat3x2::transformPoint(const Float2 pos) const noexcept
	{
		return
		{
			(pos.x * _11 + pos.y * _21 + _31),
			(pos.x * _12 + pos.y * _22 + _32)
		};
	}

	inline constexpr Vec2 Mat3x2::transformPoint(const Vec2 pos) const noexcept
	{
		return
		{
			(pos.x * _11 + pos.y * _21 + _31),
			(pos.x * _12 + pos.y * _22 + _32)
		};
	}

	inline size_t Mat3x2::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	inline constexpr Mat3x2 Mat3x2::Identity() noexcept
	{
		return{ 1.0f, 0.0f,
				0.0f, 1.0f,
				0.0f, 0.0f };
	}

	inline constexpr Mat3x2 Mat3x2::Translate(const Float2 v) noexcept
	{
		return{ 1.0f, 0.0f,
				0.0f, 1.0f,
				v.x, v.y };
	}

	template <class X, class Y>
	inline constexpr Mat3x2 Mat3x2::Translate(const X x, const Y y) noexcept
	{
		return{ 1.0f, 0.0f,
				0.0f, 1.0f,
				static_cast<value_type>(x), static_cast<value_type>(y) };
	}

	inline constexpr Mat3x2 Mat3x2::Scale(const Float2 scale, const Float2 center) noexcept
	{
		return{ scale.x, 0.0f,
				0.0f, scale.y,
				(center.x - scale.x * center.x), (center.y - scale.y * center.y) };
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Mat3x2 Mat3x2::Scale(const Arithmetic s, const Float2 center) noexcept
	{
		return{ static_cast<value_type>(s), 0.0f,
				0.0f, static_cast<value_type>(s),
				(1.0f - static_cast<value_type>(s)) * center.x,
				(1.0f - static_cast<value_type>(s)) * center.y };
	}

	template <class X, class Y, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>>>*>
	inline constexpr Mat3x2 Mat3x2::Scale(const X sx, const Y sy, const Float2 center) noexcept
	{
		return{ static_cast<value_type>(sx), 0.0f,
				0.0f, static_cast<value_type>(sy),
				(1.0f - static_cast<value_type>(sx)) * center.x,
				(1.0f - static_cast<value_type>(sy)) * center.y };
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat3x2 Mat3x2::Rotate(const Arithmetic angle, const Float2 center) noexcept
	{
		const float s = std::sin(static_cast<value_type>(angle));
		const float c = std::cos(static_cast<value_type>(angle));
		return{ c, s,
				-s, c,
				(center.x - center.x * c + center.y * s), (center.y - center.x * s - center.y * c) };
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Mat3x2 Mat3x2::ShearX(const Arithmetic sx) noexcept
	{
		return{ 1.0f, 0.0f,
				-static_cast<value_type>(sx), 1.0f,
				0.0f, 0.0f };
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Mat3x2 Mat3x2::ShearY(const Arithmetic sy) noexcept
	{
		return{ 1.0f, static_cast<value_type>(sy),
				0.0f, 1.0f,
				0.0f, 0.0f };
	}

	template <class X, class Y>
	inline constexpr Mat3x2 Mat3x2::Screen(const X width, const Y height) noexcept
	{
		return{ (2.0f / static_cast<value_type>(width)), 0.0f,
				0.0f, (-2.0f / static_cast<value_type>(height)),
				-1.0f, 1.0f };
	}
}
