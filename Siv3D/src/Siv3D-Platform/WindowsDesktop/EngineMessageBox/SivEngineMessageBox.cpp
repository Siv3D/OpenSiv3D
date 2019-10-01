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
# include <Siv3D/Windows.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace EngineMessageBox
	{
		void Show(const StringView text)
		{
			::MessageBoxW(nullptr, Unicode::ToWString(text).c_str(), L"Application Error", MB_OK | MB_ICONINFORMATION);
		}

		void ShowError(const StringView text)
		{
			::MessageBoxW(nullptr, Unicode::ToWString(text).c_str(), L"Application Error", MB_OK | MB_ICONERROR);
		}
	}
}
