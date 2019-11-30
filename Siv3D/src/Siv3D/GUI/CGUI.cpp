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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Step2D.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/HSV.hpp>
# include "CGUI.hpp"

namespace s3d
{
	CGUI::CGUI()
	{

	}

	CGUI::~CGUI()
	{
		LOG_TRACE(U"CGUI::~CGUI()");
	}

	void CGUI::init()
	{
		LOG_TRACE(U"CGUI::init()");

		m_defaultGUIFont = std::make_unique<Font>(20, Typeface::Medium);

		LOG_INFO(U"ℹ️ CGUI initialized");
	}

	const Font& CGUI::getDefaultGUIFont()
	{
		return *m_defaultGUIFont;
	}

	const Texture& CGUI::getColorPickerTexture()
	{
		if (!m_colorPickerTexture)
		{
			constexpr int32 size = 49;
			constexpr Size imageSize(size, size);
			Image image(imageSize);
			for (auto p : step(imageSize))
			{
				const Vec2 pos = p + Vec2(0.5, 0.5);
				const Vec2 center = imageSize / 2;
				const Vec2 dir = (pos - center);
				const Circular cir(dir);
				const double h = Math::ToDegrees(cir.theta);
				const double s = (cir.r / ((size - 1) / 2.0));
				image[p] = HSV(h, Saturate(s), 1.0);
			}

			m_colorPickerTexture = std::make_unique<Texture>(image, TextureDesc::Mipped);
		}

		return *m_colorPickerTexture;
	}
}
