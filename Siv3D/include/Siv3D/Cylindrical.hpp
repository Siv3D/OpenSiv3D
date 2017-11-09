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
		
		[[nodiscard]] constexpr Cylindrical operator +() const noexcept
		{
			return *this;
		}

		[[nodiscard]] constexpr Cylindrical operator -() const noexcept
		{
			return{ r, phi + Math::Pi, -y };
		}

		[[nodiscard]] Vec3 operator +(const Vec3& v) const
		{
			return toVec3() + v;
		}

		[[nodiscard]] Vec3 operator -(const Vec3& v) const
		{
			return toVec3() - v;
		}

		[[nodiscard]] Vec3 toFloat3() const
		{
			return{ r * std::cos(phi), y, r * std::sin(phi) };
		}

		[[nodiscard]] Vec3 toVec3() const
		{
			return{ r * std::cos(phi), y, r * std::sin(phi) };
		}

		[[nodiscard]] operator Vec3() const
		{
			return toVec3();
		}
	};
}

namespace s3d
{
	inline void Formatter(FormatData& formatData, const Cylindrical& value)
	{
		Formatter(formatData, Vec3(value.r, value.phi, value.y));
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
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Cylindrical& value)
	{
		return output		<< CharType('(')
			<< value.r		<< CharType(',')
			<< value.phi	<< CharType(',')
			<< value.y		<< CharType(')');
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
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Cylindrical& value)
	{
		CharType unused;
		return input		>> unused
			>> value.r		>> unused
			>> value.phi	>> unused
			>> value.y		>> unused;
	}
}

namespace fmt
{
	//template <class ArgFormatter>
	//void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::Cylindrical& value)
	//{
	//	const auto tag = s3d::detail::GetTag(format_str);

	//	const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("})");

	//	f.writer().write(fmt, c.r, c.phi, c.y);
	//}
}
