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
# include "String.hpp"

namespace s3d
{
	struct FormatData
	{
		struct DecimalPlaces
		{
			static constexpr int32 DefaultDecimalPlaces = 5;

			int32 value = DefaultDecimalPlaces;

			SIV3D_NODISCARD_CXX20
			DecimalPlaces() = default;

			SIV3D_NODISCARD_CXX20
			explicit constexpr DecimalPlaces(int32 v) noexcept
				: value{ v } {}

			friend void Formatter(FormatData& formatData, DecimalPlaces decimalPlace);
		};

		SIV3D_NODISCARD_CXX20
		FormatData() = default;

		String string;

		DecimalPlaces decimalPlaces;
	};

	[[nodiscard]]
	inline constexpr FormatData::DecimalPlaces DecimalPlaces(int32 width) noexcept;

	inline namespace Literals
	{
		inline namespace DecimalPlaceLiterals
		{
			[[nodiscard]]
			constexpr FormatData::DecimalPlaces operator ""_dp(unsigned long long width) noexcept;
		}
	}
}

# include "detail/FormatData.ipp"
