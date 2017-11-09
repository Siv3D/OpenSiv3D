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
	struct OffsetCircularBase
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

		Vec2 center;

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
		OffsetCircularBase() = default;

		constexpr OffsetCircularBase(const Vec2& _center, double _r = 0.0, double _theta = 0.0) noexcept
			: center(_center)
			, r(_r)
			, theta(_theta) {}

		constexpr OffsetCircularBase(const Vec2& _center, Arg::r_<double> _r, Arg::theta_<double> _theta) noexcept
			: center(_center)
			, r(*_r)
			, theta(*_theta) {}

		constexpr OffsetCircularBase(const Vec2& _center, Arg::theta_<double> _theta, Arg::r_<double> _r) noexcept
			: center(_center)
			, r(*_r)
			, theta(*_theta) {}

		OffsetCircularBase(const Vec2& _center, const Vec2& target) noexcept
			: center(_center)
		{
			setTarget(target);
		}

		[[nodiscard]] constexpr OffsetCircularBase operator +(const Vec2& v) const noexcept
		{
			return movedBy(v);
		}

		[[nodiscard]] constexpr OffsetCircularBase operator -(const Vec2& v) const noexcept
		{
			return movedBy(-v);
		}

		constexpr OffsetCircularBase& operator +=(const Vec2& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		constexpr OffsetCircularBase& operator -=(const Vec2& v) noexcept
		{
			return moveBy(-v.x, -v.y);
		}

		constexpr OffsetCircularBase& moveBy(double x, double y) noexcept
		{
			center.moveBy(x, y);

			return *this;
		}

		constexpr OffsetCircularBase& moveBy(const Vec2& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		[[nodiscard]] constexpr OffsetCircularBase movedBy(double x, double y) const noexcept
		{
			return OffsetCircularBase(*this).moveBy(v);
		}

		[[nodiscard]] constexpr OffsetCircularBase movedBy(const Vec2& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		constexpr OffsetCircularBase& setCenter(const Vec2& _center) noexcept
		{
			center = _center;

			return *this;
		}

		OffsetCircularBase& setTarget(const Vec2& target) noexcept
		{
			const Vec2 v = target - center;

			r = v.length();

			theta = Offset(std::atan2(v.x, -v.y));

			return *this;
		}

		constexpr OffsetCircularBase& rotate(double angle) noexcept
		{
			polar.theta += angle;

			return *this;
		}

		[[nodiscard]] constexpr OffsetCircularBase rotated(double angle) const noexcept
		{
			return Polar(*this).rotate(angle);
		}

		[[nodiscard]] Vec2 toVec2() const noexcept
		{
			return center.movedBy(std::sin(theta + Clock()) * r, -std::cos(theta + Clock()) * r);
		}

		[[nodiscard]] Float2 toFloat2() const noexcept
		{
			return{ center.x + std::sin(theta + Clock()) * r, center.y - std::cos(theta + Clock()) * r };
		}

		[[nodiscard]] operator Vec2() const noexcept
		{
			return toVec2();
		}
	};

	using OffsetCircular  = OffsetCircularBase<0>;
	using OffsetCircular0 = OffsetCircularBase<0>;
	using OffsetCircular3 = OffsetCircularBase<3>;
	using OffsetCircular6 = OffsetCircularBase<6>;
	using OffsetCircular9 = OffsetCircularBase<9>;
}

namespace s3d
{
	template <int32 Oclock>
	inline void Formatter(FormatData& formatData, const OffsetCircularBase<Oclock>& value)
	{
		Formatter(formatData, Vec4(value.center, value.r, value.theta));
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
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const OffsetCircularBase<Oclock>& value)
	{
		return output << CharType('(')
			<< value.center.x << CharType(',')
			<< value.center.y << CharType(',')
			<< value.r << CharType(',')
			<< value.theta << CharType(')');
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
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, OffsetCircularBase<Oclock>& value)
	{
		CharType unused;
		return input >> unused
			>> value.center.x >> unused
			>> value.center.y >> unused
			>> value.r >> unused
			>> value.theta >> unused;
	}
}

namespace fmt
{
	//template <class ArgFormatter, s3d::int32 Oclock>
	//void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::OffsetCircularBase<Oclock>& c)
	//{
	//	const auto tag = s3d::detail::GetTag(format_str);

	//	const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("})");

	//	f.writer().write(fmt, c.r, c.theta);
	//}
}
