//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "FastMath.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	/// @brief 円座標
	template <class Float, int32 Oclock = 0>
	struct CircularBase
	{
		using value_type = Float;
		
		using position_type = Vector2D<value_type>;

		/// @brief 半径
		value_type r;

		/// @brief 角度（ラジアン）
		value_type theta;

		SIV3D_NODISCARD_CXX20
		CircularBase() = default;

		SIV3D_NODISCARD_CXX20
		constexpr CircularBase(value_type _r, value_type _theta) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CircularBase(Arg::r_<value_type> _r, Arg::theta_<value_type> _theta) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CircularBase(Arg::theta_<value_type> _theta, Arg::r_<value_type> _r) noexcept;

		SIV3D_NODISCARD_CXX20
		CircularBase(position_type v) noexcept;

		[[nodiscard]]
		constexpr CircularBase operator +() const noexcept;

		[[nodiscard]]
		constexpr CircularBase operator -() const noexcept;

		[[nodiscard]]
		position_type operator +(position_type v) const noexcept;

		[[nodiscard]]
		position_type operator -(position_type v) const noexcept;

		[[nodiscard]]
		constexpr CircularBase rotated(value_type angle) const noexcept;

		constexpr CircularBase& rotate(value_type angle) noexcept;

		[[nodiscard]]
		Float2 toFloat2() const noexcept;

		[[nodiscard]]
		Vec2 toVec2() const noexcept;

		[[nodiscard]]
		Float2 fastToFloat2() const noexcept;

		[[nodiscard]]
		Vec2 fastToVec2() const noexcept;

		[[nodiscard]]
		position_type toPosition() const noexcept;

		[[nodiscard]]
		operator position_type() const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const CircularBase& value)
		{
			return output << CharType('(')
				<< value.r << CharType(',') << CharType(' ')
				<< value.theta << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, CircularBase& value)
		{
			CharType unused;
			return input >> unused
				>> value.r >> unused
				>> value.theta >> unused;
		}

		friend void Formatter(FormatData& formatData, const CircularBase& value)
		{
			Formatter(formatData, position_type{ value.r, value.theta });
		}

	private:

		[[nodiscard]]
		static constexpr value_type ClampAngle(value_type theta) noexcept;

		[[nodiscard]]
		static constexpr value_type Clock() noexcept;

		[[nodiscard]]
		static constexpr value_type Offset(value_type theta) noexcept;
	};

	using Circular	= CircularBase<double, 0>;
	using Circular0	= CircularBase<double, 0>;
	using Circular3	= CircularBase<double, 3>;
	using Circular6	= CircularBase<double, 6>;
	using Circular9	= CircularBase<double, 9>;

	using CircularF		= CircularBase<float, 0>;
	using Circular0F	= CircularBase<float, 0>;
	using Circular3F	= CircularBase<float, 3>;
	using Circular6F	= CircularBase<float, 6>;
	using Circular9F	= CircularBase<float, 9>;
}

# include "detail/Circular.ipp"

template <class Float, s3d::int32 Oclock>
struct SIV3D_HIDDEN fmt::formatter<s3d::CircularBase<Float, Oclock>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::CircularBase<Float, Oclock>& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {})", value.r, value.theta);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.r, value.theta);
		}
	}
};

template <class Float, s3d::int32 Oclock>
struct std::hash<s3d::CircularBase<Float, Oclock>>
{
	[[nodiscard]]
	size_t operator ()(const s3d::CircularBase<Float, Oclock>& value) const noexcept
	{
		return value.hash();
	}
};
