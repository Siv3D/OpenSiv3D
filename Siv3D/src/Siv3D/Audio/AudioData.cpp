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
# include <ThirdParty/soloud/include/soloud_wavstream.h>

namespace s3d
{
	AudioData::AudioData(Null)
	{
		// m_wave 準備
		{
			m_wave = Wave::Generate(SecondsF{ 0.5 }, [](double t) {
				return 0.5 * std::sin(t * Math::TwoPi) * std::sin(t * Math::TwoPi * 220.0 * (t * 4.0 + 1.0)); });
		
			m_wave.deinterleave();
		}

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
		m_initialized	= true;
	}

	AudioData::AudioData(Wave&& wave, const Optional<AudioLoopTiming>& loop)
		: m_loop{ loop.has_value() }
	{
		// m_wave 準備
		{
			m_wave = std::move(wave);

			if (loop && loop->endPos && (loop->endPos < m_wave.size()))
			{
				m_wave.resize(loop->endPos);
			}

			m_wave.deinterleave();
		}

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

		if (loop)
		{
			m_loopTiming = *loop;
			m_audioSource->setLooping(true);
			m_audioSource->setLoopPoint(static_cast<double>(loop->beginPos) / m_sampleRate);
		}

		m_initialized	= true;
	}

	AudioData::AudioData(const FilePathView path)
		: m_isStreaming{ true }
	{
		std::unique_ptr<SoLoud::WavStream> source = std::make_unique<SoLoud::WavStream>();

		if (SoLoud::SO_NO_ERROR != source->load(path.narrow().c_str()))
		{
			return;
		}

		m_sampleRate	= static_cast<uint32>(source->mBaseSamplerate);
		m_lengthSample	= source->mSampleCount;
		m_audioSource	= std::move(source);
		m_initialized	= true;
	}

	AudioData::AudioData(const FilePathView path, const uint64 loopBegin)
		: m_isStreaming{ true }
	{
		std::unique_ptr<SoLoud::WavStream> source = std::make_unique<SoLoud::WavStream>();

		if (SoLoud::SO_NO_ERROR != source->load(path.narrow().c_str()))
		{
			return;
		}

		m_sampleRate	= static_cast<uint32>(source->mBaseSamplerate);
		m_lengthSample	= source->mSampleCount;
		m_audioSource	= std::move(source);

		m_loopTiming	= { loopBegin, 0 };
		m_audioSource->setLooping(true);
		m_audioSource->setLoopPoint(static_cast<float>(static_cast<double>(loopBegin) / m_sampleRate));

		m_initialized	= true;
	}

	AudioData::~AudioData() {}

	bool AudioData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	uint32 AudioData::sampleRate() const noexcept
	{
		return m_sampleRate;
	}

	uint32 AudioData::samples() const noexcept
	{
		return m_lengthSample;
	}

	const AudioLoopTiming& AudioData::loopTiming() const noexcept
	{
		return m_loopTiming;
	}

	bool AudioData::isStreaming() const noexcept
	{
		return m_isStreaming;
	}
}
