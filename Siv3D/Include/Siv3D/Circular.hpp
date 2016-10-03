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

		static constexpr double Offset(double theta) noexcept
		{
			return Clamp(theta - Oclock * (Math::TwoPi / 12));
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
			: r(_r)
			, theta(_theta) {}

		constexpr CircularBase(Arg::theta_<double> _theta, Arg::r_<double> _r) noexcept
			: r(_r)
			, theta(_theta) {}

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

		Vec2 operator + (const Vec2& v) const noexcept
		{
			return toVec2() + v;
		}

		Vec2 operator - (const Vec2& v) const noexcept
		{
			return toVec2() - v;
		}

		Vec2 toVec2() const noexcept
		{
			return{ std::sin(theta + offset()) * r, -std::cos(theta + offset()) * r };
		}

		operator Vec2() const noexcept
		{
			return toVec2();
		}
	};
}
