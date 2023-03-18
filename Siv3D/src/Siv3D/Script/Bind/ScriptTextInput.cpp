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
# include <Siv3D/TextInput.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterTextInput(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("TextInput"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("String GetRawInput()", asFUNCTION(TextInput::GetRawInput), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("size_t UpdateText(String& inout, size_t, TextInputMode mode = TextInputMode::Default)", asFUNCTIONPR(TextInput::UpdateText, (String&, size_t, TextInputMode), size_t), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void UpdateText(String& inout, TextInputMode mode = TextInputMode::Default)", asFUNCTIONPR(TextInput::UpdateText, (String&, TextInputMode), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String GetEditingText()", asFUNCTION(TextInput::GetEditingText), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
