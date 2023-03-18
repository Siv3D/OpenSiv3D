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

# include <Siv3D/Script.hpp>
# include <Siv3D/FontStyle.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterFontStyle(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "FontStyle";

		[[maybe_unused]] int32 r = 0;
		{
			r = engine->RegisterEnumValue(TypeName, "Default", static_cast<int32>(FontStyle::Default)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Bold", static_cast<int32>(FontStyle::Bold)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Italic", static_cast<int32>(FontStyle::Italic)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "BoldItalic", static_cast<int32>(FontStyle::BoldItalic)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Bitmap", static_cast<int32>(FontStyle::Bitmap)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "BoldBitmap", static_cast<int32>(FontStyle::BoldBitmap)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ItalicBitmap", static_cast<int32>(FontStyle::ItalicBitmap)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "BoldItalicBitmap", static_cast<int32>(FontStyle::BoldItalicBitmap)); assert(r >= 0);
		}
	}
}
