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
# include <Siv3D/Date.hpp>

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
	
	static String ScriptFormatDate(const String& s, const Date& value)
	{
		return value.format(s);
	}

	static int32 CompareDate(const Date& other, const Date& value)
	{
		return ::memcmp(&value, &other, sizeof(Date));
	}

	void RegisterDate(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Date";

		[[maybe_unused]] int32 r = 0;
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

		r = engine->RegisterObjectMethod(TypeName, "bool isToday() const", asMETHODPR(BindType, isToday, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isLeapYear() const", asMETHODPR(BindType, isLeapYear, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 daysInYear() const", asMETHODPR(BindType, daysInYear, () const noexcept, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 daysInMonth() const", asMETHODPR(BindType, daysInMonth, () const noexcept, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isValid() const", asMETHODPR(BindType, isValid, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "String format(const String& in format = \"yyyy-MM-dd\") const", asFUNCTION(ScriptFormatDate), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// Date& operator +=(const Days& days);
		// Date& operator -=(const Days& days)

		r = engine->RegisterObjectMethod(TypeName, "int32 opCmp(const Date& in) const", asFUNCTION(CompareDate), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// Date operator +(const Date& date, const Days& days);
		// Date operator -(const Date& date, const Days& days)
		// Days operator -(const Date& to, const Date& from);

		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(BindType, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace("Date"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Date Yesterday()", asFUNCTION(Date::Yesterday), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Date Today()", asFUNCTION(Date::Today), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Date Tomorrow()", asFUNCTION(Date::Tomorrow), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("bool IsLeapYear(int32)", asFUNCTION(Date::IsLeapYear), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 DaysInYear(int32)", asFUNCTION(Date::DaysInYear), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 DaysInMonth(int32 year, int32 month)", asFUNCTION(Date::DaysInMonth), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
