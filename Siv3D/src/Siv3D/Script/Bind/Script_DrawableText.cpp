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
# include <Siv3D/Font.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = DrawableText;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const BindType& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructFS(const Font& font, const String& text, BindType* self)
	{
		new(self) BindType(font, text);
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	void RegisterDrawableText(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "DrawableText";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "Font font", asOFFSET(BindType, font)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "String text", asOFFSET(BindType, text)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TexturedCircle& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);	
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Font& in, const String& in)", asFUNCTION(ConstructFS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "DrawableText& opAssign(const DrawableText& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF boundingRect(double x, double y) const", asMETHODPR(BindType, boundingRect, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF boundingRect(const Vec2& in pos = Vec2(0, 0)) const", asMETHODPR(BindType, boundingRect, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF boundingRectAt(double x, double y) const", asMETHODPR(BindType, boundingRectAt, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF boundingRectAt(const Vec2& in pos = Vec2(0, 0)) const", asMETHODPR(BindType, boundingRectAt, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF region(double x, double y) const", asMETHODPR(BindType, region, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect region(const Point& in pos = Point(0, 0)) const", asMETHODPR(BindType, region, (const Point&) const, Rect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF region(const Vec2& in pos) const", asMETHODPR(BindType, region, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		
		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(double x, double y) const", asMETHODPR(BindType, regionAt, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(const Vec2& in pos) const", asMETHODPR(BindType, regionAt, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		//[[nodiscard]] Array<int32> getXAdvances() const;

		r = engine->RegisterObjectMethod(TypeName, "RectF draw(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool draw(const RectF& in area, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const RectF&, const ColorF&) const, bool), asCALL_THISCALL); assert(r >= 0);
	}
}
