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
# include <Siv3D/Mouse.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterMouse(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("Mouse"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("double Wheel()", asFUNCTION(Mouse::Wheel), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double WheelH()", asFUNCTION(Mouse::WheelH), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
