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
	private:

		std::unique_ptr<PrintFont> m_font;

		std::mutex m_mutex;

		String m_text;

		Point m_pos = Point{ 10, 10 };

	public:

		CPrint();

		~CPrint() override;

		void init() override;

		void write(StringView text) override;

		void writeln(StringView text) override;

		void draw() override;

		void clear() override;

		void showUnhandledEditingText(StringView text) override;
	};
}
