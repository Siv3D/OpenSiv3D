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
# if defined(_WIN32)

# ifndef NOMINMAX
#	define	NOMINMAX
# endif
# ifndef STRICT
#	define STRICT
# endif
# ifndef _WIN32_WINNT
#	define _WIN32_WINNT _WIN32_WINNT_WIN10
# endif
# ifndef NTDDI_VERSION
#	define NTDDI_VERSION NTDDI_WIN10
# endif
# include <Windows.h>
# include <wrl/client.h>

using Microsoft::WRL::ComPtr;

namespace s3d
{
	class String;

	namespace Platform::Windows
	{
		/// @brief GetLastError() の結果を文字列で取得します。
		/// @return 文字列化された GetLastError() の結果
		String GetLastErrorMessage();
	}
}

# endif
