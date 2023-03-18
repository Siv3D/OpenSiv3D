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
# include <Siv3D/WaveSample.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = WaveSample;

	static void CopyConstruct(const BindType& s, BindType* self)
	{
		new(self) BindType(s);
	}

	static void ConstructF(float mono, BindType* self)
	{
		new(self) BindType(mono);
	}

	static void ConstructFF(float left, float right, BindType* self)
	{
		new(self) BindType(left, right);
	}

	static WaveSample MulFloat(float other, const BindType& value)
	{
		return (value * other);
	}

	void RegisterWaveSample(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "WaveSample";
			r = engine->RegisterObjectProperty(TypeName, "float left", asOFFSET(WaveSample, left)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "float right", asOFFSET(WaveSample, right)); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const WaveSample &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float) explicit", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructFF), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "WaveSample& opAssign(const WaveSample& in)", asMETHODPR(WaveSample, operator=, (const WaveSample&), WaveSample&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "WaveSample& opAssign(float)", asMETHODPR(WaveSample, operator=, (float), WaveSample&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "WaveSample opMul(float) const", asMETHODPR(WaveSample, operator*, (float) const, WaveSample), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "WaveSample opMul_r(float) const", asFUNCTION(MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "WaveSample& opMulAssign(double)", asMETHODPR(WaveSample, operator*=, (float), WaveSample&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHODPR(WaveSample, clear, (), void), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "WaveSample& set(float)", asMETHODPR(WaveSample, set, (float), WaveSample&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "WaveSample& set(float, float)", asMETHODPR(WaveSample, set, (float, float), WaveSample&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "WaveSample& set(WaveSample)", asMETHODPR(WaveSample, set, (WaveSample), WaveSample&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void swapChannel()", asMETHODPR(WaveSample, swapChannel, (), void), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void lerp(WaveSample, float) const", asMETHODPR(WaveSample, lerp, (WaveSample, float) const, WaveSample), asCALL_THISCALL); assert(r >= 0);

			r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
			{
				r = engine->RegisterGlobalFunction("WaveSample FromInt16(int16)", asFUNCTIONPR(WaveSample::FromInt16, (int16), WaveSample), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("WaveSample FromInt16(int16, int16)", asFUNCTIONPR(WaveSample::FromInt16, (int16, int16), WaveSample), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("WaveSample Zero()", asFUNCTION(WaveSample::Zero), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("WaveSample Min()", asFUNCTION(WaveSample::Min), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterGlobalFunction("WaveSample Max()", asFUNCTION(WaveSample::Max), asCALL_CDECL); assert(r >= 0);
			}
			r = engine->SetDefaultNamespace(""); assert(r >= 0);
		}
	}
}
