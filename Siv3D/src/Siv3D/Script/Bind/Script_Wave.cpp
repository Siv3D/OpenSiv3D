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
# include <Siv3D/Wave.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Wave;

	struct SamplingRate_v
	{
		uint32 value = 0;
	};

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const BindType& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructUS(uint32 num_samples, SamplingRate_v samplingRate, BindType* self)
	{
		new(self) BindType(num_samples, Arg::samplingRate = samplingRate.value);
	}

	static void ConstructDS(const Duration& duration, SamplingRate_v samplingRate, BindType* self)
	{
		new(self) BindType(duration, Arg::samplingRate = samplingRate.value);
	}

	static void ConstructUWS(uint32 num_samples, const WaveSample& sample, SamplingRate_v samplingRate, BindType* self)
	{
		new(self) BindType(num_samples, sample, Arg::samplingRate = samplingRate.value);
	}

	static void ConstructDWS(const Duration& duration, const WaveSample& sample, SamplingRate_v samplingRate, BindType* self)
	{
		new(self) BindType(duration, sample, Arg::samplingRate = samplingRate.value);
	}

	static void ConstructUUDDS(int32 instrumrnt, int32 key, const Duration& duration, double velocity, SamplingRate_v samplingRate, BindType* self)
	{
		new(self) BindType(static_cast<GMInstrument>(instrumrnt), static_cast<uint8>(key), duration, velocity, Arg::samplingRate = samplingRate.value);
	}

	static void ConstructF(const FilePath& path, BindType* self)
	{
		new(self) BindType(path);
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	static bool ConvToBool(const Wave& wave)
	{
		return !wave.isEmpty();
	}

	void RegisterWave(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Wave";

		int32 r = 0;

		r = engine->SetDefaultNamespace("Wave"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const uint32 MinSamplingRate", (void*)&Wave::MinSamplingRate); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const uint32 DefaultSamplingRate", (void*)&Wave::DefaultSamplingRate); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const uint32 MaxSamplingRate", (void*)&Wave::MaxSamplingRate); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Wave& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32, Arg::samplingRate_v = (Arg::samplingRate = 44100))", asFUNCTION(ConstructUS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Duration& in, Arg::samplingRate_v = (Arg::samplingRate = 44100))", asFUNCTION(ConstructDS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32, const WaveSample& in, Arg::samplingRate_v = (Arg::samplingRate = 44100))", asFUNCTION(ConstructUWS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Duration& in, const WaveSample& in, Arg::samplingRate_v = (Arg::samplingRate = 44100))", asFUNCTION(ConstructDWS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//Wave(size_t num_samples, Arg::generator_<std::function<double(double)>> generator, Arg::samplingRate_<uint32> samplingRate = Arg::samplingRate_<uint32>(DefaultSamplingRate));
		//Wave(const Duration& duration, Arg::generator_<std::function<double(double)>> generator, Arg::samplingRate_<uint32> samplingRate = Arg::samplingRate_<uint32>(DefaultSamplingRate));
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in)", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//explicit Wave(const Array<WaveSample>& samples, Arg::samplingRate_<uint32> samplingRate = Arg::samplingRate_<uint32>(DefaultSamplingRate))
		//explicit Wave(Array<WaveSample>&& samples, Arg::samplingRate_<uint32> samplingRate = Arg::samplingRate_<uint32>(DefaultSamplingRate))
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(int32 instrumrnt, int32 key, const Duration& in, double velocity = 1.0, Arg::samplingRate_v = (Arg::samplingRate = 44100))", asFUNCTION(ConstructUUDDS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Wave& opAssign(const Wave& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void assign(const Wave& in)", asMETHODPR(BindType, assign, (const BindType&), void), asCALL_THISCALL); assert(r >= 0);
		//Wave& operator =(const Array<WaveSample>& other)

		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "uint32 samplingRate() const", asMETHOD(BindType, samplingRate), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setSamplingRate(uint32)", asMETHOD(BindType, setSamplingRate), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "uint32 samples() const", asMETHOD(BindType, samples), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 lengthSample() const", asMETHOD(BindType, lengthSample), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSec() const", asMETHOD(BindType, lengthSec), asCALL_THISCALL); assert(r >= 0);
		
		// Array functions

		//void swap(Wave& other)
		//append
		//remove_at
		//reverse
		//rotate
		//slice
		//saveWAVE
	}
}
