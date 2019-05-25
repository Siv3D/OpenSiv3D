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

# include <Siv3D/MessageBox.hpp>

namespace s3d
{
	int ShowMessageBox_Linux(const char* title, const char* message, const int style, const int buttons)
	{
		// [Siv3D ToDo]
		return 0;
	}
	
	namespace System
	{
		MessageBoxSelection ShowMessageBox(const String& title, const String& text, MessageBoxStyle style, MessageBoxButtons buttons)
		{
			const int32 result = ShowMessageBox_Linux(title.narrow().c_str(), text.narrow().c_str(),
															  static_cast<int32>(style), static_cast<int32>(buttons));
			
			return static_cast<MessageBoxSelection>(result);
		}
	}
}
