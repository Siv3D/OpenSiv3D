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
# include <Siv3D/Camera2D.hpp>
# include "ScriptCamera2DParameters.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Camera2D;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const BindType& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructVDC(Vec2 center, double scale, int32 cameraControl, BindType* self)
	{
		new(self) BindType(center, scale, ToEnum<CameraControl>(static_cast<uint8>(cameraControl)));
	}

	static void ConstructVSP(Vec2 center, double scale, const ScriptCamera2DParameters& p, BindType* self)
	{
		new(self) BindType(center, scale, p.asCamera2DParameters());
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	void RegisterCamera2D(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Camera2D";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Camera2D& in) explicit", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(Vec2 center, double scale = 1.0, CameraControl cameraControl = CameraControl::Default) explicit", asFUNCTION(ConstructVDC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(Vec2 center, double scale, const Camera2DParameters& in)", asFUNCTION(ConstructVSP), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// ...
		
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "void setCenter(Vec2)", asMETHODPR(BindType, setCenter, (Vec2), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& getCenter() const", asMETHODPR(BindType, getCenter, () const, const Vec2&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void setScale(double)", asMETHODPR(BindType, setScale, (double), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double getScale() const", asMETHODPR(BindType, getScale, () const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF getRegion(Point renderTargetSize = Graphics2D::GetRenderTargetSize()) const", asMETHODPR(BindType, getRegion, (Point) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Mat3x2 getMat3x2(Point renderTargetSize = Graphics2D::GetRenderTargetSize()) const", asMETHODPR(BindType, getMat3x2, (Point) const, Mat3x2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void setTargetCenter(Vec2)", asMETHODPR(BindType, setTargetCenter, (Vec2), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& getTargetCenter() const", asMETHODPR(BindType, getTargetCenter, () const, const Vec2&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void setTargetScale(double)", asMETHODPR(BindType, setTargetScale, (double), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double getTargetScale() const", asMETHODPR(BindType, getTargetScale, () const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void jumpTo(Vec2 center, double scale)", asMETHODPR(BindType, jumpTo, (Vec2, double), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void update(double deltaTime = Scene::DeltaTime(), Vec2 sceneSize = Graphics2D::GetRenderTargetSize())", asMETHODPR(BindType, update, (double, Vec2), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void draw(const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);
	}
}
