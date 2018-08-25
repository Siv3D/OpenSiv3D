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
# include <Siv3D/Periodic.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterPeriodic(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("Time"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("uint64 GetMicrosec()", asFUNCTION(Time::GetMicrosec), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->SetDefaultNamespace("Periodic"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("double Sine0_1(double, double = Time::GetMicrosec() / 1000000.0)", asFUNCTIONPR(Periodic::Sine0_1, (double, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Square0_1(double, double = Time::GetMicrosec() / 1000000.0)", asFUNCTIONPR(Periodic::Square0_1, (double, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Tringle0_1(double, double = Time::GetMicrosec() / 1000000.0)", asFUNCTIONPR(Periodic::Tringle0_1, (double, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Sawtooth0_1(double, double = Time::GetMicrosec() / 1000000.0)", asFUNCTIONPR(Periodic::Sawtooth0_1, (double, double), double), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
