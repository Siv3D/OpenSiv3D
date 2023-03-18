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
# include <Siv3D/Graphics.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterGraphics(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Graphics"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("void SetVSyncEnabled(bool)", asFUNCTION(Graphics::SetVSyncEnabled), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool IsVSyncEnabled()", asFUNCTION(Graphics::IsVSyncEnabled), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
