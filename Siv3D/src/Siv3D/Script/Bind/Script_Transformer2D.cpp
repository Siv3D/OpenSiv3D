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
# include <Siv3D/Transformer2D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Transformer2D;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void ConstructMT(const Mat3x2& mat, Transformer2D::Target target, BindType* self)
	{
		new(self) BindType(mat, target);
	}

	static void ConstructMBT(const Mat3x2& mat, bool transformCursor, Transformer2D::Target target, BindType* self)
	{
		new(self) BindType(mat, transformCursor, target);
	}

	static void ConstructMMT(const Mat3x2& mat, const Mat3x2& matCursor, Transformer2D::Target target, BindType* self)
	{
		new(self) BindType(mat, matCursor, target);
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	void RegisterTransformer2D(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Transformer2D";

		int32 r = 0;

		r = engine->SetDefaultNamespace("Transformer2D"); assert(r >= 0);
		{
			r = engine->RegisterEnum("Target"); assert(r >= 0);

			r = engine->RegisterEnumValue("Target", "PushLocal", static_cast<uint32>(Transformer2D::Target::PushLocal)); assert(r >= 0);
			r = engine->RegisterEnumValue("Target", "PushCamera", static_cast<uint32>(Transformer2D::Target::PushCamera)); assert(r >= 0);
			r = engine->RegisterEnumValue("Target", "SetLocal", static_cast<uint32>(Transformer2D::Target::SetLocal)); assert(r >= 0);
			r = engine->RegisterEnumValue("Target", "SetCamera", static_cast<uint32>(Transformer2D::Target::SetCamera)); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Mat3x2& in, Transformer2D::Target)", asFUNCTION(ConstructMT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Mat3x2& in, bool transformCursor = false, Transformer2D::Target target = Transformer2D::Target::PushLocal)", asFUNCTION(ConstructMBT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Mat3x2& in, const Mat3x2& in, Transformer2D::Target target = Transformer2D::Target::PushLocal)", asFUNCTION(ConstructMMT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		//opAssign
	}
}
