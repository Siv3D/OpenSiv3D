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
# include <Siv3D/Rectangle.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Rect;

	static void ConstructI(int32 size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructII(int32 w, int32 h, ShapeType* self)
	{
		new(self) ShapeType(w, h);
	}

	static void ConstructIII(int32 x, int32 y, int32 size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static void ConstructIIII(int32 x, int32 y, int32 w, int32 h, ShapeType* self)
	{
		new(self) ShapeType(x, y, w, h);
	}

	static void ConstructS(const Size& size, ShapeType* self)
	{
		new(self) ShapeType(size);
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

	static void ConstructIIS(int32 x, int32 y, const Point& size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static RectF ConvToRectF(const ShapeType& rect)
	{
		return rect;
	}

	void RegisterRect(asIScriptEngine *engine)
	{
		const char TypeName[] = "Rect";
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "int x", asOFFSET(ShapeType, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int y", asOFFSET(ShapeType, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int w", asOFFSET(ShapeType, w)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int h", asOFFSET(ShapeType, h)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Point pos", asOFFSET(ShapeType, pos)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Point size", asOFFSET(ShapeType, size)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int size)", asFUNCTION(ConstructI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int w, int h)", asFUNCTION(ConstructII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int x, int y, int size)", asFUNCTION(ConstructIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int x, int y, int w, int h)", asFUNCTION(ConstructIIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point &in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point &in, int size)", asFUNCTION(ConstructPI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point &in, int w, int h)", asFUNCTION(ConstructPII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point &in, const Point &in)", asFUNCTION(ConstructPS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int x, int y, const Point &in)", asFUNCTION(ConstructIIS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 center() const", asMETHOD(ShapeType, center), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line top() const", asMETHOD(ShapeType, top), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line bottom() const", asMETHOD(ShapeType, bottom), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line left() const", asMETHOD(ShapeType, left), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line right() const", asMETHOD(ShapeType, right), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Rect &in) const", asMETHOD(ShapeType, operator==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect& setPos(int, int)", asMETHODPR(ShapeType, setPos, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setPos(const Point &in)", asMETHODPR(ShapeType, setPos, (const Point&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setSize(int, int)", asMETHODPR(ShapeType, setSize, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setSize(const Point &in)", asMETHODPR(ShapeType, setSize, (const Size&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setCenter(int, int)", asMETHODPR(ShapeType, setCenter, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& setCenter(const Point &in)", asMETHODPR(ShapeType, setCenter, (const Point&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(int) const", asMETHODPR(ShapeType, stretched, (int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(int, int) const", asMETHODPR(ShapeType, stretched, (int32, int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect stretched(int, int, int, int) const", asMETHODPR(ShapeType, stretched, (int32, int32, int32, int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "Rect movedBy(int, int) const", asMETHODPR(ShapeType, movedBy, (int32, int32) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect movedBy(const Point &in) const", asMETHODPR(ShapeType, movedBy, (const Point&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& moveBy(int, int)", asMETHODPR(ShapeType, moveBy, (int32, int32), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Rect& moveBy(const Point &in)", asMETHODPR(ShapeType, moveBy, (const Point&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Point>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Vec2>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Rect>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<RectF>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Circle>), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Ellipse>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Line>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Triangle>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Quad>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<RoundRect>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Polygon>), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<LineString>), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool leftClicked() const", asMETHOD(ShapeType, leftClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftPressed() const", asMETHOD(ShapeType, leftPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool leftReleased() const", asMETHOD(ShapeType, leftReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightClicked() const", asMETHOD(ShapeType, rightClicked), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightPressed() const", asMETHOD(ShapeType, rightPressed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool rightReleased() const", asMETHOD(ShapeType, rightReleased), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool mouseOver() const", asMETHOD(ShapeType, mouseOver), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Rect& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Rect& drawFrame(double inner = 1.0, double outer = 0.0, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const Rect&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawShadow(const Vec2&in offset, double blurRadius, double spread = 0.0, const ColorF&in color = ColorF(0.0, 0.5)) const", asMETHOD(ShapeType, drawShadow), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Quad rotated(double angle) const", asMETHODPR(ShapeType, rotated, (double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(double x, double y, double angle) const", asMETHODPR(ShapeType, rotatedAt, (double, double, double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(const Vec2&in pos, double angle) const", asMETHODPR(ShapeType, rotatedAt, (const Vec2&, double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad shearedX(double vx) const", asMETHOD(ShapeType, shearedX), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad shearedY(double vy) const", asMETHOD(ShapeType, shearedY), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF opImplConv() const", asFUNCTION(ConvToRectF), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
