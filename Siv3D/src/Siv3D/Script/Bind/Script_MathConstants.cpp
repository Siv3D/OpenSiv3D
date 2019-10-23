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
# include <Siv3D/MathConstants.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterMathConstants(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("Math"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const double Pi", (void*)&Math::Pi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const float PiF", (void*)&Math::PiF); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double TwoPi", (void*)&Math::TwoPi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const float TwoPiF", (void*)&Math::TwoPiF); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double HalfPi", (void*)&Math::HalfPi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const float HalfPiF", (void*)&Math::HalfPiF); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double OneThirdPi", (void*)&Math::OneThirdPi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const float OneThirdPiF", (void*)&Math::OneThirdPiF); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double QuarterPi", (void*)&Math::QuarterPi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const float QuarterPiF", (void*)&Math::QuarterPiF); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double QNaN", (void*)&Math::Constants::QNaN); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double NaN", (void*)&Math::Constants::NaN); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Inf", (void*)&Math::Constants::Inf); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double Phi", (void*)&Math::Constants::Phi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double E", (void*)&Math::Constants::E); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
