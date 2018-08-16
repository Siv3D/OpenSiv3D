//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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

		[[nodiscard]] static constexpr double Clamp(const double theta) noexcept
		{
			return theta <= -Math::Pi ? theta + Math::TwoPi : theta;
		}
        
		[[nodiscard]] static constexpr double Clock() noexcept
		{
			return Oclock * (Math::TwoPi / 12);
		}

		[[nodiscard]] static constexpr double Offset(const double theta) noexcept
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

		[[nodiscard]] constexpr CircularBase operator +() const noexcept
		{
			return *this;
		}

		[[nodiscard]] constexpr CircularBase operator -() const noexcept
		{
			return{ r, Clamp(theta - Math::Pi) };
		}

		[[nodiscard]] Vec2 operator +(const Vec2& v) const noexcept
		{
			return toVec2() + v;
		}

		[[nodiscard]] Vec2 operator -(const Vec2& v) const noexcept
		{
			return toVec2() - v;
		}

		[[nodiscard]] Float2 toFloat2() const noexcept
		{
			return{ std::sin(theta + Clock()) * r, -std::cos(theta + Clock()) * r };
		}

		[[nodiscard]] Vec2 toVec2() const noexcept
		{
			return{ std::sin(theta + Clock()) * r, -std::cos(theta + Clock()) * r };
		}

		[[nodiscard]] operator Vec2() const noexcept
		{
			return toVec2();
		}
	};

	using Circular	= CircularBase<0>;
	using Circular0	= CircularBase<0>;
	using Circular3	= CircularBase<3>;
	using Circular6	= CircularBase<6>;
	using Circular9	= CircularBase<9>;
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	template <int32 Oclock>
	inline void Formatter(FormatData& formatData, const CircularBase<Oclock>& value)
	{
		Formatter(formatData, Vec2(value.r, value.theta));
	}

	template <class CharType, int32 Oclock>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const CircularBase<Oclock>& value)
	{
		return output << CharType('(')
			<< value.r << CharType(',') << CharType(' ')
			<< value.theta << CharType(')');
	}

	template <class CharType, int32 Oclock>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, CircularBase<Oclock>& value)
	{
		CharType unused;
		return input >> unused
			>> value.r >> unused
			>> value.theta >> unused;
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <s3d::int32 Oclock>
	struct hash<s3d::CircularBase<Oclock>>
	{
		[[nodiscard]] size_t operator ()(const s3d::CircularBase<Oclock>& value) const noexcept
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

namespace fmt
{
	template <s3d::int32 Oclock>
	struct formatter<s3d::CircularBase<Oclock>, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::CircularBase<Oclock>& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.r, value.theta);
		}
	};
}
