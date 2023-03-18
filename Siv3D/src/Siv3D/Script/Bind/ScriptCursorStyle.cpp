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
# include <Siv3D/CursorStyle.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterCursorStyle(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "CursorStyle";

		[[maybe_unused]] int32 r = 0;
		{
			r = engine->RegisterEnumValue(TypeName, "Arrow", static_cast<uint32>(CursorStyle::Arrow)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "IBeam", static_cast<uint32>(CursorStyle::IBeam)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Cross", static_cast<uint32>(CursorStyle::Cross)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Hand", static_cast<uint32>(CursorStyle::Hand)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "NotAllowed", static_cast<uint32>(CursorStyle::NotAllowed)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ResizeUpDown", static_cast<uint32>(CursorStyle::ResizeUpDown)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ResizeLeftRight", static_cast<uint32>(CursorStyle::ResizeLeftRight)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ResizeNWSE", static_cast<uint32>(CursorStyle::ResizeNWSE)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ResizeNESW", static_cast<uint32>(CursorStyle::ResizeNESW)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "ResizeAll", static_cast<uint32>(CursorStyle::ResizeAll)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Hidden", static_cast<uint32>(CursorStyle::Hidden)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Default", static_cast<uint32>(CursorStyle::Default)); assert(r >= 0);
		}
	}
}
