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
# include <Siv3D/PutText.hpp>

namespace s3d
{
	using namespace AngelScript;

	static void ScriptPutText(const String& s, double x, double y)
	{
		PutText(s, x, y);
	}

	static void ScriptPutText2(const String& s, Vec2 center)
	{
		PutText(s, center);
	}

	static void ScriptPutTextTL(const String& s, Vec2 pos)
	{
		PutText(s, Arg::topLeft = pos);
	}

	static void ScriptPutTextC(const String& s, Vec2 pos)
	{
		PutText(s, Arg::center = pos);
	}

	void RegisterPutText(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterGlobalFunction("void PutText(const String& in, double, double)", asFUNCTION(ScriptPutText), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("void PutText(const String& in, Vec2)", asFUNCTION(ScriptPutText2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("void PutText(const String& in, Arg::topLeft_Vec2)", asFUNCTION(ScriptPutTextTL), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("void PutText(const String& in, Arg::center_Vec2)", asFUNCTION(ScriptPutTextC), asCALL_CDECL); assert(r >= 0);

	}
}
