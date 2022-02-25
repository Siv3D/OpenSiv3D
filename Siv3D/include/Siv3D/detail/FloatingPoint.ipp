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
# include <cstring>
# if  __has_include(<bit>)
#	include <bit>
# endif

namespace s3d
{
	template <class Float32, std::enable_if_t<std::is_same_v<Float32, float>>*>
	inline SIV3D_CONSTEXPR_BITCAST uint32 AsUint32(const Float32 value) noexcept
	{
	# if __cpp_lib_bit_cast

		return std::bit_cast<uint32>(value);
	
	# else

		uint32 i;
		
		std::memcpy(&i, &value, sizeof(float));
		
		return i;

	# endif
	}

	template <class Float64, std::enable_if_t<std::is_same_v<Float64, double>>*>
	inline SIV3D_CONSTEXPR_BITCAST uint64 AsUint64(const Float64 value) noexcept
	{
	# if __cpp_lib_bit_cast
	
		return std::bit_cast<uint64>(value);

	# else

		uint64 i;
		
		std::memcpy(&i, &value, sizeof(double));
		
		return i;
	
	# endif
	}
}
