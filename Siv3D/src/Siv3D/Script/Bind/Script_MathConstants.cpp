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
			r = engine->RegisterGlobalProperty("const double Pi", (void*)&Math::Constants::Pi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const float PiF", (void*)&Math::Constants::PiF); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double TwoPi", (void*)&Math::Constants::TwoPi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const float TwoPiF", (void*)&Math::Constants::TwoPiF); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double HalfPi", (void*)&Math::Constants::HalfPi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const float HalfPiF", (void*)&Math::Constants::HalfPiF); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double QuarterPi", (void*)&Math::Constants::QuarterPi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const float QuarterPiF", (void*)&Math::Constants::QuarterPiF); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double QNaN", (void*)&Math::Constants::QNaN); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double NaN", (void*)&Math::Constants::NaN); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Inf", (void*)&Math::Constants::Inf); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double Phi", (void*)&Math::Constants::Phi); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double E", (void*)&Math::Constants::E); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
