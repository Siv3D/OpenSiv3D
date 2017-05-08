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
# include "Fwd.hpp"
# include "Vector3D.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	/// <summary>
	/// 球面座標
	/// </summary>
	struct Spherical
	{
		double r, theta, phi;

		Spherical() = default;

		constexpr Spherical(double _r, double _theta, double _phi) noexcept
			: r(_r)
			, theta(_theta)
			, phi(_phi) {}

		constexpr Spherical(Arg::r_<double> _r, Arg::theta_<double> _theta, Arg::phi_<double> _phi) noexcept
			: r(*_r)
			, theta(*_theta)
			, phi(*_phi) {}

		constexpr Spherical(Arg::r_<double> _r, Arg::phi_<double> _phi, Arg::theta_<double> _theta) noexcept
			: r(*_r)
			, theta(*_theta)
			, phi(*_phi) {}

		constexpr Spherical(Arg::theta_<double> _theta, Arg::r_<double> _r, Arg::phi_<double> _phi) noexcept
			: r(*_r)
			, theta(*_theta)
			, phi(*_phi) {}

		constexpr Spherical(Arg::theta_<double> _theta, Arg::phi_<double> _phi, Arg::r_<double> _r) noexcept
			: r(*_r)
			, theta(*_theta)
			, phi(*_phi) {}

		constexpr Spherical(Arg::phi_<double> _phi, Arg::r_<double> _r, Arg::theta_<double> _theta) noexcept
			: r(*_r)
			, theta(*_theta)
			, phi(*_phi) {}

		constexpr Spherical(Arg::phi_<double> _phi, Arg::theta_<double> _theta, Arg::r_<double> _r) noexcept
			: r(*_r)
			, theta(*_theta)
			, phi(*_phi) {}

		Spherical(const Vec3& pos)
			: r(pos.length())
			, theta(std::acos(pos.y / r))
			, phi(std::atan2(pos.z, pos.x)) {}

		constexpr Spherical operator +() const noexcept
		{
			return *this;
		}

		constexpr Spherical operator -() const noexcept
		{
			return{ r, theta + Math::Pi, phi + Math::Pi };
		}

		Vec3 operator +(const Vec3& v) const
		{
			return toVec3() + v;
		}

		Vec3 operator -(const Vec3& v) const
		{
			return toVec3() - v;
		}

		Vec3 toFloat3() const
		{
			const double s = std::sin(theta);
			return{ r * s * std::cos(phi), r * std::cos(theta), r * s * std::sin(phi) };
		}

		Vec3 toVec3() const
		{
			const double s = std::sin(theta);
			return{ r * s * std::cos(phi), r * std::cos(theta), r * s * std::sin(phi) };
		}

		operator Vec3() const
		{
			return toVec3();
		}
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Cylindrical
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
	inline void Formatter(FormatData& formatData, const Spherical& s)
	{
		Formatter(formatData, Vec3(s.r, s.theta, s.phi));
	}

	/// <summary>
	/// 出力ストリームに球面座標を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="s">
	/// 球面座標
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Spherical& s)
	{
		return os		<< CharType('(')
			<< s.r		<< CharType(',')
			<< s.theta	<< CharType(',')
			<< s.phi	<< CharType(')');
	}

	/// <summary>
	/// 入力ストリームに球面座標を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="s">
	/// 球面座標
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Spherical& s)
	{
		CharType unused;
		return is		>> unused
			>> s.r		>> unused
			>> s.theta	>> unused
			>> s.phi	>> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::Spherical& s)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, s.r, s.theta, s.phi);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
