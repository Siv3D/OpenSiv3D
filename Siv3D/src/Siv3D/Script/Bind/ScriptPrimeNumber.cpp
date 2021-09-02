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
# include <Siv3D/PrimeNumber.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterPrimeNumber(asIScriptEngine* engine)
	{
		int32 r;

		r = engine->SetDefaultNamespace("Math"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("bool IsPrime(uint64)", asFUNCTION(Math::IsPrime), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
