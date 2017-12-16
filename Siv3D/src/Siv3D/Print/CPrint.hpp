﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "IPrint.hpp"
# include <Siv3D/Font.hpp>

namespace s3d
{
	class CPrint : public ISiv3DPrint
	{
	private:

		Font m_font;

		size_t m_maxLines = 6;

		int32 m_maxWidth = 640;

		int32 m_currentPosX = 0;

		Array<Array<std::pair<char32_t, int32>>> m_messageLines;

	public:

		CPrint();

		~CPrint() override;

		bool init() override;

		void add(const String& text) override;

		void draw() override;

		void clear() override;
	};
}
