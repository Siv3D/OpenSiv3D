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
		int r = 0;

		r = engine->SetDefaultNamespace("System"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("bool Update()", asFUNCTION(ScriptSystemUpdate), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double DeltaTime(double maxDuration = 0.1)", asFUNCTION(System::DeltaTime), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
