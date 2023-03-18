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
# include <Siv3D/Emoji.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Emoji;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const Emoji& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructS(const String& emoji, BindType* self)
	{
		new(self) BindType(emoji);
	}

	static void Destruct(BindType* self)
	{
		self->~Emoji();
	}

	static bool EmojiHasGlyph(const String& s)
	{
		return Emoji::HasGlyph(s);
	}

	static GlyphIndex EmojiGetGlyphIndex(const String& s)
	{
		return Emoji::GetGlyphIndex(s);
	}

	static Image EmojiCreateImage(const String& emoji)
	{
		return Emoji::CreateImage(emoji);
	}

	static Image EmojiCreateImageByGlyphIndex(GlyphIndex emoji)
	{
		return Emoji::CreateImageByGlyphIndex(emoji);
	}

	static Image EmojiCreateSilhouetteImage(const String& emoji)
	{
		return Emoji::CreateSilhouetteImage(emoji);
	}

	static Image EmojiCreateSilhouetteImageByGlyphIndex(GlyphIndex emoji)
	{
		return Emoji::CreateSilhouetteImageByGlyphIndex(emoji);
	}

	static Emoji EmojiLiteral(const String& emoji)
	{
		return Emoji(emoji);
	}

	void RegisterEmoji(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Emoji";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Emoji& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
	
		r = engine->RegisterObjectMethod(TypeName, "Emoji& opAssign(const Emoji& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace("Emoji"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const Point ImageSize", (void*)&Emoji::ImageSize); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("bool HasGlyph(const String& in)", asFUNCTION(EmojiHasGlyph), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("GlyphIndex GetGlyphIndex(const String& in)", asFUNCTION(EmojiGetGlyphIndex), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Image CreateImage(const String& in)", asFUNCTION(EmojiCreateImage), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Image CreateImageByGlyphIndex(GlyphIndex)", asFUNCTION(EmojiCreateImageByGlyphIndex), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Image CreateSilhouetteImage(const String& in)", asFUNCTION(EmojiCreateSilhouetteImage), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Image CreateSilhouetteImageByGlyphIndex(GlyphIndex)", asFUNCTION(EmojiCreateSilhouetteImageByGlyphIndex), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Emoji _emoji(const String& in)", asFUNCTION(EmojiLiteral), asCALL_CDECL); assert(r >= 0);
	}
}
