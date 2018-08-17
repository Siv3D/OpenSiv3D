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
# include <Siv3D/DateTime.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = DateTime;

	static void ConstructIIIIIII(int32 year, int32 month, int32 day,
		int32 hour, int32 minute, int32 second, int32 milliseconds, BindType* self)
	{
		new(self) BindType(year, month, day, hour, minute, second, milliseconds);
	}

	static void ConstructDIIII(const Date& date,
		int32 hour, int32 minute, int32 second, int32 milliseconds, BindType* self)
	{
		new(self) BindType(date, hour, minute, second, milliseconds);
	}

	void RegisterDateTime(asIScriptEngine *engine)
	{
		const char TypeName[] = "DateTime";
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "int32 year", asOFFSET(BindType, year)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 month", asOFFSET(BindType, month)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 day", asOFFSET(BindType, day)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 hour", asOFFSET(BindType, hour)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 minute", asOFFSET(BindType, minute)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 second", asOFFSET(BindType, second)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 milliseconds", asOFFSET(BindType, milliseconds)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 year, int32 month, int32 day, int32 _hour = 0, int32 minute = 0, int32 second = 0, int32 milliseconds = 0)", asFUNCTION(ConstructIIIIIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Date&in date, int32 _hour = 0, int32 minute = 0, int32 second = 0, int32 milliseconds = 0)", asFUNCTION(ConstructDIIII), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "String format(const String&in format = \"yyyy/M/d HH:mm:ss\") const", asMETHOD(BindType, format), asCALL_THISCALL); assert(r >= 0);

		//
		//	...
		//
	}
}
