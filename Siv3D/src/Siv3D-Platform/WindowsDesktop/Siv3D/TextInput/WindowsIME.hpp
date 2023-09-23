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
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/TextInput.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <msctf.h>

/*
	This file contains modified code from the Simple DirectMedia Layer (SDL) library.
	Original copyright: Copyright (C) 1997-2023 Sam Lantinga <slouken@libsdl.org>

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

namespace s3d
{
	class CTextInput;

	struct TextInputData
	{
		CTextInput* pTextInput = nullptr;

		ITfThreadMgr* ime_threadmgr = nullptr;

		bool ime_initialized = false;
		bool ime_enabled = false;
		bool ime_available = false;

		HWND hwnd = nullptr;
		HIMC himc = nullptr;

		bool ime_suppress_endcomposition_event = false;

		std::wstring composition;
		std::array<unsigned char, 256> attributes;
		int ime_cursor = 0;

		bool ime_candlist = 0;

		TextInput::CandidateState candidateState;

		UINT ime_candpgsize = 0;
		int ime_candlistindexbase = 0;
		bool ime_candvertical = true;

		bool ime_dirty = false;

		HKL ime_hkl = nullptr;
		HMODULE ime_himm32 = nullptr;
		UINT(WINAPI* GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pnErrorIndex, BOOL* pfIsVertical, PUINT puMaxReadingLen) = nullptr;
		BOOL(WINAPI* ShowReadingWindow)(HIMC himc, BOOL bShow) = nullptr;

		LONG ime_uicontext = 0;
	};

	void WIN_InitKeyboard(TextInputData* data);
	void WIN_StartTextInput(TextInputData* videodata, HWND hwnd);
	void WIN_StopTextInput(TextInputData* videodata, HWND hwnd);

	int IME_Init(TextInputData* videodata, HWND hwnd);
	void IME_Enable(TextInputData* videodata);
	void IME_Disable(TextInputData* videodata);
	void IME_Quit(TextInputData* videodata);
	BOOL IME_HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM* lParam, TextInputData* videodata);
}
