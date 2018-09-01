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

	using ShapeType = Vec3;

	static void Construct(const Vec3& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructDDD(double x, double y, double z, ShapeType* self)
	{
		new(self) ShapeType(x, y, z);
	}

	static void ConstructVD(const Vec2& xy, double z, ShapeType* self)
	{
		new(self) ShapeType(xy, z);
	}

	static void ConstructDV(double x, const Vec2& yz, ShapeType* self)
	{
		new(self) ShapeType(x, yz);
	}

	static void ConstructList(const double* list, ShapeType* self)
	{
		new(self) ShapeType(list[0], list[1], list[2]);
	}

	void RegisterVec3(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Vec3";
		
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(Vec3, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(Vec3, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double z", asOFFSET(Vec3, z)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec3& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double z)", asFUNCTION(ConstructDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double)", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double, const Vec2& in)", asFUNCTION(ConstructDV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float3& in)", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const double& in) {double, double, double}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double elem(uint64) const", asMETHOD(Vec3, elem), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, -, *, /
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec3 opNeg() const", asMETHODPR(Vec3, operator-, () const, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 opAdd(const Vec3& in) const", asMETHODPR(Vec3, operator+, (const Vec3&) const, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 opSub(const Vec3& in) const", asMETHODPR(Vec3, operator-, (const Vec3&) const, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 opMul(double) const", asMETHODPR(Vec3, operator*, (double) const, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 opMul(const Vec3& in) const", asMETHODPR(Vec3, operator*, (const Vec3&) const, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 opDiv(double) const", asMETHODPR(Vec3, operator/, (double) const, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 opDiv(const Vec3& in) const", asMETHODPR(Vec3, operator/, (const Vec3&) const, Vec3), asCALL_THISCALL); assert(r >= 0);

		//
		//	+=, -=, *=, /=
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec3& opAddAssign(const Vec3& in)", asMETHODPR(Vec3, operator+=, (const Vec3&), Vec3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& opSubAssign(const Vec3& in)", asMETHODPR(Vec3, operator-=, (const Vec3&), Vec3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& opMulAssign(double)", asMETHODPR(Vec3, operator*=, (double), Vec3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& opMulAssign(const Vec3& in)", asMETHODPR(Vec3, operator*=, (const Vec3&), Vec3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& opDivAssign(double)", asMETHODPR(Vec3, operator/=, (double), Vec3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& opDivAssign(const Vec3& in)", asMETHODPR(Vec3, operator/=, (const Vec3&), Vec3&), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Vec3& in) const", asMETHOD(Vec3, operator==), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec3& set(double, double, double)", asMETHODPR(Vec3, set, (double, double, double), Vec3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& set(const Vec2& in, double)", asMETHODPR(Vec3, set, (const Vec2&, double), Vec3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& set(double, const Vec2& in)", asMETHODPR(Vec3, set, (double, const Vec2&), Vec3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& set(const Vec3& in)", asMETHODPR(Vec3, set, (const Vec3&), Vec3&), asCALL_THISCALL); assert(r >= 0);

		//
		//	movedBy
		//	
		r = engine->RegisterObjectMethod(TypeName, "Vec3 movedBy(double, double, double) const", asMETHODPR(Vec3, movedBy, (double, double, double) const, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 movedBy(const Vec3& in) const", asMETHODPR(Vec3, movedBy, (const Vec3&) const, Vec3), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Vec3& moveBy(double, double, double)", asMETHODPR(Vec3, moveBy, (double, double, double), Vec3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& moveBy(const Vec3& in)", asMETHODPR(Vec3, moveBy, (const Vec3&), Vec3&), asCALL_THISCALL); assert(r >= 0);

		//
		//	Utils
		//
		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHOD(Vec3, isZero), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHOD(Vec3, hasNaN), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 dot(const Vec3& in) const", asMETHOD(Vec3, dot), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 cross(const Vec3& in) const", asMETHOD(Vec3, cross), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHOD(Vec3, length), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHOD(Vec3, lengthSq), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthInv() const", asMETHOD(Vec3, lengthInv), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& setLength(double)", asMETHOD(Vec3, setLength), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(double x, double y, double z) const", asMETHODPR(Vec3, distanceFrom, (double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(const Vec3& in) const", asMETHODPR(Vec3, distanceFrom, (const Vec3&) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(double x, double y, double z) const", asMETHODPR(Vec3, distanceFromSq, (double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(const Vec3& in) const", asMETHODPR(Vec3, distanceFromSq, (const Vec3&) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 normalized() const", asMETHOD(Vec3, normalized), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3& normalize()", asMETHOD(Vec3, normalize), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 lerp(const Vec3& in, double) const", asMETHOD(Vec3, lerp), asCALL_THISCALL); assert(r >= 0);
	
		r = engine->RegisterObjectMethod(TypeName, "Vec2 xx() const", asMETHOD(Vec3, xx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 xy() const", asMETHOD(Vec3, xy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 xz() const", asMETHOD(Vec3, xz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yx() const", asMETHOD(Vec3, yx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yy() const", asMETHOD(Vec3, yy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 yz() const", asMETHOD(Vec3, yz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 zx() const", asMETHOD(Vec3, zx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 zy() const", asMETHOD(Vec3, zy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 zz() const", asMETHOD(Vec3, zz), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 xxx() const", asMETHOD(Vec3, xxx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 yyy() const", asMETHOD(Vec3, yyy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 zzz() const", asMETHOD(Vec3, zzz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 xyz() const", asMETHOD(Vec3, xyz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 xzy() const", asMETHOD(Vec3, xzy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 yxz() const", asMETHOD(Vec3, yxz), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 yzx() const", asMETHOD(Vec3, yzx), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 zxy() const", asMETHOD(Vec3, zxy), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 zyx() const", asMETHOD(Vec3, zyx), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Vec3 Zero()", asFUNCTION(Vec3::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 One()", asFUNCTION(Vec3::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 All()", asFUNCTION(Vec3::All), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 UnitX()", asFUNCTION(Vec3::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 UnitY()", asFUNCTION(Vec3::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 UnitZ()", asFUNCTION(Vec3::UnitZ), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 Left(double length = 1)", asFUNCTION(Vec3::Left), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 Right(double length = 1)", asFUNCTION(Vec3::Right), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 Up(double length = 1)", asFUNCTION(Vec3::Up), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 Down(double length = 1)", asFUNCTION(Vec3::Down), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 Forward(double length = 1)", asFUNCTION(Vec3::Forward), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 Backward(double length = 1)", asFUNCTION(Vec3::Backward), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 opMul_r(double) const", asFUNCTIONPR(operator*, (double, const Vec3&), Vec3), asCALL_CDECL_OBJLAST);
	}
}
