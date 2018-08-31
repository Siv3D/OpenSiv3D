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
# include <Siv3D/TextureRegion.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = TextureRegion;

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
		self->~TextureRegion();
	}

	void RegisterTextureRegion(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "TextureRegion";

		int32 r = 0;

		//members
		//

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TextureRegion& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TextureRegion& opAssign(const Texture& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF region(double, double) const", asMETHODPR(BindType, region, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF region(const Vec2& in pos = Vec2(0, 0)) const", asMETHODPR(BindType, region, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);
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

		//[[nodiscard]] TextureRegion mirrored() const;

		//[[nodiscard]] TextureRegion mirrored(bool doMirror) const;

		//[[nodiscard]] TextureRegion flipped() const;

		//[[nodiscard]] TextureRegion flipped(bool doFlip) const;

		//[[nodiscard]] TextureRegion scaled(double s) const;

		//[[nodiscard]] TextureRegion scaled(double sx, double sy) const;

		//[[nodiscard]] TextureRegion scaled(const Vec2& s) const;

		//[[nodiscard]] TextureRegion resized(double _size) const;

		//[[nodiscard]] TextureRegion resized(double width, double height) const;

		//[[nodiscard]] TextureRegion resized(const Vec2& _size) const;

		//[[nodiscard]] TextureRegion fitted(double width, double height, bool scaleUp = true) const;

		//[[nodiscard]] TextureRegion fitted(const Vec2& _size, bool scaleUp = true) const;

		//[[nodiscard]] TexturedQuad rotated(double angle) const;

		//[[nodiscard]] TexturedQuad rotatedAt(double x, double y, double angle) const;

		//[[nodiscard]] TexturedQuad rotatedAt(const Vec2& pos, double angle) const;
	}
}
