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

# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/EngineLog.hpp>
# include "AudioData.hpp"
# include <ThirdParty/soloud/include/soloud_wav.h>

namespace s3d
{
	AudioData::AudioData(Null)
	{
		m_wave = Wave::Generate(SecondsF{ 0.5 }, [](double t) {
			return 0.5 * std::sin(t * Math::TwoPi) * std::sin(t * Math::TwoPi * 220.0 * (t * 4.0 + 1.0)); });

		m_wave.deinterleave();

		std::unique_ptr<SoLoud::Wav> source = std::make_unique<SoLoud::Wav>();

		if (SoLoud::SO_NO_ERROR != source->loadRawWave(&m_wave[0].left,
			static_cast<uint32>(m_wave.size() * 2), static_cast<float>(m_wave.sampleRate()),
			2, false, false))
		{
			return;
		}

		m_sampleRate	= static_cast<uint32>(source->mBaseSamplerate);
		m_lengthSample	= source->mSampleCount;
		m_audioSource	= std::move(source);

		m_initialized = true;
	}

	AudioData::AudioData(const FilePathView path)
	{

		m_initialized = true;
	}

	AudioData::~AudioData()
	{

	}

	bool AudioData::isInitialized() const noexcept
	{
		return m_initialized;
	}
}
