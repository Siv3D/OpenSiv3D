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

	using ShapeType = Float2;

	static void Construct(const Float2& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructDD(float x, float y, ShapeType* self)
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

	static Vec2 ConvToVec2(const Float2& v)
	{
		return v;
	}

	void RegisterFloat2(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Float2";
		
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "float x", asOFFSET(Float2, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float y", asOFFSET(Float2, y)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float2& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float x, float y)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in)", asFUNCTION(ConstructP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in)", asFUNCTION(ConstructV2), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const float& in) {float, float}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float elem(uint64) const", asMETHOD(Float2, elem), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, -, *, /
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2 opNeg() const", asMETHODPR(Float2, operator-, () const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opAdd(const Float2& in) const", asMETHODPR(Float2, operator+, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opSub(const Float2& in) const", asMETHODPR(Float2, operator-, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opMul(float) const", asMETHODPR(Float2, operator*, (float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opMul(const Float2& in) const", asMETHODPR(Float2, operator*, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opDiv(float) const", asMETHODPR(Float2, operator/, (float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 opDiv(const Float2& in) const", asMETHODPR(Float2, operator/, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);

		//
		//	+=, -=, *=, /=
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2& opAddAssign(const Float2& in)", asMETHODPR(Float2, operator+=, (const Float2&), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opSubAssign(const Float2& in)", asMETHODPR(Float2, operator-=, (const Float2&), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opMulAssign(float)", asMETHODPR(Float2, operator*=, (float), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opMulAssign(const Float2& in)", asMETHODPR(Float2, operator*=, (const Float2&), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opDivAssign(float)", asMETHODPR(Float2, operator/=, (float), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& opDivAssign(const Float2& in)", asMETHODPR(Float2, operator/=, (const Float2&), Float2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Float2& in) const", asMETHOD(Float2, operator==), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2& set(float, float)", asMETHODPR(Float2, set, (float, float), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& set(const Float2& in)", asMETHODPR(Float2, set, (const Float2&), Float2&), asCALL_THISCALL); assert(r >= 0);
		
		//
		//	movedBy
		//	
		r = engine->RegisterObjectMethod(TypeName, "Float2 movedBy(float, float) const", asMETHODPR(Float2, movedBy, (float, float) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 movedBy(const Float2& in) const", asMETHODPR(Float2, movedBy, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2& moveBy(float, float)", asMETHODPR(Float2, moveBy, (float, float), Float2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& moveBy(const Float2& in)", asMETHODPR(Float2, moveBy, (const Float2&), Float2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	clamp, clamped
		//
		r = engine->RegisterObjectMethod(TypeName, "Float2 clamped(const RectF& in) const", asMETHODPR(Float2, clamped, (const RectF&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& clamp(const RectF& in)", asMETHODPR(Float2, clamp, (const RectF&), Float2&), asCALL_THISCALL); assert(r >= 0);

		//
		//	Utils
		//
		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHOD(Float2, isZero), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHOD(Float2, hasNaN), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 dot(const Float2& in) const", asMETHOD(Float2, dot), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 cross(const Float2& in) const", asMETHOD(Float2, cross), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float length() const", asMETHOD(Float2, length), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float lengthSq() const", asMETHOD(Float2, lengthSq), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float lengthInv() const", asMETHOD(Float2, lengthInv), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& setLength(float)", asMETHOD(Float2, setLength), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float distanceFrom(float x, float y) const", asMETHODPR(Float2, distanceFrom, (float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFrom(const Float2& in) const", asMETHODPR(Float2, distanceFrom, (const Float2&) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFromSq(float x, float y) const", asMETHODPR(Float2, distanceFromSq, (float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFromSq(const Float2& in) const", asMETHODPR(Float2, distanceFromSq, (const Float2&) const, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 normalized() const", asMETHOD(Float2, normalized), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& normalize()", asMETHOD(Float2, normalize), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 rotated(float) const", asMETHOD(Float2, rotated), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2& rotate(float)", asMETHOD(Float2, rotate), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float getAngle(const Float2& in) const", asMETHOD(Float2, getAngle), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 projection(const Float2& in) const", asMETHOD(Float2, projection), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 lerp(const Float2& in, double) const", asMETHOD(Float2, lerp), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point asPoint() const", asMETHOD(Float2, asPoint), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Float2& in) const", asMETHODPR(ShapeType, intersects, (const Float2&) const, bool), asCALL_THISCALL); assert(r >= 0);
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

		r = engine->RegisterObjectMethod(TypeName, "Float2 xx() const", asMETHOD(Float2, xx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 xy() const", asMETHOD(Float2, xy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yx() const", asMETHOD(Float2, yx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yy() const", asMETHOD(Float2, yy), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Float2 Zero()", asFUNCTION(Float2::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 One()", asFUNCTION(Float2::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 All()", asFUNCTION(Float2::All), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 UnitX()", asFUNCTION(Float2::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 UnitY()", asFUNCTION(Float2::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 Left(float length = 1)", asFUNCTION(Float2::Left), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 Right(float length = 1)", asFUNCTION(Float2::Right), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 Up(float length = 1)", asFUNCTION(Float2::Up), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float2 Down(float length = 1)", asFUNCTION(Float2::Down), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 opMul_r(float) const", asFUNCTIONPR(operator*, (float, const Float2&), Float2), asCALL_CDECL_OBJLAST);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opImplConv() const", asFUNCTION(ConvToVec2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
