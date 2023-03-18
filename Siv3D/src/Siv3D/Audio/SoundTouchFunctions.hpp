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

# pragma once
# include <Siv3D/Common.hpp>

extern "C"
{
	void* soundtouch_createInstance();
	void soundtouch_destroyInstance(void* h);
	void soundtouch_setPitchSemiTones(void* h, float newPitch);
	void soundtouch_setChannels(void* h, unsigned int numChannels);
	void soundtouch_setSampleRate(void* h, unsigned int sampleRate);
	void soundtouch_putSamples(void* h, const float* samples, unsigned int numSamples);
	unsigned int soundtouch_receiveSamples(void* h, float* outBuffer,unsigned int maxSamples);
	unsigned int soundtouch_numSamples(void* h);
}

namespace s3d
{
	struct SoundTouchFunctions
	{
		decltype(soundtouch_createInstance)* p_soundtouch_createInstance = nullptr;
		decltype(soundtouch_destroyInstance)* p_soundtouch_destroyInstance = nullptr;
		decltype(soundtouch_setPitchSemiTones)* p_soundtouch_setPitchSemiTones = nullptr;
		decltype(soundtouch_setChannels)* p_soundtouch_setChannels = nullptr;
		decltype(soundtouch_setSampleRate)* p_soundtouch_setSampleRate = nullptr;
		decltype(soundtouch_putSamples)* p_soundtouch_putSamples = nullptr;
		decltype(soundtouch_receiveSamples)* p_soundtouch_receiveSamples = nullptr;
		decltype(soundtouch_numSamples)* p_soundtouch_numSamples = nullptr;
	};
}
