//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 3x2 行列
	/// </summary>
	struct Mat3x2
	{
		float _11, _12;
		float _21, _22;
		float _31, _32;

		Mat3x2() = default;

		constexpr Mat3x2(float _11, float _12, float _21, float _22, float _31, float _32) noexcept
			: _11{ _11 }
			, _12{ _12 }
			, _21{ _21 }
			, _22{ _22 }
			, _31{ _31 }
			, _32{ _32 } {}

		static constexpr Mat3x2 Identity()
		{
			return Mat3x2(1.0f, 0.0f,
						  0.0f, 1.0f,
						  0.0f, 0.0f);
		}

		static constexpr Mat3x2 Translate(const Float2& v)
		{
			return Mat3x2(1.0f, 0.0f,
						  0.0f, 1.0f,
						  v.x, v.y);
		}

		static constexpr Mat3x2 Translate(double x, double y)
		{
			return Translate({ x, y });
		}

		static constexpr Mat3x2 Scale(const Float2& scale, const Float2& center = { 0,0 })
		{
			return Mat3x2(scale.x, 0.0f,
						  0.0f, scale.y,
						  center.x - scale.x * center.x, center.y - scale.x * center.y);
		}

		static constexpr Mat3x2 Scale(double s, const Float2& center = { 0,0 })
		{
			return Scale({ s, s }, center);
		}

		static constexpr Mat3x2 Scale(double sx, double sy, const Float2& center = { 0,0 })
		{
			return Scale({ sx, sy }, center);
		}

		static Mat3x2 Rotate(double angle, const Float2& center = { 0,0 })
		{
			Mat3x2 m;
			const float s = std::sinf(static_cast<float>(angle));
			const float c = std::cosf(static_cast<float>(angle));
			m._11 = c;
			m._12 = s;
			m._21 = -s;
			m._22 = c;
			m._31 = center.x - center.x * c + center.y * s;
			m._32 = center.y - center.x * s - center.y * c;
			return m;
		}

		static constexpr Mat3x2 Screen(double width, double height)
		{
			return Screen({ width, height });
		}
		
		static constexpr Mat3x2 Screen(const Float2& size)
		{
			return Mat3x2(2.0f / size.x, 0.0f,
						  0.0f, -2.0f / size.y,
						  -1.0f, 1.0f);
		}

		Mat3x2 translate(const Float2& v) const
		{
			Mat3x2 result;
			result.setProduct(*this, Translate(v));
			return result;
		}

		Mat3x2 translate(double x, double y) const
		{
			return translate({ x, y });
		}

		Mat3x2 scale(double s, const Float2& center = { 0,0 }) const
		{
			return scale({ s, s }, center);
		}

		Mat3x2 scale(const Float2& scale, const Float2& center = { 0,0 }) const
		{
			Mat3x2 result;
			result.setProduct(*this, Scale(scale, center));
			return result;
		}

		Mat3x2 scale(double sx, double sy, const Float2& center = { 0,0 }) const
		{
			return scale({ sx, sy }, center);
		}

		Mat3x2 rotate(double angle, const Float2& center = { 0,0 }) const
		{
			Mat3x2 result;
			result.setProduct(*this, Rotate(angle, center));
			return result;
		}

		constexpr float determinant() const
		{
			return (_11 * _22) - (_12 * _21);
		}

		Mat3x2 inverse() const
		{
			const float det = determinant();
			assert(det != 0.0f);
			const float detInv = 1.0f / det;

			Mat3x2 out;
			out._11 = (_22) * detInv;
			out._12 = (-_12) * detInv;
			out._21 = (-_21) * detInv;
			out._22 = (_11) * detInv;
			out._31 = (_21*_32 - _22*_31) * detInv;
			out._32 = (_12*_31 - _11*_32) * detInv;
			return out;
		}

		constexpr void setProduct(const Mat3x2 &a, const Mat3x2 &b)
		{
			_11 = a._11 * b._11 + a._12 * b._21;
			_12 = a._11 * b._12 + a._12 * b._22;
			_21 = a._21 * b._11 + a._22 * b._21;
			_22 = a._21 * b._12 + a._22 * b._22;
			_31 = a._31 * b._11 + a._32 * b._21 + b._31;
			_32 = a._31 * b._12 + a._32 * b._22 + b._32;
		}

		Mat3x2 operator*(const Mat3x2 &matrix) const
		{
			Mat3x2 result;
			result.setProduct(*this, matrix);
			return result;
		}

		constexpr Float2 transform(const Point& pos) const
		{
			return
			{
				pos.x * _11 + pos.y * _21 + _31,
				pos.x * _12 + pos.y * _22 + _32
			};
		}

		constexpr Float2 transform(const Float2& pos) const
		{
			return
			{
				pos.x * _11 + pos.y * _21 + _31,
				pos.x * _12 + pos.y * _22 + _32
			};
		}

		constexpr Vec2 transform(const Vec2& pos) const
		{
			return
			{
				pos.x * _11 + pos.y * _21 + _31,
				pos.x * _12 + pos.y * _22 + _32
			};
		}
	};
}
