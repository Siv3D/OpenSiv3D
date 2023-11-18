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

	using ShapeType = Float2;

	static void Construct(const Float2& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructFF(float x, float y, ShapeType* self)
	{
		new(self) ShapeType(x, y);
	}

	static void ConstructP(const Point& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructV2(const Vec2& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructList(const float* list, ShapeType* self)
	{
		new(self) ShapeType(list[0], list[1]);
	}

	//static Float2 ConvToFloat2(const Vec2& v)
	//{
	//	return v;
	//}

	static Float2 MulFloat(float other, const ShapeType& value)
	{
		return (value * other);
	}

	static bool EqualsFloat2(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	void RegisterFloat2(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Float2";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "float x", asOFFSET(Float2, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float y", asOFFSET(Float2, y)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float2& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float x, float y)", asFUNCTION(ConstructFF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in)", asFUNCTION(ConstructP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in)", asFUNCTION(ConstructV2), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const float& in) {float, float}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// elem
		//
		r = engine->RegisterObjectMethod(TypeName, "float elem(size_t) const", asMETHODPR(Float2, elem, (size_t) const noexcept, float), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, -, *, /
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2 opNeg() const", asMETHODPR(Float2, operator-, () const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opAdd(Float2) const", asMETHODPR(Float2, operator+, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opSub(Float2) const", asMETHODPR(Float2, operator-, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opMul(float) const", asMETHODPR(Float2, operator*, (float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opMul(Float2) const", asMETHODPR(Float2, operator*, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opDiv(float) const", asMETHODPR(Float2, operator/, (float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opDiv(Float2) const", asMETHODPR(Float2, operator/, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opMul_r(float) const", asFUNCTION(MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	+=, -=, *=, /=
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2& opAddAssign(Float2)", asMETHODPR(Float2, operator+=, (Float2), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opSubAssign(Float2)", asMETHODPR(Float2, operator-=, (Float2), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opMulAssign(float)", asMETHODPR(Float2, operator*=, (float), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opMulAssign(Float2)", asMETHODPR(Float2, operator*=, (Float2), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opDivAssign(float)", asMETHODPR(Float2, operator/=, (float), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opDivAssign(Float2)", asMETHODPR(Float2, operator/=, (Float2), Float2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Float2& in) const", asFUNCTION(EqualsFloat2), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool epsilonEquals(Float2, float) const", asMETHODPR(Float2, epsilonEquals, (Float2, float) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasSameDirection(Float2) const", asMETHODPR(Float2, hasSameDirection, (Float2) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasOppositeDirection(Float2) const", asMETHODPR(Float2, hasOppositeDirection, (Float2) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHODPR(Float2, isZero, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHODPR(Float2, hasNaN, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float minComponent() const", asMETHODPR(Float2, minComponent, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float maxComponent() const", asMETHODPR(Float2, maxComponent, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHODPR(Float2, clear, () noexcept, void), asCALL_THISCALL); assert(r >= 0);

		//
		//	with
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2 withX(float) const", asMETHODPR(Float2, withX, (float) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 withY(float) const", asMETHODPR(Float2, withY, (float) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2& set(float, float)", asMETHODPR(Float2, set, (float, float), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& set(Float2)", asMETHODPR(Float2, set, (Float2), Float2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	movedBy
		//	
		r = engine->RegisterObjectMethod(TypeName, "Float2 movedBy(float, float) const", asMETHODPR(Float2, movedBy, (float, float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 movedBy(Float2) const", asMETHODPR(Float2, movedBy, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2& moveBy(float, float)", asMETHODPR(Float2, moveBy, (float, float), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& moveBy(Float2)", asMETHODPR(Float2, moveBy, (Float2), Float2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	clamp, clamped
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2 clamped(const RectF& in) const", asMETHODPR(Float2, clamped, (const RectF&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& clamp(const RectF& in)", asMETHODPR(Float2, clamp, (const RectF&), Float2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	Utils
		//
		r = engine->RegisterObjectMethod(TypeName, "float dot(Float2) const", asMETHODPR(Float2, dot, (Float2) const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float cross(Float2) const", asMETHODPR(Float2, cross, (Float2) const noexcept, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float length() const", asMETHODPR(Float2, length, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float lengthSq() const", asMETHODPR(Float2, lengthSq, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float invLength() const", asMETHODPR(Float2, invLength, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float manhattanLength() const", asMETHODPR(Float2, manhattanLength, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float manhattanDistanceFrom(float, float) const", asMETHODPR(Float2, manhattanDistanceFrom, (float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float manhattanDistanceFrom(Float2) const", asMETHODPR(Float2, manhattanDistanceFrom, (Float2) const, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float distanceFrom(float x, float y) const", asMETHODPR(Float2, distanceFrom, (float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFrom(Float2) const", asMETHODPR(Float2, distanceFrom, (Float2) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFromSq(float x, float y) const", asMETHODPR(Float2, distanceFromSq, (float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFromSq(Float2) const", asMETHODPR(Float2, distanceFromSq, (Float2) const, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 withLength(float) const", asMETHODPR(Float2, withLength, (float) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& setLength(float)", asMETHODPR(Float2, setLength, (float) noexcept, Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 limitLength(float) const", asMETHODPR(Float2, limitLength, (float) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& limitLengthSelf(float)", asMETHODPR(Float2, limitLengthSelf, (float) noexcept, Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 normalized() const", asMETHODPR(Float2, normalized, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& normalize()", asMETHODPR(Float2, normalize, () noexcept, Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 rotated(float) const", asMETHODPR(Float2, rotated, (float) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& rotate(float)", asMETHODPR(Float2, rotate, (float) noexcept, Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 rotatedAt(Float2, float) const", asMETHODPR(Float2, rotatedAt, (Float2, float) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& rotateAt(Float2, float)", asMETHODPR(Float2, rotateAt, (Float2, float) noexcept, Float2&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float getAngle() const", asMETHODPR(Float2, getAngle, () const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float getAngle(Float2) const", asMETHODPR(Float2, getAngle, (Float2) const, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 getPerpendicularCW() const", asMETHODPR(Float2, getPerpendicularCW, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 getPerpendicularCCW() const", asMETHODPR(Float2, getPerpendicularCCW, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 getMidpoint(Float2) const", asMETHODPR(Float2, getMidpoint, (Float2) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 projection(Float2) const", asMETHODPR(Float2, projection, (Float2) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 getPointByAngleAndDistance(float, float) const", asMETHODPR(Float2, getPointByAngleAndDistance, (float, float) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 lerp(Float2, float) const", asMETHODPR(Float2, lerp, (Float2, float) const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point asPoint() const", asMETHODPR(Float2, asPoint, () const noexcept, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle asCircle(double) const", asMETHODPR(Float2, asCircle, (double) const noexcept, Circle), asCALL_THISCALL); assert(r >= 0);

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

		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Float2, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 xx() const", asMETHODPR(Float2, xx, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 xy() const", asMETHODPR(Float2, xy, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yx() const", asMETHODPR(Float2, yx, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yy() const", asMETHODPR(Float2, yy, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 x0() const", asMETHODPR(Float2, x0, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 y0() const", asMETHODPR(Float2, y0, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 xy0() const", asMETHODPR(Float2, xy0, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Float2 Zero()", asFUNCTION(Float2::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 One()", asFUNCTION(Float2::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 All(float value = 1)", asFUNCTION(Float2::All), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 UnitX()", asFUNCTION(Float2::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 UnitY()", asFUNCTION(Float2::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 Left(float length = 1)", asFUNCTION(Float2::Left), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 Right(float length = 1)", asFUNCTION(Float2::Right), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 Up(float length = 1)", asFUNCTION(Float2::Up), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 Down(float length = 1)", asFUNCTION(Float2::Down), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Float2 AnchorCenter()", asFUNCTION(Float2::AnchorCenter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 AnchorTopLeft()", asFUNCTION(Float2::AnchorTopLeft), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 AnchorTopCenter()", asFUNCTION(Float2::AnchorTopCenter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 AnchorTopRight()", asFUNCTION(Float2::AnchorTopRight), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 AnchorRightCenter()", asFUNCTION(Float2::AnchorRightCenter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 AnchorBottomRight()", asFUNCTION(Float2::AnchorBottomRight), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 AnchorBottomCenter()", asFUNCTION(Float2::AnchorBottomCenter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 AnchorBottomLeft()", asFUNCTION(Float2::AnchorBottomLeft), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 AnchorLeftCenter()", asFUNCTION(Float2::AnchorLeftCenter), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "Float2 opImplConv() const", asFUNCTION(ConvToFloat2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
