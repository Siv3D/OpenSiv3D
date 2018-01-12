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
# include <Siv3D/Line.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Line;

	static void ConstructDDDD(double x0, double y0, double x1, double y1, ShapeType* self)
	{
		new(self) ShapeType(x0, y0, x1, y1);
	}

	static void ConstructVDD(const Vec2& pos, double x1, double y1, ShapeType* self)
	{
		new(self) ShapeType(pos, x1, y1);
	}

	static void ConstructDDV(double x0, double y0, const Vec2& pos, ShapeType* self)
	{
		new(self) ShapeType(x0, y0, pos);
	}

	static void ConstructVV(const Vec2& p0, const Vec2& p1, ShapeType* self)
	{
		new(self) ShapeType(p0, p1);
	}

	void RegisterLine(asIScriptEngine *engine)
	{
		const char TypeName[] = "Line";
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "Vec2 begin", asOFFSET(ShapeType, begin)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 end", asOFFSET(ShapeType, end)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x0, double y0, double x1, double y1)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2&in begin, double x1, double y1)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x0, double y0, const Vec2&in end)", asFUNCTION(ConstructDDV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2&in begin, const Vec2&in end)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Line movedBy(double x, double y) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line movedBy(const Vec2&in v) const", asMETHODPR(ShapeType, movedBy, (const Vec2&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& moveBy(double x, double y)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& moveBy(const Vec2&in v)", asMETHODPR(ShapeType, moveBy, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Point>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Vec2>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Rect>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<RectF>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Circle>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Ellipse>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Line>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Triangle>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Quad>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<RoundRect>), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<Polygon>), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString&in shape) const", asSMethodPtr<sizeof(void (ShapeType::*)())>::Convert(&ShapeType::intersects<LineString>), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(const ColorF&in color = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(double thickness, const ColorF&in color = Palette::White) const", asMETHODPR(ShapeType, draw, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
	}
}
