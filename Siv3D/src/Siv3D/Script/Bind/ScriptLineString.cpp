//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/LineString.hpp>
# include "ScriptArray.hpp"

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

	static void ConstructI(uint32 size, ShapeType* self)
	{
		new(self) ShapeType(size);
	}

	static void ConstructIV(uint32 size, const Vec2& value, ShapeType* self)
	{
		new(self) ShapeType(size, value);
	}

	//static void ConstructAP(const CScriptArray* arr, ShapeType* self)
	//{
	//	new(self) ShapeType(detail::FromScriptArray<Point>(arr));
	//}

	static void ConstructAV(const CScriptArray* arr, ShapeType* self)
	{
		new(self) ShapeType(detail::FromScriptArray<Vec2>(arr));
	}

	static void Destruct(ShapeType* self)
	{
		self->~LineString();
	}

	static void ListConstruct(const void* list, ShapeType* self)
	{
		const size_t length = *static_cast<const asUINT*>(list);
		const Vec2* data = static_cast<const Vec2*>(static_cast<const void*>(static_cast<const uint8*>(list) + 4));
		new(self) ShapeType(data, data + length);
	}

	static void AssignAP(const CScriptArray* arr, LineString& value)
	{
		value = detail::FromScriptArray<Point>(arr);
	}

	static void AssignAV(const CScriptArray* arr, LineString& value)
	{
		value = detail::FromScriptArray<Vec2>(arr);
	}

	static LineString& OpAssignAP(const CScriptArray* arr, LineString& value)
	{
		AssignAP(arr, value);
		return value;
	}

	static LineString& OpAssignAV(const CScriptArray* arr, LineString& value)
	{
		AssignAV(arr, value);
		return value;
	}

	static bool ConvToBool(const LineString& lineString)
	{
		return static_cast<bool>(lineString);
	}

	void RegisterLineString(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "LineString";

		int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineString& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32) explicit", asFUNCTION(ConstructI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32, const Vec2& in)", asFUNCTION(ConstructIV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const Vec2& in) {repeat Vec2}", asFUNCTION(ListConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Array<Point>& in)", asFUNCTION(ConstructAP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Array<Vec2>& in)", asFUNCTION(ConstructAV), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//
		// =
		//
		r = engine->RegisterObjectMethod(TypeName, "LineString& opAssign(const LineString& in)", asMETHODPR(ShapeType, operator =, (const ShapeType&), ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& opAssign(const Array<Point>& in)", asFUNCTION(OpAssignAP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& opAssign(const Array<Vec2>& in)", asFUNCTION(OpAssignAV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// assign
		r = engine->RegisterObjectMethod(TypeName, "void assign(const LineString& in)", asMETHODPR(ShapeType, assign, (const ShapeType&), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void assign(const Array<Point>& in)", asFUNCTION(AssignAP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void assign(const Array<Vec2>& in)", asFUNCTION(AssignAV), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// at
		r = engine->RegisterObjectMethod(TypeName, "Vec2& at(size_t index)", asMETHODPR(LineString, at, (size_t)&, Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& at(size_t index) const", asMETHODPR(LineString, at, (size_t) const&, const Vec2&), asCALL_THISCALL); assert(r >= 0);

		// []
		r = engine->RegisterObjectMethod(TypeName, "Vec2& opIndex(size_t index)", asMETHODPR(LineString, operator[], (size_t)&, Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& opIndex(size_t index) const", asMETHODPR(LineString, operator[], (size_t) const&, const Vec2&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void push_front(const Vec2& in)", asMETHODPR(LineString, push_front, (const Vec2&), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void push_back(const Vec2& in)", asMETHODPR(LineString, push_back, (const Vec2&), void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pop_front()", asMETHOD(LineString, pop_front), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pop_front_N(size_t)", asMETHOD(LineString, pop_front_N), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pop_back()", asMETHOD(LineString, pop_back), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pop_back_N(size_t)", asMETHOD(LineString, pop_back_N), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& opShl(const Vec2& in)", asMETHOD(LineString, operator <<), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Vec2& front()", asMETHODPR(LineString, front, (), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& front() const", asMETHODPR(LineString, front, () const, const Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2& back()", asMETHODPR(LineString, back, (), Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Vec2& back() const", asMETHODPR(LineString, back, () const, const Vec2&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool empty() const", asMETHOD(LineString, empty), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(LineString, empty), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "size_t size() const", asMETHOD(LineString, size), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t max_size() const", asMETHOD(LineString, max_size), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void reserve(size_t)", asMETHOD(LineString, reserve), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t capacity() const", asMETHOD(LineString, capacity), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void shrink_to_fit()", asMETHOD(LineString, shrink_to_fit), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHOD(LineString, clear), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void release()", asMETHOD(LineString, release), asCALL_THISCALL); assert(r >= 0);

		// ...
		// ...

		r = engine->RegisterObjectMethod(TypeName, "void resize(size_t)", asMETHODPR(LineString, resize, (LineString::size_type), void), asCALL_THISCALL); assert(r >= 0);

		// ...
		// ...

		r = engine->RegisterObjectMethod(TypeName, "void fill(const Vec2& in)", asMETHOD(LineString, fill), asCALL_THISCALL); assert(r >= 0);

		// ...
		// ...
		
		r = engine->RegisterObjectMethod(TypeName, "size_t num_points() const", asMETHOD(LineString, num_points), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t num_lines(bool closeRing = CloseRing::No) const", asMETHOD(LineString, num_lines), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Line line(size_t index, bool closeRing = CloseRing::No) const", asMETHOD(LineString, line), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 normalAtPoint(size_t index, bool closeRing = CloseRing::No) const", asMETHOD(LineString, normalAtPoint), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 normalAtLine(size_t index, bool closeRing = CloseRing::No) const", asMETHOD(LineString, normalAtLine), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineString movedBy(double, double) const", asMETHODPR(LineString, movedBy, (double, double) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString movedBy(Vec2) const", asMETHODPR(LineString, movedBy, (Vec2) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& moveBy(double, double)", asMETHODPR(LineString, moveBy, (double, double), LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& moveBy(Vec2)", asMETHODPR(LineString, moveBy, (Vec2), LineString&), asCALL_THISCALL); assert(r >= 0);
		
		r = engine->RegisterObjectMethod(TypeName, "LineString scaled(double) const", asMETHODPR(LineString, scaled, (double) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString scaled(double, double) const", asMETHODPR(LineString, scaled, (double, double) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString scaled(Vec2) const", asMETHODPR(LineString, scaled, (Vec2) const, LineString), asCALL_THISCALL); assert(r >= 0);		
		r = engine->RegisterObjectMethod(TypeName, "LineString& scale(double)", asMETHODPR(LineString, scale, (double), LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& scale(double, double)", asMETHODPR(LineString, scale, (double, double), LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& scale(Vec2)", asMETHODPR(LineString, scale, (Vec2), LineString&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineString scaledAt(Vec2, double) const", asMETHODPR(LineString, scaledAt, (Vec2, double) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString scaledAt(Vec2, double, double) const", asMETHODPR(LineString, scaledAt, (Vec2, double, double) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString scaledAt(Vec2, Vec2) const", asMETHODPR(LineString, scaledAt, (Vec2, Vec2) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& scaleAt(Vec2, double)", asMETHODPR(LineString, scaleAt, (Vec2, double), LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& scaleAt(Vec2, double, double)", asMETHODPR(LineString, scaleAt, (Vec2, double, double), LineString&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString& scaleAt(Vec2, Vec2)", asMETHODPR(LineString, scaleAt, (Vec2, Vec2), LineString&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF computeBoundingRect() const", asMETHOD(LineString, computeBoundingRect), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString simplified(double maxDistance = 2.0, bool closeRing = CloseRing::No) const", asMETHOD(LineString, simplified), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString densified(double maxDistance = 2.0, bool closeRing = CloseRing::No) const", asMETHOD(LineString, densified), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString catmullRom(int32 interpolation = 24) const", asMETHODPR(LineString, catmullRom, (int32) const, LineString), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString catmullRom(bool closeRing, int32 interpolation = 24) const", asMETHODPR(LineString, catmullRom, (CloseRing, int32) const, LineString), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double calculateLength(bool closeRing = CloseRing::No) const", asMETHOD(LineString, num_lines), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Vec2 calculatePointFromOrigin(double, bool closeRing = CloseRing::No) const", asMETHOD(LineString, num_lines), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineString extractLineString(double, double, bool closeRing = CloseRing::No) const", asMETHOD(LineString, num_lines), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Array<Vec2> computeNormals(bool closeRing = CloseRing::No) const", asFUNCTION(), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateBuffer(double distance, int32 quality = 24) const", asMETHOD(ShapeType, calculateBuffer), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateBufferClosed(double distance, int32 quality = 24) const", asMETHOD(ShapeType, calculateBufferClosed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateRoundBuffer(double distance, int32 quality = 24) const", asMETHOD(ShapeType, calculateRoundBuffer), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Polygon calculateRoundBufferClosed(double distance, int32 quality = 24) const", asMETHOD(ShapeType, calculateRoundBufferClosed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "Spline2D asSpline(bool closeRing = CloseRing::No) const", asMETHODPR(ShapeType, asSpline, (CloseRing) const, Spline2D), asCALL_THISCALL); assert(r >= 0);


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

		r = engine->RegisterObjectMethod(TypeName, "const LineString& draw(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& draw(double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& draw(const LineStyle& in, double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, draw, (const LineStyle&, double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const LineString& drawClosed(const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawClosed, (const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& drawClosed(double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawClosed, (double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const LineString& drawClosed(const LineStyle& in, double, const ColorF& in = Palette::White) const", asMETHODPR(ShapeType, drawClosed, (const LineStyle&, double, const ColorF&) const, const ShapeType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void swap(LineString& inout)", asMETHOD(ShapeType, swap), asCALL_THISCALL); assert(r >= 0);
	}
}
