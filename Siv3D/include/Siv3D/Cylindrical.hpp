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
	template <class Float>
	struct CylindricalBase
	{
		using value_type = Float;

		using position_type = Vector3D<value_type>;

		value_type r;
		
		value_type phi;
		
		value_type y;

		SIV3D_NODISCARD_CXX20
		CylindricalBase() = default;

		SIV3D_NODISCARD_CXX20
		constexpr CylindricalBase(value_type _r, value_type _phi, value_type _y) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CylindricalBase(Arg::r_<value_type> _r, Arg::phi_<value_type> _phi, Arg::y_<value_type> _y) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CylindricalBase(Arg::r_<value_type> _r, Arg::y_<value_type> _y, Arg::phi_<value_type> _phi) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CylindricalBase(Arg::phi_<value_type> _phi, Arg::r_<value_type> _r, Arg::y_<value_type> _y) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CylindricalBase(Arg::phi_<value_type> _phi, Arg::y_<value_type> _y, Arg::r_<value_type> _r) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CylindricalBase(Arg::y_<value_type> _y, Arg::r_<value_type> _r, Arg::phi_<value_type> _phi) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CylindricalBase(Arg::y_<value_type> _y, Arg::phi_<value_type> _phi, Arg::r_<value_type> _r) noexcept;

		SIV3D_NODISCARD_CXX20
		CylindricalBase(position_type pos) noexcept;

		[[nodiscard]]
		constexpr CylindricalBase operator +() const noexcept;

		[[nodiscard]]
		constexpr CylindricalBase operator -() const noexcept;

		[[nodiscard]]
		position_type operator +(position_type v) const noexcept;

		[[nodiscard]]
		position_type operator -(position_type v) const noexcept;

		[[nodiscard]]
		Float3 toFloat3() const noexcept;

		[[nodiscard]]
		Vec3 toVec3() const noexcept;

		[[nodiscard]]
		Float3 fastToFloat3() const noexcept;

		[[nodiscard]]
		Vec3 fastToVec3() const noexcept;

		[[nodiscard]]
		position_type toPosition() const noexcept;

		[[nodiscard]]
		operator position_type() const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const CylindricalBase& value)
		{
			return output << CharType('(')
				<< value.r << CharType(',') << CharType(' ')
				<< value.phi << CharType(',') << CharType(' ')
				<< value.y << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, CylindricalBase& value)
		{
			CharType unused;
			return input >> unused
				>> value.r >> unused
				>> value.phi >> unused
				>> value.y >> unused;
		}

		friend void Formatter(FormatData& formatData, const CylindricalBase& value)
		{
			Formatter(formatData, position_type{ value.r, value.phi, value.y });
		}
	};

	using Cylindrical	= CylindricalBase<double>;
	using CylindricalF	= CylindricalBase<float>;
}

# include "detail/Cylindrical.ipp"

template <class Float>
struct SIV3D_HIDDEN fmt::formatter<s3d::CylindricalBase<Float>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::CylindricalBase<Float>& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {})", value.r, value.phi, value.y);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.r, value.phi, value.y);
		}
	}
};

template <class Float>
struct std::hash<s3d::CylindricalBase<Float>>
{
	[[nodiscard]]
	size_t operator ()(const s3d::CylindricalBase<Float>& value) const noexcept
	{
		return value.hash();
	}
};
