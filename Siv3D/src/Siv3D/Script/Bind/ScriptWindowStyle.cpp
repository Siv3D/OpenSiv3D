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
# include <Siv3D/WindowStyle.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterWindowStyle(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "WindowStyle";
			r = engine->RegisterEnumValue(TypeName, "Fixed", static_cast<uint32>(WindowStyle::Fixed)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Sizable", static_cast<uint32>(WindowStyle::Sizable)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Frameless", static_cast<uint32>(WindowStyle::Frameless)); assert(r >= 0);
		}
	}
}
