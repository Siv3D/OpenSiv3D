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

# include <Siv3D/ScopedRenderStates2D.hpp>
# include <Siv3D/ScopedViewport2D.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include "CPrint.hpp"

namespace s3d
{
	CPrint::CPrint()
	{

	}

	CPrint::~CPrint()
	{
		LOG_TRACE(U"CPrint::~CPrint()");
	}

	void CPrint::init()
	{
		LOG_TRACE(U"CPrint::init()");

		m_pFont = std::make_unique<Font>(16, Typeface::Medium);

		if (!*m_pFont)
		{
			throw EngineError(U"Loading Font for Print failed");
		}

		LOG_INFO(U"ℹ️ CPrint initialized");
	}

	void CPrint::add(const String& text)
	{
		std::lock_guard lock(m_mutex);

		m_maxWidth = std::max((Scene::Width() - 20), 40);
		m_maxLines = std::max((Scene::Height() - 20) / m_pFont->height(), 1) + 1;

		const Array<int32> xAdvances = (*m_pFont)(text).getXAdvances();

		m_messageLines.emplace_back();

		if (m_messageLines.size() > m_maxLines)
		{
			m_messageLines.pop_front();
		}

		m_currentPosX = 0;

		for (size_t i = 0; i < xAdvances.size(); ++i)
		{
			const char32 ch = text[i];
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
		ScopedRenderStates2D rb(BlendState::Default, RasterizerState::Default2D, SamplerState::Default2D);
		ScopedViewport2D vp(0, 0, Scene::Size());

		String text;
		{
			std::lock_guard lock(m_mutex);

			const int32 height = m_pFont->height();
			const double overflowOffset = m_messageLines.size() == m_maxLines ? -20 : 0;
			int32 lineCount = 0;

			for (const auto& messageLine : m_messageLines)
			{
				for (const auto& ch : messageLine)
				{
					text.push_back(ch.first);
				}

				const DrawableText drawText = (*m_pFont)(text);
				drawText.draw(10.85, 8.85 + lineCount * height + overflowOffset, Palette::Black);
				drawText.draw(10, 8 + lineCount * height + overflowOffset);

				text.clear();

				++lineCount;
			}
		}

		if (m_unhandledEditingtext)
		{
			const DrawableText drawText = (*m_pFont)(m_unhandledEditingtext);
			drawText.region(1, 1).draw();
			drawText.draw(1, 1, Palette::Black);
		}
	}

	void CPrint::clear()
	{
		std::lock_guard lock(m_mutex);

		m_messageLines.clear();
		m_currentPosX = 0;
	}

	void CPrint::showUnhandledEditingText(const String& text)
	{
		m_unhandledEditingtext = text;
	}
}