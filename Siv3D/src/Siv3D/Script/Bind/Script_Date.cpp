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
# include <Siv3D/Date.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Date;

	static void ConstructIII(int32 year, int32 month, int32 day, BindType* self)
	{
		new(self) BindType(year, month, day);
	}

	void RegisterDate(asIScriptEngine *engine)
	{
		const char TypeName[] = "Date";
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "int32 year", asOFFSET(BindType, year)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 month", asOFFSET(BindType, month)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 day", asOFFSET(BindType, day)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 year, int32 month = 1, int32 day = 1)", asFUNCTION(ConstructIII), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "String format(const String&in format = \"yyyy/M/d\") const", asMETHOD(BindType, format), asCALL_THISCALL); assert(r >= 0);

		//
		//	...
		//
	}
}
