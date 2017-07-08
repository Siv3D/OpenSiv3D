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

		Float2 toFloat2() const noexcept
		{
			return{ std::sin(theta + Clock()) * r, -std::cos(theta + Clock()) * r };
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
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting CircularBase
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[x] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	template <int32 Oclock>
	inline void Formatter(FormatData& formatData, const CircularBase<Oclock>& c)
	{
		Formatter(formatData, Vec2(c.r, c.theta));
	}

	/// <summary>
	/// 出力ストリームに円座標を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="c">
	/// 円座標
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType, int32 Oclock>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const CircularBase<Oclock>& c)
	{
		return os << CharType('(')
			<< c.r << CharType(',')
			<< c.theta << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに円座標を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="c">
	/// 円座標
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType, int32 Oclock>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, CircularBase<Oclock>& c)
	{
		CharType unused;
		return is >> unused
			>> c.r >> unused
			>> c.theta >> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter, s3d::int32 Oclock>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::CircularBase<Oclock>& c)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, c.r, c.theta);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
