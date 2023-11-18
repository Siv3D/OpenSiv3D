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
# include <Siv3D/ColorHSV.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ValueType = Color;

	static void Construct(const Color& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructUUUU(uint8 r, uint8 g, uint8 b, uint8 a, ValueType* self)
	{
		new(self) ValueType(r, g, b, a);
	}

	static void ConstructUU(uint8 rgb, uint8 a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructCU(const Color& rgb, uint8 a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructCf(const ColorF& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructCfU(const ColorF& color, uint8 a, ValueType* self)
	{
		new(self) ValueType(color, a);
	}

	static void ConstructH(const HSV& hsv, ValueType* self)
	{
		new(self) ValueType(hsv);
	}

	static void ConstructHU(const HSV& hsv, uint8 a, ValueType* self)
	{
		new(self) ValueType(hsv, a);
	}

	static void ConstructS(const String& code, ValueType* self)
	{
		new(self) ValueType(code);
	}

	static bool EqualsColor(const Color& other, const Color& value)
	{
		return (value == other);
	}

	//static ColorF ConvToColorF(const ValueType& value)
	//{
	//	return value;
	//}

	void RegisterColor(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Color";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "uint8 r", 0); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "uint8 g", 1); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "uint8 b", 2); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "uint8 a", 3); assert(r >= 0);

		//
		//	Constructor
		//
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint8 r, uint8 g, uint8 b, uint8 a = 255)", asFUNCTION(ConstructUUUU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint8 rgb, uint8 a = 255) explicit", asFUNCTION(ConstructUU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, uint8 a)", asFUNCTION(ConstructCU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF& in)", asFUNCTION(ConstructCf), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF& in, uint8 a)", asFUNCTION(ConstructCfU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in)", asFUNCTION(ConstructH), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in, uint8 a)", asFUNCTION(ConstructHU), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in) explicit", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// =
		//
		r = engine->RegisterObjectMethod(TypeName, "Color& opAssign(const Color& in)", asMETHODPR(Color, operator=, (const Color&), Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& opAssign(const ColorF& in)", asMETHODPR(Color, operator=, (const ColorF&), Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& opAssign(const HSV& in)", asMETHODPR(Color, operator=, (const HSV&), Color&), asCALL_THISCALL); assert(r >= 0);

		//
		//	~
		//
		r = engine->RegisterObjectMethod(TypeName, "Color opCom() const", asMETHODPR(Color, operator~, () const noexcept, Color), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Color& in) const", asFUNCTION(EqualsColor), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	with
		//
		r = engine->RegisterObjectMethod(TypeName, "Color withR(uint32 r)", asMETHODPR(Color, withR, (uint32) const noexcept, Color), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color withG(uint32 g)", asMETHODPR(Color, withG, (uint32) const noexcept, Color), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color withB(uint32 b)", asMETHODPR(Color, withB, (uint32) const noexcept, Color), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color withA(uint32 a)", asMETHODPR(Color, withA, (uint32) const noexcept, Color), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Color& setR(uint32 r)", asMETHODPR(Color, setR, (uint32) noexcept, Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& setG(uint32 g)", asMETHODPR(Color, setG, (uint32) noexcept, Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& setB(uint32 b)", asMETHODPR(Color, setB, (uint32) noexcept, Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& setA(uint32 a)", asMETHODPR(Color, setA, (uint32) noexcept, Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& setRGB(uint32 rgb)", asMETHODPR(Color, setRGB, (uint32) noexcept, Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& setRGB(uint32 r, uint32 g, uint32 b)", asMETHODPR(Color, setRGB, (uint32, uint32, uint32) noexcept, Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& set(uint32 rgb, uint32 a = 255)", asMETHODPR(Color, set, (uint32, uint32) noexcept, Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& set(uint32 r, uint32 g, uint32 b, uint32 a = 255)", asMETHODPR(Color, set, (uint32, uint32, uint32, uint32) noexcept, Color&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color& set(Color)", asMETHODPR(Color, set, (Color) noexcept, Color&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "uint8 grayscale0_255() const", asMETHODPR(Color, grayscale0_255, () const noexcept, uint8), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double grayscale() const", asMETHODPR(Color, grayscale, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint8 minRGBComponent() const", asMETHODPR(Color, minRGBComponent, () const noexcept, uint8), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint8 maxRGBComponent() const", asMETHODPR(Color, maxRGBComponent, () const noexcept, uint8), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint8 minComponent() const", asMETHODPR(Color, minComponent, () const noexcept, uint8), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint8 maxComponent() const", asMETHODPR(Color, maxComponent, () const noexcept, uint8), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 asUint32() const", asMETHODPR(Color, asUint32, () const noexcept, uint32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color lerp(Color, double) const", asMETHODPR(Color, lerp, (Color, double) const noexcept, Color), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color gamma(double) const", asMETHODPR(Color, gamma, (double) const noexcept, Color), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF removeSRGBCurve() const", asMETHODPR(Color, removeSRGBCurve, () const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF applySRGBCurve() const", asMETHODPR(Color, applySRGBCurve, () const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "String toHex() const", asMETHODPR(Color, toHex, () const,  String), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Color, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Color Zero()", asFUNCTION(Color::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint8 ToUint8(float)", asFUNCTIONPR(Color::ToUint8, (float), uint8), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint8 ToUint8(double)", asFUNCTIONPR(Color::ToUint8, (double), uint8), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Color FromRGBA(uint32)", asFUNCTION(Color::FromRGBA), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Color FromABGR(uint32)", asFUNCTION(Color::FromABGR), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Color Alpha(uint32)", asFUNCTION(Alpha), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Color ToColor(float)", asFUNCTIONPR(ToColor, (float), Color), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Color ToColor(double)", asFUNCTIONPR(ToColor, (double), Color), asCALL_CDECL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "ColorF opImplConv() const", asFUNCTION(ConvToColorF), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
