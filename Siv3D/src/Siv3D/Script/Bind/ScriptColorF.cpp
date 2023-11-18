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

	using ValueType = ColorF;

	static void Construct(const ColorF& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructDD(double rgb, double a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructDDDD(double r, double g, double b, double a, ValueType* self)
	{
		new(self) ValueType(r, g, b, a);
	}

	static void ConstructCD(const ColorF& rgb, double a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructVD(const Vec3& rgb, double a, ValueType* self)
	{
		new(self) ValueType(rgb, a);
	}

	static void ConstructV4(const Vec4& rgba, ValueType* self)
	{
		new(self) ValueType(rgba);
	}

	static void ConstructC(const Color& color, ValueType* self)
	{
		new(self) ValueType(color);
	}

	static void ConstructCA(const Color& color, double a, ValueType* self)
	{
		new(self) ValueType(color, a);
	}

	static void ConstructH(const HSV& hsv, ValueType* self)
	{
		new(self) ValueType(hsv);
	}

	static void ConstructHA(const HSV& hsv, double a, ValueType* self)
	{
		new(self) ValueType(hsv, a);
	}

	static void ConstructS(const String& code, ValueType* self)
	{
		new(self) ValueType(code);
	}

	static ColorF MulColorF(double other, const ColorF& value)
	{
		return (value * other);
	}

	static bool EqualsColorF(const ColorF& other, const ColorF& value)
	{
		return (value == other);
	}

	void RegisterColorF(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "ColorF";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ColorF, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double g", asOFFSET(ColorF, g)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double b", asOFFSET(ColorF, b)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double a", asOFFSET(ColorF, a)); assert(r >= 0);

		//
		//	Constructor
		//
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double r, double g, double b, double a = 1.0)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double rgb, double a = 1.0) explicit", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const ColorF& in, double)", asFUNCTION(ConstructCD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec3& in, double a = 1.0) explicit", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec4& in) explicit", asFUNCTION(ConstructV4), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in)", asFUNCTION(ConstructC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, double a)", asFUNCTION(ConstructCA), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in)", asFUNCTION(ConstructH), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const HSV& in, double a)", asFUNCTION(ConstructHA), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in) explicit", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// elem
		//
		r = engine->RegisterObjectMethod(TypeName, "double elem(size_t) const", asMETHODPR(ColorF, elem, (size_t) const noexcept, double), asCALL_THISCALL); assert(r >= 0);

		//
		// =
		//
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opAssign(const ColorF& in)", asMETHODPR(ColorF, operator=, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opAssign(Color)", asMETHODPR(ColorF, operator=, (Color), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opAssign(const HSV& in)", asMETHODPR(ColorF, operator=, (const HSV&), ColorF&), asCALL_THISCALL); assert(r >= 0);

		//
		//	+, +=, -, -=
		//
		r = engine->RegisterObjectMethod(TypeName, "ColorF opAdd(const ColorF& in) const", asMETHODPR(ColorF, operator+, (const ColorF&) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opAddAssign(const ColorF& in)", asMETHODPR(ColorF, operator+=, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF opSub(const ColorF& in) const", asMETHODPR(ColorF, operator-, (const ColorF&) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& oopSubAssign(const ColorF& in)", asMETHODPR(ColorF, operator-=, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);

		//
		//	*, *=
		//
		r = engine->RegisterObjectMethod(TypeName, "ColorF opMul(double) const", asMETHODPR(ColorF, operator*, (double) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opMulAssign(double)", asMETHODPR(ColorF, operator*=, (double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF opMul(const ColorF &in) const", asMETHODPR(ColorF, operator*, (const ColorF&) const, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& opMulAssign(const ColorF &in)", asMETHODPR(ColorF, operator*=, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);	
		r = engine->RegisterObjectMethod(TypeName, "ColorF opMul_r(double) const", asFUNCTION(MulColorF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const ColorF& in) const", asFUNCTION(EqualsColorF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	with
		//
		r = engine->RegisterObjectMethod(TypeName, "ColorF withR(double) const", asMETHODPR(ColorF, withR, (double) const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF withG(double) const", asMETHODPR(ColorF, withG, (double) const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF withB(double) const", asMETHODPR(ColorF, withB, (double) const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF withA(double) const", asMETHODPR(ColorF, withA, (double) const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setR(double r)", asMETHODPR(ColorF, setR, (double) noexcept, ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setG(double g)", asMETHODPR(ColorF, setG, (double) noexcept, ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setB(double b)", asMETHODPR(ColorF, setB, (double) noexcept, ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setA(double a)", asMETHODPR(ColorF, setA, (double) noexcept, ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setRGB(double rgb)", asMETHODPR(ColorF, setRGB, (double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& setRGB(double r, double g, double b)", asMETHODPR(ColorF, setRGB, (double, double, double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& set(double rgb, double a = 1.0)", asMETHODPR(ColorF, set, (double, double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& set(double r, double g, double b, double a = 1.0)", asMETHODPR(ColorF, set, (double, double, double, double), ColorF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF& set(const ColorF& in)", asMETHODPR(ColorF, set, (const ColorF&), ColorF&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double grayscale() const", asMETHODPR(ColorF, grayscale, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double minRGBComponent() const", asMETHODPR(ColorF, minRGBComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double maxRGBComponent() const", asMETHODPR(ColorF, maxRGBComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double minComponent() const", asMETHODPR(ColorF, minComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double maxComponent() const", asMETHODPR(ColorF, maxComponent, () const noexcept, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF lerp(const ColorF& in, double) const", asMETHODPR(ColorF, lerp, (const ColorF&, double) const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF gamma(double) const", asMETHODPR(ColorF, gamma, (double) const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF removeSRGBCurve() const", asMETHODPR(ColorF, removeSRGBCurve, () const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "ColorF applySRGBCurve() const", asMETHODPR(ColorF, applySRGBCurve, () const noexcept, ColorF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(ColorF, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Color toColor() const", asMETHODPR(ColorF, toColor, () const noexcept, Color), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float4 toFloat4() const", asMETHODPR(ColorF, toFloat4, () const noexcept, Float4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 toVec4() const", asMETHODPR(ColorF, toVec4, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 rg() const", asMETHODPR(ColorF, rg, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 gb() const", asMETHODPR(ColorF, gb, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 ba() const", asMETHODPR(ColorF, ba, () const noexcept, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec3 rgb() const", asMETHODPR(ColorF, rgb, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 gba() const", asMETHODPR(ColorF, gba, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec3 bgr() const", asMETHODPR(ColorF, bgr, () const noexcept, Vec3), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec4 rgba() const", asMETHODPR(ColorF, rgba, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 rgb0() const", asMETHODPR(ColorF, rgb0, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 rgb1() const", asMETHODPR(ColorF, rgb1, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 argb() const", asMETHODPR(ColorF, argb, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec4 abgr() const", asMETHODPR(ColorF, abgr, () const noexcept, Vec4), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("ColorF Zero()", asFUNCTION(ColorF::Zero), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("ColorF One()", asFUNCTION(ColorF::One), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterGlobalFunction("ColorF AlphaF(double)", asFUNCTION(AlphaF), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("ColorF Transparency(double)", asFUNCTION(Transparency), asCALL_CDECL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "Color opImplConv() const", asMETHOD(ColorF, toColor), asCALL_THISCALL); assert(r >= 0);
	}
}
