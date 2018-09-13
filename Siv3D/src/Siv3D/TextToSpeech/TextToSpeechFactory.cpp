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

# include "CTextToSpeech_Windows.hpp"
# include "CTextToSpeech_macOS.hpp"
# include "CTextToSpeech_Linux.hpp"

namespace s3d
{
	ISiv3DTextToSpeech* ISiv3DTextToSpeech::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CTextToSpeech_Windows;

	# elif defined(SIV3D_TARGET_MACOS)
		
		return new CTextToSpeech_macOS;
		
	# elif defined(SIV3D_TARGET_LINUX)
		
		return new CTextToSpeech_Linux;
		
	# endif
	}
}

