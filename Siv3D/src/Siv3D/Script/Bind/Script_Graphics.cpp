//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterGraphics(asIScriptEngine *engine)
	{
		int r = 0;

		r = engine->SetDefaultNamespace("Graphics"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("void SetBackground(const ColorF& in)", asFUNCTION(Graphics::SetBackground), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
