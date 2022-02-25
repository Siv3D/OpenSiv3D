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
	inline constexpr Mat3x3::Mat3x3(
		const float m11, const float m12, const float m13,
		const float m21, const float m22, const float m23,
		const float m31, const float m32, const float m33) noexcept
		: _11{ m11 }, _12{ m12 }, _13{ m13 }
		, _21{ m21 }, _22{ m22 }, _23{ m23 }
		, _31{ m31 }, _32{ m32 }, _33{ m33 } {}

	inline constexpr float Mat3x3::determinant() const noexcept
	{
		return (
			+ (_11 * _22 * _33)
			+ (_12 * _23 * _31)
			+ (_13 * _21 * _32)
			- (_13 * _22 * _31)
			- (_12 * _21 * _33)
			- (_11 * _23 * _32));
	}

	inline Mat3x3 Mat3x3::inverse() const noexcept
	{
		const float invdet = (1.0f / determinant());

		Mat3x3 result;
		result._11 = ( _22 * _33 - _23 * _32) * invdet;
		result._12 = (-_12 * _33 + _13 * _32) * invdet;
		result._13 = ( _12 * _23 - _13 * _22) * invdet;
		result._21 = (-_21 * _33 + _23 * _31) * invdet;
		result._22 = ( _11 * _33 - _13 * _31) * invdet;
		result._23 = (-_11 * _23 + _13 * _21) * invdet;
		result._31 = ( _21 * _32 - _22 * _31) * invdet;
		result._32 = (-_11 * _32 + _12 * _31) * invdet;
		result._33 = ( _11 * _22 - _12 * _21) * invdet;
		return result;
	}

	inline constexpr Float2 Mat3x3::transformPoint(const Point pos) const noexcept
	{
		const float s = (_13 * pos.x + _23 * pos.y + _33);
		const float x = (_11 * pos.x + _21 * pos.y + _31) / s;
		const float y = (_12 * pos.x + _22 * pos.y + _32) / s;
		return{ x, y };
	}

	inline constexpr Float2 Mat3x3::transformPoint(const Float2 pos) const noexcept
	{
		const float s = (_13 * pos.x + _23 * pos.y + _33);
		const float x = (_11 * pos.x + _21 * pos.y + _31) / s;
		const float y = (_12 * pos.x + _22 * pos.y + _32) / s;
		return{ x, y };
	}

	inline constexpr Vec2 Mat3x3::transformPoint(const Vec2 pos) const noexcept
	{
		const double s = (_13 * pos.x + _23 * pos.y + _33);
		const double x = (_11 * pos.x + _21 * pos.y + _31) / s;
		const double y = (_12 * pos.x + _22 * pos.y + _32) / s;
		return{ x, y };
	}

	inline constexpr Quad Mat3x3::transformRect(const RectF& rect) const noexcept
	{
		const float x0 = static_cast<float>(rect.x);
		const float x1 = static_cast<float>(rect.x + rect.w);
		const float y0 = static_cast<float>(rect.y);
		const float y1 = static_cast<float>(rect.y + rect.h);

		return{ transformPoint(Float2{x0, y0}), transformPoint(Float2{x1, y0}),
				transformPoint(Float2{x1, y1}), transformPoint(Float2{x0, y1}) };
	}

	inline size_t Mat3x3::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	inline constexpr Mat3x3 Mat3x3::Identity() noexcept
	{
		return{ 1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f };
	}
}
