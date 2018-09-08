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
# include <Siv3D/LineString.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = LineString;

	static void DefaultConstruct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void CopyConstruct(const LineString& other, ShapeType* self)
	{
		new(self) ShapeType(other);
	}

	static void Destruct(ShapeType* self)
	{
		self->~LineString();
	}

	static void ConstructI(uint32 size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructIV(uint32 size, const Vec2& value, ShapeType* self)
	{
		new(self) ShapeType(size, value);
	}

	static void ListConstruct(const void* list, ShapeType* self)
	{
		const size_t length = *static_cast<const asUINT*>(list);
		const Vec2* data = static_cast<const Vec2*>(static_cast<const void*>(static_cast<const uint8*>(list) + 4));
		new(self) ShapeType(data, data + length);
	}

	static bool ConvToBool(const LineString& lineString)
	{
		return !lineString.isEmpty();
	}

	void RegisterLineString(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "LineString";

		int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineString& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32)", asFUNCTION(ConstructI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32, const Vec2& in)", asFUNCTION(ConstructIV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const Vec2& in) {repeat Vec2}", asFUNCTION(ListConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//Ctrs
		//...

		r = engine->RegisterObjectMethod(TypeName, "LineString& opAssign(const LineString& in)", asMETHODPR(ShapeType, operator =, (const ShapeType&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(ShapeType, isEmpty), asCALL_THISCALL); assert(r >= 0);

		// void assign(const LineString& other)

		r = engine->RegisterObjectMethod(TypeName, "LineString& opShl() const", asMETHOD(ShapeType, operator <<), asCALL_THISCALL); assert(r >= 0);

		// Array member functions
		// ...
		//

		//void swap(LineString& other) noexcept
		//LineString& append(const Array<Vec2>& other)
		//LineString& append(const LineString& other)

		r = engine->RegisterObjectMethod(TypeName, "uint32 size() const", asMETHOD(ShapeType, size), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 num_lines() const", asMETHOD(ShapeType, num_lines), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line line(uint32 index) const", asMETHOD(ShapeType, line), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineString movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString movedBy(const Vec2& in) const", asMETHODPR(ShapeType, movedBy, (const Vec2&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& moveBy(const Vec2& in)", asMETHODPR(ShapeType, moveBy, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF calculateBoundingRect() const", asMETHOD(ShapeType, calculateBoundingRect), asCALL_THISCALL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier3& in) const", asMETHODPR(ShapeType, intersects, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asMETHODPR(ShapeType, intersects, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asMETHODPR(ShapeType, intersects, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asMETHODPR(ShapeType, intersects, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asMETHODPR(ShapeType, intersects, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asMETHODPR(ShapeType, intersects, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asMETHODPR(ShapeType, intersects, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asMETHODPR(ShapeType, intersects, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asMETHODPR(ShapeType, intersects, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const MultiPolygon& in) const", asMETHODPR(ShapeType, intersects, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asMETHODPR(ShapeType, intersects, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineString catmullRom(bool isClosed = false, int32 interpolation = 24) const", asMETHOD(ShapeType, catmullRom), asCALL_THISCALL); assert(r >= 0);

		//const LineString& paint(Image& dst, const Color& color, bool isClosed = false) const;
		//const LineString& paint(Image& dst, int32 thickness, const Color& color, bool isClosed = false) const;
		//const LineString& overwrite(Image& dst, const Color& color, bool isClosed = false, bool antialiased = true) const;
		//const LineString& overwrite(Image& dst, int32 thickness, const Color& color, bool isClosed = false, bool antialiased = true) const;

		r = engine->RegisterObjectMethod(TypeName, "const LineString& draw(const ColorF& in = Palette::White, bool isClosed = false) const", asMETHODPR(ShapeType, draw, (const ColorF&, bool) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& draw(double, const ColorF& in = Palette::White, bool isClosed = false) const", asMETHODPR(ShapeType, draw, (double, const ColorF&, bool) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& draw(const LineStyle& in, double, const ColorF& in = Palette::White, bool isClosed = false) const", asMETHODPR(ShapeType, draw, (const LineStyle&, double, const ColorF&, bool) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void drawCatmullRom(const ColorF& in = Palette::White, bool isClosed = false, int32 interpolation = 24) const", asMETHODPR(ShapeType, drawCatmullRom, (const ColorF&, bool, int32) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawCatmullRom(double, const ColorF& in = Palette::White, bool isClosed = false, int32 interpolation = 24) const", asMETHODPR(ShapeType, drawCatmullRom, (double, const ColorF&, bool, int32) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawCatmullRom(const LineStyle& in, double, const ColorF& in = Palette::White, bool isClosed = false, int32 interpolation = 24) const", asMETHODPR(ShapeType, drawCatmullRom, (const LineStyle&, double, const ColorF&, bool, int32) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateBuffer(double distance, bool isClosed = false, int32 quality = 24) const", asMETHOD(ShapeType, catmullRom), asCALL_THISCALL); assert(r >= 0);
	}
}
