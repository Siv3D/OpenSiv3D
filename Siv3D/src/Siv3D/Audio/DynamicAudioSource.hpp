//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/IAudioStream.hpp>
# include <ThirdParty/soloud/include/soloud.h>

namespace s3d
{
	class DynamicAudioSource : public SoLoud::AudioSource
	{
	public:

		DynamicAudioSource(const std::shared_ptr<IAudioStream>& pAudioStream, uint32 sampleRate);
		
		virtual ~DynamicAudioSource();

		virtual SoLoud::AudioSourceInstance* createInstance();

		std::shared_ptr<IAudioStream> m_pAudioStream;
	};
}
