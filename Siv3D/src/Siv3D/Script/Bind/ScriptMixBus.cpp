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
# include <Siv3D/MixBus.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterMixBus(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "MixBus";

		[[maybe_unused]] int32 r = 0;
		{
			r = engine->RegisterEnumValue(TypeName, "Index0", static_cast<int32>(MixBus::Index0)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Index1", static_cast<int32>(MixBus::Index1)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Index2", static_cast<int32>(MixBus::Index2)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Index3", static_cast<int32>(MixBus::Index3)); assert(r >= 0);
		}

		r = engine->RegisterGlobalProperty("const MixBus MixBus0", (void*)&MixBus0); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const MixBus MixBus1", (void*)&MixBus1); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const MixBus MixBus2", (void*)&MixBus2); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const MixBus MixBus3", (void*)&MixBus3); assert(r >= 0);
	}
}
