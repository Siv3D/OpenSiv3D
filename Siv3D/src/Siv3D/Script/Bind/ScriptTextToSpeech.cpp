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
# include <Siv3D/TextToSpeech.hpp>

namespace s3d
{
	using namespace AngelScript;

	static bool TextToSpeechSpeech(const String& s, LanguageCode languageCode)
	{
		return TextToSpeech::Speak(s, languageCode);
	}

	void RegisterTextToSpeech(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("TextToSpeech"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("bool HasLanguage(LanguageCode)", asFUNCTION(TextToSpeech::HasLanguage), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetDefaultLanguage(LanguageCode)", asFUNCTION(TextToSpeech::SetDefaultLanguage), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("LanguageCode GetDefaultLanguage()", asFUNCTION(TextToSpeech::GetDefaultLanguage), asCALL_CDECL); assert(r >= 0);		
			engine->RegisterGlobalFunction("bool Speak(const String& in, LanguageCode languageCode = LanguageCode::Unspecified)", asFUNCTION(TextToSpeechSpeech), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("bool IsSpeaking()", asFUNCTION(TextToSpeech::IsSpeaking), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void Pause()", asFUNCTION(TextToSpeech::Pause), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void Resume()", asFUNCTION(TextToSpeech::Resume), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetVolume(double)", asFUNCTION(TextToSpeech::SetVolume), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double GetVolume()", asFUNCTION(TextToSpeech::GetVolume), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetSpeed(double)", asFUNCTION(TextToSpeech::SetSpeed), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double GetSpeed()", asFUNCTION(TextToSpeech::GetSpeed), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
