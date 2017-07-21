//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void Point_Constructor(int32 x, int32 y, Point* self)
	{
		new(self) Point(x, y);
	}

	void Point_ConstructorList(int *list, Point* self)
	{
		new(self) Point(list[0], list[1]);
	}

	static Vec2 ConvToVec2(const Point& point)
	{
		return point;
	}

	void RegisterPoint(asIScriptEngine *engine)
	{
		const char TypeName[] = "Point";
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "int x", asOFFSET(Point, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int y", asOFFSET(Point, y)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int x, int y)", asFUNCTION(Point_Constructor), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const int &in) {int, int}", asFUNCTION(Point_ConstructorList), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point xx() const", asMETHOD(Point, xx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point xy() const", asMETHOD(Point, xy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point yx() const", asMETHOD(Point, yx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point yy() const", asMETHOD(Point, yy), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point opNeg() const", asMETHODPR(Point, operator-, () const, Point), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point opAdd(const Point &in) const", asMETHODPR(Point, operator+, (const Point&) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opSub(const Point &in) const", asMETHODPR(Point, operator-, (const Point&) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opMul(int) const", asMETHODPR(Point, operator*, (int) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(double) const", asMETHODPR(Point, operator*, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opMul(const Point &in) const", asMETHODPR(Point, operator*, (const Point&) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opDiv(int) const", asMETHODPR(Point, operator/, (int) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(double) const", asMETHODPR(Point, operator/, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point& opAddAssign(const Point &in)", asMETHODPR(Point, operator+=, (const Point&), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& opSubAssign(const Point &in)", asMETHODPR(Point, operator-=, (const Point&), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& opMulAssign(const Point &in)", asMETHODPR(Point, operator*=, (int), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& opDivAssign(const Point &in)", asMETHODPR(Point, operator/=, (int), Point&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Point &in) const", asMETHOD(Point, operator==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point& set(int, int)", asMETHODPR(Point, set, (int32, int32), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& set(const Point &in)", asMETHODPR(Point, set, (const Point&), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point movedBy(int, int) const", asMETHODPR(Point, movedBy, (int32, int32) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point movedBy(const Point &in) const", asMETHODPR(Point, movedBy, (const Point&) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& moveBy(int, int)", asMETHODPR(Point, moveBy, (int32, int32), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& moveBy(const Point &in)", asMETHODPR(Point, moveBy, (const Point&), Point&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHOD(Point, isZero), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(const Point &in) const", asMETHODPR(Point, distanceFrom, (const Point&) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(const Point &in) const", asMETHODPR(Point, distanceFromSq, (const Point&) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(const Vec2 &in) const", asMETHODPR(Point, distanceFrom, (const Vec2&) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(const Vec2 &in) const", asMETHODPR(Point, distanceFromSq, (const Vec2&) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<Point>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<Vec2>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<Rect>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<RectF>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<Circle>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<Ellipse>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<Line>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<Triangle>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<Quad>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<RoundRect>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<Polygon>)), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asSMethodPtr<sizeof(void (Point::*)())>::Convert((void (Point::*)())(&Point::intersects<LineString>)), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHOD(Point, leftClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHOD(Point, leftPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHOD(Point, leftReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHOD(Point, rightClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHOD(Point, rightPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHOD(Point, rightReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHOD(Point, mouseOver), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Point Zero()", asFUNCTION(Point::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point One()", asFUNCTION(Point::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point UnitX()", asFUNCTION(Point::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point UnitY()", asFUNCTION(Point::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Left(int length = 1)", asFUNCTION(Point::Left), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Right(int length = 1)", asFUNCTION(Point::Right), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Up(int length = 1)", asFUNCTION(Point::Up), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Down(int length = 1)", asFUNCTION(Point::Down), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point opMul_r(int) const", asFUNCTIONPR(operator*, (int32, const Point &), Point), asCALL_CDECL_OBJLAST);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul_r(double) const", asFUNCTIONPR(operator*, (double, const Point &), Vec2), asCALL_CDECL_OBJLAST);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opImplConv() const", asFUNCTION(ConvToVec2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
