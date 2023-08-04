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

	using ShapeType = Rect;

	static void Construct(const Rect& rect, ShapeType* self)
	{
		new(self) ShapeType(rect);
	}

	static void ConstructI(int32 size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructII(int32 w, int32 h, ShapeType* self)
	{
		new(self) ShapeType(w, h);
	}

	static void ConstructS(const Size& size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructIII(int32 x, int32 y, int32 size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static void ConstructIIII(int32 x, int32 y, int32 w, int32 h, ShapeType* self)
	{
		new(self) ShapeType(x, y, w, h);
	}

	static void ConstructIIS(int32 x, int32 y, const Point& size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static void ConstructPI(const Point& pos, int32 size, ShapeType* self)
	{
		new(self) ShapeType(pos, size);
	}

	static void ConstructPII(const Point& pos, int32 w, int32 h, ShapeType* self)
	{
		new(self) ShapeType(pos, w, h);
	}

	static void ConstructPS(const Point& pos, const Point& size, ShapeType* self)
	{
		new(self) ShapeType(pos, size);
	}

	static void ConstructCenterPI(Vec2 pos, int32 size, ShapeType* self)
	{
		new(self) ShapeType(Arg::center = pos.asPoint(), size);
	}

	static void ConstructCenterPII(Vec2 pos, int32 w, int32 h, ShapeType* self)
	{
		new(self) ShapeType(Arg::center = pos.asPoint(), w, h);
	}

	static void ConstructCenterPS(Vec2 pos, const Point& size, ShapeType* self)
	{
		new(self) ShapeType(Arg::center = pos.asPoint(), size);
	}

	static bool EqualsRect(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	void RegisterRect(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Rect";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "int32 x", asOFFSET(ShapeType, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 y", asOFFSET(ShapeType, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 w", asOFFSET(ShapeType, w)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 h", asOFFSET(ShapeType, h)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Point pos", asOFFSET(ShapeType, pos)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Point size", asOFFSET(ShapeType, size)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Rect& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 size) explicit", asFUNCTION(ConstructI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 w, int32 h)", asFUNCTION(ConstructII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in) explicit", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 x, int32 y, int32 size)", asFUNCTION(ConstructIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 x, int32 y, int32 w, int32 h)", asFUNCTION(ConstructIIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 x, int32 y, const Point& in)", asFUNCTION(ConstructIIS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, int32 size)", asFUNCTION(ConstructPI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, int32 w, int32 h)", asFUNCTION(ConstructPII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, const Point& in)", asFUNCTION(ConstructPS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(Arg::center_Vec2, int32 size)", asFUNCTION(ConstructCenterPI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(Arg::center_Vec2, int32 w, int32 h)", asFUNCTION(ConstructCenterPII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(Arg::center_Vec2, const Point& in)", asFUNCTION(ConstructCenterPS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// ==
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Rect& in) const", asFUNCTION(EqualsRect), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect& setPos(int32, int32)", asMETHODPR(ShapeType, setPos, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setPos(Point)", asMETHODPR(ShapeType, setPos, (Point), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setCenter(int32, int32)", asMETHODPR(ShapeType, setCenter, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setCenter(Point)", asMETHODPR(ShapeType, setCenter, (Point), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setSize(int32, int32)", asMETHODPR(ShapeType, setSize, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setSize(Point)", asMETHODPR(ShapeType, setSize, (Size), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect& set(int32, int32, int32, int32)", asMETHODPR(ShapeType, set, (int32, int32, int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(int32, int32, int32)", asMETHODPR(ShapeType, set, (int32, int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(int32, int32, Point)", asMETHODPR(ShapeType, set, (int32, int32, Point), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(Point, int32)", asMETHODPR(ShapeType, set, (Point, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(Point, int32, int32)", asMETHODPR(ShapeType, set, (Point, int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(Point, Point)", asMETHODPR(ShapeType, set, (Point, Size), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& set(const Rect& in)", asMETHODPR(ShapeType, set, (const Rect&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect movedBy(int32, int32) const", asMETHODPR(ShapeType, movedBy, (int32, int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect movedBy(Point) const", asMETHODPR(ShapeType, movedBy, (Point) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& moveBy(int32, int32)", asMETHODPR(ShapeType, moveBy, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& moveBy(Point)", asMETHODPR(ShapeType, moveBy, (Point), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(int32) const", asMETHODPR(ShapeType, stretched, (int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(int32, int32) const", asMETHODPR(ShapeType, stretched, (int32, int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(Point) const", asMETHODPR(ShapeType, stretched, (Size) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(int32, int32, int32, int32) const", asMETHODPR(ShapeType, stretched, (int32, int32, int32, int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF scaled(double) const", asMETHODPR(ShapeType, scaled, (double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaled(double, double) const", asMETHODPR(ShapeType, scaled, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaled(Vec2) const", asMETHODPR(ShapeType, scaled, (Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(Vec2, double) const", asMETHODPR(ShapeType, scaledAt, (Vec2, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(Vec2, double, double) const", asMETHODPR(ShapeType, scaledAt, (Vec2, double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF scaledAt(Vec2, Vec2) const", asMETHODPR(ShapeType, scaledAt, (Vec2, Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHODPR(ShapeType, isEmpty, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asMETHODPR(ShapeType, hasArea, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasArea() const", asMETHODPR(ShapeType, hasArea, () const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int32 leftX() const", asMETHODPR(ShapeType, leftX, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 rightX() const", asMETHODPR(ShapeType, rightX, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 topY() const", asMETHODPR(ShapeType, topY, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 bottomY() const", asMETHODPR(ShapeType, bottomY, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double centerX() const", asMETHODPR(ShapeType, centerX, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double centerY() const", asMETHODPR(ShapeType, centerY, () const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point tl() const", asMETHODPR(ShapeType, tl, () const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point tr() const", asMETHODPR(ShapeType, tr, () const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point bl() const", asMETHODPR(ShapeType, bl, () const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Point br() const", asMETHODPR(ShapeType, br, () const, Point), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 topCenter() const", asMETHODPR(ShapeType, topCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 rightCenter() const", asMETHODPR(ShapeType, rightCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 bottomCenter() const", asMETHODPR(ShapeType, bottomCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 leftCenter() const", asMETHODPR(ShapeType, leftCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 center() const", asMETHODPR(ShapeType, center, () const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Line top() const", asMETHODPR(ShapeType, top, () const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line right() const", asMETHODPR(ShapeType, right, () const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line bottom() const", asMETHODPR(ShapeType, bottom, () const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line left() const", asMETHODPR(ShapeType, left, () const, Line), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Point point(size_t) const", asMETHODPR(ShapeType, point, (size_t) const, Point), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line side(size_t) const", asMETHODPR(ShapeType, side, (size_t) const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Triangle triangle(size_t) const", asMETHODPR(ShapeType, triangle, (size_t) const, Triangle), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 area() const", asMETHODPR(ShapeType, area, () const, int32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 perimeter() const", asMETHODPR(ShapeType, perimeter, () const, int32), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Quad rotated(double) const", asMETHODPR(ShapeType, rotated, (double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(double, double, double) const", asMETHODPR(ShapeType, rotatedAt, (double, double, double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(Vec2, double) const", asMETHODPR(ShapeType, rotatedAt, (Vec2, double) const, Quad), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Quad shearedX(double) const", asMETHODPR(ShapeType, shearedX, (double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad shearedY(double) const", asMETHODPR(ShapeType, shearedY, (double) const, Quad), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RoundRect rounded(double) const", asMETHODPR(ShapeType, rounded, (double) const, RoundRect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon rounded(double, double, double, double) const", asMETHODPR(ShapeType, rounded, (double, double, double, double) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad asQuad() const", asMETHODPR(ShapeType, asQuad, () const, Quad), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineString outline(bool closeRing = CloseRing::No) const", asMETHODPR(ShapeType, outline, (CloseRing) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString outline(double, double) const", asMETHODPR(ShapeType, outline, (double, double) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon asPolygon() const", asMETHODPR(ShapeType, asPolygon, () const, Polygon), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF lerp(const Rect& in, double) const", asMETHODPR(ShapeType, lerp, (const Rect&, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF lerp(const RectF& in, double) const", asMETHODPR(ShapeType, lerp, (const RectF&, double) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect getOverlap(const Rect& in) const", asMETHODPR(ShapeType, getOverlap, (const Rect&) const, Rect), asCALL_THISCALL); assert(r >= 0);
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

		r = engine->RegisterObjectMethod(TypeName, "const Rect& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		//draw (Colors)
		r = engine->RegisterObjectMethod(TypeName, "const Rect& drawFrame(double thickness = 1.0, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Rect& drawFrame(double thickness, const ColorF& in innerColor, const ColorF& in outerColor) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Rect& drawFrame(double inner, double outer, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Rect& drawFrame(double inner, double outer, const ColorF& in innerColor, const ColorF& in outerColor) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Rect& drawShadow(const Vec2&in offset, double blurRadius, double spread = 0.0, const ColorF&in color = ColorF(0.0, 0.5), bool fill = true) const", asMETHODPR(ShapeType, drawShadow, (const Vec2&, double, double, const ColorF&, bool) const, const Rect&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad opCall(const Texture& in) const", asMETHODPR(ShapeType, operator(), (const Texture&) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedQuad opCall(const TextureRegion& in) const", asMETHODPR(ShapeType, operator(), (const TextureRegion&) const, TexturedQuad), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Rect FromPoints(Point, Point)", asFUNCTION(Rect::FromPoints), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Rect Empty()", asFUNCTION(Rect::Empty), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
