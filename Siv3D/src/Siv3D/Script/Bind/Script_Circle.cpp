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
# include <Siv3D/Circle.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Circle;

	static void Construct(const Circle& circle, ShapeType* self)
	{
		new(self) ShapeType(circle);
	}

	static void ConstructD(double r, ShapeType* self)
	{
		new(self) ShapeType(r);
	}

	static void ConstructDDD(double x, double y, double r, ShapeType* self)
	{
		new(self) ShapeType(x, y, r);
	}

	static void ConstructVD(const Vec2& center, double r, ShapeType* self)
	{
		new(self) ShapeType(center, r);
	}

	void RegisterCircle(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Circle";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(ShapeType, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(ShapeType, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ShapeType, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 center", asOFFSET(ShapeType, center)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Circle& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double)", asFUNCTION(ConstructD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double, double, double)", asFUNCTION(ConstructDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double)", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//Arg::

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Circle& in) const", asMETHOD(ShapeType, operator==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle& set(double, double, double)", asMETHODPR(ShapeType, set, (double, double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& set(const Vec2& in)", asMETHODPR(ShapeType, set, (const Vec2&, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& set(const Circle& in)", asMETHODPR(ShapeType, set, (const Circle&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle& setCenter(double, double)", asMETHODPR(ShapeType, setCenter, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& setCenter(const Vec2& in)", asMETHODPR(ShapeType, setCenter, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle& setPos(double, double)", asMETHODPR(ShapeType, setPos, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& setPos(const Vec2& in)", asMETHODPR(ShapeType, setPos, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle& setR(double r)", asMETHOD(ShapeType, setR), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle movedBy(const Vec2& in) const", asMETHODPR(ShapeType, movedBy, (const Vec2&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& moveBy(const Vec2 &in)", asMETHODPR(ShapeType, moveBy, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle stretched(double) const", asMETHODPR(ShapeType, stretched, (double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse stretched(double, double) const", asMETHODPR(ShapeType, stretched, (double, double) const, Ellipse), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle scaled(double) const", asMETHODPR(ShapeType, scaled, (double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Ellipse scaled(double, double) const", asMETHODPR(ShapeType, scaled, (double, double) const, Ellipse), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 top() const", asMETHOD(ShapeType, top), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 right() const", asMETHOD(ShapeType, right), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 bbottoml() const", asMETHOD(ShapeType, bottom), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 left() const", asMETHOD(ShapeType, left), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Line lineDiameter() const", asMETHOD(ShapeType, lineDiameter), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double area() const", asMETHOD(ShapeType, area), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double perimeter() const", asMETHOD(ShapeType, perimeter), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier3& in) const", asMETHODPR(ShapeType, intersects, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asMETHODPR(ShapeType, intersects, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asMETHODPR(ShapeType, intersects, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asMETHODPR(ShapeType, intersects, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asMETHODPR(ShapeType, intersects, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asMETHODPR(ShapeType, intersects, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asMETHODPR(ShapeType, intersects, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asMETHODPR(ShapeType, intersects, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asMETHODPR(ShapeType, intersects, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const MultiPolygon& in) const", asMETHODPR(ShapeType, intersects, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asMETHODPR(ShapeType, intersects, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHOD(ShapeType, leftClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHOD(ShapeType, leftPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHOD(ShapeType, leftReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHOD(ShapeType, rightClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHOD(ShapeType, rightPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHOD(ShapeType, rightReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHOD(ShapeType, mouseOver), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Circle& draw(const ColorF&in color = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Circle& draw(const ColorF&in innerColor, const ColorF&in outerColor) const", asMETHODPR(ShapeType, draw, (const ColorF&, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawFrame(double thickness = 1.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawFrame(double thickness, const ColorF& in innerColor, const ColorF& in outerColor) const", asMETHODPR(ShapeType, drawFrame, (double, const ColorF&, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawFrame(double inner, double outer, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawFrame(double inner, double outer, const ColorF& in innerColor, const ColorF& in outerColor) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawPie(double startAngle, double angle, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawPie, (double, double, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawPie(double startAngle, double angle, const ColorF& in innerColor, const ColorF& in outerColor) const", asMETHODPR(ShapeType, drawPie, (double, double, const ColorF&, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawArc(double startAngle, double angle, double innerThickness = 1.0, double outerThickness = 0.0, const ColorF& in color = Palette::White) const", asMETHODPR(ShapeType, drawArc, (double, double, double, double, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawArc(double startAngle, double angle, double innerThickness, double outerThickness, const ColorF& in innerColor, const ColorF& in outerColor) const", asMETHODPR(ShapeType, drawArc, (double, double, double, double, const ColorF&, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawShadow(const Vec2& in offset, double blurRadius, double spread = 0.0, const ColorF& in color = ColorF(0.0, 0.5)) const", asMETHOD(ShapeType, drawShadow), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "TexturedCircle opCall(const Texture& in) const", asMETHODPR(ShapeType, operator(), (const Texture&) const, TexturedCircle), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "TexturedCircle opCall(const TextureRegion& in) const", asMETHODPR(ShapeType, operator(), (const TextureRegion&) const, TexturedCircle), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon asPolygon(uint32 quality = 24) const", asMETHOD(ShapeType, asPolygon), asCALL_THISCALL); assert(r >= 0);
	}
}
