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
# include <Siv3D/Spline2D.hpp>
# include "ScriptArray.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Spline2D;

	static void DefaultConstruct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void CopyConstruct(const Spline2D& other, ShapeType* self)
	{
		new(self) ShapeType(other);
	}

	static void Construct1(const CScriptArray* arr, double t, ShapeType* self)
	{
		new(self) ShapeType(detail::FromScriptArray<Vec2>(arr), t);
	}

	static void Construct2(const LineString& lines, double t, ShapeType* self)
	{
		new(self) ShapeType(lines, t);
	}

	static void Construct3(const CScriptArray* arr, bool closeRing, double t, ShapeType* self)
	{
		new(self) ShapeType(detail::FromScriptArray<Vec2>(arr), CloseRing{ closeRing }, t);
	}

	static void Construct4(const LineString& lines, bool closeRing, double t, ShapeType* self)
	{
		new(self) ShapeType(lines, CloseRing{ closeRing }, t);
	}

	static void Destruct(ShapeType* self)
	{
		self->~Spline2D();
	}

	static bool ConvToBool(const ShapeType& a)
	{
		return static_cast<bool>(a);
	}

	void RegisterSpline2D(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Spline2D";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineString& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Array<Vec2>& in, double tension = 0.0) explicit", asFUNCTION(Construct1), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineString& in, double tension = 0.0) explicit", asFUNCTION(Construct2), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Array<Vec2>& in, bool closeRing, double tension = 0.0) explicit", asFUNCTION(Construct3), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineString& in, bool closeRing, double tension = 0.0) explicit", asFUNCTION(Construct4), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// =
		//
		r = engine->RegisterObjectMethod(TypeName, "Spline2D& opAssign(const Spline2D& in)", asMETHODPR(ShapeType, operator =, (const ShapeType&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "size_t size() const", asMETHODPR(ShapeType, size, () const, size_t), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHODPR(ShapeType, isEmpty, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isRing() const", asMETHODPR(ShapeType, isRing, () const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHOD(ShapeType, clear), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF fastBoundingRect(size_t) const", asMETHODPR(ShapeType, fastBoundingRect, (size_t) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF boundingRect(size_t) const", asMETHODPR(ShapeType, boundingRect, (size_t) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double length(size_t i, double maxError = 0.01) const", asMETHODPR(ShapeType, length, (size_t, double) const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double length(size_t i, double t0, double t1, double maxError = 0.01) const", asMETHODPR(ShapeType, length, (size_t, double, double, double) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 position(size_t, double) const", asMETHODPR(ShapeType, position, (size_t, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 velocity(size_t, double) const", asMETHODPR(ShapeType, velocity, (size_t, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 boundingRect(size_t, double) const", asMETHODPR(ShapeType, acceleration, (size_t, double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double curvature(size_t, double) const", asMETHODPR(ShapeType, curvature, (size_t, double) const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineString asLineString(int32 quality = 24) const", asMETHODPR(ShapeType, asLineString, (int32) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateRoundBuffer(double distance, int32 quality = 24, int32 bufferQuality = 24) const", asMETHODPR(ShapeType, calculateRoundBuffer, (double, int32, int32) const, Polygon), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Spline2D& draw(const ColorF& in = Palette::White, int32 quality = 24) const", asMETHODPR(ShapeType, draw, (const ColorF&, int32) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Spline2D& draw(double, const ColorF& in = Palette::White, int32 quality = 24) const", asMETHODPR(ShapeType, draw, (double, const ColorF&, int32) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Spline2D& draw(const LineStyle& in, double, const ColorF& in = Palette::White, int32 quality = 24) const", asMETHODPR(ShapeType, draw, (const LineStyle&, double, const ColorF&, int32) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void swap(Spline2D& inout)", asMETHODPR(ShapeType, swap, (Spline2D&), void), asCALL_THISCALL); assert(r >= 0);
	}
}
