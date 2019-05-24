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
# include <Siv3D/Profiler.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterProfiler(asIScriptEngine *engine)
	{
		int r = 0;

		r = engine->SetDefaultNamespace("Profiler"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("int32 FPS()", asFUNCTION(Profiler::FPS), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void EnableAssetCreationWarning(bool)", asFUNCTION(Profiler::EnableAssetCreationWarning), asCALL_CDECL); assert(r >= 0);
			// [[nodiscard]] Statistics GetStatistics();
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
