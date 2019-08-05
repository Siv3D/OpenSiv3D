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

		[[nodiscard]] constexpr Spherical operator +() const noexcept
		{
			return *this;
		}

		[[nodiscard]] constexpr Spherical operator -() const noexcept
		{
			return{ r, theta + Math::Pi, phi + Math::Pi };
		}

		[[nodiscard]] Vec3 operator +(const Vec3& v) const;

		[[nodiscard]] Vec3 operator -(const Vec3& v) const;

		[[nodiscard]] Float3 toFloat3() const
		{
			const double s = std::sin(theta);
			return{ r * s * std::cos(phi), r * std::cos(theta), r * s * std::sin(phi) };
		}

		[[nodiscard]] Vec3 toVec3() const
		{
			const double s = std::sin(theta);
			return{ r * s * std::cos(phi), r * std::cos(theta), r * s * std::sin(phi) };
		}

		[[nodiscard]] operator Vec3() const
		{
			return toVec3();
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
	void Formatter(FormatData& formatData, const Spherical& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Spherical& value)
	{
		return output		<< CharType('(')
			<< value.r		<< CharType(',') << CharType(' ')
			<< value.theta	<< CharType(',') << CharType(' ')
			<< value.phi	<< CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Spherical& value)
	{
		CharType unused;
		return input		>> unused
			>> value.r		>> unused
			>> value.theta	>> unused
			>> value.phi	>> unused;
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
	struct hash<s3d::Spherical>
	{
		[[nodiscard]] size_t operator ()(const s3d::Spherical& value) const noexcept
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
	template <>
	struct formatter<s3d::Spherical, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Spherical& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.r, value.theta, value.phi);
		}
	};
}
