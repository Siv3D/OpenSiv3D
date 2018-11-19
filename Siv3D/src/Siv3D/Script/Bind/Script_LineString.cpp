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
# include <Siv3D/LineString.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = LineString;

	static void DefaultConstruct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void CopyConstruct(const LineString& other, ShapeType* self)
	{
		new(self) ShapeType(other);
	}

	static void Destruct(ShapeType* self)
	{
		self->~LineString();
	}

	static void ConstructI(uint32 size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructIV(uint32 size, const Vec2& value, ShapeType* self)
	{
		new(self) ShapeType(size, value);
	}

	static void ListConstruct(const void* list, ShapeType* self)
	{
		const size_t length = *static_cast<const asUINT*>(list);
		const Vec2* data = static_cast<const Vec2*>(static_cast<const void*>(static_cast<const uint8*>(list) + 4));
		new(self) ShapeType(data, data + length);
	}

	static bool ConvToBool(const LineString& lineString)
	{
		return !lineString.isEmpty();
	}

	void RegisterLineString(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "LineString";

		int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineString& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32)", asFUNCTION(ConstructI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32, const Vec2& in)", asFUNCTION(ConstructIV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const Vec2& in) {repeat Vec2}", asFUNCTION(ListConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//Ctrs
		//...

		r = engine->RegisterObjectMethod(TypeName, "LineString& opAssign(const LineString& in)", asMETHODPR(ShapeType, operator =, (const ShapeType&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void assign(const LineString& in)", asMETHODPR(ShapeType, assign, (const ShapeType&), void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2& opIndex(uint32 index)", asMETHODPR(std::vector<Vec2>, operator[], (size_t), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& opIndex(uint32 index) const", asMETHODPR(std::vector<Vec2>, operator[], (size_t) const, const Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& front()", asMETHODPR(std::vector<Vec2>, front, (), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& front() const", asMETHODPR(std::vector<Vec2>, front, () const, const Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& back()", asMETHODPR(std::vector<Vec2>, back, (), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& back() const", asMETHODPR(std::vector<Vec2>, back, () const, const Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool empty() const", asMETHOD(ShapeType, empty), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 size() const", asMETHOD(ShapeType, size), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void reserve(uint32)", asMETHOD(ShapeType, reserve), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void shrink_to_fit()", asMETHOD(std::vector<Vec2>, shrink_to_fit), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHOD(std::vector<Vec2>, clear), asCALL_THISCALL); assert(r >= 0);

		//using base_type::insert;
		//using base_type::emplace;
		//using base_type::erase;

		r = engine->RegisterObjectMethod(TypeName, "LineString& opShl()", asMETHOD(ShapeType, operator <<), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void push_back(const Vec2& in)", asMETHODPR(std::vector<Vec2>, push_back, (const Vec2&), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void push_front(const Vec2& in)", asMETHODPR(Array<Vec2>, push_front, (const Vec2&), void), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "void emplace_back()", asMETHODPR(std::vector<Vec2>, emplace_back, (), Vec2&), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "void emplace_back(double, double)", asMETHODPR(std::vector<Vec2>, emplace_back, (double, double), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pop_back()", asMETHOD(std::vector<Vec2>, pop_back), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pop_front()", asMETHOD(Array<Vec2>, pop_front), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resize(uint32)", asMETHODPR(std::vector<Vec2>, resize, (std::vector<Vec2>::size_type), void), asCALL_THISCALL); assert(r >= 0);
		//using base_type::count;
		//using base_type::count_if;
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(ShapeType, isEmpty), asCALL_THISCALL); assert(r >= 0);
		//using base_type::release;
		//using base_type::size_bytes;
		//using base_type::choice;
		r = engine->RegisterObjectMethod(TypeName, "void fill(const Vec2& in)", asMETHOD(ShapeType, fill), asCALL_THISCALL); assert(r >= 0);
		//using base_type::join;
		//using base_type::remove;

		//append
		//remove
		//remove_at
		//remove_if
		//reverse
		//reversed
		//rotate
		//rotated
		//shuffle
		//shuffled
		//slice
		//void swap(LineString& other) noexcept
		//LineString& append(const Array<Vec2>& other)
		//LineString& append(const LineString& other)

		r = engine->RegisterObjectMethod(TypeName, "uint32 num_lines() const", asMETHOD(ShapeType, num_lines), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line line(uint32 index) const", asMETHOD(ShapeType, line), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineString movedBy(double, double) const", asMETHODPR(ShapeType, movedBy, (double, double) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString movedBy(const Vec2& in) const", asMETHODPR(ShapeType, movedBy, (const Vec2&) const, ShapeType), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& moveBy(double, double)", asMETHODPR(ShapeType, moveBy, (double, double), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& moveBy(const Vec2& in)", asMETHODPR(ShapeType, moveBy, (const Vec2&), ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF calculateBoundingRect() const", asMETHOD(ShapeType, calculateBoundingRect), asCALL_THISCALL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Point& in) const", asMETHODPR(ShapeType, intersects, (const Point&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Vec2& in) const", asMETHODPR(ShapeType, intersects, (const Vec2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Line& in) const", asMETHODPR(ShapeType, intersects, (const Line&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier2& in) const", asMETHODPR(ShapeType, intersects, (const Bezier2&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Bezier3& in) const", asMETHODPR(ShapeType, intersects, (const Bezier3&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Rect& in) const", asMETHODPR(ShapeType, intersects, (const Rect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RectF& in) const", asMETHODPR(ShapeType, intersects, (const RectF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Circle& in) const", asMETHODPR(ShapeType, intersects, (const Circle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Ellipse& in) const", asMETHODPR(ShapeType, intersects, (const Ellipse&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Triangle& in) const", asMETHODPR(ShapeType, intersects, (const Triangle&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Quad& in) const", asMETHODPR(ShapeType, intersects, (const Quad&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const RoundRect& in) const", asMETHODPR(ShapeType, intersects, (const RoundRect&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const Polygon& in) const", asMETHODPR(ShapeType, intersects, (const Polygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const MultiPolygon& in) const", asMETHODPR(ShapeType, intersects, (const MultiPolygon&) const, bool), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "bool intersects(const LineString& in) const", asMETHODPR(ShapeType, intersects, (const LineString&) const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineString catmullRom(int32 interpolation = 24) const", asMETHOD(ShapeType, catmullRom), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString catmullRomClosed(int32 interpolation = 24) const", asMETHOD(ShapeType, catmullRomClosed), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateBuffer(double distance, int32 quality = 24) const", asMETHOD(ShapeType, calculateBuffer), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateBufferClosed(double distance, int32 quality = 24) const", asMETHOD(ShapeType, calculateBufferClosed), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const LineString& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& draw(double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& draw(const LineStyle& in, double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const LineStyle&, double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& drawClosed(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawClosed, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& drawClosed(double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawClosed, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& drawClosed(const LineStyle& in, double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawClosed, (const LineStyle&, double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void drawCatmullRom(const ColorF& in = Palette::White, int32 interpolation = 24) const", asMETHODPR(ShapeType, drawCatmullRom, (const ColorF&, int32) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawCatmullRom(double, const ColorF& in = Palette::White, int32 interpolation = 24) const", asMETHODPR(ShapeType, drawCatmullRom, (double, const ColorF&, int32) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawCatmullRom(const LineStyle& in, double, const ColorF& in = Palette::White, int32 interpolation = 24) const", asMETHODPR(ShapeType, drawCatmullRom, (const LineStyle&, double, const ColorF&, int32) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawCatmullRomClosed(const ColorF& in = Palette::White, int32 interpolation = 24) const", asMETHODPR(ShapeType, drawCatmullRomClosed, (const ColorF&, int32) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawCatmullRomClosed(double, const ColorF& in = Palette::White, int32 interpolation = 24) const", asMETHODPR(ShapeType, drawCatmullRomClosed, (double, const ColorF&, int32) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void drawCatmullRomClosed(const LineStyle& in, double, const ColorF& in = Palette::White, int32 interpolation = 24) const", asMETHODPR(ShapeType, drawCatmullRomClosed, (const LineStyle&, double, const ColorF&, int32) const, void), asCALL_THISCALL); assert(r >= 0);
	}
}
