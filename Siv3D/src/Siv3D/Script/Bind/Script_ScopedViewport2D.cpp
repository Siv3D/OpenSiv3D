//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/ScopedViewport2D.hpp>
# include "Script_Optional.hpp"
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = ScopedViewport2D;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void ConstructO(const CScriptOptional& viewport, BindType* self)
	{
		if (viewport.HasValue())
		{
			new(self) BindType(*static_cast<const Optional<Rect>*>(viewport.At()));
		}
		else
		{
			new(self) BindType(none);
		}
	}

	static void ConstructR(const Rect& rect, BindType* self)
	{
		new(self) BindType(rect);
	}

	static void ConstructN(uint8, BindType* self)
	{
		new(self) BindType(none);
	}

	static void ConstructIIII(int32 x, int32 y, int32 w, int32 h, BindType* self)
	{
		new(self) BindType(x, y, w, h);
	}

	static void ConstructPII(const Point& pos, int32 w, int32 h, BindType* self)
	{
		new(self) BindType(pos, w, h);
	}

	static void ConstructIIP(int32 x, int32 y, const Size& size, BindType* self)
	{
		new(self) BindType(x, y, size);
	}

	static void ConstructPP(const Point& pos, const Size& size, BindType* self)
	{
		new(self) BindType(pos, size);
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	void RegisterScopedViewport2D(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "ScopedViewport2D";

		int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Optional<Rect>& in)", asFUNCTION(ConstructO), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Rect& in)", asFUNCTION(ConstructR), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(None_t)", asFUNCTION(ConstructN), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32, int32, int32, int32)", asFUNCTION(ConstructIIII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, int32, int32)", asFUNCTION(ConstructPII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32, int32, const Point& in)", asFUNCTION(ConstructIIP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, const Point& in)", asFUNCTION(ConstructPP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//opAssign
	}
}
