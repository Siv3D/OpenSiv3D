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
# include <Siv3D/TextEncoding.hpp>

namespace s3d
{
	using namespace AngelScript;

	static int32 UnicodeGetTextEncoding(const FilePath& path)
	{
		return FromEnum(Unicode::GetTextEncoding(path));
	}

	static int32 UnicodeGetBOMSize(const int32 textEncoding)
	{
		return Unicode::GetBOMSize(ToEnum<TextEncoding>(static_cast<uint8>(textEncoding)));
	}

	void RegisterTextEncoding(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		{
			constexpr char TypeName[] = "TextEncoding";
			r = engine->RegisterEnumValue(TypeName, "Unknown", static_cast<uint32>(TextEncoding::Unknown)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "UTF8_NO_BOM", static_cast<uint32>(TextEncoding::UTF8_NO_BOM)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "UTF8_WITH_BOM", static_cast<uint32>(TextEncoding::UTF8_WITH_BOM)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "UTF16LE", static_cast<uint32>(TextEncoding::UTF16LE)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "UTF16BE", static_cast<uint32>(TextEncoding::UTF16BE)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Default", static_cast<uint32>(TextEncoding::Default)); assert(r >= 0);
		}

		r = engine->SetDefaultNamespace("Unicode"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("TextEncoding GetTextEncoding(const String& in path)", asFUNCTION(UnicodeGetTextEncoding), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 GetBOMSize(TextEncoding)", asFUNCTION(UnicodeGetBOMSize), asCALL_CDECL); assert(r >= 0);

		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
