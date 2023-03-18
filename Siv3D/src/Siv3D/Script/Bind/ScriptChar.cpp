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
# include <Siv3D/Char.hpp>

namespace s3d
{
	using namespace AngelScript;

	static uint32 ConvToUint32(const char32& value)
	{
		return value;
	}

	static char32& AssignUint32(uint32 other, char32& value)
	{
		return value = other;
	}

	static char32 AddUint32(uint32 other, const char32& value)
	{
		return (value + other);
	}

	static char32 SubUint32(uint32 other, const char32& value)
	{
		return (value - other);
	}

	static char32& AddAssignUint32(uint32 other, char32& value)
	{
		return value += other;
	}

	static char32& SubAssignUint32(uint32 other, char32& value)
	{
		return value -= other;
	}

	static bool EqualsChar32(char32 other, const char32& value)
	{
		return (value == other);
	}

	static int32 CompareChar32(char32 other, const char32& value)
	{
		if (other == value)
		{
			return 0;
		}
		else if (value < other)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	void RegisterChar(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterObjectMethod("char32", "uint32 opImplConv() const", asFUNCTION(ConvToUint32), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod("char32", "char32& opAssign(uint32)", asFUNCTION(AssignUint32), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod("char32", "char32 opAdd(uint32) const", asFUNCTION(AddUint32), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod("char32", "char32 opSub(uint32) const", asFUNCTION(SubUint32), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod("char32", "Vec2& opAddAssign(uint32)", asFUNCTION(AddAssignUint32), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod("char32", "Vec2& opSubAssign(uint32)", asFUNCTION(SubAssignUint32), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod("char32", "bool opEquals(char32) const", asFUNCTION(EqualsChar32), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod("char32", "int32 opCmp(char32) const", asFUNCTION(CompareChar32), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterGlobalFunction("bool IsASCII(uint32)", asFUNCTION(IsASCII), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsDigit(uint32)", asFUNCTION(IsDigit), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsLower(uint32)", asFUNCTION(IsLower), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsUpper(uint32)", asFUNCTION(IsUpper), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("char32 ToLower(uint32)", asFUNCTION(ToLower), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("char32 ToUpper(uint32)", asFUNCTION(ToUpper), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsAlpha(uint32)", asFUNCTION(IsAlpha), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsAlnum(uint32)", asFUNCTION(IsAlnum), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsXdigit(uint32)", asFUNCTION(IsXdigit), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsControl(uint32)", asFUNCTION(IsControl), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsBlank(uint32)", asFUNCTION(IsBlank), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsSpace(uint32)", asFUNCTION(IsSpace), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsPrint(uint32)", asFUNCTION(IsPrint), asCALL_CDECL); assert(r >= 0);
		
		r = engine->RegisterGlobalFunction("int32 CaseInsensitiveCompare(uint32, uint32)", asFUNCTION(CaseInsensitiveCompare), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool CaseInsensitiveEquals(uint32, uint32)", asFUNCTION(CaseInsensitiveEquals), asCALL_CDECL); assert(r >= 0);
	}
}
