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

namespace s3d
{
	inline constexpr LineStyle::Parameters LineStyle::Parameters::operator ()(const double _dotOffset) const noexcept
	{
		return Parameters{ _dotOffset, hasCap, isRound, isDotted, false };
	}

	inline constexpr LineStyle::Parameters LineStyle::Parameters::offset(const double _dotOffset) const noexcept
	{
		return Parameters{ _dotOffset, hasCap, isRound, isDotted, false };
	}

	inline constexpr LineStyle::LineStyle(const Parameters& params) noexcept
		: dotOffset{ params.dotOffset }
		, hasCap{ params.hasCap }
		, isRound{ params.isRound }
		, isDotted{ params.isDotted }
		, hasAlignedDot{ params.hasAlignedDot } {}

	inline constexpr bool LineStyle::hasSquareCap() const noexcept
	{
		return (hasCap && (not isRound) && (not isDotted));
	}

	inline constexpr bool LineStyle::hasRoundCap() const noexcept
	{
		return (hasCap && isRound && (not isDotted));
	}

	inline constexpr bool LineStyle::hasNoCap() const noexcept
	{
		return ((not hasCap) && (not isRound) && (not isDotted));
	}

	inline constexpr bool LineStyle::hasSquareDot() const noexcept
	{
		return (hasCap && (not isRound) && isDotted);
	}

	inline constexpr bool LineStyle::hasRoundDot() const noexcept
	{
		return (hasCap && isRound && isDotted);
	}
}
