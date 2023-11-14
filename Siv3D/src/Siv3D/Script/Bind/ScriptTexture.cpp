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
# include <Siv3D/Texture.hpp>

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

	static void ConstructIT(const Image& image, int32 desc, BindType* self)
	{
		new(self) BindType(image, ToEnum<TextureDesc>(static_cast<uint8>(desc)));
	}

	static void ConstructFT(const FilePath& path, int32 desc, BindType* self)
	{
		new(self) BindType(path, ToEnum<TextureDesc>(static_cast<uint8>(desc)));
	}

	static void ConstructFFT(const FilePath& rgb, const FilePath& alpha, int32 desc, BindType* self)
	{
		new(self) BindType(rgb, alpha, ToEnum<TextureDesc>(static_cast<uint8>(desc)));
	}

	static void ConstructCFT(const Color& rgb, const FilePath& alpha, int32 desc, BindType* self)
	{
		new(self) BindType(rgb, alpha, ToEnum<TextureDesc>(static_cast<uint8>(desc)));
	}

	static void ConstructEmT(const Emoji& emoji, int32 desc, BindType* self)
	{
		new(self) BindType(emoji, ToEnum<TextureDesc>(static_cast<uint8>(desc)));
	}

	static void ConstructIcT(const Icon& icon, int32 size, int32 desc, BindType* self)
	{
		new(self) BindType(icon, size, ToEnum<TextureDesc>(static_cast<uint8>(desc)));
	}

	static void Release(Texture& texture)
	{
		texture.release();
	}

	static bool ConvToBool(const Texture& texture)
	{
		return static_cast<bool>(texture);
	}

	static bool IsEmpty(const Texture& texture)
	{
		return texture.isEmpty();
	}

	static bool Equals(const Texture& other, const Texture& texture)
	{
		return (texture == other);
	}

	//static TextureRegion ConvToTextureRegion(const Texture& texture)
	//{
	//	return texture;
	//}

	void RegisterTexture(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		constexpr char TypeName[] = "Texture";
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Texture& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Image& in, TextureDesc = TextureDesc::Unmipped) explicit", asFUNCTION(ConstructIT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//	Texture(const Image& image, const Array<Image>& mipmaps, TextureDesc desc = TextureDesc::Mipped);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, TextureDesc = TextureDesc::Unmipped) explicit", asFUNCTION(ConstructFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructFFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructCFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Emoji& in, TextureDesc = TextureDesc::Mipped) explicit", asFUNCTION(ConstructEmT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Icon& in, int32 size, TextureDesc = TextureDesc::Mipped) explicit", asFUNCTION(ConstructIcT), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Texture& opAssign(const Texture& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void release()", asFUNCTION(Release), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asFUNCTION(IsEmpty), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Texture& in)", asFUNCTION(Equals), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 width() const", asMETHODPR(BindType, width, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 height() const", asMETHODPR(BindType, height, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point size() const", asMETHODPR(BindType, size, () const, Size), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "TextureDesc getDesc() const", asMETHOD(BindType, getDesc), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasMipMap() const", asMETHODPR(BindType, hasMipMap, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool srgbSampling() const", asMETHODPR(BindType, srgbSampling, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isSDF() const", asMETHODPR(BindType, isSDF, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasDepth() const", asMETHODPR(BindType, hasDepth, () const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect region(int32, int32) const", asMETHODPR(BindType, region, (int32, int32) const, Rect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect region(Point = Point(0, 0)) const", asMETHODPR(BindType, region, (Point) const, Rect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF region(double, double) const", asMETHODPR(BindType, region, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF region(Vec2) const", asMETHODPR(BindType, region, (Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(double, double) const", asMETHODPR(BindType, regionAt, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(Vec2) const", asMETHODPR(BindType, regionAt, (Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, draw, (const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF draw(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(double x, double y, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, draw, (double, double, const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const Vec2& in, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, draw, (const Vec2&, const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(double x, double y, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, drawAt, (double, double, const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const Vec2& in, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, drawAt, (const Vec2&, const ColorF&, const ColorF&, const ColorF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF drawClipped(double x, double y, const RectF& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawClipped, (double, double, const RectF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawClipped(const Vec2& in, const RectF& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawClipped, (const Vec2&, const RectF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF drawAtClipped(double x, double y, const RectF& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAtClipped, (double, double, const RectF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAtClipped(const Vec2& in, const RectF& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAtClipped, (const Vec2&, const RectF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

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
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion scaled(Vec2) const", asMETHODPR(BindType, scaled, (Vec2) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion resized(double) const", asMETHODPR(BindType, resized, (double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion resized(double, double) const", asMETHODPR(BindType, resized, (double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion resized(Vec2) const", asMETHODPR(BindType, resized, (Vec2) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion repeated(double, double) const", asMETHODPR(BindType, repeated, (double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion repeated(Vec2) const", asMETHODPR(BindType, repeated, (Vec2) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion mapped(double, double) const", asMETHODPR(BindType, mapped, (double, double) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion mapped(Vec2) const", asMETHODPR(BindType, mapped, (Vec2) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion fitted(double, double, bool scaleUp = AllowScaleUp::Yes) const", asMETHODPR(BindType, fitted, (double, double, AllowScaleUp) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TextureRegion fitted(const Vec2& in, bool scaleUp = AllowScaleUp::Yes) const", asMETHODPR(BindType, fitted, (const Vec2&, AllowScaleUp) const, TextureRegion), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad rotated(double) const", asMETHODPR(BindType, rotated, (double) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad rotatedAt(double, double, double) const", asMETHODPR(BindType, rotatedAt, (double, double, double) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad rotatedAt(const Vec2& in, double) const", asMETHODPR(BindType, rotatedAt, (const Vec2&, double) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TexturedRoundRect rounded(double) const", asMETHODPR(BindType, rounded, (double) const, TexturedRoundRect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedRoundRect rounded(double, double, double, double, double) const", asMETHODPR(BindType, rounded, (double, double, double, double, double) const, TexturedRoundRect), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void swap(Texture& inout)", asMETHODPR(BindType, swap, (Texture&), void), asCALL_THISCALL); assert(r >= 0);
	}
}
