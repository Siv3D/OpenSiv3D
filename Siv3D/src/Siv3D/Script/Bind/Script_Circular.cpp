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
# include <Siv3D/Circular.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Circular;

	static void ConstructDD(double r, double theta, ShapeType* self)
	{
		new(self) ShapeType(r, theta);
	}

	static void ConstructV(const Vec2& v, ShapeType* self)
	{
		new(self) ShapeType(v);
	}

	void RegisterCircular(asIScriptEngine *engine)
	{
		const char TypeName[] = "Circular";
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ShapeType, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double theta", asOFFSET(ShapeType, theta)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double r, double theta)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2&in v)", asFUNCTION(ConstructV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opNeg() const", asMETHODPR(Circular, operator-, () const, Circular), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opAdd(const Vec2 &in) const", asMETHODPR(Circular, operator+, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 opSub(const Vec2 &in) const", asMETHODPR(Circular, operator-, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 opImplConv() const", asMETHOD(Circular, toVec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 toVec2() const", asMETHOD(Circular, toVec2), asCALL_THISCALL); assert(r >= 0);
	
		// Circular(Arg::r, Arg::theta)
		// Circular(Arg::theta, Arg::r)
		// Circular::toFloat2()
	}
}
