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
# include <Siv3D/Easing.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterEasing(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterGlobalFunction("double EaseInLinear(double)", asFUNCTION(EaseInLinear), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInSine(double)", asFUNCTION(EaseInSine), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInQuad(double)", asFUNCTION(EaseInQuad), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInCubic(double)", asFUNCTION(EaseInCubic), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInQuart(double)", asFUNCTION(EaseInQuart), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInQuint(double)", asFUNCTION(EaseInQuint), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInExpo(double)", asFUNCTION(EaseInExpo), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInCirc(double)", asFUNCTION(EaseInCirc), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInBack(double)", asFUNCTION(EaseInBack), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInElastic(double)", asFUNCTION(EaseInElastic), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInBounce(double)", asFUNCTION(EaseInBounce), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("double EaseOutLinear(double)", asFUNCTION(EaseOutLinear), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutSine(double)", asFUNCTION(EaseOutSine), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutQuad(double)", asFUNCTION(EaseOutQuad), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutCubic(double)", asFUNCTION(EaseOutCubic), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutQuart(double)", asFUNCTION(EaseOutQuart), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutQuint(double)", asFUNCTION(EaseOutQuint), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutExpo(double)", asFUNCTION(EaseOutExpo), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutCirc(double)", asFUNCTION(EaseOutCirc), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutBack(double)", asFUNCTION(EaseOutBack), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutElastic(double)", asFUNCTION(EaseOutElastic), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseOutBounce(double)", asFUNCTION(EaseOutBounce), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("double EaseInOutLinear(double)", asFUNCTION(EaseInOutLinear), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutSine(double)", asFUNCTION(EaseInOutSine), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutQuad(double)", asFUNCTION(EaseInOutQuad), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutCubic(double)", asFUNCTION(EaseInOutCubic), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutQuart(double)", asFUNCTION(EaseInOutQuart), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutQuint(double)", asFUNCTION(EaseInOutQuint), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutExpo(double)", asFUNCTION(EaseInOutExpo), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutCirc(double)", asFUNCTION(EaseInOutCirc), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutBack(double)", asFUNCTION(EaseInOutBack), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutElastic(double)", asFUNCTION(EaseInOutElastic), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double EaseInOutBounce(double)", asFUNCTION(EaseInOutBounce), asCALL_CDECL); assert(r >= 0);
	}
}
