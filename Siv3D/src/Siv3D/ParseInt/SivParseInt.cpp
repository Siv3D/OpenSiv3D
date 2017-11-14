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

# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/ParseInt.hpp>
# include "../../ThirdParty/abseil/numbers.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr int32 ErrorResult = 0;
	}

	template <>
	int8 ParseInt<int8>(StringView view, Arg::radix_<uint32> radix)
	{
		int32 result;

		if (!detail::safe_int_internal(view, &result, *radix)
			|| (result < INT8_MIN || INT8_MAX < result))
		{
			return detail::ErrorResult;
		}
		
		return static_cast<int8>(result);
	}

	template <>
	uint8 ParseInt<uint8>(StringView view, Arg::radix_<uint32> radix)
	{
		uint32 result;

		if (!detail::safe_int_internal(view, &result, *radix)
			|| (UINT8_MAX < result))
		{
			return detail::ErrorResult;
		}

		return static_cast<uint8>(result);
	}

	template <>
	int16 ParseInt<int16>(StringView view, Arg::radix_<uint32> radix)
	{
		int32 result;

		if (!detail::safe_int_internal(view, &result, *radix)
			|| (result < INT16_MIN || INT16_MAX < result))
		{
			return detail::ErrorResult;
		}

		return static_cast<int8>(result);
	}

	template <>
	uint16 ParseInt<uint16>(StringView view, Arg::radix_<uint32> radix)
	{
		uint32 result;

		if (!detail::safe_int_internal(view, &result, *radix)
			|| (UINT16_MAX < result))
		{
			return detail::ErrorResult;
		}

		return static_cast<uint16>(result);
	}

	template <>
	int32 ParseInt<int32>(StringView view, Arg::radix_<uint32> radix)
	{
		int32 result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return detail::ErrorResult;
		}

		return result;
	}

	template <>
	uint32 ParseInt<uint32>(StringView view, Arg::radix_<uint32> radix)
	{
		uint32 result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return detail::ErrorResult;
		}

		return result;
	}

	template <>
	long ParseInt<long>(StringView view, Arg::radix_<uint32> radix)
	{
		long result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return detail::ErrorResult;
		}

		return result;
	}

	template <>
	unsigned long ParseInt<unsigned long>(StringView view, Arg::radix_<uint32> radix)
	{
		unsigned long result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return detail::ErrorResult;
		}

		return result;
	}

	template <>
	long long ParseInt<long long>(StringView view, Arg::radix_<uint32> radix)
	{
		long long result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return detail::ErrorResult;
		}

		return result;
	}

	template <>
	unsigned long long ParseInt<unsigned long long>(StringView view, Arg::radix_<uint32> radix)
	{
		unsigned long long result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return detail::ErrorResult;
		}

		return result;
	}


	template <>
	Optional<int8> ParseIntOpt<int8>(StringView view, Arg::radix_<uint32> radix)
	{
		int32 result;

		if (!detail::safe_int_internal(view, &result, *radix)
			|| (result < INT8_MIN || INT8_MAX < result))
		{
			return none;
		}

		return static_cast<int8>(result);
	}

	template <>
	Optional<uint8> ParseIntOpt<uint8>(StringView view, Arg::radix_<uint32> radix)
	{
		uint32 result;

		if (!detail::safe_int_internal(view, &result, *radix)
			|| (UINT8_MAX < result))
		{
			return none;
		}

		return static_cast<uint8>(result);
	}

	template <>
	Optional<int16> ParseIntOpt<int16>(StringView view, Arg::radix_<uint32> radix)
	{
		int32 result;

		if (!detail::safe_int_internal(view, &result, *radix)
			|| (result < INT16_MIN || INT16_MAX < result))
		{
			return none;
		}

		return static_cast<int8>(result);
	}

	template <>
	Optional<uint16> ParseIntOpt<uint16>(StringView view, Arg::radix_<uint32> radix)
	{
		uint32 result;

		if (!detail::safe_int_internal(view, &result, *radix)
			|| (UINT16_MAX < result))
		{
			return none;
		}

		return static_cast<uint16>(result);
	}

	template <>
	Optional<int32> ParseIntOpt<int32>(StringView view, Arg::radix_<uint32> radix)
	{
		int32 result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<uint32> ParseIntOpt<uint32>(StringView view, Arg::radix_<uint32> radix)
	{
		uint32 result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<long> ParseIntOpt<long>(StringView view, Arg::radix_<uint32> radix)
	{
		long result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<unsigned long> ParseIntOpt<unsigned long>(StringView view, Arg::radix_<uint32> radix)
	{
		unsigned long result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<long long> ParseIntOpt<long long>(StringView view, Arg::radix_<uint32> radix)
	{
		long long result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<unsigned long long> ParseIntOpt<unsigned long long>(StringView view, Arg::radix_<uint32> radix)
	{
		unsigned long long result;

		if (!detail::safe_int_internal(view, &result, *radix))
		{
			return none;
		}

		return result;
	}
}
