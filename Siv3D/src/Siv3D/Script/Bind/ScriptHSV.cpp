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

	static void ConstructHA(const HSV& hsv, double a, ValueType* self)
	{
		new(self) ValueType(hsv, a);
	}

	static void ConstructC(const Color& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructCf(const ColorF& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static bool EqualsHSV(const HSV& other, const HSV& value)
	{
		return (value == other);
	}

	//static Color ConvToColor(const HSV& hsv)
	//{
	//	return hsv.toColor();
	//}

	//static ColorF ConvToColorF(const HSV& hsv)
	//{
	//	return hsv.toColorF();
	//}

	void RegisterHSV(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "HSV";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double h", asOFFSET(HSV, h)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double s", asOFFSET(HSV, s)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double v", asOFFSET(HSV, v)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double a", asOFFSET(HSV, a)); assert(r >= 0);

		//
		//	Constructor
		//
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructDefault), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double h, double a = 1.0) explicit", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double h, double s, double v, double a = 1.0)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in, double a)", asFUNCTION(ConstructHA), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in)", asFUNCTION(ConstructC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF& in)", asFUNCTION(ConstructCf), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// elem
		//
		r = engine->RegisterObjectMethod(TypeName, "double elem(size_t) const", asMETHODPR(ColorF, elem, (size_t) const noexcept, double), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, -
		//
		r = engine->RegisterObjectMethod(TypeName, "HSV opAdd(const HSV& in) const", asMETHODPR(HSV, operator+, (const HSV&) const, HSV), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV opSub(const HSV& in) const", asMETHODPR(HSV, operator-, (const HSV&) const, HSV), asCALL_THISCALL); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const ColorF& in) const", asFUNCTION(EqualsHSV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	with
		//
		r = engine->RegisterObjectMethod(TypeName, "HSV withH(double h) const", asMETHODPR(HSV, withH, (double) const noexcept, HSV), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV withS(double s) const", asMETHODPR(HSV, withS, (double) const noexcept, HSV), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV withV(double v) const", asMETHODPR(HSV, withV, (double) const noexcept, HSV), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV withA(double a) const", asMETHODPR(HSV, withA, (double) const noexcept, HSV), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "HSV& setH(double h)", asMETHODPR(HSV, setH, (double) noexcept, HSV&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV& setS(double s)", asMETHODPR(HSV, setS, (double) noexcept, HSV&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV& setV(double v)", asMETHODPR(HSV, setV, (double) noexcept, HSV&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV& setA(double a)", asMETHODPR(HSV, setA, (double) noexcept, HSV&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV& setHSV(double h, double s, double v)", asMETHODPR(HSV, setHSV, (double, double, double) noexcept, HSV&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV& set(double h, double s, double v, double a = 1.0)", asMETHODPR(HSV, set, (double, double, double, double), HSV&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "HSV& set(const HSV& in)", asMETHODPR(HSV, set, (const HSV&), HSV&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "HSV lerp(const HSV& in, double) const", asMETHODPR(HSV, lerp, (const HSV&, double) const noexcept, HSV), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(HSV, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "ColorF removeSRGBCurve() const", asMETHODPR(HSV, removeSRGBCurve, () const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF applySRGBCurve() const", asMETHODPR(HSV, applySRGBCurve, () const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color toColor() const", asMETHODPR(HSV, toColor, () const noexcept, Color), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Color toColor(uint32) const", asMETHODPR(HSV, toColor, (uint32) const noexcept, Color), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF toColorF() const", asMETHODPR(HSV, toColorF, () const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF toColorF(double) const", asMETHODPR(HSV, toColorF, (double) const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 hsv() const", asMETHODPR(HSV, hsv, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 hsva() const", asMETHODPR(HSV, hsva, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("HSV Zero()", asFUNCTION(HSV::Zero), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "Color opImplConv() const", asFUNCTION(ConvToColor), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "ColorF opImplConv() const", asFUNCTION(ConvToColorF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Color HueToColor(double)", asFUNCTION(HueToColor), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("ColorF HueToColorF(double)", asFUNCTION(HueToColorF), asCALL_CDECL); assert(r >= 0);
	}
}
