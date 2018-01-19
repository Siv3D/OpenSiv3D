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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include <cstring>
# include <sstream>
//# include <unicode/ucnv.h>
//# include <unicode/ucsdet.h>

//constexpr size_t bufferLength = 1024;

// TODO
std::string ConvertLine(const std::string& line)
{
	return std::string(line);
}

# endif
