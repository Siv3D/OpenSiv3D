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
# include <Siv3D/Resource.hpp>

namespace s3d
{
	using namespace AngelScript;

	static String ScriptResource(const String& path) noexcept
	{
		return Resource(path);
	}

	void RegisterResource(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterGlobalFunction("String Resource(const String& in)", asFUNCTION(ScriptResource), asCALL_CDECL); assert(r >= 0);
	}
}
