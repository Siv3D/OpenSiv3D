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
# include <Siv3D/Number.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterNumber(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterGlobalFunction("bool IsNaN(float)", asFUNCTIONPR(IsNaN, (float), bool), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsNaN(double)", asFUNCTIONPR(IsNaN, (double), bool), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("bool IsFinite(float)", asFUNCTIONPR(IsFinite, (float), bool), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsFinite(double)", asFUNCTIONPR(IsFinite, (double), bool), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("bool IsInfinity(float)", asFUNCTIONPR(IsInfinity, (float), bool), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsInfinity(double)", asFUNCTIONPR(IsInfinity, (double), bool), asCALL_CDECL); assert(r >= 0);
	}
}
