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
# include <Siv3D/Wave.hpp>
# include "ScriptArray.hpp"

# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Wave;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const BindType& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructZS(size_t num_samples, uint32 sampleRate, BindType* self)
	{
		new(self) BindType(num_samples, Arg::sampleRate = sampleRate);
	}

	static void ConstructDS(const Duration& duration, uint32 sampleRate, BindType* self)
	{
		new(self) BindType(duration, Arg::sampleRate = sampleRate);
	}

	static void ConstructZWS(size_t num_samples, const WaveSample& sample, uint32 sampleRate, BindType* self)
	{
		new(self) BindType(num_samples, sample, Arg::sampleRate = sampleRate);
	}

	static void ConstructDWS(const Duration& duration, const WaveSample& sample, uint32 sampleRate, BindType* self)
	{
		new(self) BindType(duration, sample, Arg::sampleRate = sampleRate);
	}

	static void ConstructUUDDS(int32 instrument, int32 key, const Duration& duration, double velocity, uint32 sampleRate, BindType* self)
	{
		new(self) BindType(static_cast<GMInstrument>(instrument), static_cast<uint8>(key), duration, velocity, Arg::sampleRate = sampleRate);
	}

	static void ConstructUUDDDS(int32 instrument, int32 key, const Duration& noteOn, const Duration& noteOff, double velocity, uint32 sampleRate, BindType* self)
	{
		new(self) BindType(static_cast<GMInstrument>(instrument), static_cast<uint8>(key), noteOn, noteOff, velocity, Arg::sampleRate = sampleRate);
	}

	static void ConstructA(const CScriptArray* arr, uint32 sampleRate, BindType* self)
	{
		new(self) BindType(detail::FromScriptArray<WaveSample>(arr), Arg::sampleRate = sampleRate);
	}

	static void ConstructF(const FilePath& path, int32 audioFormat, BindType* self)
	{
		new(self) BindType(path, ToEnum<AudioFormat>(static_cast<uint8>(audioFormat)));
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	static void AssignA(const CScriptArray* arr, Wave& wave)
	{
		wave.assign(detail::FromScriptArray<WaveSample>(arr));
	}

	static Wave& OpAssignA(const CScriptArray* arr, Wave& wave)
	{
		AssignA(arr, wave);
		return wave;
	}

	static bool Save(const String& path, int32 audioFormat, const Wave& wave)
	{
		return wave.save(path, ToEnum<AudioFormat>(static_cast<uint8>(audioFormat)));
	}

	static bool ConvToBool(const Wave& wave)
	{
		return static_cast<bool>(wave);
	}

	void RegisterWave(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "Wave";
			r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
			{
				r = engine->RegisterGlobalProperty("const uint32 MinSampleRate", (void*)&Wave::MinSampleRate); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const uint32 DefaultSampleRate", (void*)&Wave::DefaultSampleRate); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const uint32 MaxSampleRate", (void*)&Wave::MaxSampleRate); assert(r >= 0);
			}
			r = engine->SetDefaultNamespace(""); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Wave& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t, Arg::sampleRate_uint32 = (Arg::sampleRate = Wave::DefaultSampleRate)) explicit", asFUNCTION(ConstructZS), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Duration& in, Arg::sampleRate_uint32 = (Arg::sampleRate = Wave::DefaultSampleRate)) explicit", asFUNCTION(ConstructDS), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t, const WaveSample& in, Arg::sampleRate_uint32 = (Arg::sampleRate = Wave::DefaultSampleRate))", asFUNCTION(ConstructZWS), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Duration& in, const WaveSample& in, Arg::sampleRate_uint32 = (Arg::sampleRate = Wave::DefaultSampleRate))", asFUNCTION(ConstructDWS), asCALL_CDECL_OBJLAST); assert(r >= 0);
			//Wave(size_t num_samples, Arg::generator_<std::function<double(double)>> generator, Arg::samplingRate_<uint32> samplingRate = Arg::samplingRate_<uint32>(DefaultSamplingRate));
			//Wave(const Duration& duration, Arg::generator_<std::function<double(double)>> generator, Arg::samplingRate_<uint32> samplingRate = Arg::samplingRate_<uint32>(DefaultSamplingRate));
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Array<WaveSample>& in, Arg::sampleRate_uint32 = (Arg::sampleRate = Wave::DefaultSampleRate)) explicit", asFUNCTION(ConstructA), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, AudioFormat format = AudioFormat::Unspecified) explicit", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
			//explicit Wave(const Array<WaveSample>& samples, Arg::samplingRate_<uint32> samplingRate = Arg::samplingRate_<uint32>(DefaultSamplingRate))
			//explicit Wave(Array<WaveSample>&& samples, Arg::samplingRate_<uint32> samplingRate = Arg::samplingRate_<uint32>(DefaultSamplingRate))
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(GMInstrument instrument, int32 key, const Duration& in, double velocity = 1.0, Arg::sampleRate_uint32 = (Arg::sampleRate = Wave::DefaultSampleRate))", asFUNCTION(ConstructUUDDS), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(GMInstrument instrument, int32 key, const Duration& in, const Duration& in, double velocity = 1.0, Arg::sampleRate_uint32 = (Arg::sampleRate = Wave::DefaultSampleRate))", asFUNCTION(ConstructUUDDDS), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Wave& opAssign(const Wave& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Wave& opAssign(const Array<WaveSample>& in)", asFUNCTION(OpAssignA), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "uint32 sampleRate() const", asMETHODPR(BindType, sampleRate, () const, uint32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void setSampleRate(uint32)", asMETHODPR(BindType, setSampleRate, (uint32), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "size_t samples() const", asMETHODPR(BindType, samples, () const, size_t), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "size_t lengthSample() const", asMETHODPR(BindType, lengthSample, () const, size_t), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "double lengthSec() const", asMETHODPR(BindType, lengthSec, () const, double), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void fillZero()", asMETHODPR(BindType, fillZero, (), void), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "Wave& swapLR()", asMETHODPR(BindType, swapLR, (), Wave&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Wave& removeSilenceFromBeginning()", asMETHODPR(BindType, removeSilenceFromBeginning, (), Wave&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Wave& removeSilenceFromEnd()", asMETHODPR(BindType, removeSilenceFromEnd, (), Wave&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Wave& fadeIn(size_t)", asMETHODPR(BindType, fadeIn, (size_t), Wave&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Wave& fadeOut(size_t)", asMETHODPR(BindType, fadeOut, (size_t), Wave&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void deinterleave()", asMETHODPR(BindType, deinterleave, (), void), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool save(const String& in, AudioFormat format = AudioFormat::Unspecified)", asFUNCTION(Save), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool saveWithDialog()", asMETHODPR(BindType, saveWithDialog, () const, bool), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void assign(const Wave& in)", asMETHODPR(BindType, assign, (const Wave&), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void assign(const Array<WaveSample>& in)", asFUNCTION(AssignA), asCALL_CDECL_OBJLAST); assert(r >= 0);

			// at
			r = engine->RegisterObjectMethod(TypeName, "WaveSample& at(size_t index)", asMETHODPR(BindType, at, (size_t)&, WaveSample&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "const WaveSample& at(size_t index) const", asMETHODPR(BindType, at, (size_t) const&, const WaveSample&), asCALL_THISCALL); assert(r >= 0);

			// []
			r = engine->RegisterObjectMethod(TypeName, "WaveSample& opIndex(size_t index)", asMETHODPR(BindType, operator[], (size_t)&, WaveSample&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "const WaveSample& opIndex(size_t index) const", asMETHODPR(BindType, operator[], (size_t) const&, const WaveSample&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void push_front(const WaveSample& in)", asMETHODPR(BindType, push_front, (const WaveSample&), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void push_back(const WaveSample& in)", asMETHODPR(BindType, push_back, (const WaveSample&), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void pop_front()", asMETHOD(BindType, pop_front), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void pop_front_N(size_t)", asMETHODPR(BindType, pop_front_N, (size_t), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void pop_back()", asMETHOD(BindType, pop_back), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void pop_back_N(size_t)", asMETHODPR(BindType, pop_back_N, (size_t), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "Wave& opShl(const WaveSample& in)", asMETHODPR(BindType, operator <<, (const WaveSample&), Wave&), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "WaveSample& front()", asMETHODPR(BindType, front, (), WaveSample&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "const WaveSample& front() const", asMETHODPR(BindType, front, () const, const WaveSample&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "WaveSample& back()", asMETHODPR(BindType, back, (), WaveSample&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "const WaveSample& back() const", asMETHODPR(BindType, back, () const, const WaveSample&), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool empty() const", asMETHODPR(BindType, empty, () const, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHODPR(BindType, empty, () const, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "size_t size_bytes() const", asMETHODPR(BindType, size_bytes, () const, size_t), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "size_t size() const", asMETHODPR(BindType, size, () const, size_t), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "size_t max_size() const", asMETHODPR(BindType, max_size, () const, size_t), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void reserve(size_t)", asMETHODPR(BindType, reserve, (size_t), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "size_t capacity() const", asMETHODPR(BindType, capacity, () const, size_t), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void shrink_to_fit()", asMETHOD(BindType, shrink_to_fit), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHOD(BindType, clear), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void release()", asMETHOD(BindType, release), asCALL_THISCALL); assert(r >= 0);

			// ...
		}
	}
}
