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

# include <iostream>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>

namespace s3d
{
	namespace detail
	{
		static void ShowFreestandingMessageBox(const StringView text)
		{
			// [Siv3D ToDo]
			std::cerr << text << '\n';
		}
	}

	namespace FreestandingMessageBox
	{
		void ShowInfo(const StringView text)
		{
			detail::ShowFreestandingMessageBox(text);
		}

		void ShowError(const StringView text)
		{
			detail::ShowFreestandingMessageBox(text);
		}
	}
}
