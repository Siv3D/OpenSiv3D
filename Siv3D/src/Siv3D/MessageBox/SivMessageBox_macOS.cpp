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
# if defined(SIV3D_TARGET_MACOS)

# include <Siv3D/MessageBox.hpp>

namespace s3d
{
	namespace detail
	{
		int ShowMessageBox_macOS(const char* title, const char* message, int style, int buttons);
	}
	
	namespace System
	{
		MessageBoxSelection ShowMessageBox(const String& title, const String& text, MessageBoxStyle style, MessageBoxButtons buttons)
		{
			const int32 result = detail::ShowMessageBox_macOS(title.narrow().c_str(), text.narrow().c_str(),
								 static_cast<int32>(style), static_cast<int32>(buttons));
			
			return static_cast<MessageBoxSelection>(result);
		}
	}
}

# endif
