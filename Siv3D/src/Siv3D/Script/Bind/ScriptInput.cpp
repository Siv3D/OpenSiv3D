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

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Input &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "uint8 code() const", asMETHODPR(BindType, code, () const noexcept, uint8), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint8 playerIndex() const", asMETHODPR(BindType, playerIndex, () const noexcept, uint8), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "String name() const", asMETHODPR(BindType, name, () const, String), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool down() const", asMETHODPR(BindType, down, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool pressed() const", asMETHODPR(BindType, pressed, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool up() const", asMETHODPR(BindType, up, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Duration pressedDuration() const", asMETHODPR(BindType, pressedDuration, () const, Duration), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 asUint32() const", asMETHODPR(BindType, asUint32, () const noexcept, uint32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Input& in) const", asFUNCTION(EqualsKey), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 opCmp(const Input& in) const", asFUNCTION(CompareKey), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
