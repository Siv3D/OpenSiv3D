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

	static void ConstructDD(double x, double y, Vec2* self)
	{
		new(self) Vec2(x, y);
	}

	static void ConstructList(double *list, Vec2* self)
	{
		new(self) Vec2(list[0], list[1]);
	}

	void RegisterVec2(asIScriptEngine *engine)
	{
		const char TypeName[] = "Vec2";
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(Vec2, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(Vec2, y)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const double &in) {double, double}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 xx() const", asMETHOD(Vec2, xx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 xy() const", asMETHOD(Vec2, xy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yx() const", asMETHOD(Vec2, yx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yy() const", asMETHOD(Vec2, yy), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opNeg() const", asMETHODPR(Vec2, operator-, () const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opAdd(const Vec2 &in) const", asMETHODPR(Vec2, operator+, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opSub(const Vec2 &in) const", asMETHODPR(Vec2, operator-, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(double) const", asMETHODPR(Vec2, operator*, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul(const Vec2 &in) const", asMETHODPR(Vec2, operator*, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opDiv(double) const", asMETHODPR(Vec2, operator/, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2& opAddAssign(const Vec2 &in)", asMETHODPR(Vec2, operator+=, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opSubAssign(const Vec2 &in)", asMETHODPR(Vec2, operator-=, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opMulAssign(const Vec2 &in)", asMETHODPR(Vec2, operator*=, (double), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opDivAssign(const Vec2 &in)", asMETHODPR(Vec2, operator/=, (double), Vec2&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Vec2 &in) const", asMETHOD(Vec2, operator==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2& set(double, double)", asMETHODPR(Vec2, set, (double, double), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& set(const Vec2 &in)", asMETHODPR(Vec2, set, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 movedBy(double, double) const", asMETHODPR(Vec2, movedBy, (double, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 movedBy(const Vec2 &in) const", asMETHODPR(Vec2, movedBy, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& moveBy(double, double)", asMETHODPR(Vec2, moveBy, (double, double), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& moveBy(const Vec2 &in)", asMETHODPR(Vec2, moveBy, (const Vec2&), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& setLength(double)", asMETHOD(Vec2, setLength), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point asPoint() const", asMETHOD(Vec2, asPoint), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHOD(Vec2, isZero), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(const Vec2 &in) const", asMETHODPR(Vec2, distanceFrom, (const Vec2&) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(const Vec2 &in) const", asMETHODPR(Vec2, distanceFromSq, (const Vec2&) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<Point>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<Vec2>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<Rect>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<RectF>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<Circle>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<Ellipse>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<Line>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<Triangle>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<Quad>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<RoundRect>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<Polygon>)), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asSMethodPtr<sizeof(void (Vec2::*)())>::Convert((void (Vec2::*)())(&Vec2::intersects<LineString>)), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Vec2 Zero()", asFUNCTION(Vec2::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 One()", asFUNCTION(Vec2::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 UnitX()", asFUNCTION(Vec2::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 UnitY()", asFUNCTION(Vec2::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Left(double length = 1)", asFUNCTION(Vec2::Left), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Right(double length = 1)", asFUNCTION(Vec2::Right), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Up(double length = 1)", asFUNCTION(Vec2::Up), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Down(double length = 1)", asFUNCTION(Vec2::Down), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opMul_r(double) const", asFUNCTIONPR(operator*, (double, const Vec2 &), Vec2), asCALL_CDECL_OBJLAST);
	}
}
