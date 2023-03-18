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
# include <Siv3D/TriangleIndex.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = TriangleIndex;

	static void Construct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void ConstructCopy(const TriangleIndex& r, ShapeType* self)
	{
		new(self) ShapeType(r);
	}

	void RegisterTriangleIndex(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "TriangleIndex";
			r = engine->RegisterObjectProperty(TypeName, "uint16 i0", asOFFSET(TriangleIndex, i0)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "uint16 i1", asOFFSET(TriangleIndex, i1)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "uint16 i2", asOFFSET(TriangleIndex, i2)); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TriangleIndex &in)", asFUNCTION(ConstructCopy), asCALL_CDECL_OBJLAST); assert(r >= 0);
		}
	}
}
