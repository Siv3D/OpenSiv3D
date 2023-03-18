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

extern "C"
{
	void* soundtouch_createInstance()
	{
		return nullptr;
	}

	void soundtouch_destroyInstance(void* h)
	{
		
	}
	
	void soundtouch_setPitchSemiTones(void* h, const float newPitch)
	{
		
	}
	
	void soundtouch_setChannels(void* h, const unsigned int numChannels)
	{
		
	}

	void soundtouch_setSampleRate(void* h, const unsigned int sampleRate)
	{
		
	}
	
	void soundtouch_putSamples(void* h, const float* samples, const unsigned int numSamples)
	{
		
	}
	
	unsigned int soundtouch_receiveSamples(void* h, float* outBuffer, const unsigned int maxSamples)
	{

	}
	
	unsigned int soundtouch_numSamples(void* h)
	{
	
	}
}
