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
# include <Siv3D/OpenMode.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterOpenMode(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "OpenMode";

		[[maybe_unused]] int32 r = 0;
		{
			r = engine->RegisterEnumValue(TypeName, "Trunc", static_cast<uint32>(OpenMode::Trunc)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Append", static_cast<uint32>(OpenMode::Append)); assert(r >= 0);
		}
	}
}
