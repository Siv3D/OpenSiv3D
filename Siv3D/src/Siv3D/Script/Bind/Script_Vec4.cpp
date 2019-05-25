//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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

	using ShapeType = Vec4;

	static void Construct(const Vec4& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructDDDD(double x, double y, double z, double w, ShapeType* self)
	{
		new(self) ShapeType(x, y, z, w);
	}

	static void ConstructDDV(double x, double y, const Vec2& zw, ShapeType* self)
	{
		new(self) ShapeType(x, y, zw);
	}

	static void ConstructDVD(double x, const Vec2& yz, double w, ShapeType* self)
	{
		new(self) ShapeType(x, yz, w);
	}

	static void ConstructVDD(const Vec2&xy, double z, double w, ShapeType* self)
	{
		new(self) ShapeType(xy, z, w);
	}

	static void ConstructVV(const Vec2&xy, const Vec2& zw, ShapeType* self)
	{
		new(self) ShapeType(xy, zw);
	}

	static void ConstructVD(const Vec3& xyz, double w, ShapeType* self)
	{
		new(self) ShapeType(xyz, w);
	}

	static void ConstructDV(double x, const Vec3& yzw, ShapeType* self)
	{
		new(self) ShapeType(x, yzw);
	}

	static void ConstructList(const double* list, ShapeType* self)
	{
		new(self) ShapeType(list[0], list[1], list[2], list[3]);
	}

	void RegisterVec4(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Vec4";
		
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(Vec4, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(Vec4, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double z", asOFFSET(Vec4, z)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double w", asOFFSET(Vec4, w)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec4& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double z, double w)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double, double, const Vec2& in)", asFUNCTION(ConstructDDV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double, const Vec2& in, double)", asFUNCTION(ConstructDVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double, double)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, const Vec2& in)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec3& in, double)", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double, const Vec3& in)", asFUNCTION(ConstructDV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float4& in)", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const double& in) {double, double, double, double}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double elem(uint64) const", asMETHOD(Vec4, elem), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, -, *, /
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec4 opNeg() const", asMETHODPR(Vec4, operator-, () const, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 opAdd(const Vec4& in) const", asMETHODPR(Vec4, operator+, (const Vec4&) const, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 opSub(const Vec4& in) const", asMETHODPR(Vec4, operator-, (const Vec4&) const, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 opMul(double) const", asMETHODPR(Vec4, operator*, (double) const, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 opMul(const Vec4& in) const", asMETHODPR(Vec4, operator*, (const Vec4&) const, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 opDiv(double) const", asMETHODPR(Vec4, operator/, (double) const, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 opDiv(const Vec4& in) const", asMETHODPR(Vec4, operator/, (const Vec4&) const, Vec4), asCALL_THISCALL); assert(r >= 0);

		//
		//	+=, -=, *=, /=
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec4& opAddAssign(const Vec4& in)", asMETHODPR(Vec4, operator+=, (const Vec4&), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& opSubAssign(const Vec4& in)", asMETHODPR(Vec4, operator-=, (const Vec4&), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& opMulAssign(double)", asMETHODPR(Vec4, operator*=, (double), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& opMulAssign(const Vec4& in)", asMETHODPR(Vec4, operator*=, (const Vec4&), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& opDivAssign(double)", asMETHODPR(Vec4, operator/=, (double), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& opDivAssign(const Vec4& in)", asMETHODPR(Vec4, operator/=, (const Vec4&), Vec4&), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Vec4& in) const", asMETHOD(Vec4, operator==), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec4& set(double, double, double, double)", asMETHODPR(Vec4, set, (double, double, double, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& set(const Vec2& in, double, double)", asMETHODPR(Vec4, set, (const Vec2&, double, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& set(double, const Vec2& in, double)", asMETHODPR(Vec4, set, (double, const Vec2&, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& set(double, double, const Vec2& in)", asMETHODPR(Vec4, set, (double, double, const Vec2&), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& set(const Vec3& in, double)", asMETHODPR(Vec4, set, (const Vec3&, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& set(double, const Vec3& in)", asMETHODPR(Vec4, set, (double, const Vec3&), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& set(const Vec3& in)", asMETHODPR(Vec4, set, (const Vec4&), Vec4&), asCALL_THISCALL); assert(r >= 0);


		//
		//	movedBy
		//	
		r = engine->RegisterObjectMethod(TypeName, "Vec4 movedBy(double, double, double, double) const", asMETHODPR(Vec4, movedBy, (double, double, double, double) const, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 movedBy(const Vec4& in) const", asMETHODPR(Vec4, movedBy, (const Vec4&) const, Vec4), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec4& moveBy(double, double, double, double)", asMETHODPR(Vec4, moveBy, (double, double, double, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& moveBy(const Vec4& in)", asMETHODPR(Vec4, moveBy, (const Vec4&), Vec4&), asCALL_THISCALL); assert(r >= 0);

		//
		//	Utils
		//
		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHOD(Vec4, isZero), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHOD(Vec4, hasNaN), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec4 dot(const Vec4& in) const", asMETHOD(Vec4, dot), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHOD(Vec4, length), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHOD(Vec4, lengthSq), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthInv() const", asMETHOD(Vec4, lengthInv), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& setLength(double)", asMETHOD(Vec4, setLength), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 clampLength(double)", asMETHOD(Vec4, clampLength), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(double, double, double, double) const", asMETHODPR(Vec4, distanceFrom, (double, double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(const Vec4& in) const", asMETHODPR(Vec4, distanceFrom, (const Vec4&) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(double, double, double, double) const", asMETHODPR(Vec4, distanceFromSq, (double, double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(const Vec4& in) const", asMETHODPR(Vec4, distanceFromSq, (const Vec4&) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec4 normalized() const", asMETHOD(Vec4, normalized), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4& normalize()", asMETHOD(Vec4, normalize), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec4 lerp(const Vec4& in, double) const", asMETHOD(Vec4, lerp), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 xx() const", asMETHOD(Vec4, xx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 xy() const", asMETHOD(Vec4, xy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 xz() const", asMETHOD(Vec4, xz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 xw() const", asMETHOD(Vec4, xw), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 yx() const", asMETHOD(Vec4, yx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yy() const", asMETHOD(Vec4, yy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yz() const", asMETHOD(Vec4, yz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yw() const", asMETHOD(Vec4, yw), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 zx() const", asMETHOD(Vec4, zx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 zy() const", asMETHOD(Vec4, zy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 zz() const", asMETHOD(Vec4, zz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 zw() const", asMETHOD(Vec4, zw), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 wx() const", asMETHOD(Vec4, wx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 wy() const", asMETHOD(Vec4, wy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 wz() const", asMETHOD(Vec4, wz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 ww() const", asMETHOD(Vec4, ww), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 xxx() const", asMETHOD(Vec4, xxx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 yyy() const", asMETHOD(Vec4, yyy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 zzz() const", asMETHOD(Vec4, zzz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 www() const", asMETHOD(Vec4, www), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 xyz() const", asMETHOD(Vec4, xyz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 zyx() const", asMETHOD(Vec4, zyx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 yzw() const", asMETHOD(Vec4, yzw), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 wzy() const", asMETHOD(Vec4, wzy), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec4 xxxx() const", asMETHOD(Vec4, xxxx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 yyyy() const", asMETHOD(Vec4, yyyy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 zzzz() const", asMETHOD(Vec4, zzzz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 wwww() const", asMETHOD(Vec4, wwww), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec4 xyzw() const", asMETHOD(Vec4, xyzw), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 wxyz() const", asMETHOD(Vec4, wxyz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 zwxy() const", asMETHOD(Vec4, zwxy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 yzwx() const", asMETHOD(Vec4, yzwx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 wzyx() const", asMETHOD(Vec4, wzyx), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Vec4 Zero()", asFUNCTION(Vec4::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 One()", asFUNCTION(Vec4::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 All()", asFUNCTION(Vec4::All), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 UnitX()", asFUNCTION(Vec4::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 UnitY()", asFUNCTION(Vec4::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 UnitZ()", asFUNCTION(Vec4::UnitZ), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 UnitW()", asFUNCTION(Vec4::UnitW), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec4 opMul_r(double) const", asFUNCTIONPR(operator*, (double, const Vec4&), Vec4), asCALL_CDECL_OBJLAST);
	}
}
