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
# include "ScriptOptional.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Line;

	static void Construct(const Line& line, ShapeType* self)
	{
		new(self) ShapeType(line);
	}

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

	static bool EqualsLine(const ShapeType& other, const ShapeType& value)
	{
		return (value == other);
	}

	static CScriptOptional IntersectsAtLine(const Line& other, const Line& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Optional<Vec2>");

		if (const auto result = self.intersectsAt(other))
		{
			Vec2 value = *result;

			return CScriptOptional(&value, typeID);
		}
		else
		{
			return CScriptOptional(typeID);
		}
	}

	void RegisterLine(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Line";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "Vec2 begin", asOFFSET(ShapeType, begin)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "Vec2 end", asOFFSET(ShapeType, end)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Line& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x0, double y0, double x1, double y1)", asFUNCTION(ConstructDDDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, double x1, double y1)", asFUNCTION(ConstructVDD), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(double x0, double y0, const Vec2& in)", asFUNCTION(ConstructDDV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Vec2& in, const Vec2& in)", asFUNCTION(ConstructVV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	==, !=
		//
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Line& in) const", asFUNCTION(EqualsLine), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		//	set
		//
		r = engine->RegisterObjectMethod(TypeName, "Line& set(double, double, double, double)", asMETHODPR(Line, set, (double, double, double, double), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& set(Vec2, double, double)", asMETHODPR(Line, set, (Vec2, double, double), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& set(double, double, Vec2)", asMETHODPR(Line, set, (double, double, Vec2), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& set(Vec2, Vec2)", asMETHODPR(Line, set, (Vec2, Vec2), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& set(const Line& in)", asMETHODPR(Line, set, (const Line&), Line&), asCALL_THISCALL); assert(r >= 0);

		//
		//	movedBy
		//	
		r = engine->RegisterObjectMethod(TypeName, "Line movedBy(double, double) const", asMETHODPR(Line, movedBy, (double, double) const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line movedBy(Vec2) const", asMETHODPR(Line, movedBy, (Vec2) const, Line), asCALL_THISCALL); assert(r >= 0);

		//
		//	moveBy
		//
		r = engine->RegisterObjectMethod(TypeName, "Line& moveBy(double, double)", asMETHODPR(Line, moveBy, (double, double), Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& moveBy(Vec2)", asMETHODPR(Line, moveBy, (Vec2), Line&), asCALL_THISCALL); assert(r >= 0);

		//
		//	stretched
		//
		r = engine->RegisterObjectMethod(TypeName, "Line stretched(double) const", asMETHODPR(Line, stretched, (double) const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line stretched(double, double) const", asMETHODPR(Line, stretched, (double, double) const, Line), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 vector() const", asMETHODPR(Line, vector, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 normal() const", asMETHODPR(Line, normal, () const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Line reversed() const", asMETHODPR(Line, reversed, () const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line& reverse()", asMETHODPR(Line, reverse, (), Line&), asCALL_THISCALL); assert(r >= 0);
		
		r = engine->RegisterObjectMethod(TypeName, "bool hasLength() const", asMETHODPR(Line, hasLength, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double length() const", asMETHODPR(Line, length, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSq() const", asMETHODPR(Line, lengthSq, () const, double), asCALL_THISCALL); assert(r >= 0);
		
		r = engine->RegisterObjectMethod(TypeName, "Vec2& p(size_t)", asMETHODPR(ShapeType, p, (size_t), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& p(size_t) const", asMETHODPR(ShapeType, p, (size_t) const, const Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 point(size_t) const", asMETHODPR(ShapeType, point, (size_t) const, Vec2), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2 position(double) const", asMETHODPR(ShapeType, position, (double) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 center() const", asMETHODPR(ShapeType, center, () const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 closest(Vec2) const", asMETHODPR(ShapeType, closest, (Vec2) const, Vec2), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF boundingRect() const", asMETHODPR(ShapeType, boundingRect, () const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line extractLine(double, double) const", asMETHODPR(ShapeType, extractLine, (double, double) const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line lerp(const Line& in, double) const", asMETHODPR(ShapeType, lerp, (const Line&, double) const, Line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t hash() const", asMETHODPR(Line, hash, () const, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier3& in) const", asMETHODPR(ShapeType, intersects, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
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

		r = engine->RegisterObjectMethod(TypeName, "Optional<Vec2> intersectsAt(const Line& in) const", asFUNCTION(IntersectsAtLine), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const Bezier2& in) const", asFUNCTION(IntersectsAt<Bezier2>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const Bezier3& in) const", asFUNCTION(IntersectsAt<Bezier3>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const Rect& in) const", asFUNCTION(IntersectsAt<Rect>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const RectF& in) const", asFUNCTION(IntersectsAt<RectF>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const Circle& in) const", asFUNCTION(IntersectsAt<Circle>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const Ellipse& in) const", asFUNCTION(IntersectsAt<Ellipse>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const Triangle& in) const", asFUNCTION(IntersectsAt<Triangle>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const Quad& in) const", asFUNCTION(IntersectsAt<Quad>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const RoundRect& in) const", asFUNCTION(IntersectsAt<RoundRect>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const Polygon& in) const", asFUNCTION(IntersectsAt<Polygon>), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Optional<Array<Vec2>> intersectsAt(const LineString& in) const", asFUNCTION(IntersectsAt<LineString>), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//// intersectsAt
		//// intersectsAtPrecise

		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(const ColorF& in, const ColorF& in) const", asMETHODPR(ShapeType, draw, (const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(double, const ColorF& in, const ColorF& in) const", asMETHODPR(ShapeType, draw, (double, const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(const LineStyle& in, double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const LineStyle&, double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& draw(const LineStyle& in, double, const ColorF& in, const ColorF& in) const", asMETHODPR(ShapeType, draw, (const LineStyle&, double, const ColorF&, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& drawArrow(double width = 1.0, const Vec2& in headSize = Vec2(5.0, 5.0), const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawArrow, (double, const Vec2&, const ColorF&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Line& drawDoubleHeadedArrow(double width = 1.0, const Vec2& in headSize = Vec2(5.0, 5.0), const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawDoubleHeadedArrow, (double, const Vec2&, const ColorF&) const, const Line&), asCALL_THISCALL); assert(r >= 0);
	}
}
