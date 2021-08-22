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
# include <Siv3D/GlobalAudio.hpp>
# include "ScriptArray.hpp"

namespace s3d
{
	using namespace AngelScript;

	static CScriptArray* GlobalAudioGetSamples()
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Array<float>");
		const Array<float> samples = GlobalAudio::GetSamples();

		if (void* mem = std::malloc(samples.size_bytes() + sizeof(asUINT)))
		{
			*(asUINT*)mem = static_cast<asUINT>(samples.size());
			std::memcpy(((asUINT*)mem) + 1, samples.data(), samples.size_bytes());

			const auto p = CScriptArray::Create(typeID, mem);
			std::free(mem);

			return p;
		}
		else
		{
			return nullptr;
		}
	}

	static CScriptArray* GlobalAudioBusGetSamples(size_t busIndex)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Array<float>");
		const Array<float> samples = GlobalAudio::BusGetSamples(busIndex);

		if (void* mem = std::malloc(samples.size_bytes() + sizeof(asUINT)))
		{
			*(asUINT*)mem = static_cast<asUINT>(samples.size());
			std::memcpy(((asUINT*)mem) + 1, samples.data(), samples.size_bytes());

			const auto p = CScriptArray::Create(typeID, mem);
			std::free(mem);

			return p;
		}
		else
		{
			return nullptr;
		}
	}

	void RegisterGlobalAudio(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("GlobalAudio"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("size_t GetActiveVoiceCount()", asFUNCTION(GlobalAudio::GetActiveVoiceCount), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void PauseAll()", asFUNCTION(GlobalAudio::PauseAll), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void ResumeAll()", asFUNCTION(GlobalAudio::ResumeAll), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double GetVolume()", asFUNCTION(GlobalAudio::GetVolume), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetVolume(double)", asFUNCTION(GlobalAudio::SetVolume), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void FadeVolume(double, const Duration& in)", asFUNCTION(GlobalAudio::FadeVolume), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("Array<float>@ GetSamples()", asFUNCTION(GlobalAudioGetSamples), asCALL_CDECL); assert(r >= 0);
			//GetSamples(Array<float>& in);
			
			// ...

			r = engine->RegisterGlobalFunction("Array<float>@ BusGetSamples(size_t busIndex)", asFUNCTION(GlobalAudioBusGetSamples), asCALL_CDECL); assert(r >= 0);

			// ...

			r = engine->RegisterGlobalFunction("double BusGetVolume(size_t)", asFUNCTION(GlobalAudio::BusGetVolume), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void BusSetVolume(size_t, double)", asFUNCTION(GlobalAudio::BusSetVolume), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void BusFadeVolume(size_t, double, const Duration& in)", asFUNCTION(GlobalAudio::BusFadeVolume), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void BusClearFilter(size_t, size_t)", asFUNCTION(GlobalAudio::BusClearFilter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void BusSetLowPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet = 1.0)", asFUNCTION(GlobalAudio::BusSetLowPassFilter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void BusSetHighPassFilter(size_t busIndex, size_t filterIndex, double cutoffFrequency, double resonance, double wet = 1.0)", asFUNCTION(GlobalAudio::BusSetHighPassFilter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void BusSetEchoFilter(size_t busIndex, size_t filterIndex, double delay, double decay, double wet = 1.0)", asFUNCTION(GlobalAudio::BusSetEchoFilter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void BusSetReverbFilter(size_t busIndex, size_t filterIndex, bool freeze, double roomSize, double damp, double width, double wet = 1.0)", asFUNCTION(GlobalAudio::BusSetReverbFilter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void BusSetPitchShiftFilter(size_t busIndex, size_t filterIndex, double pitchShift)", asFUNCTION(GlobalAudio::BusSetPitchShiftFilter), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("bool SupportsPitchShift()", asFUNCTION(GlobalAudio::SupportsPitchShift), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
