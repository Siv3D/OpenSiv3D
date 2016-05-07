//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../../../Include/Siv3D/Platform.hpp"
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include "../../../Include/Siv3D/Logger.hpp"
# include "../../../Include/Siv3D/String.hpp"

namespace s3d
{
	namespace detail
	{
		void Log_impl::operator()(const String& text) const
		{
			::OutputDebugStringW((text + L'\n').c_str());
		}
	}
}

# elif defined(SIV3D_TARGET_OSX)

# include <iostream>
# include <codecvt>
# include "../../../Include/Siv3D/Logger.hpp"
# include "../../../Include/Siv3D/String.hpp"

namespace s3d
{
	namespace detail
	{
		void Log_impl::operator()(const String& text) const
		{
			std::cout << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(text.str()) << '\n';
		}
	}
}

# endif
