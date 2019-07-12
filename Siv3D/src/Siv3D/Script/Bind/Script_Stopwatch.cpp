//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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

	static void ConstructDB(const Duration& time, bool startImmediately, BindType* self)
	{
		new(self) BindType(time, startImmediately);
	}

	static void Destruct(BindType *thisPointer)
	{
		thisPointer->~BindType();
	}

	static String FormatStopwatch(const String& format, const Stopwatch& stopwatch)
	{
		return stopwatch.format(format);
	}

	void RegisterStopwatch(asIScriptEngine *engine)
	{
		const char TypeName[] = "Stopwatch";
		int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(bool startImmediately = false)", asFUNCTION(ConstructB), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Duration& in, bool startImmediately = false)", asFUNCTION(ConstructDB), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "void start()", asMETHOD(BindType, start), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 d() const", asMETHOD(BindType, d), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 d64() const", asMETHOD(BindType, d64), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double dF() const", asMETHOD(BindType, dF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 h() const", asMETHOD(BindType, h), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 h64() const", asMETHOD(BindType, h64), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double hF() const", asMETHOD(BindType, hF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 min() const", asMETHOD(BindType, min), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 min64() const", asMETHOD(BindType, min64), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double minF() const", asMETHOD(BindType, minF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 s() const", asMETHOD(BindType, s), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 s64() const", asMETHOD(BindType, s64), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double sF() const", asMETHOD(BindType, sF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 ms() const", asMETHOD(BindType, ms), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 ms64() const", asMETHOD(BindType, ms64), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double msF() const", asMETHOD(BindType, msF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int64 us() const", asMETHOD(BindType, us), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 us64() const", asMETHOD(BindType, us64), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double usF() const", asMETHOD(BindType, usF), asCALL_THISCALL); assert(r >= 0);

	# if SIV3D_PLATFORM(WINDOWS)
		
		r = engine->RegisterObjectMethod(TypeName, "Duration elapsed() const", asMETHOD(BindType, elapsed), asCALL_THISCALL); assert(r >= 0);
	
	# else
	
		// [Siv3D ToDo]
		
	# endif
		
		r = engine->RegisterObjectMethod(TypeName, "bool isStarted() const", asMETHOD(BindType, isStarted), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isPaused() const", asMETHOD(BindType, isPaused), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isRunning() const", asMETHOD(BindType, isRunning), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pause()", asMETHOD(BindType, pause), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resume()", asMETHOD(BindType, resume), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void reset()", asMETHOD(BindType, reset), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void restart()", asMETHOD(BindType, restart), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void set(const Duration& in)", asMETHOD(BindType, set), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "String format(const String& in format = \"H:mm:ss.xx\")", asFUNCTION(FormatStopwatch), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
