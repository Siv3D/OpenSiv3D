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
# include <Siv3D/Profiler.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterProfiler(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Profiler"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("int32 FPS()", asFUNCTION(Profiler::FPS), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void EnableAssetCreationWarning(bool)", asFUNCTION(Profiler::EnableAssetCreationWarning), asCALL_CDECL); assert(r >= 0);
			//const ProfilerStat& GetStat();
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
