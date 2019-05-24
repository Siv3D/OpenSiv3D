//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/TextToSpeech.hpp>
# include "ScriptBind.hpp"
# include "../../Siv3DEngine.hpp"
# include "../IScript.hpp"

namespace s3d
{
	using namespace AngelScript;

	static bool Speak(const String& text, int32 languageCode)
	{
		return TextToSpeech::Speak(text, languageCode);
	}

	void RegisterTextToSpeech(asIScriptEngine *engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("LanguageCode"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const int32 ArabicSA", (void*)&LanguageCode::ArabicSA); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 ChineseCN", (void*)&LanguageCode::ChineseCN); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 ChineseHK", (void*)&LanguageCode::ChineseHK); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 ChineseTW", (void*)&LanguageCode::ChineseTW); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 EnglishAU", (void*)&LanguageCode::EnglishAU); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 EnglishGB", (void*)&LanguageCode::EnglishGB); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 EnglishUS", (void*)&LanguageCode::EnglishUS); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 FrenchFR", (void*)&LanguageCode::FrenchFR); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 GermanDE", (void*)&LanguageCode::GermanDE); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 HindiIN", (void*)&LanguageCode::HindiIN); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 ItalianIT", (void*)&LanguageCode::ItalianIT); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 Japanese", (void*)&LanguageCode::Japanese); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 Korean", (void*)&LanguageCode::Korean); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 PortugueseBR", (void*)&LanguageCode::PortugueseBR); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 RussianRU", (void*)&LanguageCode::RussianRU); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 SpanishES", (void*)&LanguageCode::SpanishES); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const int32 Unspecified", (void*)&LanguageCode::Unspecified); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->SetDefaultNamespace("TextToSpeech"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("bool HasLanguage(int32)", asFUNCTION(TextToSpeech::HasLanguage), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetDefaultLanguage(int32)", asFUNCTION(TextToSpeech::SetDefaultLanguage), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("int32 GetDefaultLanguage()", asFUNCTION(TextToSpeech::GetDefaultLanguage), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("bool Speak(const String& in, int32 languageCode = LanguageCode::Unspecified)", asFUNCTION(Speak), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("bool IsSpeaking()", asFUNCTION(TextToSpeech::IsSpeaking), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void Pause()", asFUNCTION(TextToSpeech::Pause), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void Resume()", asFUNCTION(TextToSpeech::Resume), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetVolume(double)", asFUNCTION(TextToSpeech::SetVolume), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double GetVolume()", asFUNCTION(TextToSpeech::GetVolume), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetSpeed(double)", asFUNCTION(TextToSpeech::SetSpeed), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double GetSpeed(int32)", asFUNCTION(TextToSpeech::GetSpeed), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
