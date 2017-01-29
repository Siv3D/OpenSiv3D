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

# if defined(_WIN32)

	# define SIV3D_TARGET_WINDOWS

# elif defined(__APPLE__) && defined(__MACH__)

	# define SIV3D_TARGET_MACOS

# elif defined(__linux__)

	# define SIV3D_TARGET_LINUX

# else

	# error Unsupported platform

# endif


# if defined(SIV3D_TARGET_WINDOWS) && defined(_WIN64)

	# define SIV3D_TARGET_WINDOWS_DESKTOP_X64

# elif defined(SIV3D_TARGET_WINDOWS) && !defined(_WIN64)

	# define SIV3D_TARGET_WINDOWS_DESKTOP_X86

# endif


# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64) || defined(SIV3D_TARGET_MACOS)

	# define SIV3D_TARGET_X64

# else

	# define SIV3D_TARGET_X86

# endif


# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

	# define SIV3D_PLATFORM_PTR_SIZE		8
	# define SIV3D_ALLOCATOR_MIN_ALIGNMENT	16

# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

	# define SIV3D_PLATFORM_PTR_SIZE		4
	# define SIV3D_ALLOCATOR_MIN_ALIGNMENT	8

# elif defined(SIV3D_TARGET_MACOS)

	# define SIV3D_PLATFORM_PTR_SIZE		8
	# define SIV3D_ALLOCATOR_MIN_ALIGNMENT	16

# elif defined(SIV3D_TARGET_LINUX)

	# define SIV3D_PLATFORM_PTR_SIZE		8
	# define SIV3D_ALLOCATOR_MIN_ALIGNMENT	16

# else

	# error	

# endif


# if defined(SIV3D_TARGET_WINDOWS)

	# define S3D_CONSTEXPR_CPP14	

# else

	# define S3D_CONSTEXPR_CPP14	constexpr

# endif


# if defined(SIV3D_TARGET_WINDOWS)

    # define S3D_EXCEPTION_ABI

# else

    # define S3D_EXCEPTION_ABI		__attribute__ ((__visibility__("default")))

# endif


# if defined(SIV3D_TARGET_WINDOWS)

    # define S3D_DISABLE_MSVC_WARNINGS_PUSH(warnings)	\
			 __pragma(warning(push))					\
			 __pragma(warning(disable: warnings))

	# define S3D_DISABLE_MSVC_WARNINGS_POP()			\
			 __pragma(warning(pop))

# else

	# define S3D_DISABLE_MSVC_WARNINGS_PUSH(warnings)

	# define S3D_DISABLE_MSVC_WARNINGS_POP()

# endif
