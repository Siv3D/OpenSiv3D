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

//# include <Siv3D/Print.hpp>
# include <Siv3D/Unicode.hpp>
# include "WindowsIME.hpp"
# include "CTextInput.hpp"

namespace s3d
{
	inline constexpr DWORD MaxCandidatesCount = 10;

	void WIN_InitKeyboard(TextInputData* data)
	{
		data->attributes.fill(0);
	}

	static void WIN_QuitKeyboard(TextInputData* videodata)
	{
		IME_Quit(videodata);
	}

	static void WIN_ResetDeadKeys()
	{
		// if a deadkey has been typed, but not the next character (which the deadkey might modify),
		// this tries to undo the effect pressing the deadkey.
		// see: http://archives.miloush.net/michkap/archive/2006/09/10/748775.html
		BYTE keyboardState[256];
		::GetKeyboardState(keyboardState);

		const int keycode = VK_SPACE;
		const int scancode = MapVirtualKeyW(VK_SPACE, MAPVK_VK_TO_VSC);

		if (scancode == 0)
		{
			// the keyboard doesn't have this key
			return;
		}

		for (int i = 0; i < 5; ++i)
		{
			WCHAR buffer[16]{};
			const int result = ::ToUnicode(keycode, scancode, keyboardState, buffer, 16, 0);

			if (0 < result)
			{
				// success
				return;
			}
		}
	}

	void WIN_StartTextInput(TextInputData* videodata, HWND hwnd)
	{
		WIN_ResetDeadKeys();
		IME_Init(videodata, hwnd);
		IME_Enable(videodata);
	}

	void WIN_StopTextInput(TextInputData* videodata, HWND hwnd)
	{
		WIN_ResetDeadKeys();
		IME_Init(videodata, hwnd);
		IME_Disable(videodata);
	}
}

#define LANG_CHT MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)
#define LANG_CHS MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

#define MAKEIMEVERSION(major, minor) ((DWORD)(((BYTE)(major) << 24) | ((BYTE)(minor) << 16)))
#define IMEID_VER(id)                ((id)&0xffff0000)
#define IMEID_LANG(id)               ((id)&0x0000ffff)

#define CHT_HKL_DAYI          ((HKL)(UINT_PTR)0xE0060404)
#define CHT_HKL_NEW_PHONETIC  ((HKL)(UINT_PTR)0xE0080404)
#define CHT_HKL_NEW_CHANG_JIE ((HKL)(UINT_PTR)0xE0090404)
#define CHT_HKL_NEW_QUICK     ((HKL)(UINT_PTR)0xE00A0404)
#define CHT_HKL_HK_CANTONESE  ((HKL)(UINT_PTR)0xE00B0404)
#define CHT_IMEFILENAME1      "TINTLGNT.IME"
#define CHT_IMEFILENAME2      "CINTLGNT.IME"
#define CHT_IMEFILENAME3      "MSTCIPHA.IME"
#define IMEID_CHT_VER42       (LANG_CHT | MAKEIMEVERSION(4, 2))
#define IMEID_CHT_VER43       (LANG_CHT | MAKEIMEVERSION(4, 3))
#define IMEID_CHT_VER44       (LANG_CHT | MAKEIMEVERSION(4, 4))
#define IMEID_CHT_VER50       (LANG_CHT | MAKEIMEVERSION(5, 0))
#define IMEID_CHT_VER51       (LANG_CHT | MAKEIMEVERSION(5, 1))
#define IMEID_CHT_VER52       (LANG_CHT | MAKEIMEVERSION(5, 2))
#define IMEID_CHT_VER60       (LANG_CHT | MAKEIMEVERSION(6, 0))
#define IMEID_CHT_VER_VISTA   (LANG_CHT | MAKEIMEVERSION(7, 0))

#define CHS_HKL          ((HKL)(UINT_PTR)0xE00E0804)
#define CHS_IMEFILENAME1 "PINTLGNT.IME"
#define CHS_IMEFILENAME2 "MSSCIPYA.IME"
#define IMEID_CHS_VER41  (LANG_CHS | MAKEIMEVERSION(4, 1))
#define IMEID_CHS_VER42  (LANG_CHS | MAKEIMEVERSION(4, 2))
#define IMEID_CHS_VER53  (LANG_CHS | MAKEIMEVERSION(5, 3))

#define LANG()         LOWORD((videodata->ime_hkl))
#define PRIMLANG()     ((WORD)PRIMARYLANGID(LANG()))
#define SUBLANG()      SUBLANGID(LANG())

namespace s3d
{
	static void IME_UpdateInputLocale(TextInputData* videodata);
	static void IME_ClearComposition(TextInputData* videodata);
	static void IME_SetWindow(TextInputData* videodata, HWND hwnd);

	int IME_Init(TextInputData* videodata, HWND hwnd)
	{
		HRESULT hResult = S_OK;

		if (videodata->ime_initialized)
		{
			return 0;
		}

		videodata->hwnd = hwnd;

		{
			hResult = ::CoCreateInstance(CLSID_TF_ThreadMgr, NULL, CLSCTX_INPROC_SERVER, IID_ITfThreadMgr, (LPVOID*)&videodata->ime_threadmgr);

			if (hResult != S_OK)
			{
				videodata->ime_available = false;
				return -1;
			}
		}

		videodata->ime_initialized = true;
		videodata->ime_himm32 = ::LoadLibraryExW(L"imm32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);

		if (not videodata->ime_himm32)
		{
			videodata->ime_available = false;
			return 0;
		}

		IME_SetWindow(videodata, hwnd);

		videodata->himc = ::ImmGetContext(hwnd);

		::ImmReleaseContext(hwnd, videodata->himc);

		if (not videodata->himc)
		{
			videodata->ime_available = false;

			IME_Disable(videodata);

			return 0;
		}

		videodata->ime_available = true;

		IME_UpdateInputLocale(videodata);

		IME_Disable(videodata);

		return 0;
	}

	void IME_Enable(TextInputData* videodata)
	{
		if ((not videodata->ime_initialized) || (not videodata->hwnd))
		{
			return;
		}

		if (not videodata->ime_available)
		{
			IME_Disable(videodata);
			return;
		}

		::ImmAssociateContext(videodata->hwnd, videodata->himc);

		videodata->ime_enabled = true;

		IME_UpdateInputLocale(videodata);
	}

	void IME_Disable(TextInputData* videodata)
	{
		if ((not videodata->ime_initialized) || (not videodata->hwnd))
		{
			return;
		}

		IME_ClearComposition(videodata);

		::ImmAssociateContext(videodata->hwnd, (HIMC)0);

		videodata->ime_enabled = false;
	}

	void IME_Quit(TextInputData* videodata)
	{
		if (not videodata->ime_initialized)
		{
			return;
		}

		if (videodata->hwnd)
		{
			::ImmAssociateContext(videodata->hwnd, videodata->himc);
		}

		videodata->hwnd = nullptr;
		videodata->himc = nullptr;

		if (videodata->ime_himm32)
		{
			::FreeLibrary(videodata->ime_himm32);
			videodata->ime_himm32 = nullptr;
		}

		if (videodata->ime_threadmgr)
		{
			videodata->ime_threadmgr->Release();
			videodata->ime_threadmgr = nullptr;
		}

		videodata->ime_initialized = false;
	}

	static void IME_InputLangChanged(TextInputData* videodata)
	{
		const UINT lang = PRIMLANG();
	
		IME_UpdateInputLocale(videodata);

		if (lang != PRIMLANG())
		{
			IME_ClearComposition(videodata);
		}
	}

	static DWORD IME_GetId(TextInputData* videodata, UINT uIndex)
	{
		static HKL hklprev = 0;
		static DWORD dwRet[2] = { 0 };
		DWORD dwVerSize = 0;
		DWORD dwVerHandle = 0;
		LPVOID lpVerBuffer = 0;
		LPVOID lpVerData = 0;
		UINT cbVerData = 0;
		char szTemp[256];
		HKL hkl = 0;
		DWORD dwLang = 0;
		assert(uIndex < sizeof(dwRet) / sizeof(dwRet[0]));

		hkl = videodata->ime_hkl;
		if (hklprev == hkl) {
			return dwRet[uIndex];
		}
		hklprev = hkl;

		assert(uIndex == 0);
		dwLang = ((DWORD_PTR)hkl & 0xffff);
		if (dwLang == LANG_CHT) {
			dwRet[0] = IMEID_CHT_VER_VISTA;
			dwRet[1] = 0;
			return dwRet[0];
		}
		if (hkl != CHT_HKL_NEW_PHONETIC && hkl != CHT_HKL_NEW_CHANG_JIE && hkl != CHT_HKL_NEW_QUICK && hkl != CHT_HKL_HK_CANTONESE && hkl != CHS_HKL) {
			dwRet[0] = dwRet[1] = 0;
			return dwRet[0];
		}
		if (!ImmGetIMEFileNameA(hkl, szTemp, sizeof(szTemp) - 1)) {
			dwRet[0] = dwRet[1] = 0;
			return dwRet[0];
		}
		if (!videodata->GetReadingString) {
	#define LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT)
			if (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHT_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHT_IMEFILENAME2, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHT_IMEFILENAME3, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHS_IMEFILENAME1, -1) != 2 && CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTemp, -1, CHS_IMEFILENAME2, -1) != 2) {
				dwRet[0] = dwRet[1] = 0;
				return dwRet[0];
			}
	#undef LCID_INVARIANT
			dwVerSize = GetFileVersionInfoSizeA(szTemp, &dwVerHandle);
			if (dwVerSize) {
				lpVerBuffer = std::malloc(dwVerSize);
				if (lpVerBuffer) {
					if (GetFileVersionInfoA(szTemp, dwVerHandle, dwVerSize, lpVerBuffer)) {
						if (VerQueryValueA(lpVerBuffer, "\\", &lpVerData, &cbVerData)) {
	#define pVerFixedInfo ((VS_FIXEDFILEINFO FAR *)lpVerData)
							DWORD dwVer = pVerFixedInfo->dwFileVersionMS;
							dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
							if ((videodata->GetReadingString) ||
								((dwLang == LANG_CHT) && (dwVer == MAKEIMEVERSION(4, 2) ||
									dwVer == MAKEIMEVERSION(4, 3) ||
									dwVer == MAKEIMEVERSION(4, 4) ||
									dwVer == MAKEIMEVERSION(5, 0) ||
									dwVer == MAKEIMEVERSION(5, 1) ||
									dwVer == MAKEIMEVERSION(5, 2) ||
									dwVer == MAKEIMEVERSION(6, 0))) ||
								((dwLang == LANG_CHS) && (dwVer == MAKEIMEVERSION(4, 1) ||
									dwVer == MAKEIMEVERSION(4, 2) ||
									dwVer == MAKEIMEVERSION(5, 3)))) {
								dwRet[0] = dwVer | dwLang;
								dwRet[1] = pVerFixedInfo->dwFileVersionLS;
								std::free(lpVerBuffer);
								return dwRet[0];
							}
	#undef pVerFixedInfo
						}
					}
				}
				std::free(lpVerBuffer);
			}
		}
		dwRet[0] = dwRet[1] = 0;
		return dwRet[0];
	}

	static void IME_SetWindow(TextInputData* videodata, HWND hwnd)
	{
		if (videodata->ime_threadmgr)
		{
			ITfDocumentMgr* document_mgr = nullptr;

			if (SUCCEEDED(videodata->ime_threadmgr->AssociateFocus(hwnd, nullptr, &document_mgr)))
			{
				if (document_mgr)
				{
					document_mgr->Release();
				}
			}
		}
	}

	static void IME_UpdateInputLocale(TextInputData* videodata)
	{
		const HKL hklnext = GetKeyboardLayout(0);

		if (hklnext == videodata->ime_hkl)
		{
			return;
		}

		videodata->ime_hkl = hklnext;
		videodata->ime_candvertical = ((PRIMLANG() == LANG_KOREAN || LANG() == LANG_CHS) ? false : true);
	}

	static void IME_ClearComposition(TextInputData* videodata)
	{
		if (not videodata->ime_initialized)
		{
			return;
		}

		const HIMC himc = ::ImmGetContext(videodata->hwnd);

		if (not himc)
		{
			return;
		}

		::ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);

		{
			wchar_t emptyText[1] = { L'\n' };
			::ImmSetCompositionStringW(himc, SCS_SETSTR, emptyText, sizeof(TCHAR), emptyText, sizeof(TCHAR));
		}

		::ImmNotifyIME(himc, NI_CLOSECANDIDATE, 0, 0);
		::ImmReleaseContext(videodata->hwnd, himc);

		videodata->pTextInput->sendEditingText(String{}, 0, 0);
		videodata->pTextInput->sendCandidateState({});
	}

	static bool IME_IsTextInputShown(TextInputData* videodata)
	{
		if ((not videodata->ime_initialized)
			|| (not videodata->ime_available)
			|| (not videodata->ime_enabled))
		{
			return false;
		}

		return (videodata->ime_uicontext != 0);
	}

	static void IME_GetCompositionString(TextInputData* videodata, HIMC himc, const DWORD string)
	{
		videodata->attributes.fill(0);

		const DWORD dwLang = ((DWORD_PTR)videodata->ime_hkl & 0xffff);

		LONG length = ::ImmGetCompositionStringW(himc, string, NULL, 0);

		if ((0 < length) && (videodata->composition.size() < (length / sizeof(WCHAR))))
		{
			videodata->composition.resize(length / sizeof(WCHAR));
		}

		length = ::ImmGetCompositionStringW(himc, string, videodata->composition.data(), static_cast<DWORD>(videodata->composition.size() * sizeof(WCHAR)));

		if (length < 0)
		{
			length = 0;
		}

		length /= sizeof(WCHAR);
		videodata->ime_cursor = LOWORD(::ImmGetCompositionStringW(himc, GCS_CURSORPOS, 0, 0));
	
		if (((dwLang == LANG_CHT) || (dwLang == LANG_CHS)) &&
			(0 < videodata->ime_cursor) &&
			videodata->ime_cursor < (int)(videodata->composition.size()) &&
			((videodata->composition[0] == 0x3000) || (videodata->composition[0] == 0x0020))) {
			// Traditional Chinese IMEs add a placeholder U+3000
			// Simplified Chinese IMEs seem to add a placeholder U+0020 sometimes

			for (int i = videodata->ime_cursor + 1; i < length; ++i)
			{
				videodata->composition[i - 1] = videodata->composition[i];
			}

			--length;
		}

		videodata->composition.resize(length);

		::ImmGetCompositionStringW(himc, GCS_COMPATTR, videodata->attributes.data(), static_cast<DWORD>(videodata->attributes.size()));
	}

	static void IME_SendInputEvent(TextInputData* videodata)
	{
		videodata->pTextInput->sendInputText(Unicode::FromWstring(videodata->composition));
		videodata->pTextInput->sendEditingText(String{}, 0, 0);
		videodata->pTextInput->sendCandidateState({});

		videodata->composition.clear();
		videodata->ime_cursor = 0;
	}

	static void IME_SendEditingEvent(TextInputData* videodata, HIMC himc)
	{
		if (himc)
		{
			const int cursorPos = ImmGetCompositionStringW(himc, GCS_CURSORPOS, nullptr, 0);
	
			int targetLength = 0;

			for (const auto& attribute : videodata->attributes)
			{
				if (attribute == ATTR_TARGET_CONVERTED)
				{
					++targetLength;
				}
				else if (attribute == 0)
				{
					break;
				}
			}

			videodata->pTextInput->sendEditingText(Unicode::FromWstring(videodata->composition), cursorPos, targetLength);
		}
		else
		{
			videodata->pTextInput->sendEditingText({}, 0, 0);
			videodata->pTextInput->sendCandidateState({});
		}
	}

	static void IME_GetCandidateList(HWND hwnd, TextInputData* videodata)
	{
		HIMC himc = ::ImmGetContext(hwnd);
	
		if (not himc)
		{
			videodata->candidateState.reset();
			return;
		}
	
		DWORD size = ::ImmGetCandidateListW(himc, 0, 0, 0);
	
		if (size == 0)
		{
			videodata->candidateState.reset();
		}
		else
		{
			const LPCANDIDATELIST cand_list = (LPCANDIDATELIST)std::malloc(size);

			if (cand_list == nullptr)
			{
				videodata->candidateState.reset();
			}
			else
			{
				size = ::ImmGetCandidateListW(himc, 0, cand_list, size);

				if (size != 0)
				{
					//ClearPrint();
					//Print << U"dwSelection: " << cand_list->dwSelection;
					//Print << U"dwCount: " << cand_list->dwCount;
					//Print << U"dwPageStart: " << cand_list->dwPageStart;
					//Print << U"dwPageSize: " << cand_list->dwPageSize;

					{
						videodata->candidateState.candidates.clear();

						// 候補リストで最初からトップの要素が選択状態と表示される問題のワークアラウンド
						if (videodata->candidateState.selectedIndex || (cand_list->dwSelection != 0))
						{
							videodata->candidateState.selectedIndex = cand_list->dwSelection;
						}

						videodata->candidateState.count = cand_list->dwCount;
						videodata->candidateState.pageStartIndex = cand_list->dwPageStart;
						videodata->candidateState.pageSize = cand_list->dwPageSize;
					}

					//if ((LANG() == LANG_CHS) && IME_GetId(videodata, 0))
					//{
					//	const UINT maxcandchar = 18;
					//	size_t cchars = 0;

					//	for (i = 0; i < (UINT)videodata->candidateState.count; ++i)
					//	{
					//		size_t len = std::wcslen((LPWSTR)((DWORD_PTR)cand_list + cand_list->dwOffset[i])) + 1;
					//	
					//		if (maxcandchar < (len + cchars))
					//		{
					//			if (cand_list->dwSelection < i)
					//			{
					//				break;
					//			}

					//			page_start = i;
					//			cchars = len;
					//		}
					//		else
					//		{
					//			cchars += len;
					//		}
					//	}

					//	videodata->ime_candpgsize = (i - page_start);
					//}

					UINT k = 0;
				
					for (UINT i = cand_list->dwPageStart; ((DWORD)i < cand_list->dwCount) && (k < cand_list->dwPageSize); ++i, ++k)
					{
						const LPCWSTR candidate = (LPCWSTR)((DWORD_PTR)cand_list + cand_list->dwOffset[i]);

						videodata->candidateState.candidates.push_back(Unicode::FromWstring(candidate));
					}
				}

				std::free(cand_list);
			}
		}
	
		::ImmReleaseContext(hwnd, himc);
	}

	static void IME_HideCandidateList(TextInputData* videodata)
	{
		videodata->ime_dirty = false;
		videodata->ime_candlist = false;
		IME_SendEditingEvent(videodata, nullptr);
	}

	BOOL IME_HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM* lParam, TextInputData* videodata)
	{
		if ((not videodata->ime_initialized)
			|| (not videodata->ime_available)
			|| (not videodata->ime_enabled))
		{
			return false;
		}
	
		bool trapped = false;

		switch (msg)
		{
		case WM_KEYDOWN:
			{
				//Print << U"WM_KEYDOWN";

				if (wParam == VK_PROCESSKEY)
				{
					//Print << U"+ VK_PROCESSKEY";
					videodata->ime_uicontext = 1;
					trapped = true;
				}
				else
				{
					//Print << U"+ ";
					videodata->ime_uicontext = 0;
				}
			
				break;
			}
		case WM_INPUTLANGCHANGE:
			{
				//Print << U"WM_INPUTLANGCHANGE";
				IME_InputLangChanged(videodata);
				break;
			}
		case WM_IME_SETCONTEXT:
			{
				//Print << U"WM_IME_SETCONTEXT";
				*lParam = 0;
				break;
			}
		case WM_IME_STARTCOMPOSITION:
			{
				//Print << U"WM_IME_STARTCOMPOSITION";
				videodata->ime_suppress_endcomposition_event = false;
				trapped = true;
				break;
			}
		case WM_IME_COMPOSITION:
			{
				//Print << U"WM_IME_COMPOSITION";
				trapped = true;

				if (const HIMC himc = ::ImmGetContext(hwnd))
				{
					if (*lParam & GCS_RESULTSTR)
					{
						videodata->ime_suppress_endcomposition_event = true;

						IME_GetCompositionString(videodata, himc, GCS_RESULTSTR);					
						IME_SendInputEvent(videodata);
					}

					if (*lParam & GCS_COMPSTR)
					{
						IME_GetCompositionString(videodata, himc, GCS_COMPSTR);
						IME_SendEditingEvent(videodata, himc);
					}
				
					::ImmReleaseContext(hwnd, himc);
				}

				break;
			}
		case WM_IME_ENDCOMPOSITION:
			{
				//Print << U"WM_IME_ENDCOMPOSITION";
				videodata->ime_uicontext = 0;
				videodata->composition.clear();
				videodata->ime_cursor = 0;
			
				if (videodata->ime_suppress_endcomposition_event == false)
				{
					IME_SendEditingEvent(videodata, nullptr);
				}
			
				videodata->ime_suppress_endcomposition_event = false;
			
				break;
			}
		case WM_IME_NOTIFY:
			{
				switch (wParam)
				{
				case IMN_SETCONVERSIONMODE:
				case IMN_SETOPENSTATUS:
					{
						//Print << U"WM_IME_NOTIFY + IMN_SETCONVERSIONMODE/IMN_SETOPENSTATUS";
						IME_UpdateInputLocale(videodata);
						break;
					}
				case IMN_OPENCANDIDATE:
					{
						//Print << U"WM_IME_NOTIFY + IMN_OPENCANDIDATE";
						trapped = false;
						videodata->ime_uicontext = 1;

						IME_GetCandidateList(hwnd, videodata);
						videodata->pTextInput->sendCandidateState(videodata->candidateState);

						break;
					}
				case IMN_CHANGECANDIDATE:
					{
						//Print << U"WM_IME_NOTIFY + IMN_CHANGECANDIDATE";
						trapped = false;
						videodata->ime_uicontext = 1;
				
						IME_GetCandidateList(hwnd, videodata);
						videodata->pTextInput->sendCandidateState(videodata->candidateState);

						break;
					}
				case IMN_CLOSESTATUSWINDOW:
				case IMN_CLOSECANDIDATE:
					{
						//Print << U"WM_IME_NOTIFY + IMN_CLOSESTATUSWINDOW/IMN_CLOSECANDIDATE";
						trapped = true;
						videodata->ime_uicontext = 0;
						IME_HideCandidateList(videodata);
						break;
					}
				case IMN_PRIVATE:
					{
						//Print << U"WM_IME_NOTIFY + IMN_PRIVATE";
						const DWORD dwId = IME_GetId(videodata, 0);
				
						switch (dwId)
						{
						case IMEID_CHT_VER42:
						case IMEID_CHT_VER43:
						case IMEID_CHT_VER44:
						case IMEID_CHS_VER41:
						case IMEID_CHS_VER42:
							{
								if ((*lParam == 1) || (*lParam == 2))
								{
									trapped = true;
								}

								break;
							}
						case IMEID_CHT_VER50:
						case IMEID_CHT_VER51:
						case IMEID_CHT_VER52:
						case IMEID_CHT_VER60:
						case IMEID_CHS_VER53:
							{
								if ((*lParam == 16) || (*lParam == 17) || (*lParam == 26) || (*lParam == 27) || (*lParam == 28))
								{
									trapped = true;
								}

								break;
							}
						}

						break;
					}
				default:
					{
						//Print << U"WM_IME_NOTIFY + default";
						trapped = true;
						break;
					}
				}

				break;
			}
		}

		return trapped;
	}

	bool WIN_IsTextInputShown(TextInputData* videodata)
	{
		return IME_IsTextInputShown(videodata);
	}

	void WIN_ClearComposition(TextInputData* videodata)
	{
		IME_ClearComposition(videodata);
	}
}
