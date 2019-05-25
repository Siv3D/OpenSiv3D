//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureFormat.hpp>
# include <Siv3D/TextureRegion.hpp>
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

	static void ConstructEmT(const Emoji& emoji, TextureDesc desc, BindType* self)
	{
		new(self) BindType(emoji, desc);
	}

	static void ConstructIcT(const Icon& icon, TextureDesc desc, BindType* self)
	{
		new(self) BindType(icon, desc);
	}

	static bool ConvToBool(const Texture& texture)
	{
		return !texture.isEmpty();
	}

	static TextureRegion ConvToTextureRegion(const Texture& texture)
	{
		return texture;
	}

	void RegisterTexture(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Texture";

		int32 r = 0;
		
		r = engine->RegisterEnumValue("TextureDesc", "Unmipped", static_cast<int32>(TextureDesc::Unmipped)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "UnmippedSRGB", static_cast<int32>(TextureDesc::UnmippedSRGB)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "Mipped", static_cast<int32>(TextureDesc::Mipped)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "MippedSRGB", static_cast<int32>(TextureDesc::MippedSRGB)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "SDF", static_cast<int32>(TextureDesc::SDF)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureDesc", "For3D", static_cast<int32>(TextureDesc::For3D)); assert(r >= 0);

		r = engine->RegisterEnumValue("TextureFormat", "Unknown", static_cast<int32>(TextureFormat::Unknown)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormat", "R8G8B8A8_Unorm", static_cast<int32>(TextureFormat::R8G8B8A8_Unorm)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormat", "R8G8B8A8_Unorm_SRGB", static_cast<int32>(TextureFormat::R8G8B8A8_Unorm_SRGB)); assert(r >= 0);
		
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Texture& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Image& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructIT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//	Texture(const Image& image, const Array<Image>& mipmaps, TextureDesc desc = TextureDesc::Mipped);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructFFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructCFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Emoji& in, TextureDesc = TextureDesc::Mipped)", asFUNCTION(ConstructEmT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Icon& in, TextureDesc = TextureDesc::Mipped)", asFUNCTION(ConstructIcT), asCALL_CDECL_OBJLAST); assert(r >= 0);


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

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion opImplConv() const", asFUNCTION(ConvToTextureRegion), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
