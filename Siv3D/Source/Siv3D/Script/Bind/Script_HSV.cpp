//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	static void ConstructDD(double h, double a, HSV* self)
	{
		new(self) HSV(h, a);
	}

	static void ConstructDDDD(double h, double s, double v, double a, HSV* self)
	{
		new(self) HSV(h, s, v, a);
	}

	static void ConstructC(const Color& color, HSV* self)
	{
		new(self) HSV(color);
	}

	static void ConstructCf(const ColorF& color, HSV* self)
	{
		new(self) HSV(color);
	}

	static Color ConvToColor(const HSV& hsv)
	{
		return hsv.toColor();
	}

	static ColorF ConvToColorF(const HSV& hsv)
	{
		return hsv.toColorF();
	}

	void RegisterHSV(asIScriptEngine *engine)
	{
		const char TypeName[] = "HSV";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double h", asOFFSET(HSV, h)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double s", asOFFSET(HSV, s)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double v", asOFFSET(HSV, v)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double a", asOFFSET(HSV, a)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double h, double a = 1.0)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double h, double s, double v, double a = 1.0)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color&in color)", asFUNCTION(ConstructC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF&in color)", asFUNCTION(ConstructCf), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Color opImplConv() const", asFUNCTION(ConvToColor), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF opImplConv() const", asFUNCTION(ConvToColorF), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
