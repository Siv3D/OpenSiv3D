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

# include <cassert>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Format.hpp>

namespace s3d
{
	Mat3x2 Mat3x2::Rotate(const double angle, const Float2& center) noexcept
	{
		Mat3x2 m;
		const float s = std::sin(static_cast<float>(angle));
		const float c = std::cos(static_cast<float>(angle));
		m._11 = c;
		m._12 = s;
		m._21 = -s;
		m._22 = c;
		m._31 = center.x - center.x * c + center.y * s;
		m._32 = center.y - center.x * s - center.y * c;
		return m;
	}

	Mat3x2 Mat3x2::translated(const Float2& v) const noexcept
	{
		Mat3x2 result;
		result.setProduct(*this, Translate(v));
		return result;
	}

	Mat3x2 Mat3x2::translated(double x, double y) const noexcept
	{
		return translated({ x, y });
	}

	Mat3x2 Mat3x2::scaled(double s, const Float2& center) const noexcept
	{
		return scaled({ s, s }, center);
	}

	Mat3x2 Mat3x2::scaled(const Float2& scale, const Float2& center) const noexcept
	{
		Mat3x2 result;
		result.setProduct(*this, Scale(scale, center));
		return result;
	}

	Mat3x2 Mat3x2::scaled(double sx, double sy, const Float2& center) const noexcept
	{
		return scaled({ sx, sy }, center);
	}

	Mat3x2 Mat3x2::rotated(double angle, const Float2& center) const noexcept
	{
		Mat3x2 result;
		result.setProduct(*this, Rotate(angle, center));
		return result;
	}

	Mat3x2 Mat3x2::shearedX(double sx) const noexcept
	{
		Mat3x2 result;
		result.setProduct(*this, ShearX(sx));
		return result;
	}

	Mat3x2 Mat3x2::shearedY(double sy) const noexcept
	{
		Mat3x2 result;
		result.setProduct(*this, ShearY(sy));
		return result;
	}

	Mat3x2 Mat3x2::inversed() const noexcept
	{
		const float det = determinant();
		assert(det != 0.0f);
		const float detInv = 1.0f / det;

		Mat3x2 out;
		out._11 = (_22)* detInv;
		out._12 = (-_12) * detInv;
		out._21 = (-_21) * detInv;
		out._22 = (_11)* detInv;
		out._31 = (_21 * _32 - _22 * _31) * detInv;
		out._32 = (_12 * _31 - _11 * _32) * detInv;
		return out;
	}

	void Formatter(FormatData& formatData, const Mat3x2& value)
	{
		formatData.string.push_back(L'(');
		Formatter(formatData, Float2(value._11, value._12));
		formatData.string.push_back(L',');
		Formatter(formatData, Float2(value._21, value._22));
		formatData.string.push_back(L',');
		Formatter(formatData, Float2(value._31, value._32));
		formatData.string.push_back(L')');
	}
}
