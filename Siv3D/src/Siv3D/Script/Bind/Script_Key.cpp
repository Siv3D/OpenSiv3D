//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Key.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Keyboard.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Key;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const Key& key, BindType* self)
	{
		new(self) BindType(key);
	}

	static int32 CompareKey(const Key& other, const Key& value)
	{
		const uint32 o = other.asUint32();
		const uint32 v = value.asUint32();
		return ::memcmp(&o, &v, sizeof(uint32));
	}

	void RegisterKey(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Key";

		int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Key &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(InputDevice device, uint8 code, uint8 userIndex = 0)", asFUNCTION(ConstructIII), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool down() const", asMETHOD(BindType, down), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool pressed() const", asMETHOD(BindType, pressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool up() const", asMETHOD(BindType, up), asCALL_THISCALL); assert(r >= 0);

		//[[nodiscard]] Duration pressedDuration() const;
		//[[nodiscard]] constexpr InputDevice inputDevice() const noexcept

		r = engine->RegisterObjectMethod(TypeName, "uint8 code() const", asMETHOD(BindType, code), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint8 userIndex() const", asMETHOD(BindType, userIndex), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 asUint32() const", asMETHOD(BindType, asUint32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "String name() const", asMETHOD(BindType, name), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Key& in) const", asMETHOD(BindType, operator==), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 opCmp(const Key& in) const", asFUNCTION(CompareKey), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Key MouseL", (void*)&MouseL); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key MouseR", (void*)&MouseR); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key MouseM", (void*)&MouseM); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key MouseX1", (void*)&MouseX1); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key MouseX2", (void*)&MouseX2); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key MouseX3", (void*)&MouseX3); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key MouseX4", (void*)&MouseX4); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key MouseX5", (void*)&MouseX5); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Key KeyCancel", (void*)&KeyCancel); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyBackspace", (void*)&KeyBackspace); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyTab", (void*)&KeyTab); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyClear", (void*)&KeyClear); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyEnter", (void*)&KeyEnter); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyShift", (void*)&KeyShift); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyControl", (void*)&KeyControl); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyAlt", (void*)&KeyAlt); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyPause", (void*)&KeyPause); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyEscape", (void*)&KeyEscape); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeySpace", (void*)&KeySpace); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyPageUp", (void*)&KeyPageUp); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyPageDown", (void*)&KeyPageDown); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyEnd", (void*)&KeyEnd); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyHome", (void*)&KeyHome); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Key KeyLeft", (void*)&KeyLeft); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyUp", (void*)&KeyUp); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyRight", (void*)&KeyRight); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyDown", (void*)&KeyDown); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Key KeyPrintScreen", (void*)&KeyPrintScreen); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyInsert", (void*)&KeyInsert); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyDelete", (void*)&KeyDelete); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Key Key0", (void*)&Key0); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key Key1", (void*)&Key1); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key Key2", (void*)&Key2); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key Key3", (void*)&Key3); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key Key4", (void*)&Key4); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key Key5", (void*)&Key5); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key Key6", (void*)&Key6); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key Key7", (void*)&Key7); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key Key8", (void*)&Key8); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key Key9", (void*)&Key9); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Key KeyA", (void*)&KeyA); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyB", (void*)&KeyB); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyC", (void*)&KeyC); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyD", (void*)&KeyD); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyE", (void*)&KeyE); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF", (void*)&KeyF); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyG", (void*)&KeyG); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyH", (void*)&KeyH); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyI", (void*)&KeyI); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyJ", (void*)&KeyJ); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyK", (void*)&KeyK); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyL", (void*)&KeyL); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyM", (void*)&KeyM); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyN", (void*)&KeyN); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyO", (void*)&KeyO); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyP", (void*)&KeyP); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyQ", (void*)&KeyQ); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyR", (void*)&KeyR); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyS", (void*)&KeyS); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyT", (void*)&KeyT); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyU", (void*)&KeyU); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyV", (void*)&KeyV); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyW", (void*)&KeyW); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyX", (void*)&KeyX); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyY", (void*)&KeyY); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyZ", (void*)&KeyZ); assert(r >= 0);
	
		r = engine->RegisterGlobalProperty("const Key KeyNum0", (void*)&KeyNum0); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNum1", (void*)&KeyNum1); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNum2", (void*)&KeyNum2); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNum3", (void*)&KeyNum3); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNum4", (void*)&KeyNum4); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNum5", (void*)&KeyNum5); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNum6", (void*)&KeyNum6); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNum7", (void*)&KeyNum7); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNum8", (void*)&KeyNum8); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNum9", (void*)&KeyNum9); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Key KeyNumMultiply", (void*)&KeyNumMultiply); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNumAdd", (void*)&KeyNumAdd); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNumEnter", (void*)&KeyNumEnter); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNumSubtract", (void*)&KeyNumSubtract); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNumDecimal", (void*)&KeyNumDecimal); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeKeyNumDividey", (void*)&KeyNumDivide); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Key KeyF1", (void*)&KeyF1); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF2", (void*)&KeyF2); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF3", (void*)&KeyF3); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF4", (void*)&KeyF4); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF5", (void*)&KeyF5); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF6", (void*)&KeyF6); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF7", (void*)&KeyF7); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF8", (void*)&KeyF8); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF9", (void*)&KeyF9); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF10", (void*)&KeyF10); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF11", (void*)&KeyF11); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF12", (void*)&KeyF12); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF13", (void*)&KeyF13); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF14", (void*)&KeyF14); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF15", (void*)&KeyF15); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF16", (void*)&KeyF16); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF17", (void*)&KeyF17); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF18", (void*)&KeyF18); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF19", (void*)&KeyF19); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF20", (void*)&KeyF20); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF21", (void*)&KeyF21); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF22", (void*)&KeyF22); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF23", (void*)&KeyF23); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyF24", (void*)&KeyF24); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const Key KeyNumLock", (void*)&KeyNumLock); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyLShift", (void*)&KeyLShift); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyRShift", (void*)&KeyRShift); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyLControl", (void*)&KeyLControl); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyRControl", (void*)&KeyRControl); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyLAlt", (void*)&KeyLAlt); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyRAlt", (void*)&KeyRAlt); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyNextTrack", (void*)&KeyNextTrack); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyPreviousTrack", (void*)&KeyPreviousTrack); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyStopMedia", (void*)&KeyStopMedia); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyPlayPauseMedia", (void*)&KeyPlayPauseMedia); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyColon_JP", (void*)&KeyColon_JP); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeySemicolon_US", (void*)&KeySemicolon_US); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeySemicolon_JP", (void*)&KeySemicolon_JP); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyEqual_US", (void*)&KeyEqual_US); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyComma", (void*)&KeyComma); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyMinus", (void*)&KeyMinus); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyPeriod", (void*)&KeyPeriod); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeySlash", (void*)&KeySlash); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyGraveAccent", (void*)&KeyGraveAccent); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyCommand", (void*)&KeyCommand); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyLeftCommand", (void*)&KeyLeftCommand); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyRightCommand", (void*)&KeyRightCommand); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyLBracket", (void*)&KeyLBracket); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyYen_JP", (void*)&KeyYen_JP); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyBackslash_US", (void*)&KeyBackslash_US); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyRBracket", (void*)&KeyRBracket); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyCaret_JP", (void*)&KeyCaret_JP); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyApostrophe_US", (void*)&KeyApostrophe_US); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Key KeyBackslash_JP", (void*)&KeyBackslash_JP); assert(r >= 0);
	}
}
