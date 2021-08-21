//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/GlobalAudio.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterGlobalAudio(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("GlobalAudio"); assert(r >= 0);
		{

		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
