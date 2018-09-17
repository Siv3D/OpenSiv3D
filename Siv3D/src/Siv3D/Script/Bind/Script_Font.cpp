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
# include <Siv3D/Font.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Font;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const BindType& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructITF(int32 fontSize, Typeface typeface, FontStyle style, BindType* self)
	{
		new(self) BindType(fontSize, typeface, style);
	}

	static void ConstructISF(int32 fontSize, const FilePath& path, FontStyle style, BindType* self)
	{
		new(self) BindType(fontSize, path, style);
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	static bool ConvToBool(const Font& font)
	{
		return !font.isEmpty();
	}

	void RegisterFont(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Font";

		int32 r = 0;

		r = engine->RegisterEnumValue("Typeface", "Thin", static_cast<uint32>(Typeface::Thin)); assert(r >= 0);
		r = engine->RegisterEnumValue("Typeface", "Light", static_cast<uint32>(Typeface::Light)); assert(r >= 0);
		r = engine->RegisterEnumValue("Typeface", "Regular", static_cast<uint32>(Typeface::Regular)); assert(r >= 0);
		r = engine->RegisterEnumValue("Typeface", "Medium", static_cast<uint32>(Typeface::Medium)); assert(r >= 0);
		r = engine->RegisterEnumValue("Typeface", "Bold", static_cast<uint32>(Typeface::Bold)); assert(r >= 0);
		r = engine->RegisterEnumValue("Typeface", "Heavy", static_cast<uint32>(Typeface::Heavy)); assert(r >= 0);
		r = engine->RegisterEnumValue("Typeface", "Black", static_cast<uint32>(Typeface::Black)); assert(r >= 0);
		r = engine->RegisterEnumValue("Typeface", "Default", static_cast<uint32>(Typeface::Default)); assert(r >= 0);
		
		r = engine->RegisterEnumValue("FontStyle", "Default", static_cast<uint32>(FontStyle::Default)); assert(r >= 0);
		r = engine->RegisterEnumValue("FontStyle", "Bold", static_cast<uint32>(FontStyle::Bold)); assert(r >= 0);
		r = engine->RegisterEnumValue("FontStyle", "Italic", static_cast<uint32>(FontStyle::Italic)); assert(r >= 0);
		r = engine->RegisterEnumValue("FontStyle", "BoldItalic", static_cast<uint32>(FontStyle::BoldItalic)); assert(r >= 0);
		r = engine->RegisterEnumValue("FontStyle", "Bitmap", static_cast<uint32>(FontStyle::Bitmap)); assert(r >= 0);
		r = engine->RegisterEnumValue("FontStyle", "BoldBitmap", static_cast<uint32>(FontStyle::BoldBitmap)); assert(r >= 0);
		r = engine->RegisterEnumValue("FontStyle", "ItalicBitmap", static_cast<uint32>(FontStyle::ItalicBitmap)); assert(r >= 0);
		r = engine->RegisterEnumValue("FontStyle", "BoldItalicBitmap", static_cast<uint32>(FontStyle::BoldItalicBitmap)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Font& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32, Typeface typeface = Typeface::Default, FontStyle style = FontStyle::Default)", asFUNCTION(ConstructITF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32, const String& in path, FontStyle style = FontStyle::Default)", asFUNCTION(ConstructISF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Font& opAssign(const Font& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void release()", asMETHOD(BindType, release), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(BindType, isEmpty), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 id() const", asMETHOD(BindType, id), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Texture& in)", asMETHOD(BindType, operator ==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const String& familyName() const", asMETHOD(BindType, familyName), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const String& styleName() const", asMETHOD(BindType, styleName), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 fontSize() const", asMETHOD(BindType, fontSize), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 ascent() const", asMETHOD(BindType, ascent), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 descent() const", asMETHOD(BindType, descent), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 height() const", asMETHOD(BindType, height), asCALL_THISCALL); assert(r >= 0);

		//[[nodiscard]] Glyph getGlyph(char32 codePoint) const;
		//[[nodiscard]] Array<Glyph> getGlyphs(const String& text) const;
		//[[nodiscard]] Array<Glyph> getVerticalGlyphs(const String& text) const;
		//[[nodiscard]] OutlineGlyph getOutlineGlyph(char32 codePoint) const;

		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall() const", asMETHODPR(BindType, operator(), () const, DrawableText), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const String& in) const", asMETHODPR(BindType, operator(), (const String&) const, DrawableText), asCALL_THISCALL); assert(r >= 0);


	}
}
