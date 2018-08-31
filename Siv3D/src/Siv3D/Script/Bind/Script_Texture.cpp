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
# include <Siv3D/Texture.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Texture;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const Texture& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void Destruct(BindType* self)
	{
		self->~Texture();
	}

	static void ConstructIT(const Image& image, TextureDesc desc, BindType* self)
	{
		new(self) BindType(image, desc);
	}

	static void ConstructFT(const FilePath& path, TextureDesc desc, BindType* self)
	{
		new(self) BindType(path, desc);
	}

	static void ConstructFFT(const FilePath& rgb, const FilePath& alpha, TextureDesc desc, BindType* self)
	{
		new(self) BindType(rgb, alpha, desc);
	}

	static void ConstructCFT(const Color& rgb, const FilePath& alpha, TextureDesc desc, BindType* self)
	{
		new(self) BindType(rgb, alpha, desc);
	}

	static bool ConvToBool(const Texture& texture)
	{
		return !texture.isEmpty();
	}

	void RegisterTexture(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Texture";

		int32 r = 0;
		
		r = engine->RegisterEnumValue("TextureDesc", "Unmipped", 0); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "UnmippedSRGB", 1); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "Mipped", 2); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "MippedSRGB", 3); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "JPEG2000", 4); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "SDF", 5); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "For3D", 3); assert(r >= 0);
		
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Texture& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Image& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructIT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//	Texture(const Image& image, const Array<Image>& mipmaps, TextureDesc desc = TextureDesc::Mipped);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructFFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructCFT), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//explicit Texture(const Emoji& emoji, TextureDesc desc = TextureDesc::Unmipped);
		//explicit Texture(const Icon& icon, TextureDesc desc = TextureDesc::Unmipped);


		r = engine->RegisterObjectMethod(TypeName, "Texture& opAssign(const Texture& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void release()", asMETHOD(BindType, release), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(BindType, isEmpty), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 id() const", asMETHOD(BindType, id), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Texture& in)", asMETHOD(BindType, operator ==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 width() const", asMETHOD(BindType, width), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 height() const", asMETHOD(BindType, height), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point size() const", asMETHOD(BindType, size), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureDesc getDesc() const", asMETHOD(BindType, getDesc), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isMipped() const", asMETHOD(BindType, isMipped), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isSDF() const", asMETHOD(BindType, isSDF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect region(int32, int32) const", asMETHODPR(BindType, region, (int32, int32) const, Rect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect region(const Point& in = Point(0, 0)) const", asMETHODPR(BindType, region, (const Point&) const, Rect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF region(double, double) const", asMETHODPR(BindType, region, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF region(const Vec2& in) const", asMETHODPR(BindType, region, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(double, double) const", asMETHODPR(BindType, regionAt, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(const Vec2& in) const", asMETHODPR(BindType, regionAt, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, draw, (const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF draw(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(double x, double y, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, draw, (double, double, const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const Vec2& in, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, draw, (const Vec2&, const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF drawClipped(double x, double y, const RectF& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawClipped, (double, double, const RectF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawClipped(const Vec2& in, const RectF& in, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, drawClipped, (const Vec2&, const RectF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(double x, double y, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, drawAt, (double, double, const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const Vec2& in, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, drawAt, (const Vec2&, const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF drawAtClipped(double x, double y, const RectF& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAtClipped, (double, double, const RectF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAtClipped(const Vec2& in, const RectF& in, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, drawAtClipped, (const Vec2&, const RectF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		//[[nodiscard]] TextureRegion operator ()(double x, double y, double w, double h) const;
		//[[nodiscard]] TextureRegion operator ()(const Vec2& xy, double w, double h) const;
		//[[nodiscard]] TextureRegion operator ()(double x, double y, double size) const;
		//[[nodiscard]] TextureRegion operator ()(double x, double y, const Vec2& size) const;
		//[[nodiscard]] TextureRegion operator ()(const Vec2& xy, const Vec2& size) const;
		//[[nodiscard]] TextureRegion operator ()(const RectF& rect) const;
		//[[nodiscard]] TextureRegion uv(double u, double v, double w, double h) const;
		//[[nodiscard]] TextureRegion uv(const RectF& rect) const;
		//[[nodiscard]] TextureRegion mirrored() const;
		//[[nodiscard]] TextureRegion mirrored(bool doMirror) const;
		//[[nodiscard]] TextureRegion flipped() const;
		//[[nodiscard]] TextureRegion flipped(bool doFlip) const;

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion scaled(double) const", asMETHODPR(BindType, scaled, (double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		//[[nodiscard]] TextureRegion scaled(double xs, double ys) const;
		//[[nodiscard]] TextureRegion scaled(const Vec2& s) const;
		//[[nodiscard]] TextureRegion resized(double size) const;
		//[[nodiscard]] TextureRegion resized(double width, double height) const;
		//[[nodiscard]] TextureRegion resized(const Vec2& size) const;
		//[[nodiscard]] TextureRegion repeated(double xRepeat, double yRepeat) const;
		//[[nodiscard]] TextureRegion repeated(const Vec2& _repeat) const;
		//[[nodiscard]] TextureRegion mapped(double width, double height) const;
		//[[nodiscard]] TextureRegion mapped(const Vec2& size) const;
		//[[nodiscard]] TextureRegion fitted(double width, double height, bool scaleUp = true) const;
		//[[nodiscard]] TextureRegion fitted(const Vec2& size, bool scaleUp = true) const;
		//[[nodiscard]] TexturedQuad rotated(double angle) const;
		//[[nodiscard]] TexturedQuad rotatedAt(double x, double y, double angle) const;
		//[[nodiscard]] TexturedQuad rotatedAt(const Vec2& pos, double angle) const;
	}
}
