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

	static void ConstructDefault(BindType* self)
	{
		new(self) BindType();
	}

	static void Construct(const Date& date, BindType* self)
	{
		new(self) BindType(date);
	}

	static void ConstructIII(int32 year, int32 month, int32 day, BindType* self)
	{
		new(self) BindType(year, month, day);
	}

	static int32 CompareDate(const Date& other, const Date& value)
	{
		return ::memcmp(&value, &other, sizeof(Date));
	}

	void RegisterDate(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Date";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "int32 year", asOFFSET(BindType, year)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 month", asOFFSET(BindType, month)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 day", asOFFSET(BindType, day)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructDefault), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Date& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 year, int32 month = 1, int32 day = 1)", asFUNCTION(ConstructIII), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// DayOfWeek
		// dayOfWeek
		// dayOfWeekJP
		// dayOfWeekEN

		r = engine->RegisterObjectMethod(TypeName, "bool isToday() const", asMETHOD(BindType, isToday), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isLeapYear() const", asMETHOD(BindType, isLeapYear), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 daysInMonth() const", asMETHOD(BindType, daysInMonth), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 daysInYear() const", asMETHOD(BindType, daysInYear), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isValid() const", asMETHOD(BindType, isValid), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "String format(const String& in format = \"yyyy/M/d\") const", asMETHOD(BindType, format), asCALL_THISCALL); assert(r >= 0);

		// Date& operator +=(const Days& days);
		// Date& operator -=(const Days& days)

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Date& in) const", asMETHOD(BindType, operator==), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 opCmp(const Date& in) const", asFUNCTION(CompareDate), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// Date operator +(const Date& date, const Days& days);
		// Date operator -(const Date& date, const Days& days)
		// Days operator -(const Date& to, const Date& from);

		r = engine->SetDefaultNamespace("Date"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("Date Yesterday()", asFUNCTION(Date::Yesterday), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Date Today()", asFUNCTION(Date::Today), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Date Tomorrow()", asFUNCTION(Date::Tomorrow), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
