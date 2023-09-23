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
# include <Siv3D/Audio.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Audio;

	static void ConstructAF(uint8* self)
	{
		new(self) uint8(0);
	}

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const BindType& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructW(const Wave& wave, BindType* self)
	{
		new(self) BindType(wave);
	}

	static void ConstructWL(const Wave& wave, bool loop, BindType* self)
	{
		new(self) BindType(wave, Loop{ loop });
	}

	static void ConstructS(const FilePath& path, BindType* self)
	{
		new(self) BindType(path);
	}

	static void ConstructSL(const FilePath& path, bool loop, BindType* self)
	{
		new(self) BindType(path, Loop{ loop });
	}

	static void ConstructAS(uint8, const FilePath& path, BindType* self)
	{
		new(self) BindType(Audio::Stream, path);
	}

	static void ConstructASL(uint8, const FilePath& path, bool loop, BindType* self)
	{
		new(self) BindType(Audio::Stream, path, Loop{ loop });
	}

	static void ConstructUUDDS(int32 instrument, int32 key, const Duration& duration, double velocity, uint32 sampleRate, BindType* self)
	{
		new(self) BindType(static_cast<GMInstrument>(instrument), static_cast<uint8>(key), duration, velocity, Arg::sampleRate = sampleRate);
	}

	static void ConstructUUDDDS(int32 instrument, int32 key, const Duration& noteOn, const Duration& noteOff, double velocity, uint32 sampleRate, BindType* self)
	{
		new(self) BindType(static_cast<GMInstrument>(instrument), static_cast<uint8>(key), noteOn, noteOff, velocity, Arg::sampleRate = sampleRate);
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	static void Release(BindType& a)
	{
		a.release();
	}

	static bool ConvToBool(const BindType& a)
	{
		return static_cast<bool>(a);
	}

	static bool IsEmpty(const BindType& a)
	{
		return a.isEmpty();
	}

	static bool Equals(const BindType& other, const BindType& a)
	{
		return (a == other);
	}

	void RegisterAudio(asIScriptEngine* engine)
	{
		static const uint8 AudioFileStreamingPlaceholder = 0;
		constexpr char TypeName[] = "Audio";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour("AudioFileStreaming", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructAF), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const AudioFileStreaming Stream", (void*)&AudioFileStreamingPlaceholder); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Audio& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Wave& in) explicit", asFUNCTION(ConstructW), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Wave& in, bool loop)", asFUNCTION(ConstructWL), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in) explicit", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, bool loop)", asFUNCTION(ConstructSL), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(AudioFileStreaming, const String& in) explicit", asFUNCTION(ConstructAS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(AudioFileStreaming, const String& in, bool loop)", asFUNCTION(ConstructASL), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(GMInstrument instrument, int32 key, const Duration& in, double velocity = 1.0, Arg::sampleRate_uint32 = (Arg::sampleRate = Wave::DefaultSampleRate))", asFUNCTION(ConstructUUDDS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(GMInstrument instrument, int32 key, const Duration& in, const Duration& in, double velocity = 1.0, Arg::sampleRate_uint32 = (Arg::sampleRate = Wave::DefaultSampleRate))", asFUNCTION(ConstructUUDDDS), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Audio& opAssign(const Audio& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void release()", asFUNCTION(Release), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asFUNCTION(IsEmpty), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Texture& in)", asFUNCTION(Equals), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isStreaming() const", asMETHODPR(BindType, isStreaming, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 sampleRate() const", asMETHODPR(BindType, sampleRate, () const, uint32), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t samples() const", asMETHODPR(BindType, samples, () const, size_t), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSec() const", asMETHODPR(BindType, lengthSec, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 samplesPlayed() const", asMETHODPR(BindType, samplesPlayed, () const, int64), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isActive() const", asMETHODPR(BindType, isActive, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isPlaying() const", asMETHODPR(BindType, isPlaying, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isPaused() const", asMETHODPR(BindType, isPaused, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isLoop() const", asMETHODPR(BindType, isLoop, () const, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void setLoop() const", asMETHODPR(BindType, setLoop, (bool) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setLoopPoint(uint64) const", asMETHODPR(BindType, setLoopPoint, (uint64) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setLoopPoint(const Duration& in) const", asMETHODPR(BindType, setLoopPoint, (const Duration&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void play(MixBus busIndex = MixBus0) const", asMETHODPR(BindType, play, (MixBus) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void play(const Duration& in, MixBus busIndex = MixBus0) const", asMETHODPR(BindType, play, (const Duration&, MixBus) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void play(MixBus busIndex, const Duration& in) const", asMETHODPR(BindType, play, (MixBus, const Duration&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void pause() const", asMETHODPR(BindType, pause, () const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pause(const Duration& in) const", asMETHODPR(BindType, pause, (const Duration&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void stop() const", asMETHODPR(BindType, stop, () const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void stop(const Duration& in) const", asMETHODPR(BindType, stop, (const Duration&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void playOneShot(double volume = 1.0, double pan = 0.0, double speed = 1.0, MixBus busIndex = MixBus0) const", asMETHODPR(BindType, playOneShot, (double, double, double, MixBus) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void playOneShot(MixBus busIndex, double volume = 1.0, double pan = 0.0, double speed = 1.0) const", asMETHODPR(BindType, playOneShot, (MixBus, double, double, double) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void pauseAllShots() const", asMETHODPR(BindType, pauseAllShots, () const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pauseAllShots(const Duration& in) const", asMETHODPR(BindType, pauseAllShots, (const Duration&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void resumeAllShots() const", asMETHODPR(BindType, resumeAllShots, () const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void resumeAllShots(const Duration& in) const", asMETHODPR(BindType, resumeAllShots, (const Duration&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void stopAllShots() const", asMETHODPR(BindType, stopAllShots, () const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void stopAllShots(const Duration& in) const", asMETHODPR(BindType, stopAllShots, (const Duration&) const, void), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "int64 posSample() const", asMETHODPR(BindType, posSample, () const, int64), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double posSec() const", asMETHODPR(BindType, posSec, () const, double), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void seekSamples(size_t) const", asMETHODPR(BindType, seekSamples, (size_t) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void seekTime(double) const", asMETHODPR(BindType, seekTime, (double) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void seekTime(const Duration& in) const", asMETHODPR(BindType, seekTime, (const Duration&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "size_t loopCount() const", asMETHODPR(BindType, loopCount, () const, size_t), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double getVolume() const", asMETHODPR(BindType, getVolume, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Audio& setVolume(double) const", asMETHODPR(BindType, setVolume, (double) const, const Audio&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Audio& fadeVolume(double, const Duration& in) const", asMETHODPR(BindType, fadeVolume, (double, const Duration&) const, const Audio&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double getPan() const", asMETHODPR(BindType, getPan, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Audio& setPan(double) const", asMETHODPR(BindType, setPan, (double) const, const Audio&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Audio& fadePan(double, const Duration& in) const", asMETHODPR(BindType, fadePan, (double, const Duration&) const, const Audio&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "double getSpeed() const", asMETHODPR(BindType, getSpeed, () const, double), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Audio& setSpeed(double) const", asMETHODPR(BindType, setSpeed, (double) const, const Audio&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Audio& fadeSpeed(double, const Duration& in) const", asMETHODPR(BindType, fadeSpeed, (double, const Duration&) const, const Audio&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "const Audio& setSpeedBySemitone(int32) const", asMETHODPR(BindType, setSpeedBySemitone, (int32) const, const Audio&), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Audio& fadeSpeedBySemitone(int32, const Duration& in) const", asMETHODPR(BindType, fadeSpeedBySemitone, (int32, const Duration&) const, const Audio&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void swap(Audio& inout)", asMETHODPR(BindType, swap, (Audio&), void), asCALL_THISCALL); assert(r >= 0);
	}
}
