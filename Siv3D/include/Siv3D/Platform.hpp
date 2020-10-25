﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

//////////////////////////////////////////////////
//
//	プラットフォーム
//	Platform
//
//////////////////////////////////////////////////

# define SIV3D_PLATFORM(X) SIV3D_PLATFORM_PRIVATE_DEFINITION_##X()
# define SIV3D_PLATFORM_PRIVATE_DEFINITION_WINDOWS()	0
# define SIV3D_PLATFORM_PRIVATE_DEFINITION_MACOS()		0
# define SIV3D_PLATFORM_PRIVATE_DEFINITION_LINUX()		0
# define SIV3D_PLATFORM_PRIVATE_DEFINITION_WEB()		0

# if defined(_WIN32)

	# define SIV3D_PLATFORM_NAME	U"Windows Desktop"
	# undef	 SIV3D_PLATFORM_PRIVATE_DEFINITION_WINDOWS
	# define SIV3D_PLATFORM_PRIVATE_DEFINITION_WINDOWS()	1

# elif defined(__APPLE__) && defined(__MACH__)

	# define SIV3D_PLATFORM_NAME	U"macOS"
	# undef  SIV3D_PLATFORM_PRIVATE_DEFINITION_MACOS
	# define SIV3D_PLATFORM_PRIVATE_DEFINITION_MACOS()		1

# elif defined(__linux__)

	# define SIV3D_PLATFORM_NAME	U"Linux"
	# undef  SIV3D_PLATFORM_PRIVATE_DEFINITION_LINUX
	# define SIV3D_PLATFORM_PRIVATE_DEFINITION_LINUX()		1

# elif defined(__EMSCRIPTEN__)

	# define SIV3D_PLATFORM_NAME	U"Web"
	# undef  SIV3D_PLATFORM_PRIVATE_DEFINITION_WEB
	# define SIV3D_PLATFORM_PRIVATE_DEFINITION_WEB()		1

# else

	# error Unsupported platform

# endif

// Ref:
// - Better Macros, Better Flags
//   https://www.fluentcpp.com/2019/05/28/better-macros-better-flags/


//////////////////////////////////////////////////
//
//	命令セット
//	Intrinsics
//
//////////////////////////////////////////////////

# define SIV3D_INTRINSIC(X) SIV3D_INTRINSIC_PRIVATE_DEFINITION_##X()
# define SIV3D_INTRINSIC_PRIVATE_DEFINITION_SSE()	0

# if SIV3D_PLATFORM(WINDOWS)

	# undef  SIV3D_INTRINSIC_PRIVATE_DEFINITION_SSE
	# define SIV3D_INTRINSIC_PRIVATE_DEFINITION_SSE()	1

# elif SIV3D_PLATFORM(MACOS)

	# undef  SIV3D_INTRINSIC_PRIVATE_DEFINITION_SSE
	# define SIV3D_INTRINSIC_PRIVATE_DEFINITION_SSE()	1

# elif SIV3D_PLATFORM(LINUX)

	# undef  SIV3D_INTRINSIC_PRIVATE_DEFINITION_SSE
	# define SIV3D_INTRINSIC_PRIVATE_DEFINITION_SSE()	1

# elif SIV3D_PLATFORM(WEB)


# else

	# error Unsupported platform

# endif


//////////////////////////////////////////////////
//
//	ビルド設定
//	Build mode
//
//////////////////////////////////////////////////

# define SIV3D_BUILD(X) SIV3D_BUILD_PRIVATE_DEFINITION_##X()
# define SIV3D_BUILD_PRIVATE_DEFINITION_DEBUG()		0
# define SIV3D_BUILD_PRIVATE_DEFINITION_RELEASE()	0

# if defined(_DEBUG) || defined(DEBUG)

	# undef SIV3D_BUILD_PRIVATE_DEFINITION_DEBUG
	# define SIV3D_BUILD_PRIVATE_DEFINITION_DEBUG()		1

# else

	# undef SIV3D_BUILD_PRIVATE_DEFINITION_RELEASE
	# define SIV3D_BUILD_PRIVATE_DEFINITION_RELEASE()	1

# endif


//////////////////////////////////////////////////
//
//	Visual Studio バージョンのチェック
//	Version check for Visual Studio
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS) && (_MSC_VER < 1928)

	// お使いの Visual Studio のバージョンが古い場合、このエラーが発生します
	// This error occures when your Visual Studio version is not up to date.
	# error Please update the Visual Studio. Visual Studio 2019 16.8 or later is required to build this project.

# endif


//////////////////////////////////////////////////
//
//	Windows ビルド設定のチェック
//	Target Windows system check
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS) && !defined(_WIN64)

	# error Windows 32-bit is not supported.

# endif


//////////////////////////////////////////////////
//
//	コンストラクタの [[nodiscard]]
//	[[nodiscard]] for constructors
//
//////////////////////////////////////////////////

# if defined(__cplusplus)

	# if (__has_cpp_attribute(nodiscard) >= 201907L)

		# define SIV3D_NODISCARD_CXX20 [[nodiscard]]

	# else

		# define SIV3D_NODISCARD_CXX20

	# endif

# endif


//////////////////////////////////////////////////
//
//	[[likely]], [[unlikely]] アトリビュート
//	[[likely]] and [[unlikely]] attributes
//
//////////////////////////////////////////////////

#if defined(__cplusplus)

	# if (__has_cpp_attribute(likely) && __has_cpp_attribute(unlikely) && !(defined(__GNUC__) && (9 <= __GNUC__) && (__GNUC__ < 10)))

		# define SIV3D_LIKELY [[likely]]
		# define SIV3D_UNLIKELY [[unlikely]]

	# else

		# define SIV3D_LIKELY
		# define SIV3D_UNLIKELY

	# endif

# endif


//////////////////////////////////////////////////
//
//	constexpr std::bit_cast
//
//////////////////////////////////////////////////

# if (__cpp_lib_bit_cast >= 201806L)
	
	# define SIV3D_CONSTEXPR_BITCAST constexpr

# else

	# define SIV3D_CONSTEXPR_BITCAST

# endif


//////////////////////////////////////////////////
//
//	__vectorcall
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS)

	# define SIV3D_VECTOR_CALL __vectorcall

# else

	# define SIV3D_VECTOR_CALL

# endif


//////////////////////////////////////////////////
//
//	visibility
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX) || SIV3D_PLATFORM(WEB)

	# define SIV3D_HIDDEN __attribute__((visibility("hidden")))

# else

	# define SIV3D_HIDDEN

# endif


//////////////////////////////////////////////////
//
//	コンパイラ拡張 (MSVC)
//	Compiler Extensions (MSVC)
//
//////////////////////////////////////////////////

# if defined(_MSC_VER)

    # define SIV3D_DISABLE_MSVC_WARNINGS_PUSH(warnings)	\
			 __pragma(warning(push))					\
			 __pragma(warning(disable: warnings))

	# define SIV3D_DISABLE_MSVC_WARNINGS_POP()			\
			 __pragma(warning(pop))

	# define SIV3D_NOVTABLE __declspec(novtable)

# else

	# define SIV3D_DISABLE_MSVC_WARNINGS_PUSH(warnings)
	# define SIV3D_DISABLE_MSVC_WARNINGS_POP()
	# define SIV3D_NOVTABLE

# endif


//////////////////////////////////////////////////
//
//	コンパイラ拡張 (Clang)
//	Compiler Extensions (Clang)
//
//////////////////////////////////////////////////

# if defined(__clang__)

	# define SIV3D_DISABLE_CLANG_WARNINGS_POP()\
		_Pragma("clang diagnostic pop")

# else

	# define SIV3D_DISABLE_CLANG_WARNINGS_POP()

# endif


//////////////////////////////////////////////////
//
//	コンパイラ拡張 (GCC)
//	Compiler Extensions (GCC)
//
//////////////////////////////////////////////////

# if defined(__GNUC__)

	# define SIV3D_DISABLE_GCC_WARNINGS_POP()\
		_Pragma("GCC diagnostic pop")

# else

	# define SIV3D_DISABLE_GCC_WARNINGS_POP()

# endif


//////////////////////////////////////////////////
//
// 実行ファイル埋め込みリソース
// Embedded Resource
//
//////////////////////////////////////////////////

namespace s3d::Platform
{
# if SIV3D_PLATFORM(WINDOWS)

	inline constexpr bool HasEmbeddedResource = true;

# else

	inline constexpr bool HasEmbeddedResource = false;

# endif
}
