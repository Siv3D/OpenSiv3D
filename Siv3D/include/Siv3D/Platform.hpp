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
// ターゲットプラットフォーム
// Target Platform
//
//////////////////////////////////////////////////

# if defined(_WIN32)

	/// <summary>
	/// ターゲットプラットフォーム: Windows
	/// Target platform: Windows
	/// </summary>
	# define SIV3D_TARGET_WINDOWS

	/// <summary>
	/// ターゲットプラットフォームの名前
	/// Name of the Target Platform
	/// </summary>
	# define SIV3D_PLATFORM_NAME	U"Windows Desktop"

# elif defined(__APPLE__) && defined(__MACH__)

	/// <summary>
	/// ターゲットプラットフォーム: macOS
	/// Target platform: macOS
	/// </summary>
	# define SIV3D_TARGET_MACOS

	/// <summary>
	/// ターゲットプラットフォームの名前
	/// Name of the Target Platform
	/// </summary>
	# define SIV3D_PLATFORM_NAME	U"macOS"

# elif defined(__linux__)

	/// <summary>
	/// ターゲットプラットフォーム: Linux
	/// Target platform: Linux
	/// </summary>
	# define SIV3D_TARGET_LINUX

	/// <summary>
	/// ターゲットプラットフォームの名前
	/// Name of the Target Platform
	/// </summary>
	# define SIV3D_PLATFORM_NAME	U"Linux"

# else

	# error Unsupported platform

# endif


//////////////////////////////////////////////////
//
// ターゲット Windows プラットフォーム
// Target Windows Platform
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS)

	# if defined(_WIN64)

		/// <summary>
		/// ターゲット Windows プラットフォーム: 64-bit デスクトップ
		/// Target Windows platform: 64-bit desktop application
		/// </summary>
		# define SIV3D_TARGET_WINDOWS_DESKTOP_X64

	# else

		# error Windows 32-bit 版のサポートは終了しました。
		# error Windows 32-bit is no longer supported.

	# endif

# endif


//////////////////////////////////////////////////
//
// SSE2 サポート
// SSE2 Support
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS) || defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

	# define SIV3D_HAVE_SSE2

# else

	# error Unimplemented

# endif


//////////////////////////////////////////////////
//
// __m128 のメンバ
// __m128 members
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS)

	# define SIV3D_HAVE_M128_MEMBERS

# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# else

	# error Unimplemented

# endif


//////////////////////////////////////////////////
//
// ビルド設定
// Build Configuration
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
// コンパイラ拡張
// Compiler Extensions
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS)

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
// Visual Studio のバージョンチェック
// MSVC Version Check
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS) && (_MSC_FULL_VER < 192027508)

	# error このプロジェクトをビルドするには Visual Studio 2019 以降が必要です。
	# error Visual Studio 2019 or later is required to build this project.

# endif

//////////////////////////////////////////////////
//
// 警告抑制
// Disable warning messages
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS)

	# pragma warning(disable : 26444 26451 26495)

# endif
