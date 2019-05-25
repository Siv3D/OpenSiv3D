//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
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
# include <wrl.h>

using Microsoft::WRL::ComPtr;
