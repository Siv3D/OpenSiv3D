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

# pragma once
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Window/IWindow.hpp>

namespace s3d
{
	namespace detail
	{
		static void ShowFreestandingMessageBox(const StringView text, const uint32 type)
		{
			::MessageBoxW(nullptr, text.toWstr().c_str(), L"Siv3D Engine", type);
		}
	}

	namespace FreestandingMessageBox
	{
		void ShowInfo(const StringView text)
		{
			detail::ShowFreestandingMessageBox(text, (MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL));
		}

		void ShowError(const StringView text)
		{
			detail::ShowFreestandingMessageBox(text, (MB_OK | MB_ICONERROR | MB_SYSTEMMODAL));
		}
	}
}
