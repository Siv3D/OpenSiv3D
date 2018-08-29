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

	void RegisterMath(asIScriptEngine* engine)
	{
		int32 r = 0;

		//r = engine->SetDefaultNamespace("Math"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("double ToDegrees(double)", asFUNCTIONPR(Math::Degrees, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double ToRadians(double)", asFUNCTIONPR(Math::Radians, (double), double), asCALL_CDECL); assert(r >= 0);
		}
		//r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
