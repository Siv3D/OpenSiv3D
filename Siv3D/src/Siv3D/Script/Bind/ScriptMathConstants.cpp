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
# include <Siv3D/MathConstants.hpp>

namespace s3d
{
	using namespace AngelScript;

	static float MathPiF(float x) noexcept
	{
		return (x * Math::PiF);
	}

	static double MathPi(double x) noexcept
	{
		return (x * Math::Pi);
	}

	static float MathTauF(float x) noexcept
	{
		return (x * Math::TauF);
	}

	static double MathTau(double x) noexcept
	{
		return (x * Math::Tau);
	}

	static float MathDegF(float x) noexcept
	{
		return (x * (Math::PiF / 180));
	}

	static double MathDeg(double x) noexcept
	{
		return (x * (Math::Pi / 180));
	}

	void RegisterMathConstants(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Math"); assert(r >= 0);
		{	
			r = engine->RegisterGlobalProperty("const float PiF", (void*)&Math::Constants::PiF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Pi", (void*)&Math::Constants::Pi); assert(r >= 0);
			
			r = engine->RegisterGlobalProperty("const float QuarterPiF", (void*)&Math::Constants::QuarterPiF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double QuarterPi", (void*)&Math::Constants::QuarterPi); assert(r >= 0);
			
			r = engine->RegisterGlobalProperty("const float OneThirdPiF", (void*)&Math::Constants::OneThirdPiF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double OneThirdPi", (void*)&Math::Constants::OneThirdPi); assert(r >= 0);
			
			r = engine->RegisterGlobalProperty("const float HalfPiF", (void*)&Math::Constants::HalfPiF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double HalfPi", (void*)&Math::Constants::HalfPi); assert(r >= 0);
	
			r = engine->RegisterGlobalProperty("const float TwoPiF", (void*)&Math::Constants::TwoPiF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double TwoPi", (void*)&Math::Constants::TwoPi); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const float TauF", (void*)&Math::Constants::TauF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Tau", (void*)&Math::Constants::Tau); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const float InvTwoPiF", (void*)&Math::Constants::InvTwoPiF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double InvTwoPi", (void*)&Math::Constants::InvTwoPi); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const float InvPiF", (void*)&Math::Constants::InvPiF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double InvPi", (void*)&Math::Constants::InvPi); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const float InvSqrtPiF", (void*)&Math::Constants::InvSqrtPiF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double InvSqrtPi", (void*)&Math::Constants::InvSqrtPi); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const double E", (void*)&Math::Constants::E); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Log2E", (void*)&Math::Constants::Log2E); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Log10E", (void*)&Math::Constants::Log10E); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Ln2", (void*)&Math::Constants::Ln2); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Ln10", (void*)&Math::Constants::Ln10); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Sqrt2", (void*)&Math::Constants::Sqrt2); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Sqrt3", (void*)&Math::Constants::Sqrt3); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double InvSqrt2", (void*)&Math::Constants::InvSqrt2); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double InvSqrt3", (void*)&Math::Constants::InvSqrt3); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double EGamma", (void*)&Math::Constants::EGamma); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Phi", (void*)&Math::Constants::Phi); assert(r >= 0);
	
			r = engine->RegisterGlobalProperty("const float QNaNF", (void*)&Math::Constants::QNaNF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double QNaN", (void*)&Math::Constants::QNaN); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const float NaNF", (void*)&Math::Constants::NaNF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double NaN", (void*)&Math::Constants::NaN); assert(r >= 0);

			r = engine->RegisterGlobalProperty("const float InfF", (void*)&Math::Constants::InfF); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double Inf", (void*)&Math::Constants::Inf); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
		
		r = engine->RegisterGlobalFunction("double _pi(double)", asFUNCTION(MathPi), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double _piF(double)", asFUNCTION(MathPiF), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("double _tau(double)", asFUNCTION(MathTau), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double _tauF(double)", asFUNCTION(MathTauF), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("double _deg(double)", asFUNCTION(MathDeg), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double _degF(double)", asFUNCTION(MathDegF), asCALL_CDECL); assert(r >= 0);
	}
}
