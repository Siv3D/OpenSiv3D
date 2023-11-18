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

	static void ConstructVDD(const Vec2& xy, double z, double w, ShapeType* self)
	{
		new(self) ShapeType(xy, z, w);
	}

	static void ConstructVV(const Vec2& xy, const Vec2& zw, ShapeType* self)
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

	static void ConstructF4(const Float4& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructList(const double* list, ShapeType* self)
	{
		new(self) ShapeType(list[0], list[1], list[2], list[3]);
	}

	static Vec4 MulDouble(double other, const ShapeType& value)
	{
		return (value * other);
	}

	static bool EqualsVec4(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	void RegisterVec4(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "Vec4";
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
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float4& in)", asFUNCTION(ConstructF4), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const double& in) {double, double, double, double}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

			//
			// elem
			//
			r = engine->RegisterObjectMethod(TypeName, "double elem(size_t) const", asMETHODPR(Vec4, elem, (size_t) const noexcept, double), asCALL_THISCALL); assert(r >= 0);

			//
			//	+, -, *, /
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec4 opNeg() const", asMETHODPR(Vec4, operator-, () const, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 opAdd(Vec4) const", asMETHODPR(Vec4, operator+, (Vec4) const, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 opSub(Vec4) const", asMETHODPR(Vec4, operator-, (Vec4) const, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 opMul(double) const", asMETHODPR(Vec4, operator*, (double) const, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 opMul(Vec4) const", asMETHODPR(Vec4, operator*, (Vec4) const, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 opDiv(double) const", asMETHODPR(Vec4, operator/, (double) const, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 opDiv(Vec4) const", asMETHODPR(Vec4, operator/, (Vec4) const, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 opMul_r(double) const", asFUNCTION(MulDouble), asCALL_CDECL_OBJLAST); assert(r >= 0);

			//
			//	+=, -=, *=, /=
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec4& opAddAssign(Vec4)", asMETHODPR(Vec4, operator+=, (Vec4), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& opSubAssign(Vec4)", asMETHODPR(Vec4, operator-=, (Vec4), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& opMulAssign(double)", asMETHODPR(Vec4, operator*=, (double), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& opMulAssign(Vec4)", asMETHODPR(Vec4, operator*=, (Vec4), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& opDivAssign(double)", asMETHODPR(Vec4, operator/=, (double), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& opDivAssign(Vec4)", asMETHODPR(Vec4, operator/=, (Vec4), Vec4&), asCALL_THISCALL); assert(r >= 0);

			//
			//	==, !=
			//
			r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Vec4& in) const", asFUNCTION(EqualsVec4), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool epsilonEquals(Vec4, double) const", asMETHODPR(Vec4, epsilonEquals, (Vec4, double) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasSameDirection(Vec4) const", asMETHODPR(Vec4, hasSameDirection, (Vec4) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasOppositeDirection(Vec4) const", asMETHODPR(Vec4, hasOppositeDirection, (Vec4) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHODPR(Vec4, isZero, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHODPR(Vec4, hasNaN, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double minComponent() const", asMETHODPR(Vec4, minComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double maxComponent() const", asMETHODPR(Vec4, maxComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHODPR(Vec4, clear, () noexcept, void), asCALL_THISCALL); assert(r >= 0);

			//
			//	with
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec4 withX(double) const", asMETHODPR(Vec4, withX, (double) const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 withY(double) const", asMETHODPR(Vec4, withY, (double) const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 withZ(double) const", asMETHODPR(Vec4, withZ, (double) const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 withW(double) const", asMETHODPR(Vec4, withW, (double) const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);

			//
			//	set
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec4& set(const Vec2& in, const Vec2& in)", asMETHODPR(Vec4, set, (const Vec2&, const Vec2&), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& set(const Vec2& in, double, double)", asMETHODPR(Vec4, set, (const Vec2&, double, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& set(double, const Vec2& in, double)", asMETHODPR(Vec4, set, (double, const Vec2&, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& set(double, double, const Vec2& in)", asMETHODPR(Vec4, set, (double, double, const Vec2&), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& set(const Vec3& in, double)", asMETHODPR(Vec4, set, (const Vec3&, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& set(double, const Vec3& in)", asMETHODPR(Vec4, set, (double, const Vec3&), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& set(double, double, double, double)", asMETHODPR(Vec4, set, (double, double, double, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& set(Vec4)", asMETHODPR(Vec4, set, (Vec4), Vec4&), asCALL_THISCALL); assert(r >= 0);

			//
			//	movedBy
			//	
			r = engine->RegisterObjectMethod(TypeName, "Vec4 movedBy(double, double, double, double) const", asMETHODPR(Vec4, movedBy, (double, double, double, double) const, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 movedBy(Vec4) const", asMETHODPR(Vec4, movedBy, (Vec4) const, Vec4), asCALL_THISCALL); assert(r >= 0);

			//
			//	moveBy
			//
			r = engine->RegisterObjectMethod(TypeName, "Vec4& moveBy(double, double, double, double)", asMETHODPR(Vec4, moveBy, (double, double, double, double), Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& moveBy(Vec4)", asMETHODPR(Vec4, moveBy, (Vec4), Vec4&), asCALL_THISCALL); assert(r >= 0);

			//
			//	Utils
			//
			r = engine->RegisterObjectMethod(TypeName, "double dot(Vec4) const", asMETHODPR(Vec4, dot, (Vec4) const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHODPR(Vec4, length, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHODPR(Vec4, lengthSq, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double invLength() const", asMETHODPR(Vec4, invLength, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double manhattanLength() const", asMETHODPR(Vec4, manhattanLength, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double manhattanDistanceFrom(double, double, double, double) const", asMETHODPR(Vec4, manhattanDistanceFrom, (double, double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double manhattanDistanceFrom(Vec4) const", asMETHODPR(Vec4, manhattanDistanceFrom, (Vec4) const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(double x, double y, double z, double w) const", asMETHODPR(Vec4, distanceFrom, (double, double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double distanceFrom(Vec4) const", asMETHODPR(Vec4, distanceFrom, (Vec4) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(double x, double y, double z, double w) const", asMETHODPR(Vec4, distanceFromSq, (double, double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double distanceFromSq(Vec4) const", asMETHODPR(Vec4, distanceFromSq, (Vec4) const, double), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec4 withLength(double) const", asMETHODPR(Vec4, withLength, (double) const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& setLength(double)", asMETHODPR(Vec4, setLength, (double) noexcept, Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 limitLength(double) const", asMETHODPR(Vec4, limitLength, (double) const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& limitLengthSelf(double)", asMETHODPR(Vec4, limitLengthSelf, (double) noexcept, Vec4&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 normalized() const", asMETHODPR(Vec4, normalized, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4& normalize()", asMETHODPR(Vec4, normalize, () noexcept, Vec4&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec4 getMidpoint(Vec4) const", asMETHODPR(Vec4, getMidpoint, (Vec4) const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 lerp(Vec4, double) const", asMETHODPR(Vec4, lerp, (Vec4, double) const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Vec4, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec2 xx() const", asMETHODPR(Vec4, xx, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 xy() const", asMETHODPR(Vec4, xy, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 xz() const", asMETHODPR(Vec4, xz, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 xw() const", asMETHODPR(Vec4, xw, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec2 yx() const", asMETHODPR(Vec4, yx, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 yy() const", asMETHODPR(Vec4, yy, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 yz() const", asMETHODPR(Vec4, yz, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 yw() const", asMETHODPR(Vec4, yw, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec2 zx() const", asMETHODPR(Vec4, zx, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 zy() const", asMETHODPR(Vec4, zy, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 zz() const", asMETHODPR(Vec4, zz, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 zw() const", asMETHODPR(Vec4, zw, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec2 wx() const", asMETHODPR(Vec4, wx, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 wy() const", asMETHODPR(Vec4, wy, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 wz() const", asMETHODPR(Vec4, wz, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec2 ww() const", asMETHODPR(Vec4, ww, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec3 xxx() const", asMETHODPR(Vec4, xxx, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 xyz() const", asMETHODPR(Vec4, xyz, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 yyy() const", asMETHODPR(Vec4, yyy, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 yxz() const", asMETHODPR(Vec4, yxz, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 yzw() const", asMETHODPR(Vec4, yzw, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 zzz() const", asMETHODPR(Vec4, zzz, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 zyx() const", asMETHODPR(Vec4, zyx, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 www() const", asMETHODPR(Vec4, www, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec3 wzy() const", asMETHODPR(Vec4, wzy, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Vec4 xyz0() const", asMETHODPR(Vec4, xyz0, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 xyz1() const", asMETHODPR(Vec4, xyz1, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 xyzw() const", asMETHODPR(Vec4, xyzw, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 xxxx() const", asMETHODPR(Vec4, xxxx, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 yyyy() const", asMETHODPR(Vec4, yyyy, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 zzzz() const", asMETHODPR(Vec4, zzzz, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 wwww() const", asMETHODPR(Vec4, wwww, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Vec4 wzyx() const", asMETHODPR(Vec4, wzyx, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);

			r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
			{
				r = engine->RegisterGlobalFunction("Vec4 Zero()", asFUNCTION(Vec4::Zero), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec4 One()", asFUNCTION(Vec4::One), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec4 All(double value = 1)", asFUNCTION(Vec4::All), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec4 UnitX()", asFUNCTION(Vec4::UnitX), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec4 UnitY()", asFUNCTION(Vec4::UnitY), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec4 UnitZ()", asFUNCTION(Vec4::UnitZ), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("Vec4 UnitW()", asFUNCTION(Vec4::UnitW), asCALL_CDECL); assert(r >= 0);
			}
			r = engine->SetDefaultNamespace(""); assert(r >= 0);
		}
	}
}
