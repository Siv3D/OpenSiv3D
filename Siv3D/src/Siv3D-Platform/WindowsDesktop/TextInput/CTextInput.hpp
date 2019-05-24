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

# pragma once
# include <mutex>
# include <TextInput/ITextInput.hpp>
# include <Window/IWindow.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Stopwatch.hpp>
# include "WindowsIME.h"

namespace s3d
{
	class CTextInput : public ISiv3DTextInput
	{
	private:

		HWND m_hWnd = nullptr;

		HIMC m_hImc = nullptr;

		std::mutex m_mutex;

		Stopwatch m_deletePress;


		String m_internalEditingText;

		int32 m_internalCursorPos = 0;

		int32 m_internalTargetLength = 0;

		Array<String> m_internalCandidates;

		String m_internalChars;


		String m_editingText;

		int32 m_cursorPos = 0;

		int32 m_targetLength = 0;

		Array<String> m_candidates;

		String m_chars;
			
		
		bool m_enabled = true;

		mutable bool m_editingTextHandled = true;

		std::unique_ptr<SDL_VideoData> m_pVideo;

	public:

		CTextInput();

		~CTextInput() override;

		void init() override;

		void update() override;

		void pushChar(uint32 ch) override;

		const String& getChars() const override;

		const String& getEditingText() const override;

		void enableIME(bool enabled) override;

		std::pair<int32, int32> getCursorIndex() const override;

		const Array<String>& getCandidates() const;

		bool process(UINT msg, WPARAM wParam, LPARAM *lParam);

		void sendEditingText(const String& text, int32 cursorPos, int32 targetLength);

		void sendCandidates(const Array<String>& list);

		void sendInputText(const String& text);
	};
}
