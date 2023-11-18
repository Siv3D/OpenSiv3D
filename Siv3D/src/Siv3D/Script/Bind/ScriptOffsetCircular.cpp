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
# include <Siv3D/OffsetCircular.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = OffsetCircular;

	static void Construct(const OffsetCircular& c, ShapeType* self)
	{
		new(self) ShapeType(c);
	}

	static void ConstructVDD(const Vec2& center, double r, double theta, ShapeType* self)
	{
		new(self) ShapeType(center, r, theta);
	}

	static void ConstructVV(const Vec2& center, const Vec2& v, ShapeType* self)
	{
		new(self) ShapeType(center, v);
	}

	void RegisterOffsetCircular(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "OffsetCircular";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "Vec2 center", asOFFSET(ShapeType, center)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ShapeType, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double theta", asOFFSET(ShapeType, theta)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const OffsetCircular &in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double r = 0.0, double theta = 0.0)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, const Vec2& in)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opAdd(Vec2) const", asMETHODPR(ShapeType, operator+, (Vec2) const noexcept, OffsetCircular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opSub(Vec2) const", asMETHODPR(ShapeType, operator-, (Vec2) const noexcept, OffsetCircular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& opAddAssign(Vec2)", asMETHODPR(ShapeType, operator+=, (Vec2) noexcept, OffsetCircular&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& opSubAssign(Vec2)", asMETHODPR(ShapeType, operator-=, (Vec2) noexcept, OffsetCircular&), asCALL_THISCALL); assert(r >= 0);

		//
		//	with
		//
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular withCenter(double, double) const", asMETHODPR(ShapeType, withCenter, (double, double) const noexcept, OffsetCircular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular withCenter(Vec2) const", asMETHODPR(ShapeType, withCenter, (Vec2) const noexcept, OffsetCircular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular withR(double) const", asMETHODPR(ShapeType, withR, (double) const noexcept, OffsetCircular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular withTheta(double) const", asMETHODPR(ShapeType, withTheta, (double) const noexcept, OffsetCircular), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular movedBy(Vec2) const", asMETHODPR(ShapeType, movedBy, (Vec2) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& moveBy(Vec2)", asMETHODPR(ShapeType, moveBy, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& setCenter(double, double)", asMETHODPR(ShapeType, setCenter, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& setCenter(Vec2)", asMETHODPR(ShapeType, setCenter, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& setTarget(double, double)", asMETHODPR(ShapeType, setTarget, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& setTarget(Vec2)", asMETHODPR(ShapeType, setTarget, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular rotated(double) const", asMETHODPR(ShapeType, rotated, (double) const noexcept, OffsetCircular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& rotate(double)", asMETHODPR(ShapeType, rotate, (double) noexcept, OffsetCircular&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 toFloat2() const", asMETHODPR(ShapeType, toFloat2, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 toVec2() const", asMETHODPR(ShapeType, toVec2, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 fastToFloat2() const", asMETHODPR(ShapeType, fastToFloat2, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 fastToVec2() const", asMETHODPR(ShapeType, fastToVec2, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 toPosition() const", asMETHODPR(ShapeType, toPosition, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opImplConv() const", asMETHODPR(ShapeType, toVec2, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(ShapeType, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);
	}
}
