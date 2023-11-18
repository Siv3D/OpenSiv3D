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

	static void ConstructF3(const Float3& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructList(const double* list, ShapeType* self)
	{
		new(self) ShapeType(list[0], list[1], list[2]);
	}

	static Vec3 MulDouble(double other, const ShapeType& value)
	{
		return (value * other);
	}

	static bool EqualsVec3(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	void RegisterVec3(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "Vec3";
			r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(Vec3, x)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(Vec3, y)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "double z", asOFFSET(Vec3, z)); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec3& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float3& in)", asFUNCTION(ConstructF3), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double z)", asFUNCTION(ConstructDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double)", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double, const Vec2& in)", asFUNCTION(ConstructDV), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const double& in) {double, double, double}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

			//
			// elem
			//
			r = engine->RegisterObjectMethod(TypeName, "double elem(size_t) const", asMETHODPR(Vec3, elem, (size_t) const noexcept, double), asCALL_THISCALL); assert(r >= 0);

			//
			//	+, -, *, /
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec3 opNeg() const", asMETHODPR(Vec3, operator-, () const, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 opAdd(Vec3) const", asMETHODPR(Vec3, operator+, (Vec3) const, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 opSub(Vec3) const", asMETHODPR(Vec3, operator-, (Vec3) const, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 opMul(double) const", asMETHODPR(Vec3, operator*, (double) const, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 opMul(Vec3) const", asMETHODPR(Vec3, operator*, (Vec3) const, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 opDiv(double) const", asMETHODPR(Vec3, operator/, (double) const, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 opDiv(Vec3) const", asMETHODPR(Vec3, operator/, (Vec3) const, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 opMul_r(double) const", asFUNCTION(MulDouble), asCALL_CDECL_OBJLAST); assert(r >= 0);

			//
			//	+=, -=, *=, /=
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec3& opAddAssign(Vec3)", asMETHODPR(Vec3, operator+=, (Vec3), Vec3&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& opSubAssign(Vec3)", asMETHODPR(Vec3, operator-=, (Vec3), Vec3&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& opMulAssign(double)", asMETHODPR(Vec3, operator*=, (double), Vec3&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& opMulAssign(Vec3)", asMETHODPR(Vec3, operator*=, (Vec3), Vec3&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& opDivAssign(double)", asMETHODPR(Vec3, operator/=, (double), Vec3&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& opDivAssign(Vec3)", asMETHODPR(Vec3, operator/=, (Vec3), Vec3&), asCALL_THISCALL); assert(r >= 0);

			//
			//	==, !=
			//
			r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Vec3& in) const", asFUNCTION(EqualsVec3), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool epsilonEquals(Vec3, double) const", asMETHODPR(Vec3, epsilonEquals, (Vec3, double) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasSameDirection(Vec3) const", asMETHODPR(Vec3, hasSameDirection, (Vec3) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasOppositeDirection(Vec3) const", asMETHODPR(Vec3, hasOppositeDirection, (Vec3) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHODPR(Vec3, isZero, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHODPR(Vec3, hasNaN, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double minComponent() const", asMETHODPR(Vec3, minComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double maxComponent() const", asMETHODPR(Vec3, maxComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHODPR(Vec3, clear, () noexcept, void), asCALL_THISCALL); assert(r >= 0);

			//
			//	with
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec3 withX(double) const", asMETHODPR(Vec3, withX, (double) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 withY(double) const", asMETHODPR(Vec3, withY, (double) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 withZ(double) const", asMETHODPR(Vec3, withZ, (double) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);

			//
			//	set
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec3& set(double, double, double)", asMETHODPR(Vec3, set, (double, double, double), Vec3&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& set(Vec3)", asMETHODPR(Vec3, set, (Vec3), Vec3&), asCALL_THISCALL); assert(r >= 0);

			//
			//	movedBy
			//	
			r = engine->RegisterObjectMethod(TypeName, "Vec3 movedBy(double, double, double) const", asMETHODPR(Vec3, movedBy, (double, double, double) const, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 movedBy(Vec3) const", asMETHODPR(Vec3, movedBy, (Vec3) const, Vec3), asCALL_THISCALL); assert(r >= 0);

			//
			//	moveBy
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec3& moveBy(double, double, double)", asMETHODPR(Vec3, moveBy, (double, double, double), Vec3&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& moveBy(Vec3)", asMETHODPR(Vec3, moveBy, (Vec3), Vec3&), asCALL_THISCALL); assert(r >= 0);

			////
			////	clamp, clamped
			////
			//r = engine->RegisterObjectMethod(TypeName, "Vec3 clamped(const Box& in) const", asMETHODPR(Vec3, clamped, (const Box&) const, Vec3), asCALL_THISCALL); assert(r >= 0);
			//r = engine->RegisterObjectMethod(TypeName, "Vec3& clamp(const Box& in)", asMETHODPR(Vec3, clamp, (const Box&), Vec3&), asCALL_THISCALL); assert(r >= 0);

			//
			//	Utils
			//
			r = engine->RegisterObjectMethod(TypeName, "double dot(Vec3) const", asMETHODPR(Vec3, dot, (Vec3) const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 cross(Vec3) const", asMETHODPR(Vec3, cross, (Vec3) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double angleTo(Vec3) const", asMETHODPR(Vec3, angleTo, (Vec3) const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 projectOnVector(Vec3) const", asMETHODPR(Vec3, projectOnVector, (Vec3) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 projectOnPlane(Vec3) const", asMETHODPR(Vec3, projectOnPlane, (Vec3) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHODPR(Vec3, length, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHODPR(Vec3, lengthSq, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double invLength() const", asMETHODPR(Vec3, invLength, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double manhattanLength() const", asMETHODPR(Vec3, manhattanLength, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double manhattanDistanceFrom(double, double, double) const", asMETHODPR(Vec3, manhattanDistanceFrom, (double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double manhattanDistanceFrom(Vec3) const", asMETHODPR(Vec3, manhattanDistanceFrom, (Vec3) const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(double x, double y, double z) const", asMETHODPR(Vec3, distanceFrom, (double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(Vec3) const", asMETHODPR(Vec3, distanceFrom, (Vec3) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(double x, double y, double z) const", asMETHODPR(Vec3, distanceFromSq, (double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(Vec3) const", asMETHODPR(Vec3, distanceFromSq, (Vec3) const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec3 withLength(double) const", asMETHODPR(Vec3, withLength, (double) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& setLength(double)", asMETHODPR(Vec3, setLength, (double) noexcept, Vec3&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 limitLength(double) const", asMETHODPR(Vec3, limitLength, (double) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& limitLengthSelf(double)", asMETHODPR(Vec3, limitLengthSelf, (double) noexcept, Vec3&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 normalized() const", asMETHODPR(Vec3, normalized, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3& normalize()", asMETHODPR(Vec3, normalize, () noexcept, Vec3&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec3 getMidpoint(Vec3) const", asMETHODPR(Vec3, getMidpoint, (Vec3) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 lerp(Vec3, double) const", asMETHODPR(Vec3, lerp, (Vec3, double) const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Vec3, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec2 xx() const", asMETHODPR(Vec3, xx, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 xy() const", asMETHODPR(Vec3, xy, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 xz() const", asMETHODPR(Vec3, xz, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 yx() const", asMETHODPR(Vec3, yx, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 yy() const", asMETHODPR(Vec3, yy, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 yz() const", asMETHODPR(Vec3, yz, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 zx() const", asMETHODPR(Vec3, zx, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 zy() const", asMETHODPR(Vec3, zy, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 zz() const", asMETHODPR(Vec3, zz, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec3 xxx() const", asMETHODPR(Vec3, xxx, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 xyz() const", asMETHODPR(Vec3, xyz, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 xzy() const", asMETHODPR(Vec3, xzy, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 yyy() const", asMETHODPR(Vec3, yyy, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 yxz() const", asMETHODPR(Vec3, yxz, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 yzx() const", asMETHODPR(Vec3, yzx, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 zzz() const", asMETHODPR(Vec3, zzz, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 zxy() const", asMETHODPR(Vec3, zxy, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 zyx() const", asMETHODPR(Vec3, zyx, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec4 xyz0() const", asMETHODPR(Vec3, xyz0, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 xyz1() const", asMETHODPR(Vec3, xyz1, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);

			r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
			{
				r = engine->RegisterGlobalFunction("Vec3 Zero()", asFUNCTION(Vec3::Zero), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec3 One()", asFUNCTION(Vec3::One), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec3 All(double value = 1)", asFUNCTION(Vec3::All), asCALL_CDECL); assert(r >= 0);
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
		}
	}
}
