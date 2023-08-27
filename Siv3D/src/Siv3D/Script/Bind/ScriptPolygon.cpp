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
# include <Siv3D/Polygon.hpp>
# include "ScriptBind.hpp"
# include "ScriptArray.hpp"

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

	static CScriptArray* Vertices(const Polygon& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Array<Float2>");

		if (void* mem = std::malloc(self.vertices().size_bytes() + sizeof(asUINT)))
		{
			*(asUINT*)mem = static_cast<asUINT>(self.vertices().size());
			std::memcpy(((asUINT*)mem) + 1, self.vertices().data(), self.vertices().size_bytes());

			const auto p = CScriptArray::Create(typeID, mem);
			std::free(mem);

			return p;
		}
		else
		{
			return nullptr;
		}
	}

	static CScriptArray* Indices(const Polygon& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Array<TriangleIndex>");

		if (void* mem = std::malloc(self.indices().size_bytes() + sizeof(asUINT)))
		{
			*(asUINT*)mem = static_cast<asUINT>(self.indices().size());
			std::memcpy(((asUINT*)mem) + 1, self.indices().data(), self.indices().size_bytes());

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
		return static_cast<bool>(polygon);
	}

	static bool AddHole(const CScriptArray* hole, Polygon& polygon)
	{
		return polygon.addHole(detail::FromScriptArray<Vec2>(hole));
	}

	void RegisterPolygon(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Polygon";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Polygon& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Shape2D& in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const Vec2& in) {repeat Vec2}", asFUNCTION(ListConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// =
		//
		r = engine->RegisterObjectMethod(TypeName, "Polygon& opAssign(const Polygon& in)", asMETHODPR(ShapeType, operator =, (const ShapeType&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHODPR(ShapeType, isEmpty, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool hasHoles() const", asMETHODPR(ShapeType, hasHoles, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t num_holes() const", asMETHODPR(ShapeType, num_holes, () const, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void swap(Polygon& inout)", asMETHODPR(ShapeType, swap, (Polygon&), void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Array<Vec2>@ outer() const", asFUNCTION(Outer), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Array<Float2>@ vertices() const", asFUNCTION(Vertices), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Array<TriangleIndex>@ indices() const", asFUNCTION(Indices), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const RectF& boundingRect() const", asMETHODPR(ShapeType, boundingRect, () const, const RectF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t num_triangles() const", asMETHODPR(ShapeType, num_triangles, () const, size_t), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Triangle triangle(size_t) const", asMETHODPR(ShapeType, triangle, (size_t) const, Triangle), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool addHole(const RectF& in) const", asMETHODPR(ShapeType, addHole, (const RectF&), bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool addHole(const Triangle& in) const", asMETHODPR(ShapeType, addHole, (const Triangle&), bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool addHole(const Quad& in) const", asMETHODPR(ShapeType, addHole, (const Quad&), bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool addHole(const Circle& in, uint32 quality = 24) const", asMETHODPR(ShapeType, addHole, (const Circle&, uint32), bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool addHole(const Ellipse& in, uint32 quality = 24) const", asMETHODPR(ShapeType, addHole, (const Ellipse&, uint32), bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool addHole(const RoundRect& in, uint32 quality = 24) const", asMETHODPR(ShapeType, addHole, (const RoundRect&, uint32), bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool addHole(const Array<Vec2>& in) const", asFUNCTION(AddHole), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const&, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon movedBy(Vec2) const", asMETHODPR(ShapeType, movedBy, (Vec2) const&, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& moveBy(Vec2)", asMETHODPR(ShapeType, moveBy, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon rotated(double) const", asMETHODPR(ShapeType, rotated, (double) const&, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon rotatedAt(double, double, double) const", asMETHODPR(ShapeType, rotatedAt, (double, double, double) const&, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon rotatedAt(Vec2, double) const", asMETHODPR(ShapeType, rotatedAt, (Vec2, double) const&, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon& rotate(double)", asMETHODPR(ShapeType, rotate, (double), Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& rotateAt(double, double, double)", asMETHODPR(ShapeType, rotateAt, (double, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& rotateAt(Vec2, double)", asMETHODPR(ShapeType, rotateAt, (Vec2, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon transformed(double s, double c, const Vec2& in) const", asMETHODPR(ShapeType, transformed, (double, double, const Vec2&) const&, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& transform(double s, double c, const Vec2& in)", asMETHODPR(ShapeType, transform, (double, double, const Vec2&), Polygon&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon scaled(double s) const", asMETHODPR(ShapeType, scaled, (double) const&, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon scaled(double sx, double sy) const", asMETHODPR(ShapeType, scaled, (double, double) const&, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon scaled(Vec2) const", asMETHODPR(ShapeType, scaled, (Vec2) const&, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon& scale(double s)", asMETHODPR(ShapeType, scale, (double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& scale(double sx, double sy)", asMETHODPR(ShapeType, scale, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& scale(Vec2)", asMETHODPR(ShapeType, scale, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon scaledAt(Vec2, double s) const", asMETHODPR(ShapeType, scaledAt, (Vec2, double) const&, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon scaledAt(Vec2, double sx, double sy) const", asMETHODPR(ShapeType, scaledAt, (Vec2, double, double) const&, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon scaledAt(Vec2, Vec2) const", asMETHODPR(ShapeType, scaledAt, (Vec2, Vec2) const&, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon& scaleAt(Vec2, double s)", asMETHODPR(ShapeType, scaleAt, (Vec2, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& scaleAt(Vec2, double sx, double sy)", asMETHODPR(ShapeType, scaleAt, (Vec2, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon& scaleAt(Vec2, Vec2)", asMETHODPR(ShapeType, scaleAt, (Vec2, Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double area() const", asMETHODPR(ShapeType, area, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double perimeter() const", asMETHODPR(ShapeType, perimeter, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 centroid() const", asMETHODPR(ShapeType, centroid, () const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon computeConvexHull() const", asMETHODPR(ShapeType, computeConvexHull, () const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateBuffer(double) const", asMETHODPR(ShapeType, calculateBuffer, (double) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateRoundBuffer(double) const", asMETHODPR(ShapeType, calculateRoundBuffer, (double) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon simplified(double maxDistance = 2.0) const", asMETHODPR(ShapeType, simplified, (double) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString outline(bool closeRing = CloseRing::No) const", asMETHODPR(ShapeType, outline, (CloseRing) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString outline(double, double) const", asMETHODPR(ShapeType, outline, (double, double) const, LineString), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool append(const RectF& in)", asMETHODPR(ShapeType, append, (const RectF&), bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool append(const Polygon& in)", asMETHODPR(ShapeType, append, (const Polygon&), bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier3& in) const", asMETHODPR(ShapeType, intersects, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asMETHODPR(ShapeType, intersects, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asMETHODPR(ShapeType, intersects, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asMETHODPR(ShapeType, intersects, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asMETHODPR(ShapeType, intersects, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asMETHODPR(ShapeType, intersects, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asMETHODPR(ShapeType, intersects, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asMETHODPR(ShapeType, intersects, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asMETHODPR(ShapeType, intersects, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const MultiPolygon& in) const", asMETHODPR(ShapeType, intersects, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asMETHODPR(ShapeType, intersects, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Point& in) const", asMETHODPR(ShapeType, contains, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Vec2& in) const", asMETHODPR(ShapeType, contains, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Line& in) const", asMETHODPR(ShapeType, contains, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Bezier2& in) const", asMETHODPR(ShapeType, contains, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Bezier3& in) const", asMETHODPR(ShapeType, contains, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Rect& in) const", asMETHODPR(ShapeType, contains, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const RectF& in) const", asMETHODPR(ShapeType, contains, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Circle& in) const", asMETHODPR(ShapeType, contains, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Ellipse& in) const", asMETHODPR(ShapeType, contains, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Triangle& in) const", asMETHODPR(ShapeType, contains, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Quad& in) const", asMETHODPR(ShapeType, contains, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const RoundRect& in) const", asMETHODPR(ShapeType, contains, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Polygon& in) const", asMETHODPR(ShapeType, contains, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const MultiPolygon& in) const", asMETHODPR(ShapeType, contains, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const LineString& in) const", asMETHODPR(ShapeType, contains, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHODPR(ShapeType, leftClicked, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHODPR(ShapeType, leftPressed, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHODPR(ShapeType, leftReleased, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHODPR(ShapeType, rightClicked, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHODPR(ShapeType, rightPressed, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHODPR(ShapeType, rightReleased, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHODPR(ShapeType, mouseOver, () const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Polygon& draw(const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void draw(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, draw, (double, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void draw(const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, draw, (const Vec2&, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void drawTransformed(double angle, const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawTransformed, (double, const Vec2&, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawTransformed(double s, double c, const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawTransformed, (double, double, const Vec2&, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Polygon& drawFrame(double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawFrame(double x, double y, double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawFrame(const Vec2& in, double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (const Vec2&, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Polygon& drawWireframe(double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawWireframe, (double, const ColorF&) const, const Polygon&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawWireframe(double x, double y, double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawWireframe, (double, double, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawWireframe(const Vec2& in, double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawWireframe, (const Vec2&, double, const ColorF&) const, void), asCALL_THISCALL); assert(r >= 0);

		// toBuffer2D
	}
}
