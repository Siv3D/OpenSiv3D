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
# include <Siv3D/Icon.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Icon;

	static void Construct(const Icon& c, BindType* self)
	{
		new(self) BindType(c);
	}

	static void ConstructU(uint32 code, BindType* self)
	{
		new(self) BindType(code);
	}

	static bool IconHasGlyph(uint32 code)
	{
		return Icon::HasGlyph(code);
	}

	static Image IconCreateImage(uint32 code, int32 size)
	{
		return Icon::CreateImage(code, size);
	}

	static Image IconCreateSDFImage(uint32 code, int32 size)
	{
		return Icon::CreateSDFImage(code, size);
	}

	static Image IconCreateMSDFImage(uint32 code, int32 size)
	{
		return Icon::CreateMSDFImage(code, size);
	}

	static Icon IconLiteral(uint32 code)
	{
		return Icon(code);
	}

	void RegisterIcon(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Icon";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "uint8 type", asOFFSET(BindType, type)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "uint32 code", asOFFSET(BindType, code)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Icon &in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32 code) explicit", asFUNCTION(ConstructU), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->SetDefaultNamespace("Icon"); assert(r >= 0);
		{		
			r = engine->RegisterGlobalFunction("bool HasGlyph(uint32)", asFUNCTION(IconHasGlyph), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Image CreateImage(uint32 code, int32 size)", asFUNCTION(IconCreateImage), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Image CreateSDFImage(uint32 code, int32 size)", asFUNCTION(IconCreateSDFImage), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Image CreateMSDFImage(uint32 code, int32 size)", asFUNCTION(IconCreateMSDFImage), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Icon _icon(uint32)", asFUNCTION(IconLiteral), asCALL_CDECL); assert(r >= 0);
	}
}
