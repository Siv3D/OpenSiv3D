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
# include <Siv3D/FloatRect.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = FloatRect;

	static void Construct(const FloatRect& r, ShapeType* self)
	{
		new(self) ShapeType(r);
	}

	static void ConstructFFFF(float l, float t, float r, float b, ShapeType* self)
	{
		new(self) ShapeType(l, t, r, b);
	}

	//static void ConstructIIII(int32 l, int32 t, int32 r, int32 b, ShapeType* self)
	//{
	//	new(self) ShapeType(l, t, r, b);
	//}

	//static void ConstructDDDD(double l, double t, double r, double b, ShapeType* self)
	//{
	//	new(self) ShapeType(l, t, r, b);
	//}

	void RegisterFloatRect(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "FloatRect";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "float left", asOFFSET(FloatRect, left)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float top", asOFFSET(FloatRect, top)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float right", asOFFSET(FloatRect, right)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float bottom", asOFFSET(FloatRect, bottom)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const FloatRect &in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructFFFF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32, int32, int32, int32)", asFUNCTION(ConstructIIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double, double, double, double)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
