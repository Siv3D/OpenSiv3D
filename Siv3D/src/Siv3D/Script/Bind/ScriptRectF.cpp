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
# include <Siv3D/2DShapes.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = RectF;

	static void Construct(const RectF& rect, ShapeType* self)
	{
		new(self) ShapeType(rect);
	}

	static void ConstructR(const Rect& rect, ShapeType* self)
	{
		new(self) ShapeType(rect);
	}

	static void ConstructD(double size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructDD(double w, double h, ShapeType* self)
	{
		new(self) ShapeType(w, h);
	}

	static void ConstructV(const Vec2& size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructDDD(double x, double y, double size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static void ConstructDDDD(double x, double y, double w, double h, ShapeType* self)
	{
		new(self) ShapeType(x, y, w, h);
	}

	static void ConstructDDV(double x, double y, const Vec2& size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static void ConstructVD(const Vec2& pos, double size, ShapeType* self)
	{
		new(self) ShapeType(pos, size);
	}

	static void ConstructVDD(const Vec2& pos, double w, double h, ShapeType* self)
	{
		new(self) ShapeType(pos, w, h);
	}

	static void ConstructVV(const Vec2& pos, const Vec2& size, ShapeType* self)
	{
		new(self) ShapeType(pos, size);
	}

	static void ConstructCenterVD(Vec2 pos, double size, ShapeType* self)
	{
		new(self) ShapeType(Arg::center = pos.asPoint(), size);
	}

	static void ConstructCenterVDD(Vec2 pos, double w, double h, ShapeType* self)
	{
		new(self) ShapeType(Arg::center = pos.asPoint(), w, h);
	}

	static void ConstructCenterVS(Vec2 pos, const Vec2& size, ShapeType* self)
	{
		new(self) ShapeType(Arg::center = pos.asPoint(), size);
	}

	static bool EqualsRectF(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	void RegisterRectF(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "RectF";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(ShapeType, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(ShapeType, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double w", asOFFSET(ShapeType, w)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double h", asOFFSET(ShapeType, h)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 pos", asOFFSET(ShapeType, pos)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 size", asOFFSET(ShapeType, size)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const RectF& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Rect& in)", asFUNCTION(ConstructR), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double size) explicit", asFUNCTION(ConstructD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double w, double h)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in) explicit", asFUNCTION(ConstructV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double size)", asFUNCTION(ConstructDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double w, double h)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, const Vec2& in)", asFUNCTION(ConstructDDV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double size)", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double w, double h)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, const Vec2& in)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(Arg::center_Vec2, int32 size)", asFUNCTION(ConstructCenterVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(Arg::center_Vec2, int32 w, int32 h)", asFUNCTION(ConstructCenterVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(Arg::center_Vec2, const Point& in)", asFUNCTION(ConstructCenterVS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// ==
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const RectF& in) const", asFUNCTION(EqualsRectF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF& setPos(double, double)", asMETHODPR(ShapeType, setPos, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setPos(Vec2)", asMETHODPR(ShapeType, setPos, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setCenter(double, double)", asMETHODPR(ShapeType, setCenter, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setCenter(Vec2)", asMETHODPR(ShapeType, setCenter, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setSize(double, double)", asMETHODPR(ShapeType, setSize, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setSize(Vec2)", asMETHODPR(ShapeType, setSize, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF& set(double, double, double, double)", asMETHODPR(ShapeType, set, (double, double, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& set(double, double, double)", asMETHODPR(ShapeType, set, (double, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& set(double, double, Vec2)", asMETHODPR(ShapeType, set, (double, double, Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& set(Vec2, double)", asMETHODPR(ShapeType, set, (Vec2, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& set(Vec2, double, double)", asMETHODPR(ShapeType, set, (Vec2, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& set(Vec2, Vec2)", asMETHODPR(ShapeType, set, (Vec2, Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& set(const Rect& in)", asMETHODPR(ShapeType, set, (const Rect&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& set(const RectF& in)", asMETHODPR(ShapeType, set, (const RectF&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF movedBy(Vec2) const", asMETHODPR(ShapeType, movedBy, (Vec2) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& moveBy(Vec2)", asMETHODPR(ShapeType, moveBy, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF stretched(double) const", asMETHODPR(ShapeType, stretched, (double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF stretched(double, double) const", asMETHODPR(ShapeType, stretched, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF stretched(Vec2) const", asMETHODPR(ShapeType, stretched, (Vec2) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF stretched(double, double, double, double) const", asMETHODPR(ShapeType, stretched, (double, double, double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF scaled(double) const", asMETHODPR(ShapeType, scaled, (double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaled(double, double) const", asMETHODPR(ShapeType, scaled, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaled(Vec2) const", asMETHODPR(ShapeType, scaled, (Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(Vec2, double) const", asMETHODPR(ShapeType, scaledAt, (Vec2, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(Vec2, double, double) const", asMETHODPR(ShapeType, scaledAt, (Vec2, double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(Vec2, Vec2) const", asMETHODPR(ShapeType, scaledAt, (Vec2, Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHODPR(ShapeType, isEmpty, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asMETHODPR(ShapeType, hasArea, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasArea() const", asMETHODPR(ShapeType, hasArea, () const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double leftX() const", asMETHODPR(ShapeType, leftX, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double rightX() const", asMETHODPR(ShapeType, rightX, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double topY() const", asMETHODPR(ShapeType, topY, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double bottomY() const", asMETHODPR(ShapeType, bottomY, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double centerX() const", asMETHODPR(ShapeType, centerX, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double centerY() const", asMETHODPR(ShapeType, centerY, () const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 tl() const", asMETHODPR(ShapeType, tl, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 tr() const", asMETHODPR(ShapeType, tr, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 bl() const", asMETHODPR(ShapeType, bl, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 br() const", asMETHODPR(ShapeType, br, () const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 topCenter() const", asMETHODPR(ShapeType, topCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 rightCenter() const", asMETHODPR(ShapeType, rightCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 bottomCenter() const", asMETHODPR(ShapeType, bottomCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 leftCenter() const", asMETHODPR(ShapeType, leftCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 center() const", asMETHODPR(ShapeType, center, () const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Line top() const", asMETHODPR(ShapeType, top, () const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line right() const", asMETHODPR(ShapeType, right, () const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line bottom() const", asMETHODPR(ShapeType, bottom, () const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line left() const", asMETHODPR(ShapeType, left, () const, Line), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 point(size_t) const", asMETHODPR(ShapeType, point, (size_t) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line side(size_t) const", asMETHODPR(ShapeType, side, (size_t) const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Triangle triangle(size_t) const", asMETHODPR(ShapeType, triangle, (size_t) const, Triangle), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double area() const", asMETHODPR(ShapeType, area, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double perimeter() const", asMETHODPR(ShapeType, perimeter, () const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Quad rotated(double) const", asMETHODPR(ShapeType, rotated, (double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(double, double, double) const", asMETHODPR(ShapeType, rotatedAt, (double, double, double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(Vec2, double) const", asMETHODPR(ShapeType, rotatedAt, (Vec2, double) const, Quad), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Quad shearedX(double) const", asMETHODPR(ShapeType, shearedX, (double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad shearedY(double) const", asMETHODPR(ShapeType, shearedY, (double) const, Quad), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RoundRect rounded(double) const", asMETHODPR(ShapeType, rounded, (double) const, RoundRect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon rounded(double, double, double, double) const", asMETHODPR(ShapeType, rounded, (double, double, double, double) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect asRect() const", asMETHODPR(ShapeType, asRect, () const, Rect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad asQuad() const", asMETHODPR(ShapeType, asQuad, () const, Quad), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineString outline(bool closeRing = CloseRing::No) const", asMETHODPR(ShapeType, outline, (CloseRing) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString outline(double, double) const", asMETHODPR(ShapeType, outline, (double, double) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon asPolygon() const", asMETHODPR(ShapeType, asPolygon, () const, Polygon), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF lerp(const RectF& in, double) const", asMETHODPR(ShapeType, lerp, (const RectF&, double) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF getOverlap(const RectF& in) const", asMETHODPR(ShapeType, getOverlap, (const RectF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(ShapeType, hash, () const, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
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

		//intersectsAt

		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Point& in) const", asMETHODPR(ShapeType, contains, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Vec2& in) const", asMETHODPR(ShapeType, contains, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Line& in) const", asMETHODPR(ShapeType, contains, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Bezier2& in) const", asMETHODPR(ShapeType, contains, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Bezier3& in) const", asMETHODPR(ShapeType, contains, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Rect& in) const", asMETHODPR(ShapeType, contains, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const RectF& in) const", asMETHODPR(ShapeType, contains, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Circle& in) const", asMETHODPR(ShapeType, contains, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Ellipse& in) const", asMETHODPR(ShapeType, contains, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Triangle& in) const", asMETHODPR(ShapeType, contains, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Quad& in) const", asMETHODPR(ShapeType, contains, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const RoundRect& in) const", asMETHODPR(ShapeType, contains, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const Polygon& in) const", asMETHODPR(ShapeType, contains, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const MultiPolygon& in) const", asMETHODPR(ShapeType, contains, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool contains(const LineString& in) const", asMETHODPR(ShapeType, contains, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHODPR(ShapeType, leftClicked, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHODPR(ShapeType, leftPressed, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHODPR(ShapeType, leftReleased, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHODPR(ShapeType, rightClicked, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHODPR(ShapeType, rightPressed, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHODPR(ShapeType, rightReleased, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHODPR(ShapeType, mouseOver, () const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const RectF& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		//draw (Colors)
		r = engine->RegisterObjectMethod(TypeName, "const RectF& drawFrame(double thickness = 1.0, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const RectF& drawFrame(double thickness, const ColorF& in innerColor, const ColorF& in outerColor) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const RectF& drawFrame(double inner, double outer, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const RectF& drawFrame(double inner, double outer, const ColorF& in innerColor, const ColorF& in outerColor) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const RectF& drawShadow(const Vec2&in offset, double blurRadius, double spread = 0.0, const ColorF&in color = ColorF(0.0, 0.5), bool fill = true) const", asMETHODPR(ShapeType, drawShadow, (const Vec2&, double, double, const ColorF&, bool) const, const RectF&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad opCall(const Texture& in) const", asMETHODPR(ShapeType, operator(), (const Texture&) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad opCall(const TextureRegion& in) const", asMETHODPR(ShapeType, operator(), (const TextureRegion&) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("RectF FromPoints(Vec2, Vec2)", asFUNCTION(RectF::FromPoints), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("RectF Empty()", asFUNCTION(RectF::Empty), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
