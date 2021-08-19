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
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	using namespace AngelScript;

	struct ArgVec2
	{
		Vec2 value;
	};

	static ArgVec2 MakeArgVec2(Vec2 value, const uint8&)
	{
		return ArgVec2{ value };
	}

	static ArgVec2 MakeArgVec2_DD(double x, double y, const uint8&)
	{
		return ArgVec2{ {x,y} };
	}

	static void ArgVec2_DefaultConstruct(ArgVec2* self)
	{
		new(self) ArgVec2{};
	}

	static void ArgVec2_CopyConstruct(const Vec2& v, ArgVec2* self)
	{
		new(self) ArgVec2{ v };
	}

	void RegisterNamedParameter(asIScriptEngine* engine)
	{
		static constexpr uint8 namedArgEmpty = 0;

		int32 r = 0;

		r = engine->SetDefaultNamespace("Arg"); assert(r >= 0);
		{
			{
				r = engine->RegisterGlobalProperty("const topLeft_ topLeft", (void*)&namedArgEmpty); assert(r >= 0);
				r = engine->RegisterObjectMethod("topLeft_", "topLeft_Vec2 opAssign(Vec2) const", asFUNCTION(MakeArgVec2), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectMethod("topLeft_", "topLeft_Vec2 opCall(double, double) const", asFUNCTION(MakeArgVec2_DD), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectMethod("topLeft_", "topLeft_Vec2 opCall(Vec2) const", asFUNCTION(MakeArgVec2), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("topLeft_Vec2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ArgVec2_DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("topLeft_Vec2", asBEHAVE_CONSTRUCT, "void f(const Vec2 &in)", asFUNCTION(ArgVec2_CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			}

			{
				r = engine->RegisterGlobalProperty("const center_ center", (void*)&namedArgEmpty); assert(r >= 0);
				r = engine->RegisterObjectMethod("center_", "center_Vec2 opAssign(Vec2) const", asFUNCTION(MakeArgVec2), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectMethod("center_", "center_Vec2 opCall(double, double) const", asFUNCTION(MakeArgVec2_DD), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectMethod("center_", "center_Vec2 opCall(Vec2) const", asFUNCTION(MakeArgVec2), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("center_Vec2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ArgVec2_DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("center_Vec2", asBEHAVE_CONSTRUCT, "void f(const Vec2 &in)", asFUNCTION(ArgVec2_CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			}
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
