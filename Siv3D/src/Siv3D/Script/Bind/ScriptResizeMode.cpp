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
# include <Siv3D/ResizeMode.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterResizeMode(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "ResizeMode";

		[[maybe_unused]] int32 r = 0;
		{
			r = engine->RegisterEnumValue(TypeName, "Actual", static_cast<uint32>(ResizeMode::Actual)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Virtual", static_cast<uint32>(ResizeMode::Virtual)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Keep", static_cast<uint32>(ResizeMode::Keep)); assert(r >= 0);
		}
	}
}
