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
# include <Siv3D/Ellipse.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Ellipse;

	static void Construct(const Ellipse& ellipse, ShapeType* self)
	{
		new(self) ShapeType(ellipse);
	}

	static void ConstructD(double r, ShapeType* self)
	{
		new(self) ShapeType(r);
	}

	static void ConstructDD(double a, double b, ShapeType* self)
	{
		new(self) ShapeType(a, b);
	}

	static void ConstructDDD(double x, double y, double r, ShapeType* self)
	{
		new(self) ShapeType(x, y, r);
	}

	static void ConstructDDDD(double x, double y, double a, double b, ShapeType* self)
	{
		new(self) ShapeType(x, y, a, b);
	}

	static void ConstructV(const Vec2& center, ShapeType* self)
	{
		new(self) ShapeType(center);
	}

	static void ConstructVD(const Vec2& center, double r, ShapeType* self)
	{
		new(self) ShapeType(center, r);
	}

	static void ConstructVDD(const Vec2& center, double a, double b, ShapeType* self)
	{
		new(self) ShapeType(center, a, b);
	}

	static void ConstructDDV(double x, double y, const Vec2& axis, ShapeType* self)
	{
		new(self) ShapeType(x, y, axis);
	}

	static void ConstructVV(const Vec2& center, const Vec2& axis, ShapeType* self)
	{
		new(self) ShapeType(center, axis);
	}

	static void ConstructC(const Circle& circle, ShapeType* self)
	{
		new(self) ShapeType(circle);
	}

	static void ConstructR(const RectF& rect, ShapeType* self)
	{
		new(self) ShapeType(rect);
	}

	void RegisterEllipse(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Ellipse";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(ShapeType, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(ShapeType, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double a", asOFFSET(ShapeType, a)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double b", asOFFSET(ShapeType, b)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 center", asOFFSET(ShapeType, center)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Ellipse& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double r)", asFUNCTION(ConstructD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double a, double b)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double r)", asFUNCTION(ConstructDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double a, double b)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in center)", asFUNCTION(ConstructV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in center, double r)", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in center, double a, double b)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, const Vec2&in axis)", asFUNCTION(ConstructDDV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in center, const Vec2&in axis)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Circle& in)", asFUNCTION(ConstructC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const RectF& in)", asFUNCTION(ConstructR), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Ellipse& in) const", asMETHOD(ShapeType, operator==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 top() const", asMETHOD(ShapeType, top), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 bottom() const", asMETHOD(ShapeType, bottom), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 left() const", asMETHOD(ShapeType, left), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 right() const", asMETHOD(ShapeType, right), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Ellipse& set(double x, double y, double a, double b)", asMETHODPR(ShapeType, set, (double, double, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse& set(const Vec2& in center, double r)", asMETHODPR(ShapeType, set, (const Vec2&, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse& set(const Vec2& in center, double a, double b)", asMETHODPR(ShapeType, set, (const Vec2&, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Ellipse& set(double x, double y, const Vec2&in axis)", asMETHODPR(ShapeType, set, (double, double, const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse& set(const Vec2& in center, const Vec2& in axis)", asMETHODPR(ShapeType, set, (const Vec2&, const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Ellipse& set(const Circle& in)", asMETHODPR(ShapeType, set, (const Circle&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse& set(const RectF& in)", asMETHODPR(ShapeType, set, (const RectF&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse& set(const Ellipse& in)", asMETHODPR(ShapeType, set, (const Ellipse&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Ellipse& setCenter(double x, double y)", asMETHODPR(ShapeType, setCenter, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse& setCenter(const Vec2& in)", asMETHODPR(ShapeType, setCenter, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Ellipse& setPos(double x, double y)", asMETHODPR(ShapeType, setPos, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse& setPos(const Vec2&in center)", asMETHODPR(ShapeType, setPos, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Ellipse movedBy(double x, double y) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse movedBy(const Vec2&in xy) const", asMETHODPR(ShapeType, movedBy, (const Vec2&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse& moveBy(double x, double y)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse& moveBy(const Vec2&in xy)", asMETHODPR(ShapeType, moveBy, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Ellipse stretched(double size) const", asMETHODPR(ShapeType, stretched, (double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse stretched(double x, double y) const", asMETHODPR(ShapeType, stretched, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Ellipse scaled(double s) const", asMETHODPR(ShapeType, scaled, (double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse scaled(double sx, double sy) const", asMETHODPR(ShapeType, scaled, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double area() const", asMETHOD(ShapeType, area), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF boundingRect() const", asMETHOD(ShapeType, boundingRect), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier3& in) const", asMETHODPR(ShapeType, intersects, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asMETHODPR(ShapeType, intersects, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asMETHODPR(ShapeType, intersects, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asMETHODPR(ShapeType, intersects, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asMETHODPR(ShapeType, intersects, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asMETHODPR(ShapeType, intersects, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asMETHODPR(ShapeType, intersects, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asMETHODPR(ShapeType, intersects, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asMETHODPR(ShapeType, intersects, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const MultiPolygon& in) const", asMETHODPR(ShapeType, intersects, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asMETHODPR(ShapeType, intersects, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		// intersectsAt

		// contains

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHOD(ShapeType, leftClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHOD(ShapeType, leftPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHOD(ShapeType, leftReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHOD(ShapeType, rightClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHOD(ShapeType, rightPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHOD(ShapeType, rightReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHOD(ShapeType, mouseOver), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Ellipse& draw(const ColorF& in color = Palette::White) const", asMETHOD(ShapeType, draw), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Ellipse& drawFrame(double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const Ellipse&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Ellipse& drawFrame(double inner, double outer, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const Ellipse&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon asPolygon(uint32 quality = 24) const", asMETHOD(ShapeType, asPolygon), asCALL_THISCALL); assert(r >= 0);
	}
}
