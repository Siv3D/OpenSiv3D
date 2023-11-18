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

	using ShapeType = Float3;

	static void Construct(const Float3& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructFFF(float x, float y, float z, ShapeType* self)
	{
		new(self) ShapeType(x, y, z);
	}

	static void ConstructVF(const Float2& xy, float z, ShapeType* self)
	{
		new(self) ShapeType(xy, z);
	}

	static void ConstructFV(float x, const Float2& yz, ShapeType* self)
	{
		new(self) ShapeType(x, yz);
	}

	static void ConstructV3(const Vec3& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructList(const float* list, ShapeType* self)
	{
		new(self) ShapeType(list[0], list[1], list[2]);
	}

	static Float3 MulFloat(float other, const ShapeType& value)
	{
		return (value * other);
	}

	static bool EqualsFloat3(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	void RegisterFloat3(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Float3";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "float x", asOFFSET(Float3, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float y", asOFFSET(Float3, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float z", asOFFSET(Float3, z)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float3& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec3& in)", asFUNCTION(ConstructV3), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float x, float y, float z)", asFUNCTION(ConstructFFF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float2& in, float)", asFUNCTION(ConstructVF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float, const Float2& in)", asFUNCTION(ConstructFV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const float& in) {float, float, float}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// elem
		//
		r = engine->RegisterObjectMethod(TypeName, "float elem(size_t) const", asMETHODPR(Float3, elem, (size_t) const noexcept, float), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, -, *, /
		//
		r = engine->RegisterObjectMethod(TypeName, "Float3 opNeg() const", asMETHODPR(Float3, operator-, () const, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 opAdd(Float3) const", asMETHODPR(Float3, operator+, (Float3) const, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 opSub(Float3) const", asMETHODPR(Float3, operator-, (Float3) const, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 opMul(float) const", asMETHODPR(Float3, operator*, (float) const, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 opMul(Float3) const", asMETHODPR(Float3, operator*, (Float3) const, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 opDiv(float) const", asMETHODPR(Float3, operator/, (float) const, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 opDiv(Float3) const", asMETHODPR(Float3, operator/, (Float3) const, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 opMul_r(float) const", asFUNCTION(MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	+=, -=, *=, /=
		//
		r = engine->RegisterObjectMethod(TypeName, "Float3& opAddAssign(Float3)", asMETHODPR(Float3, operator+=, (Float3), Float3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& opSubAssign(Float3)", asMETHODPR(Float3, operator-=, (Float3), Float3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& opMulAssign(float)", asMETHODPR(Float3, operator*=, (float), Float3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& opMulAssign(Float3)", asMETHODPR(Float3, operator*=, (Float3), Float3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& opDivAssign(float)", asMETHODPR(Float3, operator/=, (float), Float3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& opDivAssign(Float3)", asMETHODPR(Float3, operator/=, (Float3), Float3&), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Float3& in) const", asFUNCTION(EqualsFloat3), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool epsilonEquals(Float3, float) const", asMETHODPR(Float3, epsilonEquals, (Float3, float) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasSameDirection(Float3) const", asMETHODPR(Float3, hasSameDirection, (Float3) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasOppositeDirection(Float3) const", asMETHODPR(Float3, hasOppositeDirection, (Float3) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHODPR(Float3, isZero, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHODPR(Float3, hasNaN, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float minComponent() const", asMETHODPR(Float3, minComponent, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float maxComponent() const", asMETHODPR(Float3, maxComponent, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHODPR(Float3, clear, () noexcept, void), asCALL_THISCALL); assert(r >= 0);

		//
		//	with
		//
		r = engine->RegisterObjectMethod(TypeName, "Float3 withX(float) const", asMETHODPR(Float3, withX, (float) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 withY(float) const", asMETHODPR(Float3, withY, (float) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 withZ(float) const", asMETHODPR(Float3, withZ, (float) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Float3& set(float, float, float)", asMETHODPR(Float3, set, (float, float, float), Float3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& set(Float3)", asMETHODPR(Float3, set, (Float3), Float3&), asCALL_THISCALL); assert(r >= 0);

		//
		//	movedBy
		//	
		r = engine->RegisterObjectMethod(TypeName, "Float3 movedBy(float, float, float) const", asMETHODPR(Float3, movedBy, (float, float, float) const, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 movedBy(Float3) const", asMETHODPR(Float3, movedBy, (Float3) const, Float3), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Float3& moveBy(float, float, float)", asMETHODPR(Float3, moveBy, (float, float, float), Float3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& moveBy(Float3)", asMETHODPR(Float3, moveBy, (Float3), Float3&), asCALL_THISCALL); assert(r >= 0);

		////
		////	clamp, clamped
		////
		//r = engine->RegisterObjectMethod(TypeName, "Float3 clamped(const Box& in) const", asMETHODPR(Float3, clamped, (const Box&) const, Float3), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Float3& clamp(const Box& in)", asMETHODPR(Float3, clamp, (const Box&), Float3&), asCALL_THISCALL); assert(r >= 0);

		//
		//	Utils
		//
		r = engine->RegisterObjectMethod(TypeName, "float dot(Float3) const", asMETHODPR(Float3, dot, (Float3) const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 cross(Float3) const", asMETHODPR(Float3, cross, (Float3) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float angleTo(Float3) const", asMETHODPR(Float3, angleTo, (Float3) const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 projectOnVector(Float3) const", asMETHODPR(Float3, projectOnVector, (Float3) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 projectOnPlane(Float3) const", asMETHODPR(Float3, projectOnPlane, (Float3) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float length() const", asMETHODPR(Float3, length, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float lengthSq() const", asMETHODPR(Float3, lengthSq, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float invLength() const", asMETHODPR(Float3, invLength, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float manhattanLength() const", asMETHODPR(Float3, manhattanLength, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float manhattanDistanceFrom(float, float, float) const", asMETHODPR(Float3, manhattanDistanceFrom, (float, float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float manhattanDistanceFrom(Float3) const", asMETHODPR(Float3, manhattanDistanceFrom, (Float3) const, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float distanceFrom(float x, float y, float z) const", asMETHODPR(Float3, distanceFrom, (float, float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFrom(Float3) const", asMETHODPR(Float3, distanceFrom, (Float3) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFromSq(float x, float y, float z) const", asMETHODPR(Float3, distanceFromSq, (float, float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFromSq(Float3) const", asMETHODPR(Float3, distanceFromSq, (Float3) const, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float3 withLength(float) const", asMETHODPR(Float3, withLength, (float) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& setLength(float)", asMETHODPR(Float3, setLength, (float) noexcept, Float3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 limitLength(float) const", asMETHODPR(Float3, limitLength, (float) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& limitLengthSelf(float)", asMETHODPR(Float3, limitLengthSelf, (float) noexcept, Float3&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 normalized() const", asMETHODPR(Float3, normalized, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3& normalize()", asMETHODPR(Float3, normalize, () noexcept, Float3&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float3 getMidpoint(Float3) const", asMETHODPR(Float3, getMidpoint, (Float3) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 lerp(Float3, float) const", asMETHODPR(Float3, lerp, (Float3, float) const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Float3, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 xx() const", asMETHODPR(Float3, xx, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 xy() const", asMETHODPR(Float3, xy, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 xz() const", asMETHODPR(Float3, xz, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yx() const", asMETHODPR(Float3, yx, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yy() const", asMETHODPR(Float3, yy, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yz() const", asMETHODPR(Float3, yz, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 zx() const", asMETHODPR(Float3, zx, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 zy() const", asMETHODPR(Float3, zy, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 zz() const", asMETHODPR(Float3, zz, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float3 xxx() const", asMETHODPR(Float3, xxx, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 xyz() const", asMETHODPR(Float3, xyz, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 xzy() const", asMETHODPR(Float3, xzy, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 yyy() const", asMETHODPR(Float3, yyy, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 yxz() const", asMETHODPR(Float3, yxz, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 yzx() const", asMETHODPR(Float3, yzx, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 zzz() const", asMETHODPR(Float3, zzz, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 zxy() const", asMETHODPR(Float3, zxy, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 zyx() const", asMETHODPR(Float3, zyx, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float4 xyz0() const", asMETHODPR(Float3, xyz0, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 xyz1() const", asMETHODPR(Float3, xyz1, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Float3 Zero()", asFUNCTION(Float3::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 One()", asFUNCTION(Float3::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 All(float value = 1)", asFUNCTION(Float3::All), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 UnitX()", asFUNCTION(Float3::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 UnitY()", asFUNCTION(Float3::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 UnitZ()", asFUNCTION(Float3::UnitZ), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 Left(float length = 1)", asFUNCTION(Float3::Left), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 Right(float length = 1)", asFUNCTION(Float3::Right), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 Up(float length = 1)", asFUNCTION(Float3::Up), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 Down(float length = 1)", asFUNCTION(Float3::Down), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 Forward(float length = 1)", asFUNCTION(Float3::Forward), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float3 Backward(float length = 1)", asFUNCTION(Float3::Backward), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
