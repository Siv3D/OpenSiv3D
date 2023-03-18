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
# include <Siv3D/TexturedRoundRect.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = TexturedRoundRect;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const TexturedRoundRect& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructTFFFFR(const Texture& texture, float l, float t, float r, float b, const RoundRect& rect, BindType* self)
	{
		new(self) BindType(texture, l, t, r, b, rect);
	}

	static void ConstructTFR(const Texture& texture, const FloatRect& uvRect, const RoundRect& rect, BindType* self)
	{
		new(self) BindType(texture, uvRect, rect);
	}

	static void Destruct(BindType* self)
	{
		self->~TexturedRoundRect();
	}

	void RegisterTexturedRoundRect(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "TexturedRoundRect";
			r = engine->RegisterObjectProperty(TypeName, "RoundRect rect", asOFFSET(BindType, rect)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "Texture texture", asOFFSET(BindType, texture)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "FloatRect uvRect", asOFFSET(BindType, uvRect)); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TexturedRoundRect& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Texture& in, float, float, float, float, const RoundRect& in)", asFUNCTION(ConstructTFFFFR), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Texture& in, const FloatRect& in, const RoundRect& in)", asFUNCTION(ConstructTFR), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "TexturedRoundRect& opAssign(const TexturedRoundRect& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "const RoundRect& draw(const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const ColorF&) const, const RoundRect&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "RoundRect draw(double, double, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (double, double, const ColorF&) const, RoundRect), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "RoundRect draw(const Vec2& in,const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const Vec2&, const ColorF&) const, RoundRect), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "RoundRect drawAt(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (double, double, const ColorF&) const, RoundRect), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "RoundRect drawAt(const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, drawAt, (const Vec2&, const ColorF&) const, RoundRect), asCALL_THISCALL); assert(r >= 0);
		}
	}
}
