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

# include <Siv3D/Wave.hpp>
# include "DynamicAudioSource.hpp"

namespace s3d
{
	class DynamicAudioInstance : public SoLoud::AudioSourceInstance
	{
	public:

		DynamicAudioInstance(DynamicAudioSource* aParent)
		{
			mParent = aParent;
			mChannels = 2;
		}

		~DynamicAudioInstance() override
		{

		}

		unsigned int getAudio(float* aBuffer, unsigned int aSamplesToRead, unsigned int) override
		{
			mParent->m_pAudioStream->getAudio(aBuffer, aBuffer + aSamplesToRead, aSamplesToRead);

			return aSamplesToRead;
		}

		// Has the stream ended?
		bool hasEnded() override
		{
			return mParent->m_pAudioStream->hasEnded();
		}
		
		// Seek to certain place in the stream. Base implementation is generic "tape" seek (and slow).
		//SoLoud::result seek(SoLoud::time aSeconds, float* mScratch, unsigned int mScratchSize) override;
		
		// Rewind stream. Base implementation returns NOT_IMPLEMENTED, meaning it can't rewind.
		SoLoud::result rewind() override
		{
			mParent->m_pAudioStream->rewind();

			return 0;
		}

	private:

		DynamicAudioSource* mParent;
	};

	DynamicAudioSource::DynamicAudioSource(const std::shared_ptr<IAudioStream>& pAudioStream, const uint32 sampleRate)
		: m_pAudioStream{ pAudioStream }
	{
		mChannels = 2;
		mBaseSamplerate = static_cast<float>(sampleRate);
	}

	DynamicAudioSource::~DynamicAudioSource()
	{
		stop();
	}

	SoLoud::AudioSourceInstance* DynamicAudioSource::createInstance()
	{
		return new DynamicAudioInstance(this);
	}
}
