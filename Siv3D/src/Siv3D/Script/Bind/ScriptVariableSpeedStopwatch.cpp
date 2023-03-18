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
# include <Siv3D/VariableSpeedStopwatch.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = VariableSpeedStopwatch;

	static void Construct(BindType* self)
	{
		new(self) BindType();
	}

	static void ConstructB(bool startImmediately, BindType* self)
	{
		new(self) BindType(StartImmediately{ startImmediately });
	}

	static void ConstructDB(double speed, bool startImmediately, BindType* self)
	{
		new(self) BindType(speed, StartImmediately{ startImmediately });
	}

	static void ConstructDDB(const Duration& time, double speed, bool startImmediately, BindType* self)
	{
		new(self) BindType(time, speed, StartImmediately{ startImmediately });
	}

	static void Destruct(BindType* thisPointer)
	{
		thisPointer->~BindType();
	}

	static String FormatVariableSpeedStopwatch(const String& format, const VariableSpeedStopwatch& stopwatch)
	{
		return stopwatch.format(format);
	}

	static int32 CompareWithDuration(const Duration& other, const VariableSpeedStopwatch& value)
	{
		const auto e = value.elapsed();

		if (e == other)
		{
			return 0;
		}
		else if (e < other)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	void RegisterVariableSpeedStopwatch(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			const char TypeName[] = "VariableSpeedStopwatch";
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(bool startImmediately) explicit", asFUNCTION(ConstructB), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double speed, bool startImmediately = false) explicit", asFUNCTION(ConstructDB), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Duration& in, double speed = 1.0, bool startImmediately = false) explicit", asFUNCTION(ConstructDDB), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool isStarted() const", asMETHODPR(BindType, isStarted, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isPaused() const", asMETHODPR(BindType, isPaused, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isRunning() const", asMETHODPR(BindType, isRunning, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void start()", asMETHOD(BindType, start), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void pause()", asMETHOD(BindType, pause), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void resume()", asMETHOD(BindType, resume), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void reset()", asMETHOD(BindType, reset), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void restart()", asMETHOD(BindType, restart), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void set(const Duration& in)", asMETHODPR(BindType, set, (const Duration&), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void setSpeed(double speed)", asMETHODPR(BindType, setSpeed, (double), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double getSpeed() const", asMETHODPR(BindType, getSpeed, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "int32 d() const", asMETHODPR(BindType, d, () const, int32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "int64 d64() const", asMETHODPR(BindType, d64, () const, int64), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double dF() const", asMETHODPR(BindType, dF, () const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "int32 h() const", asMETHODPR(BindType, h, () const, int32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "int64 h64() const", asMETHODPR(BindType, h64, () const, int64), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double hF() const", asMETHODPR(BindType, hF, () const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "int32 min() const", asMETHODPR(BindType, min, () const, int32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "int64 min64() const", asMETHODPR(BindType, min64, () const, int64), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double minF() const", asMETHODPR(BindType, minF, () const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "int32 s() const", asMETHODPR(BindType, s, () const, int32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "int64 s64() const", asMETHODPR(BindType, s64, () const, int64), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double sF() const", asMETHODPR(BindType, sF, () const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "int32 ms() const", asMETHODPR(BindType, ms, () const, int32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "int64 ms64() const", asMETHODPR(BindType, ms64, () const, int64), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double msF() const", asMETHODPR(BindType, msF, () const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "int64 us() const", asMETHODPR(BindType, us, () const, int64), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "int64 us64() const", asMETHODPR(BindType, us64, () const, int64), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double usF() const", asMETHODPR(BindType, usF, () const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Duration elapsed() const", asMETHODPR(BindType, elapsed, () const, Duration), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "String format(const String& in format = \"H:mm:ss.xx\")", asFUNCTION(FormatVariableSpeedStopwatch), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "int32 opCmp(const Duration& in) const", asFUNCTION(CompareWithDuration), asCALL_CDECL_OBJLAST); assert(r >= 0);
		}
	}
}
