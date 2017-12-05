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

//////////////////////////////////////////////////
//
//	Target OS
//
//////////////////////////////////////////////////

# if defined(_WIN32)

	/// <summary>
	/// Target platform: Windows (x86 and x64)
	/// </summary>
	# define SIV3D_TARGET_WINDOWS

# elif defined(__APPLE__) && defined(__MACH__)

	/// <summary>
	/// Target platform: macOS
	/// </summary>
	# define SIV3D_TARGET_MACOS

# elif defined(__linux__)

	/// <summary>
	/// Target platform: Linux
	/// </summary>
	# define SIV3D_TARGET_LINUX

# else

	# error Unsupported platform

# endif


//////////////////////////////////////////////////
//
//	Target Windows Platform
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS)

	# if defined(_WIN64)

		/// <summary>
		/// Target Windows platform: 64-bit desktop application
		/// </summary>
		# define SIV3D_TARGET_WINDOWS_DESKTOP_X64

	# else

		/// <summary>
		/// Target Windows platform: 32-bit desktop application
		/// </summary>
		# define SIV3D_TARGET_WINDOWS_DESKTOP_X86

	# endif

# endif


//////////////////////////////////////////////////
//
//	Target Architecture
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64) || defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

	/// <summary>
	/// Target architecture: x64
	/// </summary>
	# define SIV3D_TARGET_X64

# else

	/// <summary>
	/// Target architecture: x86
	/// </summary>
	# define SIV3D_TARGET_X86

# endif


//////////////////////////////////////////////////
//
//	Name of the Target Platform
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

	/// <summary>
	/// Name of the Target Platform
	/// </summary>
	# define Siv3DPlatform	U"WindowsDesktop-x64"

# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

	/// <summary>
	/// Name of the Target Platform
	/// </summary>
	# define Siv3DPlatform	U"WindowsDesktop-x86"

# elif defined(SIV3D_TARGET_MACOS)

	/// <summary>
	/// Name of the Target Platform
	/// </summary>
	# define Siv3DPlatform	U"macOS"

# elif defined(SIV3D_TARGET_LINUX)

	/// <summary>
	/// Name of the Target Platform
	/// </summary>
	# define Siv3DPlatform	U"Linux"

# else

	# error	

# endif


//////////////////////////////////////////////////
//
//	Build Configuration
//
//////////////////////////////////////////////////

# if defined(_DEBUG) || defined(DEBUG)

	# define SIV3D_IS_DEBUG		1

# else

	# define SIV3D_IS_DEBUG		0

# endif


//////////////////////////////////////////////////
//
//	MSVC Version Check
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS) && (_MSC_FULL_VER < 191225830)

	# error Visual Studio 2017 version 15.5 or later is required

# endif


//////////////////////////////////////////////////
//
//	Pointer and Allocation
//
//////////////////////////////////////////////////

# ifdef __cplusplus

# include <cstddef>

namespace s3d
{
	namespace Platform
	{
	# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

		# define SIV3D_PLATFORM_PTR_SIZE	8
		constexpr size_t PointerSize		= 8;
		constexpr size_t AllocatorAlignment	= 16;

	# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

		# define SIV3D_PLATFORM_PTR_SIZE	4
		constexpr size_t PointerSize		= 4;
		constexpr size_t AllocatorAlignment	= 8;

	# elif defined(SIV3D_TARGET_MACOS)

		# define SIV3D_PLATFORM_PTR_SIZE	8
		constexpr size_t PointerSize		= 8;
		constexpr size_t AllocatorAlignment	= 16;

	# elif defined(SIV3D_TARGET_LINUX)

		# define SIV3D_PLATFORM_PTR_SIZE	8
		constexpr size_t PointerSize		= 8;
		constexpr size_t AllocatorAlignment	= 16;

	# else

		# error	

	# endif
	}
}
# endif


//////////////////////////////////////////////////
//
//	Compiler Extensions
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS)

    # define S3D_EXCEPTION_ABI

    # define S3D_DISABLE_MSVC_WARNINGS_PUSH(warnings)	\
			 __pragma(warning(push))					\
			 __pragma(warning(disable: warnings))

	# define S3D_DISABLE_MSVC_WARNINGS_POP()			\
			 __pragma(warning(pop))

# else

    # define S3D_EXCEPTION_ABI		__attribute__ ((__visibility__("default")))

	# define S3D_DISABLE_MSVC_WARNINGS_PUSH(warnings)

	# define S3D_DISABLE_MSVC_WARNINGS_POP()

# endif


//////////////////////////////////////////////////
//
//	MSVC Linker Options
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS)

	# pragma comment (linker, "/entry:\"wWinMainCRTStartup\"")

	# if defined _M_IX86

		# pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

	# elif defined _M_X64

		# pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")

	# endif

# endif


//////////////////////////////////////////////////
//
//	MSVC Static Libraries
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS)

	# pragma comment (lib, "winmm")

	# if (SIV3D_IS_DEBUG)

		# pragma comment (lib, "Siv3D_d")
		# pragma comment (lib, "zlib/zlib_d")
		# pragma comment (lib, "libpng/libpng16_d")
		# pragma comment (lib, "libjpeg-turbo/turbojpeg-static_d")

	# else

		# pragma comment (lib, "Siv3D")
		# pragma comment (lib, "zlib/zlib")
		# pragma comment (lib, "libpng/libpng16")
		# pragma comment (lib, "libjpeg-turbo/turbojpeg-static")

	# endif

# endif
