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

# include "CPrint.hpp"
# include <Siv3D/RenderStateBlock2D.hpp>
# include <Siv3D/ViewportBlock2D.hpp>
# include <Siv3D/Window.hpp>

# include <Siv3D/Logger.hpp>

namespace s3d
{
	CPrint::CPrint()
	{

	}

	CPrint::~CPrint()
	{

	}

	bool CPrint::init()
	{
		m_font = Font(16);

		return !!m_font;
	}

	void CPrint::add(const String& text)
	{
		m_maxWidth = std::max((Window::Width() - 20), 40);
		m_maxLines = std::max((Window::Height() - 20) / m_font.height(), 1) + 1;

		const Array<int32> xAdvances = m_font(text).getXAdvances();
		const std::u32string textUTF32 = CharacterSet::ToUTF32(text);

		assert(xAdvances.size() == textUTF32.size());

		m_messageLines.emplace_back();

		if (m_messageLines.size() > m_maxLines)
		{
			m_messageLines.pop_front();
		}

		m_currentPosX = 0;

		for (size_t i = 0; i < xAdvances.size(); ++i)
		{
			const char32_t ch = textUTF32[i];
			const int32 xAdvance = xAdvances[i];

			if (ch == U'\n')
			{
				m_messageLines.emplace_back();

				if (m_messageLines.size() > m_maxLines)
				{
					m_messageLines.pop_front();
				}

				m_currentPosX = 0;
			}
			else
			{
				if (m_currentPosX + xAdvance > m_maxWidth)
				{
					m_messageLines.emplace_back();

					if (m_messageLines.size() > m_maxLines)
					{
						m_messageLines.pop_front();
					}

					m_currentPosX = 0;
				}

				m_messageLines.back().push_back({ ch, xAdvance });

				m_currentPosX += xAdvance;
			}
		}
	}

	void CPrint::draw()
	{
		RenderStateBlock2D rb(BlendState::Default, RasterizerState::Default2D, SamplerState::Default2D);
		ViewportBlock2D vp(0, 0, Window::Size());

		std::u32string text;

		const int32 height = m_font.height();
		const double overflowOffset = m_messageLines.size() == m_maxLines ? -20 : 0;
		int32 lineCount = 0;

		for (const auto& messageLine : m_messageLines)
		{
			for (const auto& ch : messageLine)
			{
				text.push_back(ch.first);
			}

			const String str = CharacterSet::FromUTF32(text);

			m_font(str).draw(10.85, 10.85 + lineCount * height + overflowOffset, Palette::Black);
			m_font(str).draw(10, 10 + lineCount * height + overflowOffset);

			text.clear();

			++lineCount;
		}
	}

	void CPrint::clear()
	{
		m_messageLines.clear();

		m_currentPosX = 0;
	}
}