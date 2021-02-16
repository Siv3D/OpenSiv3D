//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CPrint.hpp"
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/ScopedRenderStates2D.hpp>
# include <Siv3D/ScopedCustomShader2D.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static size_t CountLines(const DrawableText& drawableText, const int32 maxWidth)
		{
			const Array<double> xAdvances = drawableText.getXAdvances();
			size_t result = 1;
			double xPos = 0.0;

			for (double xAdvance : xAdvances)
			{
				if (maxWidth < (xPos + xAdvance))
				{
					++result;
					xPos = 0;
				}

				xPos += xAdvance;
			}

			return result;
		}
	}

	CPrint::CPrint()
	{
		// do nothing
	}

	CPrint::~CPrint()
	{
		LOG_SCOPED_TRACE(U"CPrint::~CPrint()");
	}

	void CPrint::init()
	{
		LOG_SCOPED_TRACE(U"CPrint::init()");

		m_font = std::make_unique<PrintFont>();
		m_font->textFont = Font{ FontMethod::MSDF, 18, Typeface::CJK_Regular_JP };
		m_font->emojiFont = Font{ FontMethod::MSDF, 18, Typeface::MonochromeEmoji };
		m_font->textFont.setBufferThickness(2);
		m_font->textFont.addFallback(m_font->emojiFont);
		m_font->ps = HLSL{ Resource(U"engine/shader/d3d11/msdfprint.ps") }
					| GLSL{ Resource(U"engine/shader/glsl/msdfprint.frag"), { { U"PSConstants2D", 0 } } }
					| ESSL{ Resource(U"engine/shader/glsl/msdfprint.frag"), { { U"PSConstants2D", 0 } } }
					| MSL{ U"PS_Shape" }; 
	}

	void CPrint::write(const String& s)
	{
		const Array<String> lines = s.split(U'\n');
		{
			std::lock_guard lock{ m_mutex };

			for (size_t i = 0; i < lines.size(); ++i)
			{
				if (i == 0)
				{
					m_lines.back().append(lines[0]);
				}
				else
				{
					m_lines.push_back(lines[i]);
				}
			}
		}
	}

	void CPrint::writeln(const String& s)
	{
		const Array<String> lines = s.split(U'\n');
		{
			std::lock_guard lock{ m_mutex };

			for (size_t i = 0; i < lines.size(); ++i)
			{
				if (i == 0)
				{
					m_lines.back().append(lines[0]);
				}
				else
				{
					m_lines.push_back(lines[i]);
				}
			}

			// 追加の改行分
			m_lines.emplace_back();
		}
	}

	void CPrint::draw()
	{
		std::lock_guard lock{ m_mutex };

		// あふれたメッセージの除去
		trimMessages();

		if ((m_lines.size() == 1)
			&& m_lines.isEmpty())
		{
			return;
		}

		// 描画
		{
			const double maxWidth = GetMaxWidth();
			const int32 fontHeight = m_font->textFont.height();
			const Point basePos{ PosOffset.x, PosOffset.y - (m_reachedMaxLines ? (fontHeight / 2 + Padding) : 0) };
			size_t lineOffset = 0;

			ScopedRenderStates2D rb{ BlendState::Default, RasterizerState::Default2D, SamplerState::Default2D };
			
			if (m_font->textFont.method() == FontMethod::Bitmap)
			{
				for (size_t i = 0; i < m_lines.size(); ++i)
				{
					const size_t layout = m_layouts[i];
					const Point pos{ basePos.x, basePos.y + (lineOffset * fontHeight) };
					const RectF area{ pos, maxWidth, 65536 };

					if (m_drawableTexts[i].text)
					{
						//m_drawableTexts[i].draw(area.movedBy(0.85, 0.85), Palette::Black);
						m_drawableTexts[i].draw(area, Palette::Yellow);
					}

					lineOffset += layout;
				}
			}
			else
			{
				ScopedCustomShader2D shader{ m_font->ps };

				for (size_t i = 0; i < m_lines.size(); ++i)
				{
					const size_t layout = m_layouts[i];
					const Point pos{ basePos.x, basePos.y + (lineOffset * fontHeight) };
					const RectF area{ pos, maxWidth, 65536 };

					if (m_drawableTexts[i].text)
					{
						m_drawableTexts[i].draw(TextStyle::CustomShader, area, Palette::White);
					}

					lineOffset += layout;
				}
			}
		}
	}

	void CPrint::clear()
	{
		std::lock_guard lock{ m_mutex };

		m_lines = { U"" };
		m_drawableTexts.clear();
		m_layouts.clear();
		m_reachedMaxLines = false;
	}

	void CPrint::setFont(const Font& font)
	{
		std::lock_guard lock{ m_mutex };

		m_font->textFont = font;

		m_lines = { U"" };
		m_drawableTexts.clear();
		m_layouts.clear();
		m_reachedMaxLines = false;
	}

	void CPrint::showUnhandledEditingText(const StringView text)
	{
		// [Siv3D ToDo]
	}

	void CPrint::trimMessages()
	{
		const size_t maxLines = getMaxLines();

		// 超過メッセージの削除
		{
			if (maxLines < m_lines.size())
			{
				m_lines.erase(m_lines.begin(), m_lines.begin() + (m_lines.size() - maxLines));
				m_reachedMaxLines = true;
			}
		}

		// 各メッセージの行数計算
		{
			m_layouts.resize(m_lines.size());
			m_drawableTexts.resize(m_lines.size());

			const int32 maxWidth = GetMaxWidth();
			for (size_t i = 0; i < m_lines.size(); ++i)
			{
				m_drawableTexts[i] = m_font->textFont(m_lines[i]);
				m_layouts[i] = detail::CountLines(m_drawableTexts[i], maxWidth);
			}
		}

		// 超過する行を含むメッセージの削除
		if (2 <= m_lines.size())
		{
			size_t num_lines = 0;

			for (int32 i = static_cast<int32>(m_layouts.size() - 1); i >= 0; --i)
			{
				const size_t count = m_layouts[i];

				if (maxLines < (num_lines + count))
				{
					const size_t dropCount = static_cast<size_t>(i + 1);
					m_lines.pop_front_N(dropCount);
					m_drawableTexts.pop_front_N(dropCount);
					m_layouts.pop_front_N(dropCount);
					m_reachedMaxLines = true;
					break;
				}

				num_lines += count;
			}
		}
		else if ((m_lines.size() == 1) && (maxLines < m_layouts.front()))
		{
			m_reachedMaxLines = true;
		}
	}

	[[nodiscard]]
	size_t CPrint::getMaxLines() const
	{
		return (static_cast<size_t>(Max((Scene::Height() - 20) / m_font->textFont.height(), 1)) + 1);
	}

	int32 CPrint::GetMaxWidth()
	{
		return Max((Scene::Width() - (Padding * 2)), 40);
	}
}
