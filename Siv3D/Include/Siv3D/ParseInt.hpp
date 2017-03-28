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
# include "Fwd.hpp"
# include "NamedParameter.hpp"
# include "String.hpp"

namespace s3d
{
	template <class IntegerType>
	inline IntegerType ParseInt(const String& str, Arg::radix_<uint32> radix = (Arg::radix = 0));

	template <>
	inline int8 ParseInt<int8>(const String& str, Arg::radix_<uint32> radix)
	{
		const long result = ::wcstol(str.c_str(), nullptr, radix.value());
		return (result < INT8_MIN || INT8_MAX < result) ? 0 : static_cast<int8>(result);
	}

	template <>
	inline uint8 ParseInt<uint8>(const String& str, Arg::radix_<uint32> radix)
	{
		const unsigned long result = ::wcstoul(str.c_str(), nullptr, radix.value());
		return (UINT8_MAX < result) ? 0 : static_cast<uint8>(result);
	}

	template <>
	inline int16 ParseInt<int16>(const String& str, Arg::radix_<uint32> radix)
	{
		const long result = ::wcstol(str.data(), nullptr, radix.value());
		return (result < INT16_MIN || INT16_MAX < result) ? 0 : static_cast<int16>(result);
	}

	template <>
	inline uint16 ParseInt<uint16>(const String& str, Arg::radix_<uint32> radix)
	{
		const unsigned long result = ::wcstoul(str.data(), nullptr, radix.value());
		return (UINT16_MAX < result) ? 0 : static_cast<uint16>(result);
	}

	template <>
	inline int32 ParseInt<int32>(const String& str, Arg::radix_<uint32> radix)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return ::wcstol(str.data(), nullptr, radix.value());

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

		const long result = ::wcstol(str.data(), nullptr, radix.value());
		return (result < INT32_MIN || INT32_MAX < result) ? 0 : static_cast<int32>(result);

	# endif
	}

	template <>
	inline uint32 ParseInt<uint32>(const String& str, Arg::radix_<uint32> radix)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return ::wcstoul(str.data(), nullptr, radix.value());

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

		const unsigned long result = ::wcstoul(str.data(), nullptr, radix.value());
		return (UINT32_MAX < result) ? 0 : static_cast<uint32>(result);

	# endif
	}

	template <>
	inline long ParseInt<long>(const String& str, Arg::radix_<uint32> radix)
	{
		return ::wcstol(str.data(), nullptr, radix.value());
	}

	template <>
	inline unsigned long ParseInt<unsigned long>(const String& str, Arg::radix_<uint32> radix)
	{
		return ::wcstoul(str.data(), nullptr, radix.value());
	}

	template <>
	inline long long ParseInt<long long>(const String& str, Arg::radix_<uint32> radix)
	{
		return ::wcstoll(str.data(), nullptr, radix.value());
	}

	template <>
	inline unsigned long long ParseInt<unsigned long long>(const String& str, Arg::radix_<uint32> radix)
	{
		return ::wcstoull(str.data(), nullptr, radix.value());
	}

	template <class IntegerType>
	inline Optional<IntegerType> ParseIntOpt(const String& str, Arg::radix_<uint32> radix = (Arg::radix = 0));

	template <>
	inline Optional<int8> ParseIntOpt<int8>(const String& str, Arg::radix_<uint32> radix)
	{
		wchar* p;
		const long result = ::wcstol(str.data(), &p, radix.value());

		if (str.data() == p || result < INT8_MIN || INT8_MAX < result)
		{
			return none;
		}

		return static_cast<int8>(result);
	}

	template <>
	inline Optional<uint8> ParseIntOpt<uint8>(const String& str, Arg::radix_<uint32> radix)
	{
		wchar* p;
		const unsigned long result = ::wcstoul(str.data(), &p, radix.value());

		if (str.data() == p || UINT8_MAX < result)
		{
			return none;
		}

		return static_cast<uint8>(result);
	}

	template <>
	inline Optional<int16> ParseIntOpt<int16>(const String& str, Arg::radix_<uint32> radix)
	{
		wchar* p;
		const long result = ::wcstol(str.data(), &p, radix.value());

		if (str.data() == p || result < INT16_MIN || INT16_MAX < result)
		{
			return none;
		}

		return static_cast<int16>(result);
	}

	template <>
	inline Optional<uint16> ParseIntOpt<uint16>(const String& str, Arg::radix_<uint32> radix)
	{
		wchar* p;
		const unsigned long result = ::wcstoul(str.data(), &p, radix.value());

		if (str.data() == p || UINT16_MAX < result)
		{
			return none;
		}

		return static_cast<uint16>(result);
	}

	template <>
	inline Optional<int32> ParseIntOpt<int32>(const String& str, Arg::radix_<uint32> radix)
	{
	# if defined(SIV3D_TARGET_WINDOWS)
			
		wchar* p;
		const long result = ::wcstol(str.data(), &p, radix.value());

		if (str.data() == p)
		{
			return none;
		}

		return result;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

		wchar* p;
		const long result = ::wcstol(str.data(), &p, radix.value());

		if (str.data() == p || result < INT32_MIN || INT32_MAX < result)
		{
			return none;
		}

		return static_cast<int32>(result);

	# endif
	}

	template <>
	inline Optional<uint32> ParseIntOpt<uint32>(const String& str, Arg::radix_<uint32> radix)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		wchar* p;
		const unsigned long result = ::wcstoul(str.data(), &p, radix.value());

		if (str.data() == p)
		{
			return none;
		}

		return result;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

		wchar* p;
		const unsigned long result = ::wcstoul(str.data(), &p, radix.value());

		if (str.data() == p || UINT32_MAX < result)
		{
			return none;
		}

		return static_cast<uint32>(result);

	# endif
	}

	template <>
	inline Optional<long> ParseIntOpt<long>(const String& str, Arg::radix_<uint32> radix)
	{
		wchar* p;
		const long result = ::wcstol(str.data(), &p, radix.value());

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	template <>
	inline Optional<unsigned long> ParseIntOpt<unsigned long>(const String& str, Arg::radix_<uint32> radix)
	{
		wchar* p;
		const unsigned long result = ::wcstoul(str.data(), &p, radix.value());

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	template <>
	inline Optional<long long> ParseIntOpt<long long>(const String& str, Arg::radix_<uint32> radix)
	{
		wchar* p;
		const int64 result = ::wcstoll(str.data(), &p, radix.value());

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	template <>
	inline Optional<unsigned long long> ParseIntOpt<unsigned long long>(const String& str, Arg::radix_<uint32> radix)
	{
		wchar* p;
		const uint64 result = ::wcstoull(str.data(), &p, radix.value());

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}
}
