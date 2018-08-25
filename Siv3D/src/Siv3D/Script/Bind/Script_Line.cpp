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
# include <Siv3D/Line.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Line;

	static void Construct(const Line& line, ShapeType* self)
	{
		new(self) ShapeType(line);
	}

	static void ConstructDDDD(double x0, double y0, double x1, double y1, ShapeType* self)
	{
		new(self) ShapeType(x0, y0, x1, y1);
	}

	static void ConstructVDD(const Vec2& pos, double x1, double y1, ShapeType* self)
	{
		new(self) ShapeType(pos, x1, y1);
	}

	static void ConstructDDV(double x0, double y0, const Vec2& pos, ShapeType* self)
	{
		new(self) ShapeType(x0, y0, pos);
	}

	static void ConstructVV(const Vec2& p0, const Vec2& p1, ShapeType* self)
	{
		new(self) ShapeType(p0, p1);
	}

	void RegisterLine(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Line";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "Vec2 begin", asOFFSET(ShapeType, begin)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 end", asOFFSET(ShapeType, end)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Line& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x0, double y0, double x1, double y1)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double x1, double y1)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x0, double y0, const Vec2& in)", asFUNCTION(ConstructDDV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, const Vec2& in)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Line& in) const", asMETHOD(Line, operator==), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Line& set(double, double, double, double)", asMETHODPR(Line, set, (double, double, double, double), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& set(const Vec2& in, double, double)", asMETHODPR(Line, set, (const Vec2&, double, double), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& set(double, double, const Vec2& in)", asMETHODPR(Line, set, (double, double, const Vec2&), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& set(const Vec2& in, const Vec2& in)", asMETHODPR(Line, set, (const Vec2&, const Vec2&), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& set(const Line& in)", asMETHODPR(Line, set, (const Line&), Line&), asCALL_THISCALL); assert(r >= 0);

		//
		//	movedBy
		//	
		r = engine->RegisterObjectMethod(TypeName, "Line movedBy(double, double) const", asMETHODPR(Line, movedBy, (double, double) const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line movedBy(const Vec2& in) const", asMETHODPR(Line, movedBy, (const Vec2&) const, Line), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Line& moveBy(double, double)", asMETHODPR(Line, moveBy, (double, double), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& moveBy(const Vec2& in)", asMETHODPR(Line, moveBy, (const Vec2&), Line&), asCALL_THISCALL); assert(r >= 0);

		//
		//	stretched
		//
		r = engine->RegisterObjectMethod(TypeName, "Line stretched(double) const", asMETHODPR(Line, stretched, (double) const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line stretched(double, double) const", asMETHODPR(Line, stretched, (double, double) const, Line), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 vector() const", asMETHOD(Line, vector), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Line reversed() const", asMETHOD(Line, reversed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& reverse()", asMETHOD(Line, reverse), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHOD(Line, length), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHOD(Line, lengthSq), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 center() const", asMETHOD(Line, center), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 closest() const", asMETHOD(Line, closest), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF boundingRect() const", asMETHOD(Line, boundingRect), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier3& in) const", asMETHODPR(ShapeType, intersects, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asMETHODPR(ShapeType, intersects, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asMETHODPR(ShapeType, intersects, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asMETHODPR(ShapeType, intersects, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asMETHODPR(ShapeType, intersects, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asMETHODPR(ShapeType, intersects, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asMETHODPR(ShapeType, intersects, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asMETHODPR(ShapeType, intersects, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asMETHODPR(ShapeType, intersects, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const MultiPolygon& in) const", asMETHODPR(ShapeType, intersects, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asMETHODPR(ShapeType, intersects, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		// intersectsAt

		// intersectsAtPrecise

		// paint
		
		// overwrite

		// paintArrow

		// overwriteArrow

		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(const ColorF& in, const ColorF& in) const", asMETHODPR(ShapeType, draw, (const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(double, const ColorF& in, const ColorF& in) const", asMETHODPR(ShapeType, draw, (double, const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(const LineStyle& in, double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const LineStyle&, double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(const LineStyle& in, double, const ColorF& in, const ColorF& in) const", asMETHODPR(ShapeType, draw, (const LineStyle&, double, const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& drawArrow(double width = 1.0, const Vec2& in headSize = Vec2(5.0, 5.0), const ColorF& in = Palette::White) const", asMETHOD(ShapeType, drawArrow), asCALL_THISCALL); assert(r >= 0);
	}
}
