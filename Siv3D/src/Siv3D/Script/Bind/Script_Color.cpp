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
# include <Siv3D/Color.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ValueType = Color;

	static void Construct(const Color& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructUUUU(uint32 r, uint32 g, uint32 b, uint32 a, ValueType* self)
	{
		new(self) ValueType(r, g, b, a);
	}

	static void ConstructUU(uint32 rgb, uint32 a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructCU(const Color& rgb, uint32 a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructCf(const ColorF& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructH(const HSV& hsv, ValueType* self)
	{
		new(self) ValueType(hsv);
	}

	static void ConstructS(const String& code, ValueType* self)
	{
		new(self) ValueType(code);
	}

	static ColorF ConvToColorF(const ValueType& value)
	{
		return value;
	}

	void RegisterColor(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Color";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "uint8 r", 0); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "uint8 g", 1); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "uint8 b", 2); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "uint8 a", 3); assert(r >= 0);

		//
		//	Constructor
		//
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32 r, uint32 g, uint32 b, uint32 a = 255)", asFUNCTION(ConstructUUUU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32 rgb, uint32 a = 255)", asFUNCTION(ConstructUU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, uint32 a)", asFUNCTION(ConstructCU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF& in)", asFUNCTION(ConstructCf), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in)", asFUNCTION(ConstructH), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const uint32 &in) {uint32, uint32, uint32}", asFUNCTION(ConstructListUUU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const uint32 &in) {uint32, uint32, uint32, uint32}", asFUNCTION(ConstructListUUUU), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	~
		//
		r = engine->RegisterObjectMethod(TypeName, "Color opCom() const", asMETHOD(Color, operator~), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Color& in) const", asMETHOD(Color, operator==), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Color& set(uint32 r, uint32 g, uint32 b, uint32 a = 255)", asMETHODPR(Color, set, (uint32, uint32, uint32, uint32), Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& set(const Color& in)", asMETHODPR(Color, set, (const Color&), Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& setRGB(uint32 rgb)", asMETHODPR(Color, setRGB, (uint32), Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& setRGB(uint32 r, uint32 g, uint32 b)", asMETHODPR(Color, setRGB, (uint32, uint32, uint32), Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& setA(uint32 a)", asMETHOD(Color, setA), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "uint8 grayscale0_255() const", asMETHOD(Color, grayscale0_255), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double grayscale() const", asMETHOD(Color, grayscale), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 asUint32() const", asMETHOD(Color, asUint32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color lerp(const Color& in, double) const", asMETHOD(Color, lerp), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color gamma(double) const", asMETHOD(Color, gamma), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "String toHex() const", asMETHOD(Color, toHex), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "ColorF opImplConv() const", asFUNCTION(ConvToColorF), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
