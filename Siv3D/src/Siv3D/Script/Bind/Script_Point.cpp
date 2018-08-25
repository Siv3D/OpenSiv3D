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
# include <Siv3D/Point.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Point;

	static void Construct(const Point& pos, ShapeType* self)
	{
		new(self) Point(pos);
	}

	static void ConstructII(int32 x, int32 y, ShapeType* self)
	{
		new(self) Point(x, y);
	}

	static void ConstructListII(int32 *list, ShapeType* self)
	{
		new(self) Point(list[0], list[1]);
	}

	static Vec2 ConvToVec2(const Point& point)
	{
		return point;
	}

	void RegisterPoint(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Point";
		
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "int32 x", asOFFSET(Point, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 y", asOFFSET(Point, y)); assert(r >= 0);

		//
		//	Constructor
		//
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 x, int32 y)", asFUNCTION(ConstructII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const int32& in) {int32, int32}", asFUNCTION(ConstructListII), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	+, -
		//
		r = engine->RegisterObjectMethod(TypeName, "Point opNeg() const", asMETHODPR(Point, operator-, () const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opAdd(const Point& in) const", asMETHODPR(Point, operator+, (const Point&) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opSub(const Point& in) const", asMETHODPR(Point, operator-, (const Point&) const, Point), asCALL_THISCALL); assert(r >= 0);		
		//r = engine->RegisterObjectMethod(TypeName, "Float2 opAdd(const Float2& in) const", asMETHODPR(Point, operator+, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Float2 opSub(const Float2& in) const", asMETHODPR(Point, operator-, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opAdd(const Vec2& in) const", asMETHODPR(Point, operator+, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opSub(const Vec2& in) const", asMETHODPR(Point, operator-, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		//
		//	*
		//
		r = engine->RegisterObjectMethod(TypeName, "Point opMul(int32) const", asMETHODPR(Point, operator*, (int32) const, Point), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Float2 opMul(float) const", asMETHODPR(Point, operator*, (float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(double) const", asMETHODPR(Point, operator*, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opMul(const Point& in) const", asMETHODPR(Point, operator*, (const Point&) const, Point), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Float2 opMul(const Float2& in) const", asMETHODPR(Point, operator*, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(const Vec2& in) const", asMETHODPR(Point, operator*, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		//
		//	/
		//	
		r = engine->RegisterObjectMethod(TypeName, "Point opDiv(int32) const", asMETHODPR(Point, operator/, (int32) const, Point), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Float2 opDiv(double) const", asMETHODPR(Point, operator/, (float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(double) const", asMETHODPR(Point, operator/, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opDiv(const Point& in) const", asMETHODPR(Point, operator/, (const Point&) const, Point), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Float2 opDiv(const Float2& in) const", asMETHODPR(Point, operator/, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(const Vec2& in) const", asMETHODPR(Point, operator/, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		//
		//	+=, -=, *=, /=
		//	
		r = engine->RegisterObjectMethod(TypeName, "Point& opAddAssign(const Point& in)", asMETHODPR(Point, operator+=, (const Point&), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& opSubAssign(const Point& in)", asMETHODPR(Point, operator-=, (const Point&), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& opMulAssign(int32)", asMETHODPR(Point, operator*=, (int32), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& opDivAssign(int32)", asMETHODPR(Point, operator/=, (int32), Point&), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Point& in) const", asMETHOD(Point, operator==), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Point& set(int32, int32)", asMETHODPR(Point, set, (int32, int32), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& set(const Point& in)", asMETHODPR(Point, set, (const Point&), Point&), asCALL_THISCALL); assert(r >= 0);

		//
		//	movedBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Point movedBy(int32, int32) const", asMETHODPR(Point, movedBy, (int32, int32) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point movedBy(const Point& in) const", asMETHODPR(Point, movedBy, (const Point&) const, Point), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Float2 movedBy(const Float2& in) const", asMETHODPR(Point, movedBy, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 movedBy(const Vec2& in) const", asMETHODPR(Point, movedBy, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Point& moveBy(int32, int32)", asMETHODPR(Point, moveBy, (int32, int32), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& moveBy(const Point& in)", asMETHODPR(Point, moveBy, (const Point&), Point&), asCALL_THISCALL); assert(r >= 0);

		//
		//	Utils
		//
		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHOD(Point, isZero), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(double, double) const", asMETHODPR(Point, distanceFrom, (double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(const Point& in) const", asMETHODPR(Point, distanceFrom, (const Point&) const, double), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(const Float2 &in) const", asMETHODPR(Point, distanceFrom, (const Float2&) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(const Vec2& in) const", asMETHODPR(Point, distanceFrom, (const Vec2&) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(double, double) const", asMETHODPR(Point, distanceFromSq, (double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(const Point& in) const", asMETHODPR(Point, distanceFromSq, (const Point&) const, double), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(const Float2 &in) const", asMETHODPR(Point, distanceFromSq, (const Float2&) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(const Vec2& in) const", asMETHODPR(Point, distanceFromSq, (const Vec2&) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHODPR(Point, length, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHODPR(Point, lengthSq, () const, double), asCALL_THISCALL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "Float2 lerp(const Float2 &in, double) const", asMETHODPR(Point, lerp, (const Float2&, double) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 lerp(const Vec2& in, double) const", asMETHODPR(Point, lerp, (const Vec2&, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);

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

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHOD(Point, leftClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHOD(Point, leftPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHOD(Point, leftReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHOD(Point, rightClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHOD(Point, rightPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHOD(Point, rightReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHOD(Point, mouseOver), asCALL_THISCALL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "const Point& paint(Image& inout, int, const Color& in) const", asMETHOD(Point, paint), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "const Point& overwrite(Image& inout, int, const Color& in) const", asMETHOD(Point, overwrite), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point xx() const", asMETHOD(Point, xx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point xy() const", asMETHOD(Point, xy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point yx() const", asMETHOD(Point, yx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point yy() const", asMETHOD(Point, yy), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Point Zero()", asFUNCTION(Point::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point One()", asFUNCTION(Point::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point All()", asFUNCTION(Point::All), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point UnitX()", asFUNCTION(Point::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point UnitY()", asFUNCTION(Point::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Left(int32 length = 1)", asFUNCTION(Point::Left), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Right(int32 length = 1)", asFUNCTION(Point::Right), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Up(int32 length = 1)", asFUNCTION(Point::Up), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Down(int32 length = 1)", asFUNCTION(Point::Down), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point opMul_r(int32) const", asFUNCTIONPR(operator*, (int32, const Point &), Point), asCALL_CDECL_OBJLAST);
		//r = engine->RegisterObjectMethod(TypeName, "Float2 opMul_r(float) const", asFUNCTIONPR(operator*, (float, const Point &), Float2), asCALL_CDECL_OBJLAST);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul_r(double) const", asFUNCTIONPR(operator*, (double, const Point &), Vec2), asCALL_CDECL_OBJLAST);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opImplConv() const", asFUNCTION(ConvToVec2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
