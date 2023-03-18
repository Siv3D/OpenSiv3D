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
# include <Siv3D/FontMethod.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterFontMethod(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "FontMethod";

		[[maybe_unused]] int32 r = 0;
		{
			r = engine->RegisterEnumValue(TypeName, "Bitmap", static_cast<int32>(FontMethod::Bitmap)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "SDF", static_cast<int32>(FontMethod::SDF)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "MSDF", static_cast<int32>(FontMethod::MSDF)); assert(r >= 0);
		}
	}
}
