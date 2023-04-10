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
# include "Common.hpp"
# include "Stopwatch.hpp"
# include "String.hpp"
# include "Glyph.hpp"
# include "Shape2D.hpp"

namespace s3d
{

	/// @brief テキストエリアの編集情報 | Text area editing information
	struct TextAreaEditState
	{
		/// @brief テキスト | Text
		String text;

		size_t cursorPos = 0;

		double scrollY = 0.0;

		bool refreshScroll = false;

		bool active = false;

		bool textChanged = false;

		Stopwatch leftPressStopwatch, rightPressStopwatch, cursorStopwatch;

		Stopwatch upPressStopwatch, downPressStopwatch;

		Array<Glyph> glyphs;

		Array<std::pair<uint16, uint16>> glyphPositions;

		struct ClipInfo
		{
			Vec2 pos;

			RectF clipRect;

			uint32 index = 0;

			bool isEndOfLine = false;

			bool isLastLine = false;
		};

		Array<ClipInfo> clipInfos;

		SIV3D_NODISCARD_CXX20
		TextAreaEditState() = default;

		SIV3D_NODISCARD_CXX20
		explicit TextAreaEditState(const String& defaultText);

		SIV3D_NODISCARD_CXX20
		explicit TextAreaEditState(String&& defaultText) noexcept;

		void clear() noexcept;

		void resetStopwatches() noexcept;

		void rebuildGlyphs();
	};
}
