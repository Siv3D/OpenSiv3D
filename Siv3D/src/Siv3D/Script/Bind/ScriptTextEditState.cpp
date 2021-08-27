//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp> // FIXME

namespace s3d
{
	using namespace AngelScript;

	using BindType = TextEditState;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const TextEditState& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructS(const String& defaultText, BindType* self)
	{
		new(self) BindType(defaultText);
	}

	static void Destruct(BindType* self)
	{
		self->~TextEditState();
	}

	static bool TextBox(TextEditState& text, const Vec2& pos, double width, size_t maxChars, bool enabled) // FIXME ->ScriptSimpleGUI.cpp
	{
		Optional<size_t> d = (maxChars > 0) ? (Optional<size_t>)maxChars : unspecified;
		return SimpleGUI::TextBox(text, pos, width, d, enabled);
	}

	static bool TextBoxAt(TextEditState& text, const Vec2& center, double width, size_t maxChars, bool enabled) // FIXME ->ScriptSimpleGUI.cpp
	{
		Optional<size_t> d = (maxChars > 0) ? (Optional<size_t>)maxChars : unspecified;
		return SimpleGUI::TextBoxAt(text, center, width, d, enabled);
	}

	void RegisterTextEditState(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "TextEditState";

		int32 r = 0;
		r = engine->RegisterObjectType("TextEditState", sizeof(TextEditState), asOBJ_VALUE | asGetTypeTraits<TextEditState>()); assert(r >= 0); // FIXME ->ScriptTypes.cpp

		r = engine->RegisterObjectProperty(TypeName, "String text", asOFFSET(BindType, text)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "size_t cursorPos", asOFFSET(BindType, cursorPos)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "bool active", asOFFSET(BindType, active)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Stopwatch leftPressStopwatch", asOFFSET(BindType, leftPressStopwatch)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Stopwatch rightPressStopwatch", asOFFSET(BindType, rightPressStopwatch)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Stopwatch cursorStopwatch", asOFFSET(BindType, cursorStopwatch)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TextEditState& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void clear() const", asMETHOD(BindType, clear), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace("SimpleGUI"); assert(r >= 0); // FIXME ->ScriptSimpleGUI.cpp
		{
			r = engine->RegisterGlobalFunction("bool TextBox(TextEditState&, const Vec2&in, double = 200.0, size_t = 0, bool = true)", asFUNCTION(TextBox), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool TextBoxAt(TextEditState&, const Vec2&in, double = 200.0, size_t = 0, bool = true)", asFUNCTION(TextBoxAt), asCALL_CDECL); assert(r >= 0);
		}
	}
}
