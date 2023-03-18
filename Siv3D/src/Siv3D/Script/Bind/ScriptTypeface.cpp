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
# include <Siv3D/Typeface.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterTypeface(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "Typeface";
			r = engine->RegisterEnumValue(TypeName, "CJK_Regular_JP", static_cast<int32>(Typeface::CJK_Regular_JP)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "CJK_Regular_KR", static_cast<int32>(Typeface::CJK_Regular_KR)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "CJK_Regular_SC", static_cast<int32>(Typeface::CJK_Regular_SC)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "CJK_Regular_TC", static_cast<int32>(Typeface::CJK_Regular_TC)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "CJK_Regular_HK", static_cast<int32>(Typeface::CJK_Regular_HK)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "MonochromeEmoji", static_cast<int32>(Typeface::MonochromeEmoji)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ColorEmoji", static_cast<int32>(Typeface::ColorEmoji)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Mplus_Thin", static_cast<int32>(Typeface::Mplus_Thin)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Mplus_Light", static_cast<int32>(Typeface::Mplus_Light)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Mplus_Regular", static_cast<int32>(Typeface::Mplus_Regular)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Mplus_Medium", static_cast<int32>(Typeface::Mplus_Medium)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Mplus_Bold", static_cast<int32>(Typeface::Mplus_Bold)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Mplus_Heavy", static_cast<int32>(Typeface::Mplus_Heavy)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Mplus_Black", static_cast<int32>(Typeface::Mplus_Black)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Icon_Awesome_Solid", static_cast<int32>(Typeface::Icon_Awesome_Solid)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Icon_Awesome_Brand", static_cast<int32>(Typeface::Icon_Awesome_Brand)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Icon_MaterialDesign", static_cast<int32>(Typeface::Icon_MaterialDesign)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Thin", static_cast<int32>(Typeface::Thin)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Light", static_cast<int32>(Typeface::Light)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Regular", static_cast<int32>(Typeface::Regular)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Medium", static_cast<int32>(Typeface::Medium)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Bold", static_cast<int32>(Typeface::Bold)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Heavy", static_cast<int32>(Typeface::Heavy)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Black", static_cast<int32>(Typeface::Black)); assert(r >= 0);
		}
	}
}
