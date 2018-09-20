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
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

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

	void RegisterMat3x2(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Mat3x2";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "float _11", asOFFSET(BindType, _11)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _12", asOFFSET(BindType, _12)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _21", asOFFSET(BindType, _21)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _22", asOFFSET(BindType, _22)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _31", asOFFSET(BindType, _31)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float _32", asOFFSET(BindType, _32)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Mat3x2 &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float)", asFUNCTION(ConstructFFFFFF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Mat3x2 Identity()", asFUNCTION(Mat3x2::Identity), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Translate(const Float2& in)", asFUNCTIONPR(Mat3x2::Translate, (const Float2&), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Translate(double, double)", asFUNCTIONPR(Mat3x2::Translate, (double, double), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Scale(const Float2&, const Float2& in center = Float2(0, 0))", asFUNCTIONPR(Mat3x2::Scale, (const Float2&, const Float2&), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Scale(double, const Float2& in center = Float2(0, 0))", asFUNCTIONPR(Mat3x2::Scale, (double, const Float2&), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Scale(double, double, const Float2& in center = Float2(0, 0))", asFUNCTIONPR(Mat3x2::Scale, (double, double, const Float2&), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Rotate(double, const Float2& in center = Float2(0, 0))", asFUNCTIONPR(Mat3x2::Rotate, (double, const Float2&), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 ShearX(double)", asFUNCTIONPR(Mat3x2::ShearX, (double), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 ShearY(double)", asFUNCTIONPR(Mat3x2::ShearY, (double), Mat3x2), asCALL_CDECL); assert(r >= 0);		
			r = engine->RegisterGlobalFunction("Mat3x2 Screen(double, double)", asFUNCTIONPR(Mat3x2::Translate, (double, double), Mat3x2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Mat3x2 Screen(const Float2& in)", asFUNCTIONPR(Mat3x2::Translate, (const Float2&), Mat3x2), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 translated(const Float2&) const", asMETHODPR(BindType, translated, (const Float2&) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 translated(double, double) const", asMETHODPR(BindType, translated, (double, double) const, BindType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 scaled(double, const Float2& in center = Float2(0, 0)) const", asMETHODPR(BindType, scaled, (double, const Float2&) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 scaled(const Float2& in, const Float2& in center = Float2(0, 0)) const", asMETHODPR(BindType, scaled, (const Float2&, const Float2&) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 scaled(double, double, const Float2& in center = Float2(0, 0)) const", asMETHODPR(BindType, scaled, (double, double, const Float2&) const, BindType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 rotated(double, const Float2& in center = Float2(0, 0)) const", asMETHODPR(BindType, rotated, (double, const Float2&) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 shearedX(double, const Float2& in center = Float2(0, 0)) const", asMETHODPR(BindType, shearedX, (double) const, BindType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 shearedY(double, const Float2& in center = Float2(0, 0)) const", asMETHODPR(BindType, shearedY, (double) const, BindType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "float determinant() const", asMETHOD(BindType, determinant), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 inversed() const", asMETHOD(BindType, inversed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setProduct(const Mat3x2& in, const Mat3x2& in)", asMETHOD(BindType, setProduct), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 opMul(const Mat3x2& in) const", asMETHODPR(Mat3x2, operator*, (const Mat3x2&) const, Mat3x2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Float2 transform(const Point& in) const", asMETHODPR(Mat3x2, transform, (const Point&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Float2 transform(const Float2& in) const", asMETHODPR(Mat3x2, transform, (const Float2&) const, Float2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 transform(const Vec2& in) const", asMETHODPR(Mat3x2, transform, (const Vec2&) const, Vec2), asCALL_THISCALL); assert(r >= 0);
	}
}
