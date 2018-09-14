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
# include <Siv3D/PointVector.hpp>
# include "ScriptBind.hpp"

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

	static Float2 ConvToFloat2(const Vec2& v)
	{
		return v;
	}

	void RegisterVec2(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Vec2";
		
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(Vec2, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(Vec2, y)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in)", asFUNCTION(ConstructP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float2& in)", asFUNCTION(ConstructF2), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const double& in) {double, double}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double elem(uint64) const", asMETHOD(Vec2, elem), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, -, *, /
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opNeg() const", asMETHODPR(Vec2, operator-, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opAdd(const Vec2& in) const", asMETHODPR(Vec2, operator+, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opSub(const Vec2& in) const", asMETHODPR(Vec2, operator-, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(double) const", asMETHODPR(Vec2, operator*, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(const Vec2& in) const", asMETHODPR(Vec2, operator*, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(double) const", asMETHODPR(Vec2, operator/, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(const Vec2& in) const", asMETHODPR(Vec2, operator/, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		//
		//	+=, -=, *=, /=
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opAddAssign(const Vec2& in)", asMETHODPR(Vec2, operator+=, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opSubAssign(const Vec2& in)", asMETHODPR(Vec2, operator-=, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opMulAssign(double)", asMETHODPR(Vec2, operator*=, (double), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opMulAssign(const Vec2& in)", asMETHODPR(Vec2, operator*=, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opDivAssign(double)", asMETHODPR(Vec2, operator/=, (double), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opDivAssign(const Vec2& in)", asMETHODPR(Vec2, operator/=, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Vec2& in) const", asMETHOD(Vec2, operator==), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec2& set(double, double)", asMETHODPR(Vec2, set, (double, double), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& set(const Vec2& in)", asMETHODPR(Vec2, set, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);
		
		//
		//	movedBy
		//	
		r = engine->RegisterObjectMethod(TypeName, "Vec2 movedBy(double, double) const", asMETHODPR(Vec2, movedBy, (double, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 movedBy(const Vec2& in) const", asMETHODPR(Vec2, movedBy, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec2& moveBy(double, double)", asMETHODPR(Vec2, moveBy, (double, double), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& moveBy(const Vec2& in)", asMETHODPR(Vec2, moveBy, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	clamp, clamped
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec2 clamped(const RectF& in) const", asMETHODPR(Vec2, clamped, (const RectF&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& clamp(const RectF& in)", asMETHODPR(Vec2, clamp, (const RectF&), Vec2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	Utils
		//
		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHOD(Vec2, isZero), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHOD(Vec2, hasNaN), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 dot(const Vec2& in) const", asMETHOD(Vec2, dot), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 cross(const Vec2& in) const", asMETHOD(Vec2, cross), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHOD(Vec2, length), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHOD(Vec2, lengthSq), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthInv() const", asMETHOD(Vec2, lengthInv), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& setLength(double)", asMETHOD(Vec2, setLength), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(double x, double y) const", asMETHODPR(Vec2, distanceFrom, (double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(const Vec2& in) const", asMETHODPR(Vec2, distanceFrom, (const Vec2&) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(double x, double y) const", asMETHODPR(Vec2, distanceFromSq, (double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(const Vec2& in) const", asMETHODPR(Vec2, distanceFromSq, (const Vec2&) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 normalized() const", asMETHOD(Vec2, normalized), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& normalize()", asMETHOD(Vec2, normalize), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 rotated(double) const", asMETHOD(Vec2, rotated), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& rotate(double)", asMETHOD(Vec2, rotate), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double getAngle(const Vec2& in) const", asMETHOD(Vec2, getAngle), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 projection(const Vec2& in) const", asMETHOD(Vec2, projection), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 lerp(const Vec2& in, double) const", asMETHOD(Vec2, lerp), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point asPoint() const", asMETHOD(Vec2, asPoint), asCALL_THISCALL); assert(r >= 0);

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

		r = engine->RegisterObjectMethod(TypeName, "Vec2 xx() const", asMETHOD(Vec2, xx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 xy() const", asMETHOD(Vec2, xy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yx() const", asMETHOD(Vec2, yx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yy() const", asMETHOD(Vec2, yy), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Vec2 Zero()", asFUNCTION(Vec2::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 One()", asFUNCTION(Vec2::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 All()", asFUNCTION(Vec2::All), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 UnitX()", asFUNCTION(Vec2::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 UnitY()", asFUNCTION(Vec2::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Left(double length = 1)", asFUNCTION(Vec2::Left), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Right(double length = 1)", asFUNCTION(Vec2::Right), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Up(double length = 1)", asFUNCTION(Vec2::Up), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Down(double length = 1)", asFUNCTION(Vec2::Down), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul_r(double) const", asFUNCTIONPR(operator*, (double, const Vec2&), Vec2), asCALL_CDECL_OBJLAST);

		r = engine->RegisterObjectMethod(TypeName, "Float2 opImplConv() const", asFUNCTION(ConvToFloat2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
