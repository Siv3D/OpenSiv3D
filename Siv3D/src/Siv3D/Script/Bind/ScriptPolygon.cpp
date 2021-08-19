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
# include <Siv3D/Polygon.hpp>
# include "ScriptBind.hpp"
# include "../angelscript/scriptarray.h"

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = Polygon;

	static void DefaultConstruct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void CopyConstruct(const Polygon& other, ShapeType* self)
	{
		new(self) ShapeType(other);
	}

	static void ConstructS(const Shape2D& shape2D, ShapeType* self)
	{
		new(self) ShapeType(shape2D);
	}

	static void Destruct(ShapeType* self)
	{
		self->~Polygon();
	}

	static void ListConstruct(const void* list, ShapeType* self)
	{
		const size_t length = *static_cast<const asUINT*>(list);
		const Vec2* data = static_cast<const Vec2*>(static_cast<const void*>(static_cast<const uint8*>(list) + 4));
		new(self) ShapeType(data, length);
	}

	static CScriptArray* Outer(const Polygon& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Array<Vec2>");

		if (void* mem = std::malloc(self.outer().size_bytes() + sizeof(asUINT)))
		{
			*(asUINT*)mem = static_cast<asUINT>(self.outer().size());
			std::memcpy(((asUINT*)mem) + 1, self.outer().data(), self.outer().size_bytes());

			const auto p = CScriptArray::Create(typeID, mem);
			std::free(mem);

			return p;
		}
		else
		{
			return nullptr;
		}
	}

	static bool ConvToBool(const Polygon& polygon)
	{
		return !polygon.isEmpty();
	}

	void RegisterPolygon(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Polygon";

		int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Polygon& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Shape2D& in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_LIST_CONSTRUCT, "void f(const Vec2& in) {repeat Vec2}", asFUNCTION(ListConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

	}
}
