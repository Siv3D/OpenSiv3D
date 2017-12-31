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

# include <Siv3D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ValueType = ColorF;

	static void ConstructD(double rgb, ValueType* self)
	{
		new(self) ValueType(rgb);
	}

	static void ConstructDD(double rgb, double a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructDDDD(double r, double g, double b, double a, ValueType* self)
	{
		new(self) ValueType(r, g, b, a);
	}

	static Color ConvToColor(const ValueType& value)
	{
		return value;
	}

	void RegisterColorF(asIScriptEngine *engine)
	{
		const char TypeName[] = "ColorF";
		int r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ColorF, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double g", asOFFSET(ColorF, g)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double b", asOFFSET(ColorF, b)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double a", asOFFSET(ColorF, a)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double rgb)", asFUNCTION(ConstructD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double rgb, double a)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double r, double g, double b, double a = 1.0)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Color opImplConv() const", asFUNCTION(ConvToColor), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
