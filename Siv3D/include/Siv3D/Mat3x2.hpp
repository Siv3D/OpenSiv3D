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
# include "PointVector.hpp"
# include "ByteArrayViewAdapter.hpp"

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

		[[nodiscard]] static constexpr Mat3x2 Identity() noexcept
		{
			return Mat3x2(1.0f, 0.0f,
						  0.0f, 1.0f,
						  0.0f, 0.0f);
		}

		[[nodiscard]] static constexpr Mat3x2 Translate(const Float2& v) noexcept
		{
			return Mat3x2(1.0f, 0.0f,
						  0.0f, 1.0f,
						  v.x, v.y);
		}

		[[nodiscard]] static constexpr Mat3x2 Translate(double x, double y) noexcept
		{
			return Translate({ x, y });
		}

		[[nodiscard]] static constexpr Mat3x2 Scale(const Float2& scale, const Float2& center = Float2(0, 0)) noexcept
		{
			return Mat3x2(scale.x, 0.0f,
						  0.0f, scale.y,
						  center.x - scale.x * center.x, center.y - scale.y * center.y);
		}

		[[nodiscard]] static constexpr Mat3x2 Scale(double s, const Float2& center = Float2(0, 0)) noexcept
		{
			return Scale({ s, s }, center);
		}

		[[nodiscard]] static constexpr Mat3x2 Scale(double sx, double sy, const Float2& center = Float2(0, 0)) noexcept
		{
			return Scale({ sx, sy }, center);
		}

		[[nodiscard]] static Mat3x2 Rotate(double angle, const Float2& center = Float2(0, 0)) noexcept;

		[[nodiscard]] static constexpr Mat3x2 ShearX(double sx) noexcept
		{
			return Mat3x2(1.0f, 0.0f,
				-static_cast<float>(sx), 1.0f,
				0.0f, 0.0f);
		}

		[[nodiscard]] static constexpr Mat3x2 ShearY(double sy) noexcept
		{
			return Mat3x2(1.0f, static_cast<float>(sy),
				0.0f, 1.0f,
				0.0f, 0.0f);
		}

		[[nodiscard]] static constexpr Mat3x2 Screen(double width, double height) noexcept
		{
			return Screen({ width, height });
		}
		
		[[nodiscard]] static constexpr Mat3x2 Screen(const Float2& size) noexcept
		{
			return Mat3x2(2.0f / size.x, 0.0f,
						  0.0f, -2.0f / size.y,
						  -1.0f, 1.0f);
		}

		[[nodiscard]] constexpr bool operator ==(const Mat3x2& m) const noexcept
		{
			return (_11 == m._11) && (_12 == m._12)
				&& (_21 == m._21) && (_22 == m._22)
				&& (_31 == m._31) && (_32 == m._32);
		}

		[[nodiscard]] constexpr bool operator !=(const Mat3x2& m) const noexcept
		{
			return (_11 != m._11) || (_12 != m._12)
				|| (_21 != m._21) || (_22 != m._22)
				|| (_31 != m._31) || (_32 != m._32);
		}

		[[nodiscard]] Mat3x2 translated(const Float2& v) const noexcept;

		[[nodiscard]] Mat3x2 translated(double x, double y) const noexcept;

		[[nodiscard]] Mat3x2 scaled(double s, const Float2& center = Float2(0, 0)) const noexcept;

		[[nodiscard]] Mat3x2 scaled(const Float2& scale, const Float2& center = Float2(0, 0)) const noexcept;

		[[nodiscard]] Mat3x2 scaled(double sx, double sy, const Float2& center = Float2(0, 0)) const noexcept;

		[[nodiscard]] Mat3x2 rotated(double angle, const Float2& center = Float2(0, 0)) const noexcept;

		[[nodiscard]] Mat3x2 shearedX(double sx) const noexcept;

		[[nodiscard]] Mat3x2 shearedY(double sy) const noexcept;

		[[nodiscard]] constexpr float determinant() const noexcept
		{
			return (_11 * _22) - (_12 * _21);
		}

		[[nodiscard]] Mat3x2 inversed() const noexcept;

		constexpr void setProduct(const Mat3x2 &a, const Mat3x2 &b) noexcept
		{
			_11 = a._11 * b._11 + a._12 * b._21;
			_12 = a._11 * b._12 + a._12 * b._22;
			_21 = a._21 * b._11 + a._22 * b._21;
			_22 = a._21 * b._12 + a._22 * b._22;
			_31 = a._31 * b._11 + a._32 * b._21 + b._31;
			_32 = a._31 * b._12 + a._32 * b._22 + b._32;
		}

		[[nodiscard]] Mat3x2 operator *(const Mat3x2 &matrix) const noexcept
		{
			Mat3x2 result;
			result.setProduct(*this, matrix);
			return result;
		}

		[[nodiscard]] constexpr Float2 transform(const Point& pos) const noexcept
		{
			return
			{
				pos.x * _11 + pos.y * _21 + _31,
				pos.x * _12 + pos.y * _22 + _32
			};
		}

		[[nodiscard]] constexpr Float2 transform(const Float2& pos) const noexcept
		{
			return
			{
				pos.x * _11 + pos.y * _21 + _31,
				pos.x * _12 + pos.y * _22 + _32
			};
		}

		[[nodiscard]] constexpr Vec2 transform(const Vec2& pos) const noexcept
		{
			return
			{
				pos.x * _11 + pos.y * _21 + _31,
				pos.x * _12 + pos.y * _22 + _32
			};
		}
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Mat3x2& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Mat3x2& value)
	{
		return output << CharType('(')
			<< Float2(value._11, value._12) << CharType(',')
			<< Float2(value._21, value._22) << CharType(',')
			<< Float2(value._31, value._32) << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Mat3x2& value)
	{
		CharType unused;
		Float2 r1, r2, r3;

		input >> unused
			>> r1 >> unused
			>> r2 >> unused
			>> r3 >> unused;

		value._11 = r1.x;
		value._12 = r1.y;
		value._21 = r2.x;
		value._22 = r2.y;
		value._31 = r3.x;
		value._32 = r3.y;

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
	struct hash<s3d::Mat3x2>
	{
		[[nodiscard]] size_t operator ()(const s3d::Mat3x2& value) const noexcept
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

}
