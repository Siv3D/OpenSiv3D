//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/String.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d::Platform::Windows
{
	String GetLastErrorMessage()
	{
		LPVOID buffer;
		if (::FormatMessageW((FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM),
			nullptr,
			::GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&buffer,
			0,
			nullptr))
		{
			String message = Unicode::FromWstring(static_cast<const wchar_t*>(buffer));
			::LocalFree(buffer);
			return message.rtrim();
		}
		else
		{
			return U"Unknown Windows error";
		}
	}
}
