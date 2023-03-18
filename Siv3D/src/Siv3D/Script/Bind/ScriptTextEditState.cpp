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
# include <Siv3D/TextEditState.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = TextEditState;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

# if not SIV3D_PLATFORM(WEB)

	static void CopyConstruct(const TextEditState& other, BindType* self)
	{
		new(self) BindType(other);
	}

# endif

	static void ConstructS(const String& defaultText, BindType* self)
	{
		new(self) BindType(defaultText);
	}

	static void Destruct(BindType* self)
	{
		self->~TextEditState();
	}

	void RegisterTextEditState(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "TextEditState";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "String text", asOFFSET(BindType, text)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "size_t cursorPos", asOFFSET(BindType, cursorPos)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "bool active", asOFFSET(BindType, active)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "bool textChanged", asOFFSET(BindType, textChanged)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "bool tabKey", asOFFSET(BindType, tabKey)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "bool enterKey", asOFFSET(BindType, enterKey)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Stopwatch leftPressStopwatch", asOFFSET(BindType, leftPressStopwatch)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Stopwatch rightPressStopwatch", asOFFSET(BindType, rightPressStopwatch)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Stopwatch cursorStopwatch", asOFFSET(BindType, cursorStopwatch)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
	
# if not SIV3D_PLATFORM(WEB)
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TextEditState& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
# endif

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in) explicit", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void clear() const", asMETHOD(BindType, clear), asCALL_THISCALL); assert(r >= 0);

	}
}
