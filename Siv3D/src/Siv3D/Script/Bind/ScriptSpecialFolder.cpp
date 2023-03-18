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
# include <Siv3D/SpecialFolder.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterSpecialFolder(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "SpecialFolder";

		[[maybe_unused]] int32 r = 0;
		{
			r = engine->RegisterEnumValue(TypeName, "Desktop", static_cast<uint32>(SpecialFolder::Desktop)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Documents", static_cast<uint32>(SpecialFolder::Documents)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "LocalAppData", static_cast<uint32>(SpecialFolder::LocalAppData)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Pictures", static_cast<uint32>(SpecialFolder::Pictures)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Music", static_cast<uint32>(SpecialFolder::Music)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Videos", static_cast<uint32>(SpecialFolder::Videos)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Caches", static_cast<uint32>(SpecialFolder::Caches)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Movies", static_cast<uint32>(SpecialFolder::Movies)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "SystemFonts", static_cast<uint32>(SpecialFolder::SystemFonts)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "LocalFonts", static_cast<uint32>(SpecialFolder::LocalFonts)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "UserFonts", static_cast<uint32>(SpecialFolder::UserFonts)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "UserProfile", static_cast<uint32>(SpecialFolder::UserProfile)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ProgramFiles", static_cast<uint32>(SpecialFolder::ProgramFiles)); assert(r >= 0);
		}
	}
}
