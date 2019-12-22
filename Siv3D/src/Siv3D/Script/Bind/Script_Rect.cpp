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
# include <Siv3D/Rectangle.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Rect;

	static void Construct(const Rect& rect, ShapeType* self)
	{
		new(self) ShapeType(rect);
	}

	static void ConstructI(int32 size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructII(int32 w, int32 h, ShapeType* self)
	{
		new(self) ShapeType(w, h);
	}

	static void ConstructS(const Size& size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructIII(int32 x, int32 y, int32 size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static void ConstructIIII(int32 x, int32 y, int32 w, int32 h, ShapeType* self)
	{
		new(self) ShapeType(x, y, w, h);
	}

	static void ConstructIIS(int32 x, int32 y, const Point& size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static void ConstructPI(const Point& pos, int32 size, ShapeType* self)
	{
		new(self) ShapeType(pos, size);
	}

	static void ConstructPII(const Point& pos, int32 w, int32 h, ShapeType* self)
	{
		new(self) ShapeType(pos, w, h);
	}

	static void ConstructPS(const Point& pos, const Point& size, ShapeType* self)
	{
		new(self) ShapeType(pos, size);
	}

	static RectF ConvToRectF(const ShapeType& rect)
	{
		return rect;
	}

	void RegisterRect(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Rect";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "int32 x", asOFFSET(ShapeType, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 y", asOFFSET(ShapeType, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 w", asOFFSET(ShapeType, w)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 h", asOFFSET(ShapeType, h)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Point pos", asOFFSET(ShapeType, pos)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Point size", asOFFSET(ShapeType, size)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Rect& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 size)", asFUNCTION(ConstructI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 w, int32 h)", asFUNCTION(ConstructII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 x, int32 y, int32 size)", asFUNCTION(ConstructIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 x, int32 y, int32 w, int32 h)", asFUNCTION(ConstructIIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 x, int32 y, const Point& in)", asFUNCTION(ConstructIIS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, int32 size)", asFUNCTION(ConstructPI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, int32 w, int32 h)", asFUNCTION(ConstructPII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, const Point& in)", asFUNCTION(ConstructPS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//	Arg::

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Rect& in) const", asMETHOD(ShapeType, operator==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect& setPos(int32, int32)", asMETHODPR(ShapeType, setPos, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setPos(const Point& in)", asMETHODPR(ShapeType, setPos, (const Point&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setCenter(int32, int32)", asMETHODPR(ShapeType, setCenter, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setCenter(const Point& in)", asMETHODPR(ShapeType, setCenter, (const Point&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setSize(int32, int32)", asMETHODPR(ShapeType, setSize, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setSize(const Point& in)", asMETHODPR(ShapeType, setSize, (const Size&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect& set(int32, int32, int32, int32)", asMETHODPR(ShapeType, set, (int32, int32, int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(int32, int32, int32)", asMETHODPR(ShapeType, set, (int32, int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(const Point& in, int32)", asMETHODPR(ShapeType, set, (const Point&, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(const Point& in, int32, int32)", asMETHODPR(ShapeType, set, (const Point&, int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(const Point& in, const Point& in)", asMETHODPR(ShapeType, set, (const Point&, const Size&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(const Rect& in)", asMETHODPR(ShapeType, set, (const Rect&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect movedBy(int32, int32) const", asMETHODPR(ShapeType, movedBy, (int32, int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect movedBy(const Point& in) const", asMETHODPR(ShapeType, movedBy, (const Point&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& moveBy(int32, int32)", asMETHODPR(ShapeType, moveBy, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& moveBy(const Point& in)", asMETHODPR(ShapeType, moveBy, (const Point&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(int32) const", asMETHODPR(ShapeType, stretched, (int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(int32, int32) const", asMETHODPR(ShapeType, stretched, (int32, int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(const Point& in) const", asMETHODPR(ShapeType, stretched, (const Size&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(int32, int32, int32, int32) const", asMETHODPR(ShapeType, stretched, (int32, int32, int32, int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF scaled(double) const", asMETHODPR(ShapeType, scaled, (double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaled(double, double) const", asMETHODPR(ShapeType, scaled, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaled(const Vec2& in) const", asMETHODPR(ShapeType, scaled, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(double, double, double) const", asMETHODPR(ShapeType, scaledAt, (double, double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(double, double, double, double) const", asMETHODPR(ShapeType, scaledAt, (double, double, double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(double, double, const Vec2& in) const", asMETHODPR(ShapeType, scaledAt, (double, double, const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(const Vec2& in, double) const", asMETHODPR(ShapeType, scaledAt, (const Vec2&, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(const Vec2& in, double, double) const", asMETHODPR(ShapeType, scaledAt, (const Vec2&, double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(const Vec2& in, const Vec2& in) const", asMETHODPR(ShapeType, scaledAt, (const Vec2&, const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point tl() const", asMETHOD(ShapeType, tl), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point tr() const", asMETHOD(ShapeType, tr), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point bl() const", asMETHOD(ShapeType, bl), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point br() const", asMETHOD(ShapeType, br), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 topCenter() const", asMETHOD(ShapeType, topCenter), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 bottomCenter() const", asMETHOD(ShapeType, bottomCenter), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 leftCenter() const", asMETHOD(ShapeType, leftCenter), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 rightCenter() const", asMETHOD(ShapeType, rightCenter), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 center() const", asMETHOD(ShapeType, center), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Line top() const", asMETHOD(ShapeType, top), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line right() const", asMETHOD(ShapeType, right), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line bottom() const", asMETHOD(ShapeType, bottom), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line left() const", asMETHOD(ShapeType, left), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 area() const", asMETHOD(ShapeType, area), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 perimeter() const", asMETHOD(ShapeType, perimeter), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Quad rotated() const", asMETHOD(ShapeType, rotated), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(double, double, double) const", asMETHODPR(ShapeType, rotatedAt, (double, double, double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(const Vec2& in, double) const", asMETHODPR(ShapeType, rotatedAt, (const Vec2&, double) const, Quad), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Quad shearedX(double) const", asMETHOD(ShapeType, shearedX), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad shearedY(double) const", asMETHOD(ShapeType, shearedY), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RoundRect rounded(double) const", asMETHODPR(ShapeType, rounded, (double) const, RoundRect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon rounded(double, double, double, double) const", asMETHODPR(ShapeType, rounded, (double, double, double, double) const, Polygon), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier3& in) const", asMETHODPR(ShapeType, intersects, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asMETHODPR(ShapeType, intersects, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asMETHODPR(ShapeType, intersects, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asMETHODPR(ShapeType, intersects, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asMETHODPR(ShapeType, intersects, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asMETHODPR(ShapeType, intersects, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asMETHODPR(ShapeType, intersects, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asMETHODPR(ShapeType, intersects, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asMETHODPR(ShapeType, intersects, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const MultiPolygon& in) const", asMETHODPR(ShapeType, intersects, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asMETHODPR(ShapeType, intersects, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		//intersectsAt

		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Point& in) const", asMETHODPR(ShapeType, contains, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Vec2& in) const", asMETHODPR(ShapeType, contains, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Line& in) const", asMETHODPR(ShapeType, contains, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Bezier2& in) const", asMETHODPR(ShapeType, contains, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Bezier3& in) const", asMETHODPR(ShapeType, contains, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Rect& in) const", asMETHODPR(ShapeType, contains, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const RectF& in) const", asMETHODPR(ShapeType, contains, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Circle& in) const", asMETHODPR(ShapeType, contains, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Ellipse& in) const", asMETHODPR(ShapeType, contains, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Triangle& in) const", asMETHODPR(ShapeType, contains, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Quad& in) const", asMETHODPR(ShapeType, contains, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const RoundRect& in) const", asMETHODPR(ShapeType, contains, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Polygon& in) const", asMETHODPR(ShapeType, contains, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const MultiPolygon& in) const", asMETHODPR(ShapeType, contains, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const LineString& in) const", asMETHODPR(ShapeType, contains, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHOD(ShapeType, leftClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHOD(ShapeType, leftPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHOD(ShapeType, leftReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHOD(ShapeType, rightClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHOD(ShapeType, rightPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHOD(ShapeType, rightReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHOD(ShapeType, mouseOver), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Rect& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		
		//draw (Colors)

		r = engine->RegisterObjectMethod(TypeName, "const Rect& drawFrame(double thickness = 1.0, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Rect& drawFrame(double inner, double outer, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Rect& drawShadow(const Vec2&in offset, double blurRadius, double spread = 0.0, const ColorF&in color = ColorF(0.0, 0.5)) const", asMETHOD(ShapeType, drawShadow), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad opCall(const Texture& in) const", asMETHODPR(ShapeType, operator(), (const Texture&) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad opCall(const TextureRegion& in) const", asMETHODPR(ShapeType, operator(), (const TextureRegion&) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);
		
		r = engine->RegisterObjectMethod(TypeName, "Polygon asPolygon() const", asMETHOD(ShapeType, asPolygon), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF opImplConv() const", asFUNCTION(ConvToRectF), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
