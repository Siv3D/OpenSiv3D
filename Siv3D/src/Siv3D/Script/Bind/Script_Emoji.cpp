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
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Image.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Emoji;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const Emoji& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructS(const String& emoji, BindType* self)
	{
		new(self) BindType(emoji);
	}

	static void Destruct(BindType* self)
	{
		self->~Emoji();
	}

	static Image EmojiLoadImage(const String& emoji)
	{
		return Emoji::LoadImage(emoji);
	}

	static Image EmojiLoadSilhouette(const String& emoji)
	{
		return Emoji::LoadSilhouette(emoji);
	}

	void RegisterEmoji(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Emoji";

		int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Emoji& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Emoji& opAssign(const Emoji& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace("Emoji"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const Point ImageSize", (void*)&Emoji::ImageSize); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Image LoadImage(const String& in)", asFUNCTION(EmojiLoadImage), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Image LoadSilhouette(const String& in)", asFUNCTION(EmojiLoadSilhouette), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
