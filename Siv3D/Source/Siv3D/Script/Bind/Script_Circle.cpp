//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Circle;

	static void ConstructD(double r, ShapeType* self)
	{
		new(self) ShapeType(r);
	}

	static void ConstructDD(double x, double y, ShapeType* self)
	{
		new(self) ShapeType(x, y);
	}

	static void ConstructDDD(double x, double y, double r, ShapeType* self)
	{
		new(self) ShapeType(x, y, r);
	}

	static void ConstructV(const Vec2& center, Rect* self)
	{
		new(self) ShapeType(center);
	}

	static void ConstructVD(const Vec2& center, double r, ShapeType* self)
	{
		new(self) ShapeType(center, r);
	}

	void RegisterCircle(asIScriptEngine *engine)
	{
		const char TypeName[] = "Circle";
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(ShapeType, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(ShapeType, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double r", asOFFSET(ShapeType, r)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 center", asOFFSET(ShapeType, center)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double r)", asFUNCTION(ConstructD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double r)", asFUNCTION(ConstructDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2&in center)", asFUNCTION(ConstructV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2&in center, double r)", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle& setPos(double x, double y)", asMETHODPR(ShapeType, setPos, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& setPos(const Vec2&in center)", asMETHODPR(ShapeType, setPos, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& setCenter(double x, double y)", asMETHODPR(ShapeType, setPos, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& setCenter(const Vec2&in center)", asMETHODPR(ShapeType, setPos, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& setR(double r)", asMETHODPR(ShapeType, setR, (double), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle stretched(double size) const", asMETHODPR(ShapeType, stretched, (double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Circle movedBy(double x, double y) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle movedBy(const Vec2&in xy) const", asMETHODPR(ShapeType, movedBy, (const Vec2&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& moveBy(double x, double y)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Circle& moveBy(const Vec2&in xy)", asMETHODPR(ShapeType, moveBy, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<Point>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<Vec2>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<Rect>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<RectF>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<Circle>)), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<Ellipse>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<Line>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<Triangle>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<Quad>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<RoundRect>)), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<Polygon>)), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert((void (ShapeType::*)())(&ShapeType::intersects<LineString>)), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHOD(ShapeType, leftClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHOD(ShapeType, leftPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHOD(ShapeType, leftReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHOD(ShapeType, rightClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHOD(ShapeType, rightPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHOD(ShapeType, rightReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHOD(ShapeType, mouseOver), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Circle& draw(const ColorF&in color = Palette::White) const", asMETHOD(ShapeType, draw), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Circle& drawFrame(double inner = 1.0, double outer = 0.0, const ColorF&in color = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawPie(double startAngle, double angle, const ColorF&in color = Palette::White) const", asMETHOD(ShapeType, drawPie), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawArc(double startAngle, double angle, double innerThickness = 1.0, double outerThickness = 0.0, const ColorF&in color = Palette::White) const", asMETHOD(ShapeType, drawArc), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawShadow(const Vec2&in offset, double blurRadius, double spread = 0.0, const ColorF&in color = ColorF(0.0, 0.5)) const", asMETHOD(ShapeType, drawShadow), asCALL_THISCALL); assert(r >= 0);
	}
}
