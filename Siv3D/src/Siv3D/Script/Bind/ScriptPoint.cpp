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
# include <Siv3D/PointVector.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Geometry2D.hpp>

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

	static void ConstructListII(int32* list, ShapeType* self)
	{
		new(self) Point(list[0], list[1]);
	}

	static Point MulInt32(int32 other, const ShapeType& value)
	{
		return (value * other);
	}

	static Float2 MulFloat(float other, const ShapeType& value)
	{
		return (value * other);
	}

	static Vec2 MulDouble(double other, const ShapeType& value)
	{
		return (value * other);
	}

	static bool EqualsPoint(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	//static Float2 ConvToFloat2(const Point& point)
	//{
	//	return point;
	//}

	//static Vec2 ConvToVec2(const Point& point)
	//{
	//	return point;
	//}

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
		// elem
		//
		r = engine->RegisterObjectMethod(TypeName, "int32 elem(size_t) const", asMETHOD(Point, elem), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, -
		//
		r = engine->RegisterObjectMethod(TypeName, "Point opNeg() const", asMETHODPR(Point, operator-, () const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opAdd(Point) const", asMETHODPR(Point, operator+, (Point) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opSub(Point) const", asMETHODPR(Point, operator-, (Point) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opAdd(Float2) const", asMETHODPR(Point, operator+, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opSub(Float2) const", asMETHODPR(Point, operator-, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opAdd(Vec2) const", asMETHODPR(Point, operator+, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opSub(Vec2) const", asMETHODPR(Point, operator-, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		//
		//	*
		//
		r = engine->RegisterObjectMethod(TypeName, "Point opMul(int32) const", asMETHODPR(Point, operator*, (int32) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opMul(float) const", asMETHODPR(Point, operator*, (float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(double) const", asMETHODPR(Point, operator*, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opMul(Point) const", asMETHODPR(Point, operator*, (Point) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opMul(Float2) const", asMETHODPR(Point, operator*, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(Vec2) const", asMETHODPR(Point, operator*, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opMul_r(int32) const", asFUNCTION(MulInt32), asCALL_CDECL_OBJLAST);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opMul_r(float) const", asFUNCTION(MulFloat), asCALL_CDECL_OBJLAST);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul_r(double) const", asFUNCTION(MulDouble), asCALL_CDECL_OBJLAST);

		//
		//	/
		//	
		r = engine->RegisterObjectMethod(TypeName, "Point opDiv(int32) const", asMETHODPR(Point, operator/, (int32) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opDiv(float) const", asMETHODPR(Point, operator/, (float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(double) const", asMETHODPR(Point, operator/, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point opDiv(Point) const", asMETHODPR(Point, operator/, (Point) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opDiv(Float2) const", asMETHODPR(Point, operator/, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(Vec2) const", asMETHODPR(Point, operator/, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		//
		//	+=, -=, *=, /=
		//	
		r = engine->RegisterObjectMethod(TypeName, "Point& opAddAssign(Point)", asMETHODPR(Point, operator+=, (Point), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& opSubAssign(Point)", asMETHODPR(Point, operator-=, (Point), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& opMulAssign(int32)", asMETHODPR(Point, operator*=, (int32), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& opDivAssign(int32)", asMETHODPR(Point, operator/=, (int32), Point&), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Point& in) const", asFUNCTION(EqualsPoint), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHOD(Point, isZero), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 minComponent() const", asMETHOD(Point, minComponent), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 maxComponent() const", asMETHOD(Point, maxComponent), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHOD(Point, clear), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Point& set(int32, int32)", asMETHODPR(Point, set, (int32, int32), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& set(Point)", asMETHODPR(Point, set, (Point), Point&), asCALL_THISCALL); assert(r >= 0);

		//
		//	movedBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Point movedBy(int32, int32) const", asMETHODPR(Point, movedBy, (int32, int32) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point movedBy(Point) const", asMETHODPR(Point, movedBy, (Point) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 movedBy(Float2) const", asMETHODPR(Point, movedBy, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 movedBy(Vec2) const", asMETHODPR(Point, movedBy, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Point& moveBy(int32, int32)", asMETHODPR(Point, moveBy, (int32, int32), Point&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point& moveBy(Point)", asMETHODPR(Point, moveBy, (Point), Point&), asCALL_THISCALL); assert(r >= 0);

		//
		//	Utils
		//
		r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHODPR(Point, length, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHODPR(Point, lengthSq, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 manhattanLength() const", asMETHOD(Point, manhattanLength), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 manhattanDistanceFrom(int32, int32) const", asMETHODPR(Point, manhattanDistanceFrom, (int32, int32) const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 manhattanDistanceFrom(Point) const", asMETHODPR(Point, manhattanDistanceFrom, (Point) const, int32), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(double, double) const", asMETHODPR(Point, distanceFrom, (double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(Point) const", asMETHODPR(Point, distanceFrom, (Point) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(Float2) const", asMETHODPR(Point, distanceFrom, (Float2) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(Vec2) const", asMETHODPR(Point, distanceFrom, (Vec2) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(double, double) const", asMETHODPR(Point, distanceFromSq, (double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(Point) const", asMETHODPR(Point, distanceFromSq, (Point) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(Float2) const", asMETHODPR(Point, distanceFromSq, (Float2) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(Vec2) const", asMETHODPR(Point, distanceFromSq, (Vec2) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 area() const", asMETHOD(Point, area), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double getAngle() const", asMETHODPR(Point, getAngle, () const, double), asCALL_THISCALL); assert(r >= 0);	
		r = engine->RegisterObjectMethod(TypeName, "float getAngle(Float2) const", asMETHODPR(Point, getAngle, (Float2) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double getAngle(Vec2) const", asMETHODPR(Point, getAngle, (Vec2) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point getPerpendicularCW() const", asMETHOD(Point, getPerpendicularCW), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point getPerpendicularCCW() const", asMETHOD(Point, getPerpendicularCCW), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 getMidpoint(Point) const", asMETHODPR(Point, getMidpoint, (Point) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 getMidpoint(Float2) const", asMETHODPR(Point, getMidpoint, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 getMidpoint(Vec2) const", asMETHODPR(Point, getMidpoint, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 getPointByAngleAndDistance(double, double) const", asMETHODPR(Point, getPointByAngleAndDistance, (double, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 lerp(Point, double) const", asMETHODPR(Point, lerp, (Point, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 lerp(Float2, double) const", asMETHODPR(Point, lerp, (Float2, double) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 lerp(Vec2, double) const", asMETHODPR(Point, lerp, (Vec2, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle asCircle(double) const", asMETHOD(Point, asCircle), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
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

		//paint
		//overwrite

		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHOD(Point, hash), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point xx() const", asMETHOD(Point, xx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point xy() const", asMETHOD(Point, xy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point yx() const", asMETHOD(Point, yx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point yy() const", asMETHOD(Point, yy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point x0() const", asMETHOD(Point, x0), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point y0() const", asMETHOD(Point, y0), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Point Zero()", asFUNCTION(Point::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point One()", asFUNCTION(Point::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point All(int32 value = 1)", asFUNCTION(Point::All), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point UnitX()", asFUNCTION(Point::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point UnitY()", asFUNCTION(Point::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Left(int32 length = 1)", asFUNCTION(Point::Left), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Right(int32 length = 1)", asFUNCTION(Point::Right), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Up(int32 length = 1)", asFUNCTION(Point::Up), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Down(int32 length = 1)", asFUNCTION(Point::Down), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "Float2 opImplConv() const", asFUNCTION(ConvToFloat2), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Vec2 opImplConv() const", asFUNCTION(ConvToVec2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
