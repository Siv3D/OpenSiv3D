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
# include <Siv3D/OffsetCircular.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

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

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "Vec2 center", asOFFSET(ShapeType, center)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ShapeType, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double theta", asOFFSET(ShapeType, theta)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const OffsetCircular &in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double r, double theta)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, const Vec2& in)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opAdd(const Vec2 &in) const", asMETHOD(ShapeType, operator+), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opSub(const Vec2 &in) const", asMETHOD(ShapeType, operator-), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& opAddAssign(const Vec2 &in)", asMETHOD(ShapeType, operator+=), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& opSubAssign(const Vec2 &in)", asMETHOD(ShapeType, operator-=), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular movedBy(const Vec2& in) const", asMETHODPR(ShapeType, movedBy, (const Vec2&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& moveBy(const Vec2 &in)", asMETHODPR(ShapeType, moveBy, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& setCenter(double, double)", asMETHODPR(ShapeType, setCenter, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& setCenter(const Vec2& in)", asMETHODPR(ShapeType, setCenter, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& setTarget(double, double)", asMETHODPR(ShapeType, setTarget, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& setTarget(const Vec2& in)", asMETHODPR(ShapeType, setTarget, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular rotated(double) const", asMETHOD(ShapeType, rotated), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "OffsetCircular& rotate(double)", asMETHOD(ShapeType, rotate), asCALL_THISCALL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "Float2 toFloat2() const", asMETHOD(ShapeType, toFloat2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 toVec2() const", asMETHOD(ShapeType, toVec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opImplConv() const", asMETHOD(ShapeType, toVec2), asCALL_THISCALL); assert(r >= 0);

		// Circular(Arg::r, Arg::theta)
		// Circular(Arg::theta, Arg::r)
	}
}
