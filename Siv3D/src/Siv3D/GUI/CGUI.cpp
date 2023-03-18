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

# include "CGUI.hpp"
# include <Siv3D/Step2D.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CGUI::CGUI() {}

	CGUI::~CGUI()
	{
		LOG_SCOPED_TRACE(U"CGUI::~CGUI()");
	}

	void CGUI::init()
	{
		LOG_SCOPED_TRACE(U"CGUI::init()");

		m_defaultFont = std::make_unique<Font>(FontMethod::MSDF, 20, Typeface::CJK_Regular_JP);

		if (Font::IsAvailable(Typeface::Icon_Awesome_Solid))
		{
			m_iconFonts.emplace_back(FontMethod::MSDF, 20, Typeface::Icon_Awesome_Solid);
		}

		if (Font::IsAvailable(Typeface::Icon_MaterialDesign))
		{
			m_iconFonts.emplace_back(FontMethod::MSDF, 20, Typeface::Icon_MaterialDesign);
		}

		for (const auto& iconFont : m_iconFonts)
		{
			m_defaultFont->addFallback(iconFont);
		}
	}

	const Font& CGUI::getDefaultFont() const noexcept
	{
		return *m_defaultFont;
	}

	const Texture& CGUI::getColorPickerTexture()
	{
		if (not m_colorPickerTexture)
		{
			constexpr int32 size = 49;
			constexpr Size imageSize{ size, size };
			constexpr Vec2 center{ imageSize / 2.0 };
			Image image{ imageSize };
			
			for (auto p : step(imageSize))
			{
				const Vec2 pos = p + Vec2{ 0.5, 0.5 };
				const Vec2 dir = (pos - center);
				const Circular cir(dir);
				const double h = Math::ToDegrees(cir.theta);
				const double s = (cir.r / ((size - 1) / 2.0));
				image[p] = HSV{ h, Math::Saturate(s), 1.0 };
			}

			m_colorPickerTexture = std::make_unique<Texture>(image, TextureDesc::Mipped);
		}

		return *m_colorPickerTexture;
	}
}
