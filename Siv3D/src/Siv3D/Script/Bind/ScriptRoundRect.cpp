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

	using ShapeType = RoundRect;

	static void Construct(const RoundRect& roundRect, ShapeType* self)
	{
		new(self) ShapeType(roundRect);
	}

	static void ConstructDDDDD(double x, double y, double w, double h, double r, ShapeType* self)
	{
		new(self) ShapeType(x, y, w, h, r);
	}

	static void ConstructVDDD(const Vec2& pos, double w, double h, double r, ShapeType* self)
	{
		new(self) ShapeType(pos, w, h, r);
	}

	static void ConstructDDVD(double x, double y, const Vec2& size, double r, ShapeType* self)
	{
		new(self) ShapeType(x, y, size, r);
	}

	static void ConstructVDD(const Vec2& pos, double size, double r, ShapeType* self)
	{
		new(self) ShapeType(pos, size, r);
	}

	static void ConstructVVD(const Vec2& pos, const Vec2& size, double r, ShapeType* self)
	{
		new(self) ShapeType(pos, size, r);
	}

	static void ConstructRD(const RectF& rect, double r, ShapeType* self)
	{
		new(self) ShapeType(rect, r);
	}

	static bool Equals(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	void RegisterRoundRect(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "RoundRect";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(ShapeType, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(ShapeType, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double w", asOFFSET(ShapeType, w)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double h", asOFFSET(ShapeType, h)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ShapeType, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "RectF rect", asOFFSET(ShapeType, rect)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const RoundRect& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double _x, double _y, double _w, double _h, double _r)", asFUNCTION(ConstructDDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2 &in, double _w, double _h, double _r)", asFUNCTION(ConstructVDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double _x, double _y, const Vec2 &in, double _r)", asFUNCTION(ConstructDDVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2 &in, double size, double r)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2 &in, const Vec2 &in, double r)", asFUNCTION(ConstructVVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const RectF &in, double r)", asFUNCTION(ConstructRD), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// ==
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const RoundRect& in) const", asFUNCTION(Equals), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RoundRect& set(double, double, double, double, double)", asMETHODPR(ShapeType, set, (double, double, double, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& set(const Vec2& in, double, double, double)", asMETHODPR(ShapeType, set, (const Vec2&, double, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& set(double, double, const Vec2& in, double)", asMETHODPR(ShapeType, set, (double, double, const Vec2&, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& set(const Vec2& in, const Vec2& in, double)", asMETHODPR(ShapeType, set, (const Vec2&, const Vec2&, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& set(const RectF& in, double)", asMETHODPR(ShapeType, set, (const RectF&, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& set(const RoundRect& in)", asMETHODPR(ShapeType, set, (const RoundRect&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RoundRect& setPos(double, double)", asMETHODPR(ShapeType, setPos, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& setPos(Vec2)", asMETHODPR(ShapeType, setPos, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RoundRect& setCenter(double, double)", asMETHODPR(ShapeType, setCenter, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& setCenter(Vec2)", asMETHODPR(ShapeType, setCenter, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RoundRect& setSize(double, double)", asMETHODPR(ShapeType, setSize, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& setSize(Vec2)", asMETHODPR(ShapeType, setSize, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RoundRect movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect movedBy(Vec2) const", asMETHODPR(ShapeType, movedBy, (Vec2) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect& moveBy(Vec2)", asMETHODPR(ShapeType, moveBy, (Vec2), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RoundRect stretched(double) const", asMETHODPR(ShapeType, stretched, (double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect stretched(double, double) const", asMETHODPR(ShapeType, stretched, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect stretched(Vec2) const", asMETHODPR(ShapeType, stretched, (Vec2) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect stretched(double, double, double, double) const", asMETHODPR(ShapeType, stretched, (double, double, double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 topCenter() const", asMETHODPR(ShapeType, topCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 rightCenter() const", asMETHODPR(ShapeType, rightCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 bottomCenter() const", asMETHODPR(ShapeType, bottomCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 leftCenter() const", asMETHODPR(ShapeType, leftCenter, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 center() const", asMETHODPR(ShapeType, center, () const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double area() const", asMETHODPR(ShapeType, area, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double perimeter() const", asMETHODPR(ShapeType, perimeter, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon asPolygon(uint32 quality = 24) const", asMETHODPR(ShapeType, asPolygon, (uint32) const, Polygon), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RoundRect lerp(const RoundRect& in, double) const", asMETHODPR(ShapeType, lerp, (const RoundRect&, double) const, RoundRect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(ShapeType, hash, () const, size_t), asCALL_THISCALL); assert(r >= 0);

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

		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Point& in) const", asMETHODPR(ShapeType, contains, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Vec2& in) const", asMETHODPR(ShapeType, contains, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Line& in) const", asMETHODPR(ShapeType, contains, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		////r = engine->RegisterObjectMethod(TypeName, "bool contains(const Bezier2& in) const", asMETHODPR(ShapeType, contains, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		////r = engine->RegisterObjectMethod(TypeName, "bool contains(const Bezier3& in) const", asMETHODPR(ShapeType, contains, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Rect& in) const", asMETHODPR(ShapeType, contains, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const RectF& in) const", asMETHODPR(ShapeType, contains, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		////r = engine->RegisterObjectMethod(TypeName, "bool contains(const Circle& in) const", asMETHODPR(ShapeType, contains, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		////r = engine->RegisterObjectMethod(TypeName, "bool contains(const Ellipse& in) const", asMETHODPR(ShapeType, contains, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Triangle& in) const", asMETHODPR(ShapeType, contains, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool contains(const Quad& in) const", asMETHODPR(ShapeType, contains, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		////r = engine->RegisterObjectMethod(TypeName, "bool contains(const RoundRect& in) const", asMETHODPR(ShapeType, contains, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		////r = engine->RegisterObjectMethod(TypeName, "bool contains(const Polygon& in) const", asMETHODPR(ShapeType, contains, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		////r = engine->RegisterObjectMethod(TypeName, "bool contains(const MultiPolygon& in) const", asMETHODPR(ShapeType, contains, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		////r = engine->RegisterObjectMethod(TypeName, "bool contains(const LineString& in) const", asMETHODPR(ShapeType, contains, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHODPR(ShapeType, leftClicked, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHODPR(ShapeType, leftPressed, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHODPR(ShapeType, leftReleased, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHODPR(ShapeType, rightClicked, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHODPR(ShapeType, rightPressed, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHODPR(ShapeType, rightReleased, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHODPR(ShapeType, mouseOver, () const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const RoundRect& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const RoundRect& drawFrame(double thickness = 1.0, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const RoundRect& drawFrame(double innerThickness, double outerThickness, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const RoundRect& drawShadow(const Vec2& in offset, double blurRadius, double spread = 0.0, const ColorF& in color = ColorF(0.0, 0.5), bool fill = true) const", asMETHODPR(ShapeType, drawShadow, (const Vec2&, double, double, const ColorF&, bool) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TexturedRoundRect opCall(const Texture& in) const", asMETHODPR(ShapeType, operator(), (const Texture&) const, TexturedRoundRect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedRoundRect opCall(const TextureRegion& in) const", asMETHODPR(ShapeType, operator(), (const TextureRegion&) const, TexturedRoundRect), asCALL_THISCALL); assert(r >= 0);
	}
}
