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
# include <Siv3D/DynamicTexture.hpp>
# include <Siv3D/TextureRegion.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = DynamicTexture;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const DynamicTexture& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void Destruct(BindType* self)
	{
		self->~DynamicTexture();
	}

	static void ConstructITfTd(const Image& image, TextureFormat format, TextureDesc desc, BindType* self)
	{
		new(self) BindType(image, format, desc);
	}

	static bool ConvToBool(const DynamicTexture& texture)
	{
		return !texture.isEmpty();
	}

	static Texture ConvToTexture(const DynamicTexture& texture)
	{
		return texture;
	}

	static TextureRegion ConvToTextureRegion(const DynamicTexture& texture)
	{
		return texture;
	}

	void RegisterDynamicTexture(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "DynamicTexture";

		int32 r = 0;
		
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const DynamicTexture& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Image& in, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped)", asFUNCTION(ConstructITfTd), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// Ctrs
		// ...

		r = engine->RegisterObjectMethod(TypeName, "DynamicTexture& opAssign(const DynamicTexture& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void release()", asMETHOD(BindType, release), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(BindType, isEmpty), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 id() const", asMETHOD(BindType, id), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const DynamicTexture& in)", asMETHOD(BindType, operator ==), asCALL_THISCALL); assert(r >= 0);

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

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion opCall(double, double, double, double) const", asMETHODPR(BindType, operator(), (double, double, double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion opCall(const Vec2& in, double, double) const", asMETHODPR(BindType, operator(), (const Vec2&, double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion opCall(double, double, double) const", asMETHODPR(BindType, operator(), (double, double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion opCall(double, double, const Vec2& in) const", asMETHODPR(BindType, operator(), (double, double, const Vec2&) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion opCall(const Vec2& in, const Vec2& in) const", asMETHODPR(BindType, operator(), (const Vec2&, const Vec2&) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion opCall(const RectF& in) const", asMETHODPR(BindType, operator(), (const RectF&) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion uv(double, double, double, double) const", asMETHODPR(BindType, uv, (double, double, double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion uv(const RectF& in) const", asMETHODPR(BindType, uv, (const RectF&) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion mirrored() const", asMETHODPR(BindType, mirrored, () const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion mirrored(bool) const", asMETHODPR(BindType, mirrored, (bool) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion flipped() const", asMETHODPR(BindType, flipped, () const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion flipped(bool) const", asMETHODPR(BindType, flipped, (bool) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion scaled(double) const", asMETHODPR(BindType, scaled, (double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion scaled(double, double) const", asMETHODPR(BindType, scaled, (double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion scaled(const Vec2& in) const", asMETHODPR(BindType, scaled, (const Vec2&) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion resized(double) const", asMETHODPR(BindType, resized, (double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion resized(double, double) const", asMETHODPR(BindType, resized, (double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion resized(const Vec2& in) const", asMETHODPR(BindType, resized, (const Vec2&) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion repeated(double, double) const", asMETHODPR(BindType, repeated, (double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion repeated(const Vec2& in) const", asMETHODPR(BindType, repeated, (const Vec2&) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion mapped(double, double) const", asMETHODPR(BindType, mapped, (double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion mapped(const Vec2& in) const", asMETHODPR(BindType, mapped, (const Vec2&) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion fitted(double, double, bool scaleUp = true) const", asMETHODPR(BindType, fitted, (double, double, bool) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion fitted(const Vec2& in, bool scaleUp = true) const", asMETHODPR(BindType, fitted, (const Vec2&, bool) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad rotated(double) const", asMETHODPR(BindType, rotated, (double) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad rotatedAt(double, double, double) const", asMETHODPR(BindType, rotatedAt, (double, double, double) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad rotatedAt(const Vec2& in, double) const", asMETHODPR(BindType, rotatedAt, (const Vec2&, double) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Texture opImplConv() const", asFUNCTION(ConvToTexture), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion opImplConv() const", asFUNCTION(ConvToTextureRegion), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool fill(const ColorF& in)", asMETHODPR(BindType, fill, (const ColorF&), bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool fill(const Image& in)", asMETHODPR(BindType, fill, (const Image&), bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool tryFill(const Image& in)", asMETHODPR(BindType, tryFill, (const Image&), bool), asCALL_THISCALL); assert(r >= 0);
	}
}
