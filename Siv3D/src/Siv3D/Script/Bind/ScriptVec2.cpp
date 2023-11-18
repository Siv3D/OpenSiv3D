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
# include <Siv3D/PointVector.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Geometry2D.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Vec2;

	static void Construct(const Vec2& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructDD(double x, double y, ShapeType* self)
	{
		new(self) ShapeType(x, y);
	}

	static void ConstructP(const Point& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructF2(const Float2& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructList(const double* list, ShapeType* self)
	{
		new(self) ShapeType(list[0], list[1]);
	}

	//static Float2 ConvToFloat2(const Vec2& v)
	//{
	//	return v;
	//}

	static Vec2 MulDouble(double other, const ShapeType& value)
	{
		return (value * other);
	}

	static bool EqualsVec2(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	void RegisterVec2(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "Vec2";
			r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(Vec2, x)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(Vec2, y)); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in)", asFUNCTION(ConstructP), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float2& in)", asFUNCTION(ConstructF2), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const double& in) {double, double}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

			//
			// elem
			//
			r = engine->RegisterObjectMethod(TypeName, "double elem(size_t) const", asMETHODPR(Vec2, elem, (size_t) const noexcept, double), asCALL_THISCALL); assert(r >= 0);

			//
			//	+, -, *, /
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec2 opNeg() const", asMETHODPR(Vec2, operator-, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 opAdd(Vec2) const", asMETHODPR(Vec2, operator+, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 opSub(Vec2) const", asMETHODPR(Vec2, operator-, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(double) const", asMETHODPR(Vec2, operator*, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(Vec2) const", asMETHODPR(Vec2, operator*, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(double) const", asMETHODPR(Vec2, operator/, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(Vec2) const", asMETHODPR(Vec2, operator/, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul_r(double) const", asFUNCTION(MulDouble), asCALL_CDECL_OBJLAST); assert(r >= 0);

			//
			//	+=, -=, *=, /=
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec2& opAddAssign(Vec2)", asMETHODPR(Vec2, operator+=, (Vec2), Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& opSubAssign(Vec2)", asMETHODPR(Vec2, operator-=, (Vec2), Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& opMulAssign(double)", asMETHODPR(Vec2, operator*=, (double), Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& opMulAssign(Vec2)", asMETHODPR(Vec2, operator*=, (Vec2), Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& opDivAssign(double)", asMETHODPR(Vec2, operator/=, (double), Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& opDivAssign(Vec2)", asMETHODPR(Vec2, operator/=, (Vec2), Vec2&), asCALL_THISCALL); assert(r >= 0);

			//
			//	==, !=
			//
			r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Vec2& in) const", asFUNCTION(EqualsVec2), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool epsilonEquals(Vec2, double) const", asMETHODPR(Vec2, epsilonEquals, (Vec2, double) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasSameDirection(Vec2) const", asMETHODPR(Vec2, hasSameDirection, (Vec2) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasOppositeDirection(Vec2) const", asMETHODPR(Vec2, hasOppositeDirection, (Vec2) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHODPR(Vec2, isZero, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHODPR(Vec2, hasNaN, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double minComponent() const", asMETHODPR(Vec2, minComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double maxComponent() const", asMETHODPR(Vec2, maxComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHODPR(Vec2, clear, () noexcept, void), asCALL_THISCALL); assert(r >= 0);

			//
			//	with
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec2 withX(double) const", asMETHODPR(Vec2, withX, (double) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 withY(double) const", asMETHODPR(Vec2, withY, (double) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

			//
			//	set
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec2& set(double, double)", asMETHODPR(Vec2, set, (double, double), Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& set(Vec2)", asMETHODPR(Vec2, set, (Vec2), Vec2&), asCALL_THISCALL); assert(r >= 0);

			//
			//	movedBy
			//	
			r = engine->RegisterObjectMethod(TypeName, "Vec2 movedBy(double, double) const", asMETHODPR(Vec2, movedBy, (double, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 movedBy(Vec2) const", asMETHODPR(Vec2, movedBy, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);

			//
			//	moveBy
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec2& moveBy(double, double)", asMETHODPR(Vec2, moveBy, (double, double), Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& moveBy(Vec2)", asMETHODPR(Vec2, moveBy, (Vec2), Vec2&), asCALL_THISCALL); assert(r >= 0);

			//
			//	clamp, clamped
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec2 clamped(const RectF& in) const", asMETHODPR(Vec2, clamped, (const RectF&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& clamp(const RectF& in)", asMETHODPR(Vec2, clamp, (const RectF&), Vec2&), asCALL_THISCALL); assert(r >= 0);

			//
			//	Utils
			//
			r = engine->RegisterObjectMethod(TypeName, "double dot(Vec2) const", asMETHODPR(Vec2, dot, (Vec2) const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double cross(Vec2) const", asMETHODPR(Vec2, cross, (Vec2) const noexcept, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHODPR(Vec2, length, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHODPR(Vec2, lengthSq, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double invLength() const", asMETHODPR(Vec2, invLength, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double manhattanLength() const", asMETHODPR(Vec2, manhattanLength, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double manhattanDistanceFrom(double, double) const", asMETHODPR(Vec2, manhattanDistanceFrom, (double, double) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double manhattanDistanceFrom(Vec2) const", asMETHODPR(Vec2, manhattanDistanceFrom, (Vec2) const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(double x, double y) const", asMETHODPR(Vec2, distanceFrom, (double, double) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(Vec2) const", asMETHODPR(Vec2, distanceFrom, (Vec2) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(double x, double y) const", asMETHODPR(Vec2, distanceFromSq, (double, double) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(Vec2) const", asMETHODPR(Vec2, distanceFromSq, (Vec2) const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec2 withLength(double) const", asMETHODPR(Vec2, withLength, (double) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& setLength(double)", asMETHODPR(Vec2, setLength, (double) noexcept, Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 limitLength(double) const", asMETHODPR(Vec2, limitLength, (double) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& limitLengthSelf(double)", asMETHODPR(Vec2, limitLengthSelf, (double) noexcept, Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 normalized() const", asMETHODPR(Vec2, normalized, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& normalize()", asMETHODPR(Vec2, normalize, () noexcept, Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 rotated(double) const", asMETHODPR(Vec2, rotated, (double) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& rotate(double)", asMETHODPR(Vec2, rotate, (double) noexcept, Vec2&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 rotatedAt(Vec2, double) const", asMETHODPR(Vec2, rotatedAt, (Vec2, double) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2& rotateAt(Vec2, double)", asMETHODPR(Vec2, rotateAt, (Vec2, double) noexcept, Vec2&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double getAngle() const", asMETHODPR(Vec2, getAngle, () const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double getAngle(Vec2) const", asMETHODPR(Vec2, getAngle, (Vec2) const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec2 getPerpendicularCW() const", asMETHODPR(Vec2, getPerpendicularCW, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 getPerpendicularCCW() const", asMETHODPR(Vec2, getPerpendicularCCW, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 getMidpoint(Vec2) const", asMETHODPR(Vec2, getMidpoint, (Vec2) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 projection(Vec2) const", asMETHODPR(Vec2, projection, (Vec2) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec2 getPointByAngleAndDistance(double, double) const", asMETHODPR(Vec2, getPointByAngleAndDistance, (double, double) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 lerp(Vec2, double) const", asMETHODPR(Vec2, lerp, (Vec2, double) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Point asPoint() const", asMETHODPR(Vec2, asPoint, () const noexcept, Point), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Circle asCircle(double) const", asMETHODPR(Vec2, asCircle, (double) const noexcept, Circle), asCALL_THISCALL); assert(r >= 0);

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

			r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Vec2, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec2 xx() const", asMETHODPR(Vec2, xx, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 xy() const", asMETHODPR(Vec2, xy, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 yx() const", asMETHODPR(Vec2, yx, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 yy() const", asMETHODPR(Vec2, yy, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 x0() const", asMETHODPR(Vec2, x0, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 y0() const", asMETHODPR(Vec2, y0, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 xy0() const", asMETHODPR(Vec2, xy0, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);

			r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
			{
				r = engine->RegisterGlobalFunction("Vec2 Zero()", asFUNCTION(Vec2::Zero), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 One()", asFUNCTION(Vec2::One), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 All(double value = 1)", asFUNCTION(Vec2::All), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 UnitX()", asFUNCTION(Vec2::UnitX), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 UnitY()", asFUNCTION(Vec2::UnitY), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 Left(double length = 1)", asFUNCTION(Vec2::Left), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 Right(double length = 1)", asFUNCTION(Vec2::Right), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 Up(double length = 1)", asFUNCTION(Vec2::Up), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 Down(double length = 1)", asFUNCTION(Vec2::Down), asCALL_CDECL); assert(r >= 0);

				r = engine->RegisterGlobalFunction("Vec2 AnchorCenter()", asFUNCTION(Vec2::AnchorCenter), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 AnchorTopLeft()", asFUNCTION(Vec2::AnchorTopLeft), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 AnchorTopCenter()", asFUNCTION(Vec2::AnchorTopCenter), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 AnchorTopRight()", asFUNCTION(Vec2::AnchorTopRight), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 AnchorRightCenter()", asFUNCTION(Vec2::AnchorRightCenter), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 AnchorBottomRight()", asFUNCTION(Vec2::AnchorBottomRight), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 AnchorBottomCenter()", asFUNCTION(Vec2::AnchorBottomCenter), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 AnchorBottomLeft()", asFUNCTION(Vec2::AnchorBottomLeft), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec2 AnchorLeftCenter()", asFUNCTION(Vec2::AnchorLeftCenter), asCALL_CDECL); assert(r >= 0);
			}
			r = engine->SetDefaultNamespace(""); assert(r >= 0);

			//r = engine->RegisterObjectMethod(TypeName, "Float2 opImplConv() const", asFUNCTION(ConvToFloat2), asCALL_CDECL_OBJLAST); assert(r >= 0);
		}
	}
}
