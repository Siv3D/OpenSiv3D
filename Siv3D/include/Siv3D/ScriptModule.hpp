//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# ifndef AS_USE_NAMESPACE
#  define AS_USE_NAMESPACE
# endif
# include <ThirdParty/angelscript/angelscript.h>

namespace s3d
{
	struct ScriptModule
	{
		AngelScript::asIScriptModule* module = nullptr;

		AngelScript::asIScriptContext* context = nullptr;

		uint64 scriptID = 0;

		bool withLineCues = false;

		ScriptModule() = default;

		~ScriptModule();
	};
}
