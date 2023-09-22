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
# include <Siv3D/Windows/Windows.hpp>
# include <msctf.h>

/*
	Simple DirectMedia Layer
	Copyright (C) 1997-2023 Sam Lantinga <slouken@libsdl.org>

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

#define SDL_TEXTEDITINGEVENT_TEXT_SIZE (32)
#define MAX_CANDLIST   10
#define MAX_CANDLENGTH 256
#define MAX_CANDSIZE   (sizeof(WCHAR) * MAX_CANDLIST * MAX_CANDLENGTH)

namespace s3d
{
	class CTextInput;
}

typedef struct SDL_VideoData
{
	s3d::CTextInput* pTextInput = nullptr;

	struct ITfThreadMgr* ime_threadmgr;
	bool ime_initialized;
	bool ime_enabled;
	bool ime_available;
	HWND ime_hwnd_main;
	HWND ime_hwnd_current;
	bool ime_suppress_endcomposition_event;
	HIMC ime_himc;

	WCHAR* ime_composition;
	int ime_composition_length;
	WCHAR ime_readingstring[16];
	int ime_cursor;
	std::array<unsigned char, 256> ime_attributes3;

	bool ime_candlist;
	s3d::Array<s3d::String> ime_candidates2;
	DWORD ime_candcount;
	DWORD ime_candref;
	DWORD ime_candsel;
	UINT ime_candpgsize;
	int ime_candlistindexbase;
	bool ime_candvertical;

	bool ime_dirty;

	HKL ime_hkl;
	HMODULE ime_himm32;
	UINT(WINAPI* GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pnErrorIndex, BOOL* pfIsVertical, PUINT puMaxReadingLen);
	BOOL(WINAPI* ShowReadingWindow)(HIMC himc, BOOL bShow);

	LONG ime_uicontext;

} SDL_VideoData;

void WIN_InitKeyboard(SDL_VideoData* data);

void WIN_StartTextInput(SDL_VideoData* videodata, HWND hwnd);
void WIN_StopTextInput(SDL_VideoData* videodata, HWND hwnd);

int IME_Init(SDL_VideoData* videodata, HWND hwnd);
void IME_Enable(SDL_VideoData* videodata, HWND hwnd);
void IME_Disable(SDL_VideoData* videodata, HWND hwnd);
void IME_Quit(SDL_VideoData* videodata);

BOOL IME_HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM* lParam, SDL_VideoData* videodata);