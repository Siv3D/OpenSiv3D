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
	/// 円柱座標
	/// </summary>
	struct Cylindrical
	{
		double r, phi, y;

		Cylindrical() = default;

		constexpr Cylindrical(double _r, double _phi, double _y) noexcept
			: r(_r)
			, phi(_phi)
			, y(_y) {}

		constexpr Cylindrical(Arg::r_<double> _r, Arg::phi_<double> _phi, Arg::y_<double> _y) noexcept
			: r(*_r)
			, phi(*_phi)
			, y(*_y) {}

		constexpr Cylindrical(Arg::r_<double> _r, Arg::y_<double> _y, Arg::phi_<double> _phi) noexcept
			: r(*_r)
			, phi(*_phi)
			, y(*_y) {}

		constexpr Cylindrical(Arg::phi_<double> _phi, Arg::r_<double> _r, Arg::y_<double> _y) noexcept
			: r(*_r)
			, phi(*_phi)
			, y(*_y) {}

		constexpr Cylindrical(Arg::phi_<double> _phi, Arg::y_<double> _y, Arg::r_<double> _r) noexcept
			: r(*_r)
			, phi(*_phi)
			, y(*_y) {}

		constexpr Cylindrical(Arg::y_<double> _y, Arg::r_<double> _r, Arg::phi_<double> _phi) noexcept
			: r(*_r)
			, phi(*_phi)
			, y(*_y) {}

		constexpr Cylindrical(Arg::y_<double> _y, Arg::phi_<double> _phi, Arg::r_<double> _r) noexcept
			: r(*_r)
			, phi(*_phi)
			, y(*_y) {}

		Cylindrical(const Vec3& pos)
			: r(pos.xz().length())
			, phi(std::atan2(pos.z, pos.x))
			, y(pos.y) {}
		
		constexpr Cylindrical operator +() const noexcept
		{
			return *this;
		}

		constexpr Cylindrical operator -() const noexcept
		{
			return{ r, phi + Math::Pi, -y };
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
			return{ r * std::cos(phi), y, r * std::sin(phi) };
		}

		Vec3 toVec3() const
		{
			return{ r * std::cos(phi), y, r * std::sin(phi) };
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
	inline void Formatter(FormatData& formatData, const Cylindrical& c)
	{
		Formatter(formatData, Vec3(c.r, c.phi, c.y));
	}

	/// <summary>
	/// 出力ストリームに円柱座標を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="c">
	/// 円柱座標
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Cylindrical& c)
	{
		return os		<< CharType('(')
			<< c.r		<< CharType(',')
			<< c.phi	<< CharType(',')
			<< c.y		<< CharType(')');
	}

	/// <summary>
	/// 入力ストリームに円柱座標を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="c">
	/// 円柱座標
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Cylindrical& c)
	{
		CharType unused;
		return is		>> unused
			>> c.r		>> unused
			>> c.phi	>> unused
			>> c.y		>> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::Cylindrical& c)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, c.r, c.phi, c.y);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
