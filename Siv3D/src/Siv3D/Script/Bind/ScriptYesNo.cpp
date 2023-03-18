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

	namespace detail
	{
		inline constexpr bool Yes = true;
		inline constexpr bool No = false;
	}

	static void RegisterYesNo(asIScriptEngine* engine, const char* name)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace(name); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const bool Yes", (void*)&detail::Yes); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const bool No", (void*)&detail::No); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}

	void RegisterYesNo(asIScriptEngine* engine)
	{
		RegisterYesNo(engine, "StartImmediately");
		//RegisterYesNo(engine, "AllowUndo");
		RegisterYesNo(engine, "Centering");
		RegisterYesNo(engine, "CloseRing");
		RegisterYesNo(engine, "SkipValidation");
		RegisterYesNo(engine, "TransformCursor");
		RegisterYesNo(engine, "AllowScaleUp");
		RegisterYesNo(engine, "Loop");
		RegisterYesNo(engine, "InvertColor");
		RegisterYesNo(engine, "AllowHoles");
		RegisterYesNo(engine, "Antialiased");
	}
}
