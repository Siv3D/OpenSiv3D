//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/UserAction.hpp>
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
		const auto callback = Siv3DEngine::Get<ISiv3DScript>()->getSystemUpdateCallback(scriptID);

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

		{
			r = engine->RegisterEnumValue("UserAction", "CloseButtonClicked", UserAction::CloseButtonClicked); assert(r >= 0);
			r = engine->RegisterEnumValue("UserAction", "EscapeKeyDown", UserAction::EscapeKeyDown); assert(r >= 0);
			r = engine->RegisterEnumValue("UserAction", "WindowDeactivated", UserAction::WindowDeactivated); assert(r >= 0);
			r = engine->RegisterEnumValue("UserAction", "AnyKeyDown", UserAction::AnyKeyDown); assert(r >= 0);
			r = engine->RegisterEnumValue("UserAction", "MouseButtonDown", UserAction::MouseButtonDown); assert(r >= 0);
			r = engine->RegisterEnumValue("UserAction", "AnyKeyOrMouseDown", UserAction::AnyKeyOrMouseDown); assert(r >= 0);
			r = engine->RegisterEnumValue("UserAction", "Default", UserAction::Default); assert(r >= 0);
			r = engine->RegisterEnumValue("UserAction", "None", UserAction::None); assert(r >= 0);
		}

		r = engine->SetDefaultNamespace("System"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("bool Update()", asFUNCTION(ScriptSystemUpdate), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void Exit(double maxDuration = 0.1)", asFUNCTION(System::Exit), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetTerminationTriggers(uint32)", asFUNCTION(System::SetTerminationTriggers), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("uint32 GetTerminationTriggers()", asFUNCTION(System::GetTerminationTriggers), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("uint32 GetUserActions()", asFUNCTION(System::GetUserActions), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void Sleep(int32)", asFUNCTIONPR(System::Sleep, (int32), void), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void Sleep(const Duration& in)", asFUNCTIONPR(System::Sleep, (const Duration&), void), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("bool LaunchBrowser(const String& in)", asFUNCTION(System::LaunchBrowser), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
