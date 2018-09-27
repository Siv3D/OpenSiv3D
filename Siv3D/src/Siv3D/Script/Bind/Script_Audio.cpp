//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Audio.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Audio;

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

	static void ConstructS(const FilePath& path, BindType* self)
	{
		new(self) BindType(path);
	}

	static void Destruct(BindType* self)
	{
		self->~BindType();
	}

	static bool ConvToBool(const Audio& audio)
	{
		return !audio.isEmpty();
	}

	void RegisterAudio(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Audio";

		int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Audio& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Wave& in)", asFUNCTION(ConstructW), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in)", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		// Ctrs
		// ...

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);


		r = engine->RegisterObjectMethod(TypeName, "Audio& opAssign(const Audio& in)", asMETHODPR(BindType, operator =, (const BindType&), BindType&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void release()", asMETHOD(BindType, release), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asFUNCTION(ConvToBool), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHOD(BindType, isEmpty), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 id() const", asMETHOD(BindType, id), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const Texture& in)", asMETHOD(BindType, operator ==), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "uint32 samplingRate() const", asMETHOD(BindType, samplingRate), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "uint32 samples() const", asMETHOD(BindType, samples), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setLoop(bool) const", asMETHODPR(BindType, setLoop, (bool), void), asCALL_THISCALL); assert(r >= 0);

		//void setLoop(Arg::loopBegin_<uint64> loopBegin);
		//void setLoop(Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);
		//void setLoop(Arg::loopBegin_<Duration> loopBegin);
		//void setLoop(Arg::loopBegin_<Duration> loopBegin, Arg::loopEnd_<Duration> loopEnd);

		r = engine->RegisterObjectMethod(TypeName, "bool play(const Duration& in = Duration(0.0)) const", asMETHOD(BindType, play), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void pause(const Duration& in = Duration(0.0)) const", asMETHOD(BindType, play), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void stop(const Duration& in = Duration(0.0)) const", asMETHOD(BindType, play), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void playOneShot(double volume = 1.0, double pitch = 1.0) const", asMETHOD(BindType, playOneShot), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void stopAllShots() const", asMETHOD(BindType, stopAllShots), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool isPlaying() const", asMETHOD(BindType, isPlaying), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool isPaused() const", asMETHOD(BindType, isPaused), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 posSample() const", asMETHOD(BindType, posSample), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double posSec() const", asMETHOD(BindType, posSec), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 streamPosSample() const", asMETHOD(BindType, streamPosSample), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int64 samplesPlayed() const", asMETHOD(BindType, samplesPlayed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double lengthSec() const", asMETHOD(BindType, lengthSec), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "const Wave& getWave() const", asMETHOD(BindType, getWave), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void setPosSec(double) const", asMETHOD(BindType, setPosSec), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setPosSample(int64) const", asMETHOD(BindType, setPosSample), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setVolume(double) const", asMETHOD(BindType, setVolume), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setVolumeLR(double, double) const", asMETHOD(BindType, setVolumeLR), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setVolume_dB(double) const", asMETHOD(BindType, setVolume_dB), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setVolumeLR_dB(double, double) const", asMETHOD(BindType, setVolumeLR_dB), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "void setSpeed(double) const", asMETHOD(BindType, setSpeed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "void setSpeedBySemitone(int32) const", asMETHOD(BindType, setSpeedBySemitone), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double getSpeed() const", asMETHOD(BindType, getSpeed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double getMinSpeed() const", asMETHOD(BindType, getMinSpeed), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "double getMaxSpeed() const", asMETHOD(BindType, getMaxSpeed), asCALL_THISCALL); assert(r >= 0);

	}
}
