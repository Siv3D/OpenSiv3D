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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "CBinaryReader_windows.hpp"

namespace s3d
{
	BinaryReader::CBinaryReader::CBinaryReader()
	{

	}

	BinaryReader::CBinaryReader::~CBinaryReader()
	{
		close();
	}


}

# endif
