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

# pragma once
# include <Siv3D/Font.hpp>
# include <Siv3D/Texture.hpp>
# include "IGUI.hpp"

namespace s3d
{
	class CGUI final : public ISiv3DGUI
	{
	private:

		std::unique_ptr<Font> m_defaultFont;

		std::unique_ptr<Texture> m_colorPickerTexture;

	public:

		CGUI();

		~CGUI() override;

		void init() override;

		const Font& getDefaultFont() const noexcept override;

		const Texture& getColorPickerTexture() override;
	};
}
