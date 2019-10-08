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
# include <Siv3D/Polygon.hpp>
# include "ScriptBind.hpp"
# include "../AngelScript/scriptarray.h"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Polygon;

	static void DefaultConstruct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void CopyConstruct(const Polygon& other, ShapeType* self)
	{
		new(self) ShapeType(other);
	}

	static void ConstructS(const Shape2D& shape2D, ShapeType* self)
	{
		new(self) ShapeType(shape2D);
	}

	static void Destruct(ShapeType* self)
	{
		self->~Polygon();
	}

	static void ListConstruct(const void* list, ShapeType* self)
	{
		const size_t length = *static_cast<const asUINT*>(list);
		const Vec2* data = static_cast<const Vec2*>(static_cast<const void*>(static_cast<const uint8*>(list) + 4));
		new(self) ShapeType(data, length);
	}

	static CScriptArray* Outer(const Polygon& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Array<Vec2>");

		if (void* mem = std::malloc(self.outer().size_bytes() + sizeof(asUINT)))
		{
			*(asUINT*)mem = static_cast<asUINT>(self.outer().size());
			std::memcpy(((asUINT*)mem) + 1, self.outer().data(), self.outer().size_bytes());

			const auto p = CScriptArray::Create(typeID, mem);
			std::free(mem);

			return p;
		}
		else
		{
			return nullptr;
		}
	}

	static bool ConvToBool(const Polygon& polygon)
	{
		return !polygon.isEmpty();
	}

	void RegisterPolygon(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Polygon";

		int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Polygon& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Shape2D& in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const Vec2& in) {repeat Vec2}", asFUNCTION(ListConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);


		//Ctrs
		//...

		r = engine->RegisterObjectMethod(TypeName, "Polygon& opAssign(const Polygon& in)", asMETHODPR(ShapeType, operator =, (const ShapeType&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(ShapeType, isEmpty), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool hasHoles() const", asMETHOD(ShapeType, hasHoles), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 num_holes() const", asMETHOD(ShapeType, num_holes), asCALL_THISCALL); assert(r >= 0);

		// void swap(Polygon& polygon) noexcept;
		r = engine->RegisterObjectMethod(TypeName, "Array<Vec2>@ outer() const", asFUNCTION(Outer), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//[[nodiscard]] const Array<Array<Vec2>>& inners() const;
		//[[nodiscard]] const Array<Float2>& vertices() const;
		//[[nodiscard]] const Array<uint32>& indices() const;

		r = engine->RegisterObjectMethod(TypeName, "const RectF& boundingRect() const", asMETHOD(ShapeType, boundingRect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 num_triangles() const", asMETHOD(ShapeType, num_triangles), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Triangle triangle(uint32) const", asMETHOD(ShapeType, triangle), asCALL_THISCALL); assert(r >= 0);

		//Polygon& addHole(const Array<Vec2>& hole);
		//Polygon& addHoles(const Array<Array<Vec2>>& holes);

		r = engine->RegisterObjectMethod(TypeName, "Polygon movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon movedBy(const Vec2& in) const", asMETHODPR(ShapeType, movedBy, (const Vec2&) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& moveBy(const Vec2 &in)", asMETHODPR(ShapeType, moveBy, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon rotated() const", asMETHOD(ShapeType, rotated), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon rotatedAt(double, double, double) const", asMETHODPR(ShapeType, rotatedAt, (double, double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon rotatedAt(const Vec2& in, double) const", asMETHODPR(ShapeType, rotatedAt, (const Vec2&, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon& rotate()", asMETHOD(ShapeType, rotate), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& rotateAt(double, double, double)", asMETHODPR(ShapeType, rotateAt, (double, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& rotateAt(const Vec2& in, double)", asMETHODPR(ShapeType, rotateAt, (const Vec2&, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon transformed(double s, double c, const Vec2& in) const", asMETHOD(ShapeType, transformed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& transform(double s, double c, const Vec2& in)", asMETHOD(ShapeType, transform), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon scaled(double s) const", asMETHODPR(ShapeType, scaled, (double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& scale(double s)", asMETHODPR(ShapeType, scale, (double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon scaled(const Vec2& s) const", asMETHODPR(ShapeType, scaled, (const Vec2&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& scale(const Vec2& s)", asMETHODPR(ShapeType, scale, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double area() const", asMETHOD(ShapeType, area), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double perimeter() const", asMETHOD(ShapeType, perimeter), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 centroid() const", asMETHOD(ShapeType, centroid), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateConvexHull() const", asMETHOD(ShapeType, calculateConvexHull), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateBuffer(double) const", asMETHOD(ShapeType, calculateBuffer), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateRoundBuffer(double) const", asMETHOD(ShapeType, calculateRoundBuffer), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon simplified(double maxDistance = 2.0) const", asMETHOD(ShapeType, simplified), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool append(const Polygon& in)", asMETHOD(ShapeType, append), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier3& in) const", asMETHODPR(ShapeType, intersects, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asMETHODPR(ShapeType, intersects, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asMETHODPR(ShapeType, intersects, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asMETHODPR(ShapeType, intersects, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asMETHODPR(ShapeType, intersects, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asMETHODPR(ShapeType, intersects, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asMETHODPR(ShapeType, intersects, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asMETHODPR(ShapeType, intersects, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asMETHODPR(ShapeType, intersects, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const MultiPolygon& in) const", asMETHODPR(ShapeType, intersects, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asMETHODPR(ShapeType, intersects, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		// contains

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHOD(ShapeType, leftClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHOD(ShapeType, leftPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHOD(ShapeType, leftReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHOD(ShapeType, rightClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHOD(ShapeType, rightPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHOD(ShapeType, rightReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHOD(ShapeType, mouseOver), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Polygon& draw(const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void draw(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, draw, (double, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void draw(const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, draw, (const Vec2&, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);
		//const Polygon& draw(const Array<ColorF>& colors) const;

		r = engine->RegisterObjectMethod(TypeName, "const Polygon& drawFrame(double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawFrame(double x, double y, double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawFrame(const Vec2& in, double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (const Vec2&, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Polygon& drawWireframe(double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawWireframe, (double, const ColorF&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawWireframe(double x, double y, double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawWireframe, (double, double, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawWireframe(const Vec2& in, double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawWireframe, (const Vec2&, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void drawTransformed(double s, double c, const Vec2& in, const ColorF& in color = Palette::White) const", asMETHOD(ShapeType, drawTransformed), asCALL_THISCALL); assert(r >= 0);
	}
}
