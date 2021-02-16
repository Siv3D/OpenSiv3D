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
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Print/IPrint.hpp>

namespace s3d
{
	struct PrintFont
	{
		Font textFont;
		Font emojiFont;
		PixelShader ps;
	};

	class CPrint : public ISiv3DPrint
	{
	public:

		CPrint();

		~CPrint() override;

		void init() override;

		void write(const String& s) override;

		void writeln(const String& s) override;

		void draw() override;

		void clear() override;

		void setFont(const Font& font) override;

		void showUnhandledEditingText(StringView text) override;

	private:

		static constexpr int32 Padding = 10;

		static constexpr Point PosOffset = Point::All(Padding);

		std::unique_ptr<PrintFont> m_font;

		std::mutex m_mutex;

		Array<String> m_lines = { U"" };

		Array<DrawableText> m_drawableTexts;

		Array<size_t> m_layouts;

		bool m_reachedMaxLines = false;

		void trimMessages();

		[[nodiscard]]
		size_t getMaxLines() const;

		[[nodiscard]]
		static int32 GetMaxWidth();

	};
}
