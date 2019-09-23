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

//////////////////////////////////////////////////
//
//	プラットフォームマクロ
//	Platform Macros
//
//////////////////////////////////////////////////

# define SIV3D_PLATFORM(X) SIV3D_PLATFORM_PRIVATE_DEFINITION_##X()
# define SIV3D_PLATFORM_PRIVATE_DEFINITION_WINDOWS() 0
# define SIV3D_PLATFORM_PRIVATE_DEFINITION_MACOS() 0
# define SIV3D_PLATFORM_PRIVATE_DEFINITION_LINUX() 0

# if defined(_WIN32)

	/// <summary>
	/// ターゲットプラットフォームの名前
	/// Name of the Target Platform
	/// </summary>
	# define SIV3D_PLATFORM_NAME	U"Windows Desktop"

	# undef SIV3D_PLATFORM_PRIVATE_DEFINITION_WINDOWS
	# define SIV3D_PLATFORM_PRIVATE_DEFINITION_WINDOWS() 1

# elif defined(__APPLE__) && defined(__MACH__)

	/// <summary>
	/// ターゲットプラットフォームの名前
	/// Name of the Target Platform
	/// </summary>
	# define SIV3D_PLATFORM_NAME	U"macOS"

	# undef SIV3D_PLATFORM_PRIVATE_DEFINITION_MACOS
	# define SIV3D_PLATFORM_PRIVATE_DEFINITION_MACOS() 1

# elif defined(__linux__)

	/// <summary>
	/// ターゲットプラットフォームの名前
	/// Name of the Target Platform
	/// </summary>
	# define SIV3D_PLATFORM_NAME	U"Linux"

	# undef SIV3D_PLATFORM_PRIVATE_DEFINITION_LINUX
	# define SIV3D_PLATFORM_PRIVATE_DEFINITION_LINUX() 1

# else

	# error Unsupported platform

# endif


//////////////////////////////////////////////////
//
//	機能マクロ
//	Feature Macros
//
//////////////////////////////////////////////////

# define SIV3D_WITH_FEATURE(X) SIV3D_WITH_FEATURE_PRIVATE_DEFINITION_##X()
# define SIV3D_WITH_FEATURE_PRIVATE_DEFINITION_SSE2() 0

# if SIV3D_PLATFORM(WINDOWS)

	# undef SIV3D_WITH_FEATURE_PRIVATE_DEFINITION_SSE2
	# define SIV3D_WITH_FEATURE_PRIVATE_DEFINITION_SSE2() 1

# elif SIV3D_PLATFORM(MACOS)

	# undef SIV3D_WITH_FEATURE_PRIVATE_DEFINITION_SSE2
	# define SIV3D_WITH_FEATURE_PRIVATE_DEFINITION_SSE2() 1

# elif SIV3D_PLATFORM(LINUX)

	# undef SIV3D_WITH_FEATURE_PRIVATE_DEFINITION_SSE2
	# define SIV3D_WITH_FEATURE_PRIVATE_DEFINITION_SSE2() 1

# else

	# error Unimplemented

# endif


//////////////////////////////////////////////////
//
//	__vectorcall
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS)

	# define SIV3D_VECTOR_CALL __vectorcall

# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

	# define SIV3D_VECTOR_CALL

# else

	# error Unimplemented

# endif


//////////////////////////////////////////////////
//
//	ビルド設定
//	Build Configuration
//
//////////////////////////////////////////////////

# if defined(_DEBUG) || defined(DEBUG)

	# define SIV3D_DEBUG		1

# else

	# define SIV3D_DEBUG		0

# endif

namespace s3d
{
	namespace Platform
	{
		inline constexpr bool DebugBuild = (SIV3D_DEBUG == 1);
	}
}


//////////////////////////////////////////////////
//
//	コンパイラ拡張
//	Compiler Extensions
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS)

    # define SIV3D_DISABLE_MSVC_WARNINGS_PUSH(warnings)	\
			 __pragma(warning(push))					\
			 __pragma(warning(disable: warnings))

	# define SIV3D_DISABLE_MSVC_WARNINGS_POP()			\
			 __pragma(warning(pop))

# else

	# define SIV3D_DISABLE_MSVC_WARNINGS_PUSH(warnings)

	# define SIV3D_DISABLE_MSVC_WARNINGS_POP()

# endif


//////////////////////////////////////////////////
//
//	Visual Studio のバージョンチェック
//	MSVC Version Check
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS) && (_MSC_FULL_VER < 192227905)

	# error このプロジェクトをビルドするには Visual Studio 2019 16.2 以降が必要です。
	# error Visual Studio 2019 16.2 or later is required to build this project.

# endif


//////////////////////////////////////////////////
//
//	Windows システムのチェック
//	Target Windows system check
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS) && !defined(_WIN64)

	# error Windows 32-bit 版のサポートは終了しました。
	# error Windows 32-bit is no longer supported.

# endif


//////////////////////////////////////////////////
//
//	警告抑制
//	Disable warning messages
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS)

	# pragma warning(disable : 26444 26451 26495)

# endif
