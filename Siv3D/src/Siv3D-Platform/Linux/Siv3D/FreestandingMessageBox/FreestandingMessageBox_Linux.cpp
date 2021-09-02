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

# include <iostream>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>

namespace s3d
{
	namespace detail
	{
		static void ShowFreestandingMessageBox(const StringView text)
		{
			// [Siv3D ToDo]
			std::cout << text << '\n';
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
