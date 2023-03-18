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
# include <Siv3D/Timer.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Timer;

	static void Construct(BindType* self)
	{
		new(self) BindType();
	}

	static void ConstructDuB(const Duration& time, bool startImmediately, BindType* self)
	{
		new(self) BindType(time, StartImmediately{ startImmediately });
	}

	static void Destruct(BindType* thisPointer)
	{
		thisPointer->~BindType();
	}

	static String FormatTimer(const String& format, const Timer& timer)
	{
		return timer.format(format);
	}

	static int32 CompareWithDuration(const Duration& other, const Timer& value)
	{
		const auto e = value.remaining();

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

	void RegisterTimer(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			const char TypeName[] = "Timer";
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Duration& in, bool startImmediately = false) explicit", asFUNCTION(ConstructDuB), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool isStarted() const", asMETHODPR(BindType, isStarted, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isPaused() const", asMETHODPR(BindType, isPaused, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isRunning() const", asMETHODPR(BindType, isRunning, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool reachedZero() const", asMETHODPR(BindType, reachedZero, () const, bool), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void start()", asMETHOD(BindType, start), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void pause()", asMETHOD(BindType, pause), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void resume()", asMETHOD(BindType, resume), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void reset()", asMETHOD(BindType, reset), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void restart()", asMETHODPR(BindType, restart, (), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void restart(const Duration& in)", asMETHODPR(BindType, restart, (const Duration&), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void set(const Duration& in)", asMETHODPR(BindType, set, (const Duration&), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void setRemaining(const Duration& in)", asMETHODPR(BindType, setRemaining, (const Duration&), void), asCALL_THISCALL); assert(r >= 0);

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
			r = engine->RegisterObjectMethod(TypeName, "Duration duration() const", asMETHODPR(BindType, duration, () const, Duration), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Duration remaining() const", asMETHODPR(BindType, remaining, () const, Duration), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double progress1_0() const", asMETHODPR(BindType, progress1_0, () const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double progress0_1() const", asMETHODPR(BindType, progress0_1, () const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "String format(const String& in format = \"H:mm:ss.xx\")", asFUNCTION(FormatTimer), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "int32 opCmp(const Duration& in) const", asFUNCTION(CompareWithDuration), asCALL_CDECL_OBJLAST); assert(r >= 0);
		}
	}
}
