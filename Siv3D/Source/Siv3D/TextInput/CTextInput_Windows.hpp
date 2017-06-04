//-----------------------------------------------
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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <mutex>
# include "ITextInput.hpp"
# include <Siv3D/String.hpp>

namespace s3d
{
	class CTextInput_Windows : public ISiv3DTextInput
	{
	private:

		std::mutex m_mutex;

		String m_internalChars;

		std::u32string m_chars;

	public:

		CTextInput_Windows();

		~CTextInput_Windows() override;

		bool init() override;

		void update() override;

		void pushChar(char32_t ch) override;

		const std::u32string& getChars() const override;
	};
}

# endif
