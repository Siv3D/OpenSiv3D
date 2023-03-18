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
# include <Siv3D/Font.hpp>
# include <Siv3D/DrawableText.hpp>

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

	static void ConstructISF(int32 fontSize, const FilePath& path, int32 style, BindType* self)
	{
		new(self) BindType(fontSize, path, ToEnum<FontStyle>(static_cast<uint8>(style)));
	}

	static void ConstructISZF(int32 fontSize, const FilePath& path, size_t faceIndex, int32 style, BindType* self)
	{
		new(self) BindType(fontSize, path, faceIndex, ToEnum<FontStyle>(static_cast<uint8>(style)));
	}

	static void ConstructITF(int32 fontSize, int32 typeface, int32 style, BindType* self)
	{
		new(self) BindType(fontSize, ToEnum<Typeface>(static_cast<uint8>(typeface)), ToEnum<FontStyle>(static_cast<uint8>(style)));
	}

	static void ConstructMISF(int32 method, int32 fontSize, const FilePath& path, int32 style, BindType* self)
	{
		new(self) BindType(ToEnum<FontMethod>(static_cast<uint8>(method)), fontSize, path, ToEnum<FontStyle>(static_cast<uint8>(style)));
	}

	static void ConstructMISZF(int32 method, int32 fontSize, const FilePath& path, size_t faceIndex, int32 style, BindType* self)
	{
		new(self) BindType(ToEnum<FontMethod>(static_cast<uint8>(method)), fontSize, path, faceIndex, ToEnum<FontStyle>(static_cast<uint8>(style)));
	}

	static void ConstructMITF(int32 method, int32 fontSize, int32 typeface, int32 style, BindType* self)
	{
		new(self) BindType(ToEnum<FontMethod>(static_cast<uint8>(method)), fontSize, ToEnum<Typeface>(static_cast<uint8>(typeface)), ToEnum<FontStyle>(static_cast<uint8>(style)));
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	static void Release(BindType& a)
	{
		a.release();
	}

	static bool ConvToBool(const BindType& a)
	{
		return static_cast<bool>(a);
	}

	static bool IsEmpty(const BindType& a)
	{
		return a.isEmpty();
	}

	static bool Equals(const BindType& other, const BindType& a)
	{
		return (a == other);
	}

	static bool FontHasGlyph(const String& s, const BindType& a)
	{
		return a.hasGlyph(s);
	}

	static GlyphIndex FontGetGlyphIndex(const String& s, const BindType& a)
	{
		return a.getGlyphIndex(s);
	}

	static bool FontPreload(const String& s, const BindType& a)
	{
		return a.preload(s);
	}

	String FormatBase(const void** args, const int* types, size_t num_args);

	DrawableText FontOpCall_T1(
		const void* ref1, int typeID1,
		const Font& font
	)
	{
		return font(FormatBase(&ref1, &typeID1, 1));
	}

	DrawableText FontOpCall_T2(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const Font& font
	)
	{
		const void* args[] = { ref1, ref2 };
		const int types[] = { typeID1, typeID2 };
		return font(FormatBase(args, types, std::size(args)));
	}

	DrawableText FontOpCall_T3(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const Font& font
	)
	{
		const void* args[] = { ref1, ref2, ref3 };
		const int types[] = { typeID1, typeID2, typeID3 };
		return font(FormatBase(args, types, std::size(args)));
	}

	DrawableText FontOpCall_T4(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const Font& font
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4 };
		return font(FormatBase(args, types, std::size(args)));
	}

	DrawableText FontOpCall_T5(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const Font& font
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5 };
		return font(FormatBase(args, types, std::size(args)));
	}

	DrawableText FontOpCall_T6(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6,
		const Font& font
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6 };
		return font(FormatBase(args, types, std::size(args)));
	}

	DrawableText FontOpCall_T7(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6,
		const void* ref7, int typeID7,
		const Font& font
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7 };
		return font(FormatBase(args, types, std::size(args)));
	}

	DrawableText FontOpCall_T8(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6,
		const void* ref7, int typeID7,
		const void* ref8, int typeID8,
		const Font& font
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7, typeID8 };
		return font(FormatBase(args, types, std::size(args)));
	}

	DrawableText FontOpCall_T9(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6,
		const void* ref7, int typeID7,
		const void* ref8, int typeID8,
		const void* ref9, int typeID9,
		const Font& font
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8, ref9 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7, typeID8, typeID9 };
		return font(FormatBase(args, types, std::size(args)));
	}

	DrawableText FontOpCall_T10(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6,
		const void* ref7, int typeID7,
		const void* ref8, int typeID8,
		const void* ref9, int typeID9,
		const void* ref10, int typeID10,
		const Font& font
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8, ref9, ref10 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7, typeID8, typeID9, typeID10 };
		return font(FormatBase(args, types, std::size(args)));
	}

	void RegisterFont(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Font";

		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Font& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32, const String& in path, FontStyle style = FontStyle::Default)", asFUNCTION(ConstructISF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32, const String& in path, size_t faceIndex, FontStyle style = FontStyle::Default)", asFUNCTION(ConstructISZF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default)", asFUNCTION(ConstructITF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(FontMethod fontMethod, int32, const String& in path, FontStyle style = FontStyle::Default)", asFUNCTION(ConstructMISF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(FontMethod fontMethod, int32, const String& in path, size_t faceIndex, FontStyle style = FontStyle::Default)", asFUNCTION(ConstructMISZF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(FontMethod fontMethod, int32, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default)", asFUNCTION(ConstructMITF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Font& opAssign(const Font& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void release()", asFUNCTION(Release), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asFUNCTION(IsEmpty), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Texture& in)", asFUNCTION(Equals), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void addFallback(const Font& in) const", asMETHODPR(BindType, addFallback, (const Font&) const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const String& familyName() const", asMETHODPR(BindType, familyName, () const, const String&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const String& styleName() const", asMETHODPR(BindType, styleName, () const, const String&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasColor() const", asMETHODPR(BindType, hasColor, () const, bool), asCALL_THISCALL); assert(r >= 0);
		// style()
		// method()
		// 
		r = engine->RegisterObjectMethod(TypeName, "int32 fontSize() const", asMETHODPR(BindType, fontSize, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 ascender() const", asMETHODPR(BindType, ascender, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 descender() const", asMETHODPR(BindType, descender, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 height() const", asMETHODPR(BindType, height, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double spaceWidth() const", asMETHODPR(BindType, spaceWidth, () const, double), asCALL_THISCALL); assert(r >= 0);
		
		r = engine->RegisterObjectMethod(TypeName, "int32 indentSize() const", asMETHODPR(BindType, indentSize, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Font& setIndentSize(int32) const", asMETHODPR(BindType, setIndentSize, (int32) const, const Font&), asCALL_THISCALL); assert(r >= 0);
		
		r = engine->RegisterObjectMethod(TypeName, "const Font& setBufferThickness(int32) const", asMETHODPR(BindType, setBufferThickness, (int32) const, const Font&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 getBufferThickness() const", asMETHODPR(BindType, getBufferThickness, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasGlyph(char32) const", asMETHODPR(BindType, hasGlyph, (char32) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasGlyph(const String& in)", asFUNCTION(FontHasGlyph), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 num_glyphs() const", asMETHODPR(BindType, num_glyphs, () const, uint32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "GlyphIndex getGlyphIndex(char32) const", asMETHODPR(BindType, getGlyphIndex, (char32) const, GlyphIndex), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "GlyphIndex getGlyphIndex(const String& in)", asFUNCTION(FontGetGlyphIndex), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//getGlyphClusters()
		//getGlyphInfo()
		//getGlyphInfoByGlyphIndex()
		//renderOutline()
		//renderPolygon()
		// ...

		r = engine->RegisterObjectMethod(TypeName, "bool preload(const String& in)", asFUNCTION(FontPreload), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Texture& getTexture() const", asMETHODPR(BindType, getTexture, () const, const Texture&), asCALL_THISCALL); assert(r >= 0);

		// ...

		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall() const", asMETHODPR(BindType, operator(), () const, DrawableText), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const String& in) const", asMETHODPR(BindType, operator(), (const String&) const, DrawableText), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in) const", asFUNCTION(FontOpCall_T1), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in, const ?&in) const", asFUNCTION(FontOpCall_T2), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in, const ?&in, const ?&in) const", asFUNCTION(FontOpCall_T3), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in, const ?&in, const ?&in, const ?&in) const", asFUNCTION(FontOpCall_T4), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in) const", asFUNCTION(FontOpCall_T5), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in) const", asFUNCTION(FontOpCall_T6), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in) const", asFUNCTION(FontOpCall_T7), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in) const", asFUNCTION(FontOpCall_T8), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in) const", asFUNCTION(FontOpCall_T9), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "DrawableText opCall(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in) const", asFUNCTION(FontOpCall_T10), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void swap(Font& inout)", asMETHODPR(BindType, swap, (Font&), void), asCALL_THISCALL); assert(r >= 0);
	}
}
