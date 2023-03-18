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
# include <Siv3D/LanguageCode.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterLanguageCode(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		constexpr char TypeName[] = "LanguageCode";

		{
			r = engine->RegisterEnumValue(TypeName, "ArabicSA", static_cast<int32>(LanguageCode::ArabicSA)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ChineseCN", static_cast<int32>(LanguageCode::ChineseCN)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ChineseHK", static_cast<int32>(LanguageCode::ChineseHK)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ChineseTW", static_cast<int32>(LanguageCode::ChineseTW)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "EnglishAU", static_cast<int32>(LanguageCode::EnglishAU)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "EnglishGB", static_cast<int32>(LanguageCode::EnglishGB)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "EnglishUS", static_cast<int32>(LanguageCode::EnglishUS)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "FrenchFR", static_cast<int32>(LanguageCode::FrenchFR)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "GermanDE", static_cast<int32>(LanguageCode::GermanDE)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "HindiIN", static_cast<int32>(LanguageCode::HindiIN)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ItalianIT", static_cast<int32>(LanguageCode::ItalianIT)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Japanese", static_cast<int32>(LanguageCode::Japanese)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Korean", static_cast<int32>(LanguageCode::Korean)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "PortugueseBR", static_cast<int32>(LanguageCode::PortugueseBR)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "RussianRU", static_cast<int32>(LanguageCode::RussianRU)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "SpanishES", static_cast<int32>(LanguageCode::SpanishES)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Unspecified", static_cast<int32>(LanguageCode::Unspecified)); assert(r >= 0);
		}
	}
}
