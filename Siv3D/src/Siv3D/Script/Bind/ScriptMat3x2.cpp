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
# include <Siv3D/Mat3x2.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Mat3x2;

	static void CopyConstruct(const Mat3x2& mat, BindType* self)
	{
		new(self) BindType(mat);
	}

	static void ConstructFFFFFF(float _11, float _12, float _21, float _22, float _31, float _32, BindType* self)
	{
		new(self) BindType(_11, _12, _21, _22, _31, _32);
	}

	static bool EqualsMat3x2(const BindType& other, const BindType& value)
	{
		return (value == other);
	}

	void RegisterMat3x2(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Mat3x2";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "float _11", asOFFSET(BindType, _11)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _12", asOFFSET(BindType, _12)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _21", asOFFSET(BindType, _21)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _22", asOFFSET(BindType, _22)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _31", asOFFSET(BindType, _31)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _32", asOFFSET(BindType, _32)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Mat3x2 &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float)", asFUNCTION(ConstructFFFFFF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Mat3x2& in) const", asFUNCTION(EqualsMat3x2), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 translated(Float2) const", asMETHODPR(BindType, translated, (Float2) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 translated(double, double) const", asMETHODPR(BindType, translated, (double, double) const, BindType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 scaled(double, Float2 center = Float2(0, 0)) const", asMETHODPR(BindType, scaled, (double, Float2) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 scaled(Float2, Float2 center = Float2(0, 0)) const", asMETHODPR(BindType, scaled, (Float2, Float2) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 scaled(double, double, Float2 center = Float2(0, 0)) const", asMETHODPR(BindType, scaled, (double, double, Float2) const, BindType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 rotated(double, Float2 center = Float2(0, 0)) const", asMETHODPR(BindType, rotated, (double, Float2) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 shearedX(double) const", asMETHODPR(BindType, shearedX, (double) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 shearedY(double) const", asMETHODPR(BindType, shearedY, (double) const, BindType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float determinant() const", asMETHODPR(BindType, determinant, () const noexcept, float), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 inverse() const", asMETHODPR(BindType, inverse, () const noexcept, Mat3x2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setProduct(const Mat3x2& in, const Mat3x2& in)", asMETHODPR(BindType, setProduct, (const Mat3x2&, const Mat3x2&) noexcept, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 opMul(const Mat3x2& in) const", asMETHODPR(Mat3x2, operator*, (const Mat3x2&) const, Mat3x2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 transformPoint(Point) const", asMETHODPR(Mat3x2, transformPoint, (Point) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 transformPoint(Float2) const", asMETHODPR(Mat3x2, transformPoint, (Float2) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 transformPoint(Vec2) const", asMETHODPR(Mat3x2, transformPoint, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Mat3x2, hash, () const noexcept, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Mat3x2 Identity()", asFUNCTION(Mat3x2::Identity), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Translate(Float2)", asFUNCTIONPR(Mat3x2::Translate, (Float2), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Translate(double, double)", asFUNCTIONPR(Mat3x2::Translate, (double, double), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Scale(Float2, Float2 center = Float2(0, 0))", asFUNCTIONPR(Mat3x2::Scale, (Float2, Float2), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Scale(double, Float2 center = Float2(0, 0))", asFUNCTIONPR(Mat3x2::Scale, (double, Float2), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Scale(double, double, Float2 center = Float2(0, 0))", asFUNCTIONPR(Mat3x2::Scale, (double, double, Float2), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Rotate(double, Float2 center = Float2(0, 0))", asFUNCTIONPR(Mat3x2::Rotate, (double, Float2), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 ShearX(double)", asFUNCTIONPR(Mat3x2::ShearX, (double), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 ShearY(double)", asFUNCTIONPR(Mat3x2::ShearY, (double), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Screen(double, double)", asFUNCTIONPR(Mat3x2::Screen, (double, double), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Screen(Float2)", asFUNCTIONPR(Mat3x2::Screen, (Float2), Mat3x2), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
