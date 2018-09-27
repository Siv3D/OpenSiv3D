//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/System.hpp>
# include "ScriptBind.hpp"
# include "../../Siv3DEngine.hpp"
# include "../IScript.hpp"

namespace s3d
{
	using namespace AngelScript;

	bool ScriptSystemUpdate()
	{
		const asIScriptContext* context = asGetActiveContext();
		const uint64 scriptID = *static_cast<const uint64*>(context->GetUserData(static_cast<uint32>(detail::ScriptUserDataIndex::ScriptID)));
		const auto callback = Siv3DEngine::GetScript()->getSystemUpdateCallback(scriptID);

		if (callback && !callback())
		{
			return false;
		}

		if (uint64* stepCounter = static_cast<uint64*>(context->GetUserData(AngelScript::asPWORD(static_cast<uint32>(detail::ScriptUserDataIndex::StepCounter)))))
		{
			*stepCounter = 0;
		}	

		return System::Update();
	}

	void RegisterSystem(asIScriptEngine *engine)
	{
		int32 r = 0;

		r = engine->RegisterEnumValue("WindowEvent", "CloseButton", WindowEvent::CloseButton); assert(r >= 0);
		r = engine->RegisterEnumValue("WindowEvent", "EscapeKey", WindowEvent::EscapeKey); assert(r >= 0);
		r = engine->RegisterEnumValue("WindowEvent", "Unfocus", WindowEvent::Unfocus); assert(r >= 0);
		r = engine->RegisterEnumValue("WindowEvent", "AnyKey", WindowEvent::AnyKey); assert(r >= 0);
		r = engine->RegisterEnumValue("WindowEvent", "Default", WindowEvent::Default); assert(r >= 0);
		r = engine->RegisterEnumValue("WindowEvent", "Manual", WindowEvent::Manual); assert(r >= 0);

		r = engine->SetDefaultNamespace("System"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("bool Update()", asFUNCTION(ScriptSystemUpdate), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void Exit(double maxDuration = 0.1)", asFUNCTION(System::Exit), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetExitEvent(uint32)", asFUNCTION(System::SetExitEvent), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("uint32 GetPreviousEvent()", asFUNCTION(System::GetPreviousEvent), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double DeltaTime(double maxDuration = 0.1)", asFUNCTION(System::DeltaTime), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void Sleep(int32)", asFUNCTIONPR(System::Sleep, (int32), void), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("int32 FrameCount()", asFUNCTION(System::FrameCount), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetFrameCount(int32)", asFUNCTION(System::SetFrameCount), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("bool LaunchBrowser(const String& in)", asFUNCTION(System::LaunchBrowser), asCALL_CDECL); assert(r >= 0);

		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
