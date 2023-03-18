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
# include <Siv3D/DrawableText.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = DrawableText;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const BindType& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructFS(const Font& font, const String& text, BindType* self)
	{
		new(self) BindType(font, text);
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	void RegisterDrawableText(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "DrawableText";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "Font font", asOFFSET(BindType, font)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "String text", asOFFSET(BindType, text)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const DrawableText& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Font& in, const String& in)", asFUNCTION(ConstructFS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "DrawableText& opAssign(const DrawableText& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "Array<double>@ getXAdvances() const", asFUNCTION(GetXAdvances), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "Array<double>@ getXAdvances(double) const", asFUNCTION(GetXAdvancesD), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF region(double x, double y) const", asMETHODPR(BindType, region, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF region(Vec2 pos = Vec2(0,0)) const", asMETHODPR(BindType, region, (Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF region(double, double x, double y) const", asMETHODPR(BindType, region, (double, double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF region(double, Vec2 pos = Vec2(0,0)) const", asMETHODPR(BindType, region, (double, Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF regionBase(double x, double y) const", asMETHODPR(BindType, regionBase, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionBase(Vec2 pos = Vec2(0,0)) const", asMETHODPR(BindType, regionBase, (Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionBase(double, double x, double y) const", asMETHODPR(BindType, regionBase, (double, double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionBase(double, Vec2 pos = Vec2(0,0)) const", asMETHODPR(BindType, regionBase, (double, Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(double x, double y) const", asMETHODPR(BindType, regionAt, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(Vec2) const", asMETHODPR(BindType, regionAt, (Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(double, double x, double y) const", asMETHODPR(BindType, regionAt, (double, double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionAt(double, Vec2) const", asMETHODPR(BindType, regionAt, (double, Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF regionBaseAt(double x, double y) const", asMETHODPR(BindType, regionBaseAt, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionBaseAt(Vec2 pos = Vec2(0,0)) const", asMETHODPR(BindType, regionBaseAt, (Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionBaseAt(double, double x, double y) const", asMETHODPR(BindType, regionBaseAt, (double, double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF regionBaseAt(double, Vec2 pos = Vec2(0,0)) const", asMETHODPR(BindType, regionBaseAt, (double, Vec2) const, RectF), asCALL_THISCALL); assert(r >= 0);

		//r = engine->RegisterObjectMethod(TypeName, "RectF boundingRect(double x, double y) const", asMETHODPR(BindType, boundingRect, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "RectF boundingRect(const Vec2& in pos = Vec2(0, 0)) const", asMETHODPR(BindType, boundingRect, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "RectF boundingRectAt(double x, double y) const", asMETHODPR(BindType, boundingRectAt, (double, double) const, RectF), asCALL_THISCALL); assert(r >= 0);
		//r = engine->RegisterObjectMethod(TypeName, "RectF boundingRectAt(const Vec2& in pos = Vec2(0, 0)) const", asMETHODPR(BindType, boundingRectAt, (const Vec2&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "RectF draw(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(double, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (double, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(double, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (double, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const TextStyle&in, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const TextStyle&, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const TextStyle&in, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const TextStyle&, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const TextStyle&in, double, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const TextStyle&, double, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF draw(const TextStyle&in, double, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const TextStyle&, double, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool draw(const RectF& in area, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const RectF&, const ColorF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool draw(double, const RectF& in area, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (double, const RectF&, const ColorF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool draw(const TextStyle&in, const RectF& in area, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const TextStyle&, const RectF&, const ColorF&) const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool draw(const TextStyle&in, double, const RectF& in area, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const TextStyle&, double, const RectF&, const ColorF&) const, bool), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(double, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (double, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(double, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (double, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(const TextStyle&in, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (const TextStyle&, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(const TextStyle&in, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (const TextStyle&, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(const TextStyle&in, double, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (const TextStyle&, double, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBase(const TextStyle&in, double, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBase, (const TextStyle&, double, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(double, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (double, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(double, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (double, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const TextStyle&in, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (const TextStyle&, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const TextStyle&in, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (const TextStyle&, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const TextStyle&in, double, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (const TextStyle&, double, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawAt(const TextStyle&in, double, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (const TextStyle&, double, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(double, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (double, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(double, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (double, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(const TextStyle&in, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (const TextStyle&, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(const TextStyle&in, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (const TextStyle&, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(const TextStyle&in, double, double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (const TextStyle&, double, double, double, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "RectF drawBaseAt(const TextStyle&in, double, const Vec2& in pos = Vec2(0, 0), const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawBaseAt, (const TextStyle&, double, const Vec2&, const ColorF&) const, RectF), asCALL_THISCALL); assert(r >= 0);
	}
}
