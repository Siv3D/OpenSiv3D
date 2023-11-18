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

	using ShapeType = Float4;

	static void Construct(const Float4& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructFFFF(float x, float y, float z, float w, ShapeType* self)
	{
		new(self) ShapeType(x, y, z, w);
	}

	static void ConstructFFV(float x, float y, const Float2& zw, ShapeType* self)
	{
		new(self) ShapeType(x, y, zw);
	}

	static void ConstructFVF(float x, const Float2& yz, float w, ShapeType* self)
	{
		new(self) ShapeType(x, yz, w);
	}

	static void ConstructVFF(const Float2& xy, float z, float w, ShapeType* self)
	{
		new(self) ShapeType(xy, z, w);
	}

	static void ConstructVV(const Float2& xy, const Float2& zw, ShapeType* self)
	{
		new(self) ShapeType(xy, zw);
	}

	static void ConstructVF(const Float3& xyz, float w, ShapeType* self)
	{
		new(self) ShapeType(xyz, w);
	}

	static void ConstructFV(float x, const Float3& yzw, ShapeType* self)
	{
		new(self) ShapeType(x, yzw);
	}

	static void ConstructV4(const Vec4& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	static void ConstructList(const float* list, ShapeType* self)
	{
		new(self) ShapeType(list[0], list[1], list[2], list[3]);
	}

	static Float4 MulFloat(float other, const ShapeType& value)
	{
		return (value * other);
	}

	static bool EqualsFloat4(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	void RegisterFloat4(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Float4";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "float x", asOFFSET(Float4, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float y", asOFFSET(Float4, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float z", asOFFSET(Float4, z)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float w", asOFFSET(Float4, w)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float4& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float x, float y, float z, float w)", asFUNCTION(ConstructFFFF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float, float, const Float2& in)", asFUNCTION(ConstructFFV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float, const Float2& in, float)", asFUNCTION(ConstructFVF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float2& in, float, float)", asFUNCTION(ConstructVFF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float2& in, const Float2& in)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Float3& in, float)", asFUNCTION(ConstructVF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float, const Float3& in)", asFUNCTION(ConstructFV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec4& in)", asFUNCTION(ConstructV4), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const float& in) {float, float, float, float}", asFUNCTION(ConstructList), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// elem
		//
		r = engine->RegisterObjectMethod(TypeName, "float elem(size_t) const", asMETHODPR(Float4, elem, (size_t) const noexcept, float), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, -, *, /
		//
		r = engine->RegisterObjectMethod(TypeName, "Float4 opNeg() const", asMETHODPR(Float4, operator-, () const, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 opAdd(Float4) const", asMETHODPR(Float4, operator+, (Float4) const, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 opSub(Float4) const", asMETHODPR(Float4, operator-, (Float4) const, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 opMul(float) const", asMETHODPR(Float4, operator*, (float) const, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 opMul(Float4) const", asMETHODPR(Float4, operator*, (Float4) const, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 opDiv(float) const", asMETHODPR(Float4, operator/, (float) const, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 opDiv(Float4) const", asMETHODPR(Float4, operator/, (Float4) const, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 opMul_r(float) const", asFUNCTION(MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	+=, -=, *=, /=
		//
		r = engine->RegisterObjectMethod(TypeName, "Float4& opAddAssign(Float4)", asMETHODPR(Float4, operator+=, (Float4), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& opSubAssign(Float4)", asMETHODPR(Float4, operator-=, (Float4), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& opMulAssign(float)", asMETHODPR(Float4, operator*=, (float), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& opMulAssign(Float4)", asMETHODPR(Float4, operator*=, (Float4), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& opDivAssign(float)", asMETHODPR(Float4, operator/=, (float), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& opDivAssign(Float4)", asMETHODPR(Float4, operator/=, (Float4), Float4&), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Float4& in) const", asFUNCTION(EqualsFloat4), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool epsilonEquals(Float4, float) const", asMETHODPR(Float4, epsilonEquals, (Float4, float) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasSameDirection(Float4) const", asMETHODPR(Float4, hasSameDirection, (Float4) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasOppositeDirection(Float4) const", asMETHODPR(Float4, hasOppositeDirection, (Float4) const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isZero() const", asMETHODPR(Float4, isZero, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasNaN() const", asMETHODPR(Float4, hasNaN, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float minComponent() const", asMETHODPR(Float4, minComponent, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float maxComponent() const", asMETHODPR(Float4, maxComponent, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHODPR(Float4, clear, () noexcept, void), asCALL_THISCALL); assert(r >= 0);

		//
		//	with
		//
		r = engine->RegisterObjectMethod(TypeName, "Float4 withX(float) const", asMETHODPR(Float4, withX, (float) const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 withY(float) const", asMETHODPR(Float4, withY, (float) const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 withZ(float) const", asMETHODPR(Float4, withZ, (float) const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 withW(float) const", asMETHODPR(Float4, withW, (float) const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Float4& set(const Float2& in, const Float2& in)", asMETHODPR(Float4, set, (const Float2&, const Float2&), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& set(const Float2& in, float, float)", asMETHODPR(Float4, set, (const Float2&, float, float), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& set(float, const Float2& in, float)", asMETHODPR(Float4, set, (float, const Float2&, float), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& set(float, float, const Float2& in)", asMETHODPR(Float4, set, (float, float, const Float2&), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& set(const Float3& in, float)", asMETHODPR(Float4, set, (const Float3&, float), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& set(float, const Float3& in)", asMETHODPR(Float4, set, (float, const Float3&), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& set(float, float, float, float)", asMETHODPR(Float4, set, (float, float, float, float), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& set(Float4)", asMETHODPR(Float4, set, (Float4), Float4&), asCALL_THISCALL); assert(r >= 0);

		//
		//	movedBy
		//	
		r = engine->RegisterObjectMethod(TypeName, "Float4 movedBy(float, float, float, float) const", asMETHODPR(Float4, movedBy, (float, float, float, float) const, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 movedBy(Float4) const", asMETHODPR(Float4, movedBy, (Float4) const, Float4), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Float4& moveBy(float, float, float, float)", asMETHODPR(Float4, moveBy, (float, float, float, float), Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& moveBy(Float4)", asMETHODPR(Float4, moveBy, (Float4), Float4&), asCALL_THISCALL); assert(r >= 0);

		//
		//	Utils
		//
		r = engine->RegisterObjectMethod(TypeName, "float dot(Float4) const", asMETHODPR(Float4, dot, (Float4) const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float length() const", asMETHODPR(Float4, length, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float lengthSq() const", asMETHODPR(Float4, lengthSq, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float invLength() const", asMETHODPR(Float4, invLength, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float manhattanLength() const", asMETHODPR(Float4, manhattanLength, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float manhattanDistanceFrom(float, float, float, float) const", asMETHODPR(Float4, manhattanDistanceFrom, (float, float, float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float manhattanDistanceFrom(Float4) const", asMETHODPR(Float4, manhattanDistanceFrom, (Float4) const, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float distanceFrom(float x, float y, float z, float w) const", asMETHODPR(Float4, distanceFrom, (float, float, float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFrom(Float4) const", asMETHODPR(Float4, distanceFrom, (Float4) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFromSq(float x, float y, float z, float w) const", asMETHODPR(Float4, distanceFromSq, (float, float, float, float) const, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "float distanceFromSq(Float4) const", asMETHODPR(Float4, distanceFromSq, (Float4) const, float), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float4 withLength(float) const", asMETHODPR(Float4, withLength, (float) const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& setLength(float)", asMETHODPR(Float4, setLength, (float) noexcept, Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 limitLength(float) const", asMETHODPR(Float4, limitLength, (float) const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& limitLengthSelf(float)", asMETHODPR(Float4, limitLengthSelf, (float) noexcept, Float4&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 normalized() const", asMETHODPR(Float4, normalized, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4& normalize()", asMETHODPR(Float4, normalize, () noexcept, Float4&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float4 getMidpoint(Float4) const", asMETHODPR(Float4, getMidpoint, (Float4) const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 lerp(Float4, float) const", asMETHODPR(Float4, lerp, (Float4, float) const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Float4, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 xx() const", asMETHODPR(Float4, xx, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 xy() const", asMETHODPR(Float4, xy, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 xz() const", asMETHODPR(Float4, xz, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 xw() const", asMETHODPR(Float4, xw, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 yx() const", asMETHODPR(Float4, yx, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yy() const", asMETHODPR(Float4, yy, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yz() const", asMETHODPR(Float4, yz, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 yw() const", asMETHODPR(Float4, yw, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 zx() const", asMETHODPR(Float4, zx, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 zy() const", asMETHODPR(Float4, zy, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 zz() const", asMETHODPR(Float4, zz, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 zw() const", asMETHODPR(Float4, zw, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 wx() const", asMETHODPR(Float4, wx, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 wy() const", asMETHODPR(Float4, wy, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 wz() const", asMETHODPR(Float4, wz, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 ww() const", asMETHODPR(Float4, ww, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float3 xxx() const", asMETHODPR(Float4, xxx, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 xyz() const", asMETHODPR(Float4, xyz, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 yyy() const", asMETHODPR(Float4, yyy, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 yxz() const", asMETHODPR(Float4, yxz, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 yzw() const", asMETHODPR(Float4, yzw, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 zzz() const", asMETHODPR(Float4, zzz, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 zyx() const", asMETHODPR(Float4, zyx, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 www() const", asMETHODPR(Float4, www, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float3 wzy() const", asMETHODPR(Float4, wzy, () const noexcept, Float3), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float4 xyz0() const", asMETHODPR(Float4, xyz0, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 xyz1() const", asMETHODPR(Float4, xyz1, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 xyzw() const", asMETHODPR(Float4, xyzw, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 xxxx() const", asMETHODPR(Float4, xxxx, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 yyyy() const", asMETHODPR(Float4, yyyy, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 zzzz() const", asMETHODPR(Float4, zzzz, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 wwww() const", asMETHODPR(Float4, wwww, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 wzyx() const", asMETHODPR(Float4, wzyx, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Float4 Zero()", asFUNCTION(Float4::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float4 One()", asFUNCTION(Float4::One), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float4 All(float value = 1)", asFUNCTION(Float4::All), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float4 UnitX()", asFUNCTION(Float4::UnitX), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float4 UnitY()", asFUNCTION(Float4::UnitY), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float4 UnitZ()", asFUNCTION(Float4::UnitZ), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float4 UnitW()", asFUNCTION(Float4::UnitW), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
