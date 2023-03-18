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
# include <Siv3D/CameraControl.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterCameraControl(asIScriptEngine* engine)
	{
		constexpr char EnumName[] = "CameraControl";

		[[maybe_unused]] int32 r = 0;
		{
			r = engine->RegisterEnumValue(EnumName, "None_", static_cast<uint32>(CameraControl::None_)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "WASDKeys", static_cast<uint32>(CameraControl::WASDKeys)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "UpDownKeys", static_cast<uint32>(CameraControl::UpDownKeys)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "RightClick", static_cast<uint32>(CameraControl::RightClick)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Wheel", static_cast<uint32>(CameraControl::Wheel)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Keyboard", static_cast<uint32>(CameraControl::Keyboard)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Mouse", static_cast<uint32>(CameraControl::Mouse)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Default", static_cast<uint32>(CameraControl::Default)); assert(r >= 0);
		}
	}
}
