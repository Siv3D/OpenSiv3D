//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <iostream>
# include "Fwd.hpp"
# include "NamedParameter.hpp"
# include "PointVector.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	/// <summary>
	/// 円座標
	/// </summary>
	template <int32 Oclock>
	struct CircularBase
	{
	private:

		static constexpr double Clamp(double theta) noexcept
		{
			return theta <= -Math::Pi ? theta + Math::TwoPi : theta;
		}
        
		static constexpr double Clock() noexcept
		{
			return Oclock * (Math::TwoPi / 12);
		}

		static constexpr double Offset(double theta) noexcept
		{
			return Clamp(theta - Clock());
		}

	public:

		/// <summary>
		/// 半径
		/// </summary>
		double r;

		/// <summary>
		/// 角度（ラジアン）
		/// </summary>
		double theta;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		CircularBase() = default;

		constexpr CircularBase(double _r, double _theta) noexcept
			: r(_r)
			, theta(_theta) {}

		constexpr CircularBase(Arg::r_<double> _r, Arg::theta_<double> _theta) noexcept
			: r(*_r)
			, theta(*_theta) {}

		constexpr CircularBase(Arg::theta_<double> _theta, Arg::r_<double> _r) noexcept
			: r(*_r)
			, theta(*_theta) {}

		CircularBase(const Vec2& v) noexcept
			: r(v.length()), theta(Offset(std::atan2(v.x, -v.y))) {}

		constexpr CircularBase operator +() const noexcept
		{
			return *this;
		}

		constexpr CircularBase operator -() const noexcept
		{
			return{ r, Clamp(theta - Math::Pi) };
		}

		Vec2 operator +(const Vec2& v) const noexcept
		{
			return toVec2() + v;
		}

		Vec2 operator -(const Vec2& v) const noexcept
		{
			return toVec2() - v;
		}

		Vec2 toVec2() const noexcept
		{
			return{ std::sin(theta + Clock()) * r, -std::cos(theta + Clock()) * r };
		}

		operator Vec2() const noexcept
		{
			return toVec2();
		}
	};

	/// <summary>
	/// 出力ストリームに点を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="v">
	/// 点
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType, int32 Oclock>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const CircularBase<Oclock>& c)
	{
		return os	<< CharType('(')
					<< c.r << CharType(',')
					<< c.theta << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに点を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="v">
	/// 点
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType, int32 Oclock>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, CircularBase<Oclock>& v)
	{
		CharType unused;
		return is	>> unused
					>> v.r >> unused
					>> v.theta >> unused;
	}

	template <int32 Oclock>
	inline void Formatter(FormatData& formatData, const CircularBase<Oclock>& value)
	{
		Formatter(formatData, Vec2(value.r, value.theta));
	}
}
