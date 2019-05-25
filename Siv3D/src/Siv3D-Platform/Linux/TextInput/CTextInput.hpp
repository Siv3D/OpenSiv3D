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
# include <Window/IWindow.hpp>
# include <TextInput/ITextInput.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Stopwatch.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

namespace s3d
{
	class CTextInput : public ISiv3DTextInput
	{
	private:

		std::mutex m_mutex;
		
		std::u16string m_internalChars;
		
		String m_chars;
		
		
		std::mutex m_mutexMarkedText;
		
		String m_internalMarkedText;
		
		String m_markedText;
		
		bool m_haveMarkedText = false;
		
		
		Stopwatch m_enterPress;
		
		Stopwatch m_tabPress;
		
		Stopwatch m_backSpacePress;
		
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
		
		static void OnCharacterInput(GLFWwindow*, uint32 codePoint);
		
		void onHaveMarkedText(const char* text);
	};
}
