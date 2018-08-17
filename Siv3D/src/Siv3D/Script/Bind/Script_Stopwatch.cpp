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
# include <Siv3D/Stopwatch.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Stopwatch;

	static void ConstructB(bool startImmediately, BindType* self)
	{
		new(self) BindType(startImmediately);
	}

	static void Destruct(BindType *thisPointer)
	{
		thisPointer->~BindType();
	}

	void RegisterStopwatch(asIScriptEngine *engine)
	{
		const char TypeName[] = "Stopwatch";
		int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(bool startImmediately = false)", asFUNCTION(ConstructB), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 ms() const", asMETHOD(BindType, ms), asCALL_THISCALL); assert(r >= 0);
	}
}
