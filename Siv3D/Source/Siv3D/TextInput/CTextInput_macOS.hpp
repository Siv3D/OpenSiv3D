//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <mutex>
# include "../Window/IWindow.hpp"
# include "ITextInput.hpp"
# include <Siv3D/String.hpp>

namespace s3d
{
	class CTextInput_macOS : public ISiv3DTextInput
	{
	private:
		
		std::mutex m_mutex;
		
		std::u16string m_internalChars;

		std::u32string m_chars;
		
		
		std::mutex m_mutexMarkedText;
		
		String m_internalMarkedText;
		
		String m_markedText;
		
		bool m_haveMarkedText = false;

	public:

		CTextInput_macOS();

		~CTextInput_macOS() override;

		bool init() override;

		void update() override;

		void pushChar(char32_t ch) override;

		const std::u32string& getChars() const override;
		
		const String& getMarkedText() const override;
		
		static void OnCharacterInput(WindowHandle, uint32 codePoint);
		
		void onHaveMarkedText(const char* text);
	};
}

# endif
