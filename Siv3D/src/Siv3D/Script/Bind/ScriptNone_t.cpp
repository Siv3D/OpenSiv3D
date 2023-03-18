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

namespace s3d
{
	using namespace AngelScript;
	
	using BindType = uint8;

	static void Construct(uint8* self)
	{
		new(self) BindType(0);
	}

	void RegisterNone_t(asIScriptEngine* engine)
	{
		static const uint8 NoneDummy = 0;
		const char TypeName[] = "None_t";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterGlobalProperty("const None_t none", (void*)&NoneDummy); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const None_t unspecified", (void*)&NoneDummy); assert(r >= 0);
	}
}
