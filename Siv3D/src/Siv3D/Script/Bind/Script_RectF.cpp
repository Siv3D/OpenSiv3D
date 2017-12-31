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

# include <Siv3D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = RectF;

	static void ConstructD(double size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructDD(double w, double h, ShapeType* self)
	{
		new(self) ShapeType(w, h);
	}

	static void ConstructDDD(double x, double y, double size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static void ConstructDDDD(double x, double y, double w, double h, ShapeType* self)
	{
		new(self) ShapeType(x, y, w, h);
	}

	static void ConstructV(const Vec2& size, ShapeType* self)
	{
		new(self) ShapeType(size);
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

	static void ConstructDDV(double x, double y, const Vec2& size, ShapeType* self)
	{
		new(self) ShapeType(x, y, size);
	}

	static const RectF& RectF_DrawCC(const ColorF& c0, const ColorF& c1, const RectF* thisPointer)
	{
		return thisPointer->draw(Arg::top = c0, Arg::bottom = c1);
	}

	void RegisterRectF(asIScriptEngine *engine)
	{
		const char TypeName[] = "RectF";
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double x", asOFFSET(ShapeType, x)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double y", asOFFSET(ShapeType, y)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double w", asOFFSET(ShapeType, w)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double h", asOFFSET(ShapeType, h)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 pos", asOFFSET(ShapeType, pos)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 size", asOFFSET(ShapeType, size)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double size)", asFUNCTION(ConstructD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double w, double h)", asFUNCTION(ConstructDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double size)", asFUNCTION(ConstructDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, double w, double h)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2 &in)", asFUNCTION(ConstructV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2 &in, double size)", asFUNCTION(ConstructVD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2 &in, double w, double h)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2 &in, const Vec2 &in)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x, double y, const Vec2 &in)", asFUNCTION(ConstructDDV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 center() const", asMETHOD(ShapeType, center), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line top() const", asMETHOD(ShapeType, top), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line bottom() const", asMETHOD(ShapeType, bottom), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line left() const", asMETHOD(ShapeType, left), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line right() const", asMETHOD(ShapeType, right), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const RectF &in) const", asMETHOD(ShapeType, operator==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF& setPos(double, double)", asMETHODPR(ShapeType, setPos, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setPos(const Vec2 &in)", asMETHODPR(ShapeType, setPos, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setSize(double, double)", asMETHODPR(ShapeType, setSize, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setSize(const Vec2 &in)", asMETHODPR(ShapeType, setSize, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setCenter(double, double)", asMETHODPR(ShapeType, setCenter, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& setCenter(const Vec2 &in)", asMETHODPR(ShapeType, setCenter, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF stretched(double) const", asMETHODPR(ShapeType, stretched, (double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF stretched(double, double) const", asMETHODPR(ShapeType, stretched, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF stretched(double, double, double, double) const", asMETHODPR(ShapeType, stretched, (double, double, double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "RectF movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF movedBy(const Vec2 &in) const", asMETHODPR(ShapeType, movedBy, (const Vec2&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF& moveBy(const Vec2 &in)", asMETHODPR(ShapeType, moveBy, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

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

		r = engine->RegisterObjectMethod(TypeName, "const RectF& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const RectF& draw(const ColorF& in, const ColorF& in) const", asFUNCTION(RectF_DrawCC), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const RectF& drawFrame(double inner = 1.0, double outer = 0.0, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawFrame, (double, double, const ColorF&) const, const RectF&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawShadow(const Vec2&in offset, double blurRadius, double spread = 0.0, const ColorF&in color = ColorF(0.0, 0.5)) const", asMETHOD(ShapeType, drawShadow), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Quad rotated(double angle) const", asMETHODPR(ShapeType, rotated, (double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(double x, double y, double angle) const", asMETHODPR(ShapeType, rotatedAt, (double, double, double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad rotatedAt(const Vec2&in pos, double angle) const", asMETHODPR(ShapeType, rotatedAt, (const Vec2&, double) const, Quad), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad shearedX(double vx) const", asMETHOD(ShapeType, shearedX), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Quad shearedY(double vy) const", asMETHOD(ShapeType, shearedY), asCALL_THISCALL); assert(r >= 0);
	}
}
