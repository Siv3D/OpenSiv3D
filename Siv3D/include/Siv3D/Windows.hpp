//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# ifndef NOMINMAX
#	define	NOMINMAX
# endif

# ifndef STRICT
#	define	STRICT
# endif

# ifndef _WIN32_WINNT
#	define	_WIN32_WINNT _WIN32_WINNT_WIN8
# endif

# ifndef NTDDI_VERSION
#	define	NTDDI_VERSION NTDDI_WIN8
# endif

# include <Windows.h>

# endif
