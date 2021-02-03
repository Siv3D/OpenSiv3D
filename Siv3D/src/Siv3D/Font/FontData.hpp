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
# include <Siv3D/Common.hpp>
# include <Siv3D/StringView.hpp>
# include "FontResourceHolder.hpp"
# include "FontFace.hpp"

namespace s3d
{
	class FontData
	{
	public:

		struct Null {};

		FontData() = default;

		explicit FontData(Null);

		FontData(FT_Library library, FilePathView path, int32 fontSize, FontStyle style);

		~FontData();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		const FontFaceProperty& getProperty() const noexcept;

		[[nodiscard]]
		bool hasGlyph(StringView ch);

		[[nodiscard]]
		GlyphInfo getGlyphInfo(StringView ch);

		[[nodiscard]]
		GlyphOutline getGlyphOutline(StringView ch);

		[[nodiscard]]
		Array<GlyphOutline> getGlyphOutlines(StringView s);

	private:

	# if SIV3D_PLATFORM(WINDOWS)

		FontResourceHolder m_resource;

	# endif

		FontFace m_fontFace;

		bool m_initialized = false;
	};
}
