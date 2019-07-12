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

		[[nodiscard]] Vec3 operator +(const Vec3& v) const;

		[[nodiscard]] Vec3 operator -(const Vec3& v) const;

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

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Cylindrical& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Cylindrical& value)
	{
		return output		<< CharType('(')
			<< value.r		<< CharType(',') << CharType(' ')
			<< value.phi	<< CharType(',') << CharType(' ')
			<< value.y		<< CharType(')');
	}

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

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::Cylindrical>
	{
		[[nodiscard]] size_t operator ()(const s3d::Cylindrical& value) const noexcept
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
	struct formatter<s3d::Cylindrical, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Cylindrical& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.r, value.phi, value.y);
		}
	};
}
