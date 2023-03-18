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
# include <Siv3D/FloatingPoint.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterFloatingPoint(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterGlobalFunction("uint32 AsUint32(float)", asFUNCTIONPR(AsUint32, (float), uint32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 AsUint64(double)", asFUNCTIONPR(AsUint64, (double), uint64), asCALL_CDECL); assert(r >= 0);
	}
}
