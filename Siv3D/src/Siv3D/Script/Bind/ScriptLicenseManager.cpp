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
# include <Siv3D/LicenseManager.hpp>
# include "ScriptArray.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterLicenseManager(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("LicenseManager"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("void SetApplicationLicense(const String& in, const LicenseInfo& in)", asFUNCTION(LicenseManager::SetApplicationLicense), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void AddLicense(const LicenseInfo& in)", asFUNCTION(LicenseManager::AddLicense), asCALL_CDECL); assert(r >= 0);
			//r = engine->RegisterGlobalFunction("Array<LicenseInfo> EnumLicenses()", asFUNCTION(LicenseManagerSetApplicationLicense), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void EnableDefaultTrigger()", asFUNCTION(LicenseManager::EnableDefaultTrigger), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void DisableDefaultTrigger()", asFUNCTION(LicenseManager::DisableDefaultTrigger), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void ShowInBrowser()", asFUNCTION(LicenseManager::ShowInBrowser), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
