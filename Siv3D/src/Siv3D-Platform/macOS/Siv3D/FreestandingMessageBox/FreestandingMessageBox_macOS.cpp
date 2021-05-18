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

# include <Siv3D/MessageBox.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>

namespace s3d
{
	namespace FreestandingMessageBox
	{
		void ShowInfo(const StringView text)
		{
			System::MessageBoxOK(U"Application Error", text, MessageBoxStyle::Info);
		}

		void ShowError(const StringView text)
		{
			System::MessageBoxOK(U"Application Error", text, MessageBoxStyle::Error);
		}
	}
}
