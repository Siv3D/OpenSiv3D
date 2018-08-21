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
# include <Siv3D/Graphics.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	bool ScriptSystemUpdate()
	{
		//auto current = FileSystem::WriteTime(L"Main.siv3d");

		//if (current && current != updateTime)
		//{
		//	return false;
		//}

		//return System::Update() && !Input::KeySpace.clicked;

		return System::Update();
	}

	void RegisterSystem(asIScriptEngine *engine)
	{
		int r = 0;

		r = engine->SetDefaultNamespace("System"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("bool Update()", asFUNCTION(ScriptSystemUpdate), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
