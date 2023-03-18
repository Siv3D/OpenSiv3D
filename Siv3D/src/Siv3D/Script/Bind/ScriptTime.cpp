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
# include <Siv3D/Time.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterTime(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Time"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("uint64 GetSec()", asFUNCTION(Time::GetSec), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint64 GetMillisec()", asFUNCTION(Time::GetMillisec), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint64 GetMicrosec()", asFUNCTION(Time::GetMicrosec), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint64 GetNanosec()", asFUNCTION(Time::GetNanosec), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint64 GetSecSinceEpoch()", asFUNCTION(Time::GetSecSinceEpoch), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint64 GetMillisecSinceEpoch()", asFUNCTION(Time::GetMillisecSinceEpoch), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint64 GetMicrosecSinceEpoch()", asFUNCTION(Time::GetMicrosecSinceEpoch), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint64 UTCOffsetMinutes()", asFUNCTION(Time::UTCOffsetMinutes), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
