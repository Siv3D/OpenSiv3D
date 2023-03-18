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
# include <array>
# include <Siv3D/Common.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <msctf.h>

/*
	Simple DirectMedia Layer
	Copyright (C) 1997-2017 Sam Lantinga <slouken@libsdl.org>

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

#define SDL_TEXTEDITINGEVENT_TEXT_SIZE (512)
#define MAX_CANDLIST    9
#define MAX_CANDLENGTH  512

typedef struct
{
	void** lpVtbl;
	int refcount;
	void* data;
} TSFSink;

namespace s3d
{
	class CTextInput;
}

typedef struct SDL_VideoData
{
	s3d::CTextInput* pTextInput = nullptr;

	DWORD clipboard_count;

	BOOL ime_com_initialized;
	struct ITfThreadMgr* ime_threadmgr;
	BOOL ime_initialized;
	BOOL ime_enabled;
	BOOL ime_available;
	HWND ime_hwnd_main;
	HWND ime_hwnd_current;
	HIMC ime_himc;

	WCHAR ime_composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
	std::array<s3d::uint8, SDL_TEXTEDITINGEVENT_TEXT_SIZE> ime_composition_attributes;
	WCHAR ime_readingstring[16];
	int ime_cursor;

	BOOL ime_candlist;
	WCHAR ime_candidates[MAX_CANDLIST][MAX_CANDLENGTH];
	DWORD ime_candcount;
	DWORD ime_candref;
	DWORD ime_candsel;
	UINT ime_candpgsize;
	int ime_candlistindexbase;
	BOOL ime_candvertical;

	BOOL ime_dirty;
	int ime_winwidth;
	int ime_winheight;

	HKL ime_hkl;
	HMODULE ime_himm32;
	UINT(WINAPI* GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pnErrorIndex, BOOL* pfIsVertical, PUINT puMaxReadingLen);
	BOOL(WINAPI* ShowReadingWindow)(HIMC himc, BOOL bShow);
	//LPINPUTCONTEXT2(WINAPI *ImmLockIMC)(HIMC himc);
	BOOL(WINAPI* ImmUnlockIMC)(HIMC himc);
	LPVOID(WINAPI* ImmLockIMCC)(HIMCC himcc);
	BOOL(WINAPI* ImmUnlockIMCC)(HIMCC himcc);

	BOOL ime_uiless;
	struct ITfThreadMgrEx* ime_threadmgrex;
	DWORD ime_uielemsinkcookie;
	DWORD ime_alpnsinkcookie;
	DWORD ime_openmodesinkcookie;
	DWORD ime_convmodesinkcookie;
	TSFSink* ime_uielemsink;
	TSFSink* ime_ippasink;
} SDL_VideoData;

void WIN_InitKeyboard(SDL_VideoData* data);
BOOL IME_HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM* lParam, SDL_VideoData* videodata);

void WIN_StartTextInput(SDL_VideoData* videodata, HWND hwnd);
void WIN_StopTextInput(SDL_VideoData* videodata, HWND hwnd);

void IME_Init(SDL_VideoData* videodata, HWND hwnd);
void IME_Enable(SDL_VideoData* videodata, HWND hwnd);
void IME_Disable(SDL_VideoData* videodata, HWND hwnd);
void IME_Quit(SDL_VideoData* videodata);
