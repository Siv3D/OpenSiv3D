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
# include <string>
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DTextInput
	{
	public:

		static ISiv3DTextInput* Create();

		virtual ~ISiv3DTextInput() = default;

		virtual bool init() = 0;

		virtual void update() = 0;

		virtual void pushChar(char32_t ch) = 0;

		virtual const std::u32string& getChars() const = 0;
		
		virtual const String& getMarkedText() const = 0;
	};
}
