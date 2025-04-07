//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextToSpeech/CTextToSpeech.hpp>

namespace s3d
{
	ISiv3DTextToSpeech* ISiv3DTextToSpeech::Create()
	{
		return new CTextToSpeech;
	}
}
