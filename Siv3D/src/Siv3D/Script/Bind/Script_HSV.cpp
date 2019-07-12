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
# include <Siv3D/HSV.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ValueType = HSV;

	static void ConstructDefault(ValueType* self)
	{
		new(self) ValueType();
	}

	static void Construct(const HSV& hsv, ValueType* self)
	{
		new(self) ValueType(hsv);
	}

	static void ConstructDD(double h, double a, ValueType* self)
	{
		new(self) ValueType(h, a);
	}

	static void ConstructDDDD(double h, double s, double v, double a, ValueType* self)
	{
		new(self) ValueType(h, s, v, a);
	}

	static void ConstructC(const Color& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructCf(const ColorF& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static Color ConvToColor(const HSV& hsv)
	{
		return hsv.toColor();
	}

	static ColorF ConvToColorF(const HSV& hsv)
	{
		return hsv.toColorF();
	}

	void RegisterHSV(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "HSV";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double h", asOFFSET(HSV, h)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double s", asOFFSET(HSV, s)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double v", asOFFSET(HSV, v)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double a", asOFFSET(HSV, a)); assert(r >= 0);

		//
		//	Constructor
		//
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructDefault), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double h, double a = 1.0)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double h, double s, double v, double a = 1.0)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in)", asFUNCTION(ConstructC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF& in)", asFUNCTION(ConstructCf), asCALL_CDECL_OBJLAST); assert(r >= 0);
	
		//
		//	+, -
		//
		r = engine->RegisterObjectMethod(TypeName, "HSV opAdd(const HSV& in) const", asMETHODPR(HSV, operator+, (const HSV&) const, HSV), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV opSub(const HSV& in) const", asMETHODPR(HSV, operator-, (const HSV&) const, HSV), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "HSV lerp(const HSV& in, double) const", asMETHOD(HSV, lerp), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Color toColor() const", asMETHODPR(HSV, toColor, () const, Color), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color toColor(uint32) const", asMETHODPR(HSV, toColor, (uint32) const, Color), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Color toColorF() const", asMETHODPR(HSV, toColorF, () const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color toColorF(double) const", asMETHODPR(HSV, toColorF, (double) const, ColorF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 hsv() const", asMETHOD(HSV, hsv), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 hsva() const", asMETHOD(HSV, hsva), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "uint64 hash() const", asMETHOD(HSV, hash), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "Color opImplConv() const", asFUNCTION(ConvToColor), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF opImplConv() const", asFUNCTION(ConvToColorF), asCALL_CDECL_OBJLAST); assert(r >= 0);



		r = engine->RegisterGlobalFunction("Color HueToColor(double)", asFUNCTION(HueToColor), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("ColorF HueToColorF(double)", asFUNCTION(HueToColorF), asCALL_CDECL); assert(r >= 0);
	}
}
