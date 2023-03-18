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
# include <Siv3D/Common.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Font.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DPrint
	{
	public:

		static ISiv3DPrint* Create();

		virtual ~ISiv3DPrint() = default;

		virtual void init() = 0;

		virtual void write(const String& s) = 0;

		virtual void writeln(const String& s) = 0;

		virtual void put(String&& s, const Vec2& pos, int32 alignment) = 0;

		virtual void draw() = 0;

		virtual void clear() = 0;

		virtual void setFont(const Font& font) = 0;

		virtual const Font& getFont() const = 0;

		virtual void showUnhandledEditingText(StringView text) = 0;
	};
}
