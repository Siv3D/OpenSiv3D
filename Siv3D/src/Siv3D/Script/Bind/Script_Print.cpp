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
# include <Siv3D/Print.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = uint8;

	static void PrintShl(const String& text, BindType*)
	{
		Print(text);
	}

	void RegisterPrint(asIScriptEngine *engine)
	{
		static const uint8 PrintImplDummy = 0;

		const char TypeName[] = "Print_impl";
		
		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "uint8 _dummy", 0); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void opShl(const String&in text) const", asFUNCTION(PrintShl), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Print_impl Print", (void*)&PrintImplDummy); assert(r >= 0);

		engine->RegisterGlobalFunction("void ClearPrint()", asFUNCTION(ClearPrint), asCALL_CDECL); assert(r >= 0);
	}
}
