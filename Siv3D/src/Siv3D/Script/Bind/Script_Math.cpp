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
# include <Siv3D/Math.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	template <class Type>
	static constexpr auto AbsPrimitive(Type x) noexcept
	{
		return std::abs(x);
	}

	void RegisterMath(asIScriptEngine* engine)
	{
		int32 r = 0;

		//r = engine->SetDefaultNamespace("Math"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("int32 Abs(int8)", asFUNCTION(AbsPrimitive<int8>), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Abs(int16)", asFUNCTION(AbsPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Abs(int32)", asFUNCTION(AbsPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int64 Abs(int64)", asFUNCTION(AbsPrimitive<int64>), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("float Abs(float)", asFUNCTIONPR(Math::Abs, (float), float), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Abs(double)", asFUNCTIONPR(Math::Abs, (double), double), asCALL_CDECL); assert(r >= 0);

			//r = engine->RegisterGlobalFunction("float ToDegrees(float)", asFUNCTIONPR(Math::ToDegrees, (float), float), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double ToDegrees(double)", asFUNCTIONPR(Math::ToDegrees, (double), double), asCALL_CDECL); assert(r >= 0);

			//r = engine->RegisterGlobalFunction("float ToRadians(float)", asFUNCTIONPR(Math::ToRadians, (float), float), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double ToRadians(double)", asFUNCTIONPR(Math::ToRadians, (double), double), asCALL_CDECL); assert(r >= 0);


			r = engine->RegisterGlobalFunction("double Atan2(double, double)", asFUNCTIONPR(Math::Atan2, (double, double), double), asCALL_CDECL); assert(r >= 0);


		}
		//r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
