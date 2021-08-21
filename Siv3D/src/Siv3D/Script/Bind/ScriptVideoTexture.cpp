//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/VideoTexture.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = VideoTexture;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const VideoTexture& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void Destruct(BindType* self)
	{
		self->~VideoTexture();
	}

	static void ConstructS(const FilePath& path, bool loop, int32 desc, BindType* self)
	{
		new(self) BindType(path, Loop{ loop }, ToEnum<TextureDesc>(static_cast<uint8>(desc)));
	}

	static bool ConvToBool(const VideoTexture& texture)
	{
		return static_cast<bool>(texture);
	}

	//static TextureRegion ConvToTextureRegion(const VideoTexture& texture)
	//{
	//	return texture;
	//}

	void RegisterVideoTexture(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "VideoTexture";

		int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const VideoTexture& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, bool loop = Loop::Yes, TextureDesc = TextureDesc::Unmipped) explicit", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
	
		r = engine->RegisterObjectMethod(TypeName, "VideoTexture& opAssign(const VideoTexture& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(BindType, isEmpty), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void release() const", asMETHOD(BindType, release), asCALL_THISCALL); assert(r >= 0);
	
		r = engine->RegisterObjectMethod(TypeName, "void advance(double deltaTimeSec = Scene::DeltaTime()) const", asMETHOD(BindType, advance), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void reset() const", asMETHOD(BindType, reset), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isLoop() const", asMETHOD(BindType, isLoop), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool posSec() const", asMETHOD(BindType, posSec), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool lengthSec() const", asMETHOD(BindType, lengthSec), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setPosSec(double) const", asMETHOD(BindType, setPosSec), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Texture& getTexture() const", asMETHOD(BindType, getTexture), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Texture& opImplConv() const", asMETHOD(BindType, getTexture), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 width() const", asMETHOD(BindType, width), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 height() const", asMETHOD(BindType, height), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point size() const", asMETHOD(BindType, size), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "TextureDesc getDesc() const", asMETHOD(BindType, getDesc), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isMipped() const", asMETHOD(BindType, isMipped), asCALL_THISCALL); assert(r >= 0);

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
		r = engine->RegisterObjectMethod(TypeName, "RectF drawClipped(const Vec2& in, const RectF& in, const ColorF& in, const ColorF& in, const ColorF& in, const ColorF& in) const", asMETHODPR(BindType, drawClipped, (const Vec2&, const RectF&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

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

		r = engine->RegisterObjectMethod(TypeName, "void swap(VideoTexture& inout)", asMETHOD(BindType, swap), asCALL_THISCALL); assert(r >= 0);
	}
}
