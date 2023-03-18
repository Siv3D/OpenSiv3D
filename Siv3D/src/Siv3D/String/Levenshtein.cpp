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

# include <Siv3D/Common.hpp>
# include <Siv3D/String.hpp>

# if defined(__GNUC__)
	_Pragma("GCC diagnostic push")
	_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
# endif
# if defined(__clang__)
	_Pragma("clang diagnostic push")
	_Pragma("clang diagnostic ignored \"-Wunused-parameter\"")
	_Pragma("clang diagnostic ignored \"-Wshorten-64-to-32\"")
# endif
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4267)
# include <ThirdParty/levenshtein-sse/levenshtein-sse.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_CLANG_WARNINGS_POP()
SIV3D_DISABLE_GCC_WARNINGS_POP()

namespace s3d
{
	size_t String::levenshteinDistanceFrom(const StringView other) const noexcept
	{
		return levenshteinSSE::levenshtein(begin(), end(), other.begin(), other.end());
	}
}
