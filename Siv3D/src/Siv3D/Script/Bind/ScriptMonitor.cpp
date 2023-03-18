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
# include <Siv3D/Monitor.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterMonitor(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("System"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("size_t GetCurrentMonitorIndex()", asFUNCTION(System::GetCurrentMonitorIndex), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
