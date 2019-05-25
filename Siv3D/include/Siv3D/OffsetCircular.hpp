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
			return OffsetCircularBase(*this).moveBy(x, y);
		}

		[[nodiscard]] constexpr OffsetCircularBase movedBy(const Vec2& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		constexpr OffsetCircularBase& setCenter(double x, double y) noexcept
		{
			return setCenter(Vec2(x, y));
		}

		constexpr OffsetCircularBase& setCenter(const Vec2& _center) noexcept
		{
			center = _center;

			return *this;
		}

		OffsetCircularBase& setTarget(double x, double y) noexcept
		{
			return setTarget(Vec2(x, y));
		}

		OffsetCircularBase& setTarget(const Vec2& target) noexcept
		{
			const Vec2 v = target - center;

			r = v.length();

			theta = Offset(std::atan2(v.x, -v.y));

			return *this;
		}

		[[nodiscard]] constexpr OffsetCircularBase rotated(double angle) const noexcept
		{
			return OffsetCircularBase(*this).rotate(angle);
		}

		constexpr OffsetCircularBase& rotate(double angle) noexcept
		{
			theta += angle;

			return *this;
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

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	template <int32 Oclock>
	inline void Formatter(FormatData& formatData, const OffsetCircularBase<Oclock>& value)
	{
		Formatter(formatData, Vec4(value.center, value.r, value.theta));
	}

	template <class CharType, int32 Oclock>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const OffsetCircularBase<Oclock>& value)
	{
		return output << CharType('(')
			<< value.center.x << CharType(',') << CharType(' ')
			<< value.center.y << CharType(',') << CharType(' ')
			<< value.r << CharType(',') << CharType(' ')
			<< value.theta << CharType(')');
	}

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

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <s3d::int32 Oclock>
	struct hash<s3d::OffsetCircularBase<Oclock>>
	{
		[[nodiscard]] size_t operator ()(const s3d::OffsetCircularBase<Oclock>& value) const noexcept
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
	template <s3d::int32 Oclock>
	struct formatter<s3d::OffsetCircularBase<Oclock>, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::OffsetCircularBase<Oclock>& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.x, value.y, value.r, value.theta);
		}
	};
}
