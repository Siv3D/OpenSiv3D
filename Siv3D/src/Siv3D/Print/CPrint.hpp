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
# include <Siv3D/Font.hpp>
# include <Siv3D/Window.hpp>
# include "IPrint.hpp"

namespace s3d
{
	class CPrint : public ISiv3DPrint
	{
	private:

		std::unique_ptr<Font> m_pFont;

		std::mutex m_mutex;

		size_t m_maxLines = 6;

		int32 m_maxWidth = Window::DefaultClientSize.x;

		int32 m_currentPosX = 0;

		Array<Array<std::pair<char32_t, int32>>> m_messageLines;

		String m_unhandledEditingtext;

	public:

		CPrint();

		~CPrint() override;

		void init() override;

		void add(const String& text) override;

		void draw() override;

		void clear() override;

		void showUnhandledEditingText(const String& text) override;
	};
}
