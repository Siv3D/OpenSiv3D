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
# include <Siv3D/TexturedCircle.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = TexturedCircle;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const TexturedCircle& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructTFFFFC(const Texture& texture, float l, float t, float r, float b, const Circle& circle, BindType* self)
	{
		new(self) BindType(texture, l, t, r, b, circle);
	}

	static void ConstructTFC(const Texture& texture, const FloatRect& uvRect, const Circle& circle, BindType* self)
	{
		new(self) BindType(texture, uvRect, circle);
	}

	static void Destruct(BindType* self)
	{
		self->~TexturedCircle();
	}

	void RegisterTexturedCircle(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "TexturedCircle";

			r = engine->RegisterObjectProperty(TypeName, "Circle circle", asOFFSET(BindType, circle)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "Texture texture", asOFFSET(BindType, texture)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "FloatRect uvRect", asOFFSET(BindType, uvRect)); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TexturedCircle& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Texture& in, float, float, float, float, const Circle& in)", asFUNCTION(ConstructTFFFFC), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Texture& in, const FloatRect& in, const Circle& in)", asFUNCTION(ConstructTFC), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "TexturedCircle& opAssign(const TexturedCircle& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "const Circle& draw(const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const ColorF&) const, const Circle&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Circle draw(double x, double y, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (double, double, const ColorF&) const, Circle), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Circle draw(const Vec2& in, const ColorF& in color = Palette::White) const", asMETHODPR(BindType, draw, (const Vec2&, const ColorF&) const, Circle), asCALL_THISCALL); assert(r >= 0);
		}
	}
}
