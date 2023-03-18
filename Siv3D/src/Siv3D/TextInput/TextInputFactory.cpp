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

# include <Siv3D/TextInput/CTextInput.hpp>

namespace s3d
{
	ISiv3DTextInput* ISiv3DTextInput::Create()
	{
		return new CTextInput;
	}
}
