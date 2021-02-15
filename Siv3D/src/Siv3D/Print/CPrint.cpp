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
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/ScopedCustomShader2D.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
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

	void CPrint::write(const StringView text)
	{
		std::lock_guard lock{ m_mutex };

		m_text.append(text);
	}

	void CPrint::writeln(const StringView text)
	{
		std::lock_guard lock{ m_mutex };

		m_text.append(text);
		m_text.push_back('\n');
	}

	void CPrint::draw()
	{
		ScopedCustomShader2D shader{ m_font->ps };
		{
			std::lock_guard lock{ m_mutex };
			m_font->textFont(m_text)
				.draw(TextStyle::CustomShader, m_pos);
		}
	}

	void CPrint::clear()
	{
		std::lock_guard lock{ m_mutex };

		m_text.clear();
	}

	void CPrint::showUnhandledEditingText(const StringView text)
	{

	}
}
