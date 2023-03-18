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
# include <Siv3D/Shape2D.hpp>
# include "ScriptArray.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Shape2D;

	static void DefaultConstruct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void CopyConstruct(const Shape2D& other, ShapeType* self)
	{
		new(self) ShapeType(other);
	}

	static void ConstructAA(const CScriptArray* vertices, const CScriptArray* indices, ShapeType* self)
	{
		new(self) ShapeType(detail::FromScriptArray<Float2>(vertices), detail::FromScriptArray<TriangleIndex>(indices));
	}

	static void Destruct(ShapeType* self)
	{
		self->~Shape2D();
	}

	void RegisterShape2D(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Shape2D";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Shape2D& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Array<Float2>& in, const Array<TriangleIndex>& in)", asFUNCTION(ConstructAA), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Shape2D& opAssign(const Shape2D& in)", asMETHODPR(ShapeType, operator =, (const ShapeType&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace("Shape2D"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("Shape2D Cross(double r, double width, const Vec2& in center = Vec2(0, 0), double angle = 0.0)", asFUNCTION(Shape2D::Cross), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Plus(double r, double width, const Vec2& in center = Vec2(0, 0), double angle = 0.0)", asFUNCTION(Shape2D::Plus), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Pentagon(double r, const Vec2& in center = Vec2(0, 0), double angle = 0.0)", asFUNCTION(Shape2D::Pentagon), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Hexagon(double r, const Vec2& in center = Vec2(0, 0), double angle = 0.0)", asFUNCTION(Shape2D::Hexagon), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Ngon(uint32 n, double r, const Vec2& in center = Vec2(0, 0), double angle = 0.0)", asFUNCTION(Shape2D::Ngon), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Star(double r, const Vec2& in center = Vec2(0, 0), double angle = 0.0)", asFUNCTION(Shape2D::Star), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D NStar(uint32 n, double rOuter, double rInner, const Vec2& in center = Vec2(0, 0), double angle = 0.0)", asFUNCTION(Shape2D::NStar), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Arrow(const Vec2& in from, const Vec2& in to, double width, const Vec2& in headSize)", asFUNCTIONPR(Shape2D::Arrow, (const Vec2&, const Vec2&, double, const Vec2&), Shape2D), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Arrow(const Line& in line, double width, const Vec2& in headSize)", asFUNCTIONPR(Shape2D::Arrow, (const Line&, double, const Vec2&), Shape2D), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D DoubleHeadedArrow(const Vec2& in from, const Vec2& in to, double width, const Vec2& in headSize)", asFUNCTIONPR(Shape2D::DoubleHeadedArrow, (const Vec2&, const Vec2&, double, const Vec2&), Shape2D), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D DoubleHeadedArrow(const Line& in line, double width, const Vec2& in headSize)", asFUNCTIONPR(Shape2D::DoubleHeadedArrow, (const Line&, double, const Vec2&), Shape2D), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Rhombus(double w, double h, const Vec2& in center = Vec2(0, 0), double angle = 0.0)", asFUNCTION(Shape2D::Rhombus), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D RectBalloon(const RectF& in rect, const Vec2& in target, double pointingRootRatio = 0.5)", asFUNCTION(Shape2D::RectBalloon), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Stairs(const Vec2& in base, double w, double h, int32 steps, bool upStairs = true)", asFUNCTION(Shape2D::Stairs), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Heart(double r, const Vec2& in center = Vec2(0, 0), double angle = 0.0)", asFUNCTION(Shape2D::Heart), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Shape2D Squircle(double r, const Vec2& in center, uint32 quality)", asFUNCTION(Shape2D::Squircle), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		// const Array<Float2>& vertices() const
		// const Array<uint32> indices() const

		r = engine->RegisterObjectMethod(TypeName, "const Shape2D& draw(const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const Shape2D&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Shape2D& drawFrame(double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&) const, const Shape2D&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Shape2D& drawWireframe(double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawWireframe, (double, const ColorF&) const, const Shape2D&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon asPolygon() const", asMETHODPR(ShapeType, asPolygon, () const, Polygon), asCALL_THISCALL); assert(r >= 0);

		//toBuffer2D
	}
}
