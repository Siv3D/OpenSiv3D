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
# include <Siv3D/Font.hpp>
# include <Siv3D/Texture.hpp>
# include "IGUI.hpp"

namespace s3d
{
	class CGUI final : public ISiv3DGUI
	{
	public:

		CGUI();

		~CGUI() override;

		void init() override;

		const Font& getDefaultFont() const noexcept override;

		const Texture& getColorPickerTexture() override;

	private:

		std::unique_ptr<Font> m_defaultFont;

		Array<Font> m_iconFonts;

		std::unique_ptr<Texture> m_colorPickerTexture;
	};
}
