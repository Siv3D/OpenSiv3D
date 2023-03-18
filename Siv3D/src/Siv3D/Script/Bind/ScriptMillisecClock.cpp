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
# include <Siv3D/MillisecClock.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = MillisecClock;

	static void Construct(BindType* self)
	{
		new(self) BindType();
	}

	static void Destruct(BindType* thisPointer)
	{
		thisPointer->~BindType();
	}

	void RegisterMillisecClock(asIScriptEngine* engine)
	{
		const char TypeName[] = "MillisecClock";
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "uint64 ms() const", asMETHODPR(BindType, ms, () const noexcept, uint64), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void log() const", asMETHOD(BindType, log), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void console() const", asMETHOD(BindType, console), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void print() const", asMETHOD(BindType, print), asCALL_THISCALL); assert(r >= 0);
	}
}
