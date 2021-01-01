//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# ifdef __GNUC__
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wsign-compare"
# endif
# ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wsign-compare"
# endif
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4389)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(26495)
# include <ThirdParty/fmt/format.h>
# include <ThirdParty/fmt/ostream.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
# ifdef __clang__
#	pragma clang diagnostic pop
# endif
# ifdef __GNUC__
#	pragma GCC diagnostic pop
# endif
