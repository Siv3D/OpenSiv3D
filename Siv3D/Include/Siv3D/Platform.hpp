//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

# if defined(_WIN32)
	# define SIV3D_TARGET_WINDOWS
# elif defined(__APPLE__) && defined(__MACH__)
	# define SIV3D_TARGET_OSX
# else
	# error Unsupported platform
# endif

# if defined(SIV3D_TARGET_WINDOWS) && defined(_WIN64)
	# define SIV3D_TARGET_WINDOWS_X64
# elif defined(SIV3D_TARGET_WINDOWS) && !defined(_WIN64)
	# define SIV3D_TARGET_WINDOWS_X86
# endif

# if defined(SIV3D_TARGET_WINDOWS_X64)
	# define SIV3D_PLATFORM_PTR_SIZE		8
	# define SIV3D_ALLOCATOR_MIN_ALIGNMENT	16
# elif defined(SIV3D_TARGET_WINDOWS_X86)
	# define SIV3D_PLATFORM_PTR_SIZE		4
	# define SIV3D_ALLOCATOR_MIN_ALIGNMENT	8
# elif defined(SIV3D_TARGET_OSX)
	# define SIV3D_PLATFORM_PTR_SIZE		8
	# define SIV3D_ALLOCATOR_MIN_ALIGNMENT	16
# else
	# error	
# endif
