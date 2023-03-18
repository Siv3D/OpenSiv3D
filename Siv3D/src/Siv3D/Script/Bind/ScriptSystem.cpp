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
# include <Siv3D/System.hpp>
# include <Siv3D/Script/IScript.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	using namespace AngelScript;

	static bool ScriptSystemUpdate()
	{
		const asIScriptContext* context = asGetActiveContext();
		const uint64 scriptID = *static_cast<const uint64*>(context->GetUserData(static_cast<uint32>(detail::ScriptUserDataIndex::ScriptID)));
		const auto callback = SIV3D_ENGINE(Script)->getSystemUpdateCallback(scriptID);

		if (callback && (not callback()))
		{
			return false;
		}

		if (uint64* stepCounter = static_cast<uint64*>(context->GetUserData(AngelScript::asPWORD(static_cast<uint32>(detail::ScriptUserDataIndex::StepCounter)))))
		{
			*stepCounter = 0;
		}

		return System::Update();
	}

	static bool ScriptSystemLaunchBrowser(const String& s)
	{
		return System::LaunchBrowser(s);
	}

	static bool ScriptSystemShowInFileManager(const String& s)
	{
		return System::ShowInFileManager(s);
	}

	void RegisterSystem(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("System"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("bool Update()", asFUNCTION(ScriptSystemUpdate), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Exit()", asFUNCTION(System::Exit), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetTerminationTriggers(uint32)", asFUNCTION(System::SetTerminationTriggers), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint32 GetTerminationTriggers()", asFUNCTION(System::GetTerminationTriggers), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("uint32 GetUserActions()", asFUNCTION(System::GetUserActions), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Sleep(int32)", asFUNCTIONPR(System::Sleep, (int32), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Sleep(const Duration& in)", asFUNCTIONPR(System::Sleep, (const Duration&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool LaunchBrowser(const String& in)", asFUNCTION(ScriptSystemLaunchBrowser), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool ShowInFileManager(const String& in)", asFUNCTION(ScriptSystemShowInFileManager), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
