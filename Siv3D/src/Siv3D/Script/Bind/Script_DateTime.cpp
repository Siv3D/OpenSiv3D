//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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

	static void ConstructDefault(BindType* self)
	{
		new(self) BindType();
	}

	static void Construct(const DateTime& dateTime, BindType* self)
	{
		new(self) BindType(dateTime);
	}

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

	static int32 CompareDateTime(const DateTime& other, const DateTime& value)
	{
		return ::memcmp(&value, &other, sizeof(DateTime));
	}

	void RegisterDateTime(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "DateTime";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "int32 year", asOFFSET(BindType, year)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 month", asOFFSET(BindType, month)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 day", asOFFSET(BindType, day)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 hour", asOFFSET(BindType, hour)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 minute", asOFFSET(BindType, minute)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 second", asOFFSET(BindType, second)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 milliseconds", asOFFSET(BindType, milliseconds)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructDefault), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const DateTime& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 year, int32 month, int32 day, int32 _hour = 0, int32 minute = 0, int32 second = 0, int32 milliseconds = 0)", asFUNCTION(ConstructIIIIIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Date& in date, int32 _hour = 0, int32 minute = 0, int32 second = 0, int32 milliseconds = 0)", asFUNCTION(ConstructDIIII), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isValid() const", asMETHOD(BindType, isValid), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "String format(const String& in format = \"yyyy/M/d HH:mm:ss\") const", asMETHOD(BindType, format), asCALL_THISCALL); assert(r >= 0);

		// DateTime& operator +=(const Days& days)
		// DateTime& operator -=(const Days& days)
		// DateTime& operator +=(const Milliseconds& _milliseconds);
		// DateTime& operator -= (const Milliseconds& _milliseconds)

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const DateTime& in) const", asMETHOD(BindType, operator==), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 opCmp(const DateTime& in) const", asFUNCTION(CompareDateTime), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->SetDefaultNamespace("DateTime"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("DateTime Now()", asFUNCTION(DateTime::Now), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("DateTime NowUTC()", asFUNCTION(DateTime::NowUTC), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		// DateTime operator +(const DateTime& dateTime, const Days& days)
		// DateTime operator -(const DateTime& dateTime, const Days& days)
		// DateTime operator +(const DateTime& dateTime, const Milliseconds& milliseconds)
		// DateTime operator -(const DateTime& dateTime, const Milliseconds& milliseconds)
		// Milliseconds operator -(const DateTime& a, const DateTime& b);
	}
}
