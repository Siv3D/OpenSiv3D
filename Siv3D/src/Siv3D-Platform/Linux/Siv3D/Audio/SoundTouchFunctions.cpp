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

# include <soundtouch/SoundTouch.h>

extern "C"
{
	typedef struct
	{
		unsigned int magic;
		soundtouch::SoundTouch* soundTouch;
	} SoundTouchHandle;

	const unsigned int STMAGIC = 0x1770C001u;

	void* soundtouch_createInstance()
	{
		SoundTouchHandle* handle = new SoundTouchHandle;

		if (handle)
		{
			handle->magic = STMAGIC;
			handle->soundTouch = new soundtouch::SoundTouch();
			
			if (not handle->soundTouch)
			{
				delete handle;
				handle = nullptr;
			}
		}

		return static_cast<void*>(handle);
	}

	void soundtouch_destroyInstance(void* h)
	{
		SoundTouchHandle* handle = static_cast<SoundTouchHandle*>(h);
		
		if (handle->magic != STMAGIC)
		{
			return;
		}

		handle->magic = 0;

		if (handle->soundTouch)
		{
			delete handle->soundTouch;
		}
		
		handle->soundTouch = nullptr;

		delete handle;
	}
	
	void soundtouch_setPitchSemiTones(void* h, const float newPitch)
	{
		SoundTouchHandle* handle = static_cast<SoundTouchHandle*>(h);
		
		if (handle->magic != STMAGIC)
		{
			return;
		}

		handle->soundTouch->setPitchSemiTones(newPitch);
	}
	
	void soundtouch_setChannels(void* h, const unsigned int numChannels)
	{
		SoundTouchHandle* handle = static_cast<SoundTouchHandle*>(h);
		
		if (handle->magic != STMAGIC)
		{
			return;
		}

		handle->soundTouch->setChannels(numChannels);
	}

	void soundtouch_setSampleRate(void* h, const unsigned int sampleRate)
	{
		SoundTouchHandle* handle = static_cast<SoundTouchHandle*>(h);
		
		if (handle->magic != STMAGIC)
		{
			return;
		}

		handle->soundTouch->setSampleRate(sampleRate);
	}
	
	void soundtouch_putSamples(void* h, const float* samples, const unsigned int numSamples)
	{
		SoundTouchHandle* handle = static_cast<SoundTouchHandle*>(h);
		
		if (handle->magic != STMAGIC)
		{
			return;
		}

		handle->soundTouch->putSamples(samples, numSamples);
	}
	
	unsigned int soundtouch_receiveSamples(void* h, float* outBuffer, const unsigned int maxSamples)
	{
		SoundTouchHandle* handle = static_cast<SoundTouchHandle*>(h);
		
		if (handle->magic != STMAGIC)
		{
			return 0;
		}

		if (outBuffer)
		{
			return handle->soundTouch->receiveSamples(outBuffer, maxSamples);
		}
		else
		{
			return handle->soundTouch->receiveSamples(maxSamples);
		}
	}
	
	unsigned int soundtouch_numSamples(void* h)
	{
		SoundTouchHandle* handle = static_cast<SoundTouchHandle*>(h);
		
		if (handle->magic != STMAGIC)
		{
			return 0;
		}

		return handle->soundTouch->numSamples();
	}
}
