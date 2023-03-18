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
# include <Siv3D/Duration.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Duration;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType(0.0);
	}

	static void CopyConstruct(const BindType& duration, BindType* self)
	{
		new(self) BindType(duration);
	}

	static void ConstructD(double sec, BindType* self)
	{
		new(self) BindType(sec);
	}

	static Duration DurationHours(double x) noexcept
	{
		return HoursF{ x };
	}

	static Duration DurationMinutes(double x) noexcept
	{
		return MinutesF{ x };
	}

	static Duration DurationSeconds(double x) noexcept
	{
		return SecondsF{ x };
	}

	static Duration DurationMilliseconds(double x) noexcept
	{
		return MillisecondsF{ x };
	}

	static Duration DurationMicroseconds(double x) noexcept
	{
		return MicrosecondsF{ x };
	}

	static Duration DurationNanoseconds(double x) noexcept
	{
		return NanosecondsF{ x };
	}

	void RegisterDuration(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		{
			constexpr char TypeName[] = "Duration";
			r = engine->RegisterObjectProperty(TypeName, "double _rep", 0); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Duration &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double) explicit", asFUNCTION(ConstructD), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double count() const", asMETHODPR(BindType, count, () const, double), asCALL_THISCALL); assert(r >= 0);
		}

		r = engine->RegisterGlobalFunction("Duration _h(double)", asFUNCTION(DurationHours), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration _min(double)", asFUNCTION(DurationMinutes), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration _s(double)", asFUNCTION(DurationSeconds), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration _ms(double)", asFUNCTION(DurationMilliseconds), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration _us(double)", asFUNCTION(DurationMicroseconds), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration _ns(double)", asFUNCTION(DurationNanoseconds), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Duration HoursF(double)", asFUNCTION(DurationHours), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration MinutesF(double)", asFUNCTION(DurationMinutes), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration SecondsF(double)", asFUNCTION(DurationSeconds), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration MillisecondsF(double)", asFUNCTION(DurationMilliseconds), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration MicrosecondsF(double)", asFUNCTION(DurationMicroseconds), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration NanosecondsF(double)", asFUNCTION(DurationNanoseconds), asCALL_CDECL); assert(r >= 0);
	}
}
