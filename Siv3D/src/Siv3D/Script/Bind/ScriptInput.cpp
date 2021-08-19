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

# include <Siv3D/Script.hpp>
# include <Siv3D/InputGroups.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Input;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const Input& key, BindType* self)
	{
		new(self) BindType(key);
	}

	static int32 EqualsKey(const Input& other, const Input& value)
	{
		return (value == other);
	}

	static int32 CompareKey(const Input& other, const Input& value)
	{
		const uint32 o = other.asUint32();
		const uint32 v = value.asUint32();
		return ::memcmp(&v, &o, sizeof(uint32));
	}

	void RegisterInput(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Input";

		int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Input &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "uint8 code() const", asMETHOD(BindType, code), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint8 playerIndex() const", asMETHOD(BindType, playerIndex), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "String name() const", asMETHOD(BindType, name), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool down() const", asMETHOD(BindType, down), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool pressed() const", asMETHOD(BindType, pressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool up() const", asMETHOD(BindType, up), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Duration pressedDuration() const", asMETHOD(BindType, pressedDuration), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint8 asUint32() const", asMETHOD(BindType, asUint32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Input& in) const", asFUNCTION(EqualsKey), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 opCmp(const Input& in) const", asFUNCTION(CompareKey), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
