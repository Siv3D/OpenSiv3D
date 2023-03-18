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
# include <mutex>
# include <Siv3D/TextInput/ITextInput.hpp>
# include <Siv3D/Stopwatch.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class CTextInput final : public ISiv3DTextInput
	{
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
		
		const Array<String>& getCandidates() const override;
		
		//
		//	Linux
		//
		
		void onHaveMarkedText(const char* text);
		
	private:

		std::mutex m_mutex;
		
		String m_internalChars;
		
		String m_chars;
		
		
		std::mutex m_mutexMarkedText;
		
		String m_internalMarkedText;
		
		String m_markedText;
		
		bool m_haveMarkedText = false;
		
		
		Stopwatch m_enterPress;
		
		Stopwatch m_tabPress;
		
		Stopwatch m_backSpacePress;

		bool m_requestedEnablingIME = false;

		bool m_requestedDisablingIME = false;
		
		static void OnCharacterInput(uint32 codePoint);
	};
}
