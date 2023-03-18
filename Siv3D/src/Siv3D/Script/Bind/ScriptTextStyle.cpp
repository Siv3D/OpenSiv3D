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
# include <Siv3D/TextStyle.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = TextStyle;

	static void DefaultConstruct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void CopyConstruct(const TextStyle& other, ShapeType* self)
	{
		new(self) ShapeType(other);
	}

	static void Destruct(ShapeType* self)
	{
		self->~TextStyle();
	}

	void RegisterTextStyle(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "TextStyle";
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TextStyle& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
			{
				r = engine->RegisterGlobalFunction("TextStyle Default()", asFUNCTION(TextStyle::Default), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("TextStyle CustomShader()", asFUNCTION(TextStyle::CustomShader), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("TextStyle Outline(double, const ColorF& in)", asFUNCTIONPR(TextStyle::Outline, (double, const ColorF&), TextStyle), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("TextStyle Outline(double, double, const ColorF& in)", asFUNCTIONPR(TextStyle::Outline, (double, double, const ColorF&), TextStyle), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("TextStyle Shadow(const Vec2& in, const ColorF& in)", asFUNCTION(TextStyle::Shadow), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("TextStyle OutlineShadow(double, const ColorF& in, const Vec2& in, const ColorF& in)", asFUNCTIONPR(TextStyle::OutlineShadow, (double, const ColorF&, const Vec2&, const ColorF&), TextStyle), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("TextStyle OutlineShadow(double, double, const ColorF& in, const Vec2& in, const ColorF& in)", asFUNCTIONPR(TextStyle::OutlineShadow, (double, double, const ColorF&, const Vec2&, const ColorF&), TextStyle), asCALL_CDECL); assert(r >= 0);
			}
			r = engine->SetDefaultNamespace(""); assert(r >= 0);
		}
	}
}
