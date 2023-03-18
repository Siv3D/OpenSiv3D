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
	namespace detail
	{
		
		__attribute__((import_name("siv3dCallOnAlert")))
		void siv3dCallOnAlert(const char*);
	}

	namespace FreestandingMessageBox
	{
		void ShowInfo(const StringView text)
		{
			System::MessageBoxOK(U"Application Error", text, MessageBoxStyle::Info);
		}

		void ShowError(const StringView text)
		{
			detail::siv3dCallOnAlert(text.narrow().c_str());
		}
	}
}
