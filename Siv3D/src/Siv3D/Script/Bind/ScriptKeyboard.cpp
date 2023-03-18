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
# include <Siv3D/Keyboard.hpp>
# include "../angelscript/scriptarray.h"

namespace s3d
{
	using namespace AngelScript;

	static const CScriptArray* KeyboardGetAllInputs()
	{
		const auto& inputs = Keyboard::GetAllInputs();

		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Array<Input>");

		if (void* mem = std::malloc(inputs.size_bytes() + sizeof(asUINT)))
		{
			*(asUINT*)mem = static_cast<asUINT>(inputs.size());
			std::memcpy(((asUINT*)mem) + 1, inputs.data(), inputs.size_bytes());

			const auto p = CScriptArray::Create(typeID, mem);
			std::free(mem);

			return p;
		}
		else
		{
			return nullptr;
		}
	}

	void RegisterKeyboard(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Keyboard"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("Array<Input>@ GetAllInputs()", asFUNCTION(KeyboardGetAllInputs), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Input KeyCancel", (void*)&KeyCancel); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyBackspace", (void*)&KeyBackspace); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyTab", (void*)&KeyTab); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyClear", (void*)&KeyClear); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyEnter", (void*)&KeyEnter); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyShift", (void*)&KeyShift); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyControl", (void*)&KeyControl); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyAlt", (void*)&KeyAlt); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyPause", (void*)&KeyPause); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyEscape", (void*)&KeyEscape); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeySpace", (void*)&KeySpace); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyPageUp", (void*)&KeyPageUp); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyPageDown", (void*)&KeyPageDown); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyEnd", (void*)&KeyEnd); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyHome", (void*)&KeyHome); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Input KeyLeft", (void*)&KeyLeft); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyUp", (void*)&KeyUp); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyRight", (void*)&KeyRight); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyDown", (void*)&KeyDown); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Input KeyPrintScreen", (void*)&KeyPrintScreen); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyInsert", (void*)&KeyInsert); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyDelete", (void*)&KeyDelete); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Input Key0", (void*)&Key0); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input Key1", (void*)&Key1); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input Key2", (void*)&Key2); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input Key3", (void*)&Key3); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input Key4", (void*)&Key4); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input Key5", (void*)&Key5); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input Key6", (void*)&Key6); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input Key7", (void*)&Key7); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input Key8", (void*)&Key8); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input Key9", (void*)&Key9); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Input KeyA", (void*)&KeyA); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyB", (void*)&KeyB); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyC", (void*)&KeyC); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyD", (void*)&KeyD); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyE", (void*)&KeyE); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF", (void*)&KeyF); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyG", (void*)&KeyG); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyH", (void*)&KeyH); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyI", (void*)&KeyI); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyJ", (void*)&KeyJ); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyK", (void*)&KeyK); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyL", (void*)&KeyL); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyM", (void*)&KeyM); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyN", (void*)&KeyN); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyO", (void*)&KeyO); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyP", (void*)&KeyP); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyQ", (void*)&KeyQ); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyR", (void*)&KeyR); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyS", (void*)&KeyS); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyT", (void*)&KeyT); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyU", (void*)&KeyU); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyV", (void*)&KeyV); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyW", (void*)&KeyW); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyX", (void*)&KeyX); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyY", (void*)&KeyY); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyZ", (void*)&KeyZ); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Input KeyNum0", (void*)&KeyNum0); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNum1", (void*)&KeyNum1); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNum2", (void*)&KeyNum2); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNum3", (void*)&KeyNum3); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNum4", (void*)&KeyNum4); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNum5", (void*)&KeyNum5); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNum6", (void*)&KeyNum6); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNum7", (void*)&KeyNum7); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNum8", (void*)&KeyNum8); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNum9", (void*)&KeyNum9); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Input KeyNumMultiply", (void*)&KeyNumMultiply); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNumAdd", (void*)&KeyNumAdd); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNumEnter", (void*)&KeyNumEnter); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNumSubtract", (void*)&KeyNumSubtract); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNumDecimal", (void*)&KeyNumDecimal); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeKeyNumDividey", (void*)&KeyNumDivide); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Input KeyF1", (void*)&KeyF1); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF2", (void*)&KeyF2); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF3", (void*)&KeyF3); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF4", (void*)&KeyF4); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF5", (void*)&KeyF5); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF6", (void*)&KeyF6); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF7", (void*)&KeyF7); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF8", (void*)&KeyF8); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF9", (void*)&KeyF9); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF10", (void*)&KeyF10); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF11", (void*)&KeyF11); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF12", (void*)&KeyF12); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF13", (void*)&KeyF13); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF14", (void*)&KeyF14); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF15", (void*)&KeyF15); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF16", (void*)&KeyF16); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF17", (void*)&KeyF17); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF18", (void*)&KeyF18); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF19", (void*)&KeyF19); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF20", (void*)&KeyF20); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF21", (void*)&KeyF21); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF22", (void*)&KeyF22); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF23", (void*)&KeyF23); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyF24", (void*)&KeyF24); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Input KeyNumLock", (void*)&KeyNumLock); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyLShift", (void*)&KeyLShift); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyRShift", (void*)&KeyRShift); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyLControl", (void*)&KeyLControl); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyRControl", (void*)&KeyRControl); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyLAlt", (void*)&KeyLAlt); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyRAlt", (void*)&KeyRAlt); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyNextTrack", (void*)&KeyNextTrack); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyPreviousTrack", (void*)&KeyPreviousTrack); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyStopMedia", (void*)&KeyStopMedia); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyPlayPauseMedia", (void*)&KeyPlayPauseMedia); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyColon_JIS", (void*)&KeyColon_JIS); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeySemicolon_US", (void*)&KeySemicolon_US); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeySemicolon_JIS", (void*)&KeySemicolon_JIS); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyEqual_US", (void*)&KeyEqual_US); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyComma", (void*)&KeyComma); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyMinus", (void*)&KeyMinus); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyPeriod", (void*)&KeyPeriod); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeySlash", (void*)&KeySlash); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyGraveAccent", (void*)&KeyGraveAccent); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyCommand", (void*)&KeyCommand); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyLeftCommand", (void*)&KeyLeftCommand); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyRightCommand", (void*)&KeyRightCommand); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyLBracket", (void*)&KeyLBracket); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyYen_JIS", (void*)&KeyYen_JIS); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyBackslash_US", (void*)&KeyBackslash_US); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyRBracket", (void*)&KeyRBracket); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyCaret_JIS", (void*)&KeyCaret_JIS); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyApostrophe_US", (void*)&KeyApostrophe_US); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input KeyUnderscore_JIS", (void*)&KeyUnderscore_JIS); assert(r >= 0);
	}
}
