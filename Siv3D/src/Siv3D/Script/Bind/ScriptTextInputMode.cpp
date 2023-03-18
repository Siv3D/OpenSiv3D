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
# include <Siv3D/TextInputMode.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterTextInputMode(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "TextInputMode";
			r = engine->RegisterEnumValue(TypeName, "DenyControl", static_cast<uint32>(TextInputMode::DenyControl)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowEnter", static_cast<uint32>(TextInputMode::AllowEnter)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowTab", static_cast<uint32>(TextInputMode::AllowTab)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowBackSpace", static_cast<uint32>(TextInputMode::AllowBackSpace)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowDelete", static_cast<uint32>(TextInputMode::AllowDelete)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowEnterTab", static_cast<uint32>(TextInputMode::AllowEnterTab)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowEnterBackSpace", static_cast<uint32>(TextInputMode::AllowEnterBackSpace)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowEnterBackSpaceDelete", static_cast<uint32>(TextInputMode::AllowEnterBackSpaceDelete)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowTabBackSpace", static_cast<uint32>(TextInputMode::AllowTabBackSpace)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowTabBackSpaceDelete", static_cast<uint32>(TextInputMode::AllowTabBackSpaceDelete)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowBackSpaceDelete", static_cast<uint32>(TextInputMode::AllowBackSpaceDelete)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowEnterTabBackSpace", static_cast<uint32>(TextInputMode::AllowEnterTabBackSpace)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AllowEnterTabBackSpaceDelete", static_cast<uint32>(TextInputMode::AllowEnterTabBackSpaceDelete)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Default", static_cast<uint32>(TextInputMode::Default)); assert(r >= 0);
		}
	}
}
