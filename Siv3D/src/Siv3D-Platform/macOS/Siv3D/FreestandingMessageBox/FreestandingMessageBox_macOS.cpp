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

# include <Siv3D/MessageBox.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>

namespace s3d
{
	namespace FreestandingMessageBox
	{
		void ShowInfo(const StringView text)
		{
			System::MessageBoxOK(U"Siv3D Engine", text, MessageBoxStyle::Info);
		}

		void ShowError(const StringView text)
		{
			System::MessageBoxOK(U"Siv3D Engine", text, MessageBoxStyle::Error);
		}
	}
}
