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
# include <Siv3D/Circular.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Circular;

	static void Construct(const Circular& c, ShapeType* self)
	{
		new(self) ShapeType(c);
	}

	static void ConstructDD(double r, double theta, ShapeType* self)
	{
		new(self) ShapeType(r, theta);
	}

	static void ConstructV(const Vec2& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	void RegisterCircular(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Circular";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ShapeType, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double theta", asOFFSET(ShapeType, theta)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Circular &in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double r, double theta)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in)", asFUNCTION(ConstructV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opNeg() const", asMETHODPR(Circular, operator-, () const noexcept, Circular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opAdd(Vec2) const", asMETHODPR(Circular, operator+, (Vec2) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opSub(Vec2) const", asMETHODPR(Circular, operator-, (Vec2) const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		
		//
		//	with
		//
		r = engine->RegisterObjectMethod(TypeName, "Circular withR(double) const", asMETHODPR(ShapeType, withR, (double) const noexcept, Circular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circular withTheta(double) const", asMETHODPR(ShapeType, withTheta, (double) const noexcept, Circular), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circular rotated(double) const", asMETHODPR(ShapeType, rotated, (double) const noexcept, Circular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circular& rotate(double)", asMETHODPR(ShapeType, rotate, (double) noexcept, Circular&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 toFloat2() const", asMETHODPR(Circular, toFloat2, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 toVec2() const", asMETHODPR(Circular, toVec2, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 fastToFloat2() const", asMETHODPR(Circular, fastToFloat2, () const noexcept, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 fastToVec2() const", asMETHODPR(Circular, fastToVec2, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 toPosition() const", asMETHODPR(Circular, toPosition, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opImplConv() const", asMETHODPR(Circular, toVec2, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Circular, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);
	}
}
