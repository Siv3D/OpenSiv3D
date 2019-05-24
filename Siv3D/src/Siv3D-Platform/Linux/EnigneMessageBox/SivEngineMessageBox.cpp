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

# include <Siv3D/EngineMessageBox.hpp>
# include <Siv3D/MessageBox.hpp>

namespace s3d
{
	namespace EngineMessageBox
	{
		void Show(const StringView text)
		{
			System::ShowMessageBox(U"Application Error", String(text), MessageBoxStyle::Info, MessageBoxButtons::OK);
		}

		void ShowError(const StringView text)
		{
			System::ShowMessageBox(U"Application Error", String(text), MessageBoxStyle::Error, MessageBoxButtons::OK);
		}
	}
}
