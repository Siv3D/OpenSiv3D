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
# include <Siv3D/WaveSample.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

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

	void RegisterWaveSample(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "WaveSample";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "float left", asOFFSET(WaveSample, left)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "float right", asOFFSET(WaveSample, right)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const WaveSample &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructFF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "WaveSample& opAssign(const WaveSample& in)", asMETHODPR(WaveSample, operator=, (const WaveSample&), WaveSample&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "WaveSample& opAssign(float)", asMETHODPR(WaveSample, operator=, (float), WaveSample&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "WaveSample& set(const WaveSample& in)", asMETHODPR(WaveSample, set, (const WaveSample&), WaveSample&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "WaveSample& set(float)", asMETHODPR(WaveSample, set, (float), WaveSample&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "WaveSample& set(float, float)", asMETHODPR(WaveSample, set, (float, float), WaveSample&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void swapChannel()", asMETHOD(WaveSample, swapChannel), asCALL_THISCALL); assert(r >= 0);

		//[[nodiscard]] constexpr WaveSampleS16 asS16() const noexcept

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("WaveSample Zero()", asFUNCTION(WaveSample::Zero), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
