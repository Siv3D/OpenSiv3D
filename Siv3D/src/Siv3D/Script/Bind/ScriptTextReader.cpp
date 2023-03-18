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
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Console.hpp>
# include "ScriptOptional.hpp"
# include "ScriptArray.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = TextReader;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const TextReader& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructFE(const FilePath& path, int32 textEncoding, BindType* self)
	{
		new(self) BindType(path, ToEnum<TextEncoding>(static_cast<uint8>(textEncoding)));
	}

	static void ConstructFN(const FilePath& path, const uint8&, BindType* self)
	{
		new(self) BindType(path, unspecified);
	}

	static void Destruct(TextReader* self)
	{
		self->~TextReader();
	}

	static bool OpenFE(const FilePath& path, int32 textEncoding, TextReader& self)
	{
		return self.open(path, ToEnum<TextEncoding>(static_cast<uint8>(textEncoding)));
	}

	static bool OpenFN(const FilePath& path, const uint8&, TextReader& self)
	{
		return self.open(path, unspecified);
	}


	static CScriptOptional ReadChar(TextReader& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Optional<char32>");

		if (const auto result = self.readChar())
		{
			char32 value = *result;

			return CScriptOptional{ &value, typeID };
		}
		else
		{
			return CScriptOptional{ typeID };
		}
	}

	static CScriptOptional ReadLine(TextReader& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Optional<String>");

		if (const auto result = self.readLine())
		{
			String value = *result;

			return CScriptOptional{ &value, typeID };
		}
		else
		{
			return CScriptOptional{ typeID };
		}
	}

	static int32 GetTextEncoding(const TextReader& self)
	{
		return FromEnum(self.encoding());
	}

	static String GetPath(const TextReader& self)
	{
		return self.path();
	}

	void RegisterTextReader(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "TextReader";
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TextReader& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, TextEncoding)", asFUNCTION(ConstructFE), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, None_t = unspecified)", asFUNCTION(ConstructFN), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool open(const String& in, TextEncoding)", asFUNCTION(OpenFE), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool open(const String& in, None_t = unspecified)", asFUNCTION(OpenFN), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void close() const", asMETHODPR(BindType, close, (), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isOpen() const", asMETHODPR(BindType, isOpen, () const, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asMETHODPR(BindType, operator bool, () const, bool), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Optional<char32> readChar()", asFUNCTION(ReadChar), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Optional<String> readLine()", asFUNCTION(ReadLine), asCALL_CDECL_OBJLAST); assert(r >= 0);
			//r = engine->RegisterObjectMethod(TypeName, "Array<String> readLines()", asFUNCTION(ReadLines), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "String readAll()", asMETHODPR(BindType, readAll, (), String), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool readChar(char32& out)", asMETHODPR(BindType, readChar, (char32&), bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool readLine(String& out)", asMETHODPR(BindType, readLine, (String&), bool), asCALL_THISCALL); assert(r >= 0);
			//r = engine->RegisterObjectMethod(TypeName, "bool readLines(Array<String>& in)", asMETHODPR(BindType, readLines, (Array<String>&), bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool readAll(String& out)", asMETHODPR(BindType, readAll, (String&), bool), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "TextEncoding encoding() const", asFUNCTION(GetTextEncoding), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "String path() const", asFUNCTION(GetPath), asCALL_CDECL_OBJLAST); assert(r >= 0);
		}
	}
}
