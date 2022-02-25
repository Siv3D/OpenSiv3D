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
# if __has_include(<cxxabi.h>)
#	define SIV3D_HAS_CXXABI
#	include <cxxabi.h>
# endif

namespace s3d
{
# if defined(SIV3D_HAS_CXXABI)

	inline String Demangle(const char* name)
	{
		String result;
		int status = 0;
		
		if (char* p = abi::__cxa_demangle(name, nullptr, nullptr, &status))
		{
			result = Unicode::FromUTF8(p);

			std::free(p);
		}

		return result;
	}

# undef SIV3D_HAS_CXXABI

# else

	inline String Demangle(const char* name)
	{
		return Unicode::FromUTF8(name);
	}

# endif
}


