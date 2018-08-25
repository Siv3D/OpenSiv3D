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
# include <Siv3D/Cursor.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterCursor(asIScriptEngine *engine)
	{
		int r = 0;

		r = engine->RegisterEnumValue("CursorStyle", "Arrow", 0); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "IBeam", 1); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "Cross", 2); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "Hand", 3); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "NotAllowed", 4); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "ResizeUpDown", 5); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "ResizeLeftRight", 6); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "Hidden", 7); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "Default", 0); assert(r >= 0);

		r = engine->SetDefaultNamespace("Cursor"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Point Pos()", asFUNCTION(Cursor::Pos), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void RequestStyle(CursorStyle style)", asFUNCTION(Cursor::RequestStyle), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
