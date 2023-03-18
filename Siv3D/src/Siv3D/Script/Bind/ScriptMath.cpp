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
# include <Siv3D/Math.hpp>

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
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Math"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("double Fmod(double, double)", asFUNCTIONPR(Math::Fmod, (double, double), double), asCALL_CDECL); assert(r >= 0);				
			r = engine->RegisterGlobalFunction("double Fraction(double)", asFUNCTIONPR(Math::Fraction, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Frexp(double, double& inout)", asFUNCTIONPR(Math::Frexp, (double, double&), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Ldexp(double, double)", asFUNCTIONPR(Math::Ldexp, (double, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Log(double)", asFUNCTIONPR(Math::Log, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Log2(double)", asFUNCTIONPR(Math::Log2, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Log10(double)", asFUNCTIONPR(Math::Log10, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Modf(double, double& inout)", asFUNCTIONPR(Math::Modf, (double, double&), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Pow(double, double)", asFUNCTIONPR(Math::Pow, (double, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Sign(double)", asFUNCTIONPR(Math::Sign, (double), int32), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double ToRadians(double)", asFUNCTIONPR(Math::ToRadians, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double ToDegrees(double)", asFUNCTIONPR(Math::ToDegrees, (double), double), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("int32 Abs(int8)", asFUNCTION((int32(*)(int8))AbsPrimitive), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Abs(int16)", asFUNCTION((int32(*)(int16))AbsPrimitive), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Abs(int32)", asFUNCTION((int32(*)(int32))AbsPrimitive), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int64 Abs(int64)", asFUNCTION((int64(*)(int64))AbsPrimitive), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("float Abs(float)", asFUNCTIONPR(Math::Abs, (float), float), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Abs(double)", asFUNCTIONPR(Math::Abs, (double), double), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double AbsDiff(double, double)", asFUNCTIONPR(Math::AbsDiff, (double, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Square(double)", asFUNCTIONPR(Math::Square, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Exp(double)", asFUNCTIONPR(Math::Exp, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Exp2(double)", asFUNCTIONPR(Math::Exp2, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Rsqrt(double)", asFUNCTIONPR(Math::Rsqrt, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Sqrt(double)", asFUNCTIONPR(Math::Sqrt, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Ceil(double)", asFUNCTIONPR(Math::Ceil, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Floor(double)", asFUNCTIONPR(Math::Floor, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Round(double)", asFUNCTIONPR(Math::Round, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Clamp(double, double, double)", asFUNCTIONPR(Math::Clamp, (double, double, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Saturate(double)", asFUNCTIONPR(Math::Saturate, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Acos(double)", asFUNCTIONPR(Math::Acos, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Asin(double)", asFUNCTIONPR(Math::Asin, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Atan(double)", asFUNCTIONPR(Math::Atan, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Atan2(double, double)", asFUNCTIONPR(Math::Atan2, (double, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Cos(double)", asFUNCTIONPR(Math::Cos, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Cosh(double)", asFUNCTIONPR(Math::Cosh, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Sin(double)", asFUNCTIONPR(Math::Sin, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Sinh(double)", asFUNCTIONPR(Math::Sinh, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Tan(double)", asFUNCTIONPR(Math::Tan, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Tanh(double)", asFUNCTIONPR(Math::Tanh, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Normalize(double)", asFUNCTIONPR(Math::Normalize, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Smoothstep(double)", asFUNCTIONPR(Math::Smoothstep, (double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Smoothstep(double, double, double)", asFUNCTIONPR(Math::Smoothstep, (double, double, double), double), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("int64 GCD(int64, int64)", asFUNCTIONPR(Math::GCD, (int64, int64), int64), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int64 LCM(int64, int64)", asFUNCTIONPR(Math::LCM, (int64, int64), int64), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
