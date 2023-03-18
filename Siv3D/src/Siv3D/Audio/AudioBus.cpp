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

# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "SoundTouchFunctions.hpp"
# include "AudioBus.hpp"
# include <ThirdParty/soloud/include/soloud_bus.h>
# include <ThirdParty/soloud/include/soloud_biquadresonantfilter.h>
# include <ThirdParty/soloud/include/soloud_echofilter.h>
# include <ThirdParty/soloud/include/soloud_freeverbfilter.h>

namespace s3d
{
	class CustomFilter;

	class CustomFilterInstance : public SoLoud::FilterInstance
	{
	private:

		enum FILTERPARAMS
		{
			WET,
			PITCH,
		};

		CustomFilter* mParent;

		const SoundTouchFunctions* m_functions = nullptr;

		void* m_leftHandle = nullptr;

		void* m_rightHandle = nullptr;

		void updatePerChannel(void* handle, float* samples, const uint32 length)
		{
			if (not m_functions)
			{
				return;
			}

			m_functions->p_soundtouch_putSamples(handle, samples, length);

			const uint32 available = m_functions->p_soundtouch_numSamples(handle);
			const uint32 readSamples = Min(length, available);
			uint32 offset = 0;

			if (available < length)
			{
				offset = (length - available);

				for (size_t i = 0; i < offset; ++i)
				{
					samples[i] = 0.0f;
				}
			}

			m_functions->p_soundtouch_receiveSamples(handle, (samples + offset), readSamples);
		}

	public:

		CustomFilterInstance(CustomFilter* aParent);

		virtual void filter(float* aBuffer, unsigned int aSamples, unsigned int, unsigned int, float, SoLoud::time aTime) override
		{
			updateParams(aTime);

			if (mParamChanged & (1 << PITCH))
			{
				m_functions->p_soundtouch_setPitchSemiTones(m_rightHandle, mParam[PITCH]);
				m_functions->p_soundtouch_setPitchSemiTones(m_leftHandle, mParam[PITCH]);
			}

			float* leftSamples = aBuffer;
			float* rightSamples = (aBuffer + aSamples);

			updatePerChannel(m_leftHandle, leftSamples, aSamples);
			updatePerChannel(m_rightHandle, rightSamples, aSamples);
		}

		virtual ~CustomFilterInstance() override
		{
			if (m_leftHandle)
			{
				m_functions->p_soundtouch_destroyInstance(m_leftHandle);
				m_leftHandle = nullptr;
			}

			if (m_rightHandle)
			{
				m_functions->p_soundtouch_destroyInstance(m_rightHandle);
				m_rightHandle = nullptr;
			}
		}
	};

	class CustomFilter : public SoLoud::Filter
	{
	public:

		enum FILTERPARAMS
		{
			WET,
			PITCH,
		};

		float m_pitch = 0.0f;

		CustomFilter()
		{
			setParams(0.0f);
		}

		virtual ~CustomFilter() override {}

		virtual CustomFilterInstance* createInstance() override
		{
			return new CustomFilterInstance(this);
		}

		virtual int getParamCount() override
		{
			return 2;
		}

		virtual const char* getParamName(unsigned int aParamIndex) override
		{
			if (aParamIndex > 1)
				return 0;
			const char* names[2] = {
				"Wet",
				"Pitch",
			};
			return names[aParamIndex];
		}

		virtual unsigned int getParamType(unsigned int) override
		{
			return FLOAT_PARAM;
		}

		virtual float getParamMax(unsigned int aParamIndex) override
		{
			switch (aParamIndex)
			{
			case PITCH: return 12.0f;
			}
			return 0;
		}

		virtual float getParamMin(unsigned int aParamIndex) override
		{
			switch (aParamIndex)
			{
			case PITCH: return -12.0f;
			}
			return 0;
		}

		SoLoud::result setParams(float pitch)
		{
			if ((pitch < -12.0f) || (12.0f < pitch))
			{
				return SoLoud::INVALID_PARAMETER;
			}

			m_pitch = pitch;
			return 0;
		}
	};

	CustomFilterInstance::CustomFilterInstance(CustomFilter* aParent)
	{
		mParent = aParent;
		initParams(2);
		mParam[PITCH] = aParent->m_pitch;
		const uint32 inputSampleRate = 44100;

		m_functions = SIV3D_ENGINE(Audio)->getSoundTouchFunctions();
		
		if (not m_functions)
		{
			return;
		}

		m_leftHandle = m_functions->p_soundtouch_createInstance();
		m_rightHandle = m_functions->p_soundtouch_createInstance();

		m_functions->p_soundtouch_setSampleRate(m_leftHandle, inputSampleRate);
		m_functions->p_soundtouch_setChannels(m_leftHandle, 1);
		m_functions->p_soundtouch_setPitchSemiTones(m_leftHandle, mParam[PITCH]);

		m_functions->p_soundtouch_setSampleRate(m_rightHandle, inputSampleRate);
		m_functions->p_soundtouch_setChannels(m_rightHandle, 1);
		m_functions->p_soundtouch_setPitchSemiTones(m_rightHandle, mParam[PITCH]);

		Array<float> blank(inputSampleRate / 10 * 2);
		m_functions->p_soundtouch_putSamples(m_leftHandle, blank.data(), static_cast<uint32>(blank.size()));
		m_functions->p_soundtouch_putSamples(m_rightHandle, blank.data(), static_cast<uint32>(blank.size()));
	}
}


namespace s3d
{
	AudioBus::AudioBus(SoLoud::Soloud* pSoloud)
		: m_pSoloud{ pSoloud }
	{
		m_bus.setVisualizationEnable(true);

		m_handle = pSoloud->play(m_bus);
	}

	SoLoud::Bus& AudioBus::getBus() noexcept
	{
		return m_bus;
	}

	void AudioBus::annexSoundHandle(const SoLoud::handle handle)
	{
		m_bus.annexSound(handle);
	}

	double AudioBus::getVolume()
	{
		return m_pSoloud->getVolume(m_handle);
	}

	void AudioBus::setVolume(const double volume)
	{
		m_pSoloud->setVolume(m_handle, static_cast<float>(volume));
	}

	void AudioBus::fadeVolume(const double volume, const Duration& time)
	{
		m_pSoloud->fadeVolume(m_handle, static_cast<float>(volume), time.count());
	}

	void AudioBus::clearFilter(const size_t filterIndex)
	{
		if (not m_filters[filterIndex])
		{
			return;
		}

		m_bus.setFilter(static_cast<uint32>(filterIndex), nullptr);

		m_filters[filterIndex].reset();
	}

	void AudioBus::setLowPassFilter(const size_t filterIndex, const double cutoffFrequency, const double resonance, const double wet)
	{
		if (not m_filters[filterIndex])
		{
			auto filter = std::make_unique<SoLoud::BiquadResonantFilter>();
			filter->setParams(SoLoud::BiquadResonantFilter::LOWPASS,
				static_cast<float>(cutoffFrequency),
				static_cast<float>(resonance));
			m_filters[filterIndex] = std::move(filter);
			m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());
		}
		else if (auto p = dynamic_cast<SoLoud::BiquadResonantFilter*>(m_filters[filterIndex].get()))
		{
			p->setParams(SoLoud::BiquadResonantFilter::LOWPASS,
				static_cast<float>(cutoffFrequency),
				static_cast<float>(resonance));

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::BiquadResonantFilter::TYPE,
				SoLoud::BiquadResonantFilter::LOWPASS);

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::BiquadResonantFilter::FREQUENCY,
				static_cast<float>(cutoffFrequency));

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::BiquadResonantFilter::RESONANCE,
				static_cast<float>(resonance));
		}
		else
		{
			m_bus.setFilter(static_cast<uint32>(filterIndex), nullptr);

			auto filter = std::make_unique<SoLoud::BiquadResonantFilter>();
			filter->setParams(SoLoud::BiquadResonantFilter::LOWPASS,
				static_cast<float>(cutoffFrequency),
				static_cast<float>(resonance));
			m_filters[filterIndex] = std::move(filter);
			m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());
		}

		m_pSoloud->setFilterParameter(m_handle,
			static_cast<uint32>(filterIndex),
			SoLoud::BiquadResonantFilter::WET,
			static_cast<float>(wet));
	}

	void AudioBus::setHighPassFilter(const size_t filterIndex, const double cutoffFrequency, const double resonance, const double wet)
	{
		if (not m_filters[filterIndex])
		{
			auto filter = std::make_unique<SoLoud::BiquadResonantFilter>();
			filter->setParams(SoLoud::BiquadResonantFilter::HIGHPASS,
				static_cast<float>(cutoffFrequency),
				static_cast<float>(resonance));
			m_filters[filterIndex] = std::move(filter);
			m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());
		}
		else if (auto p = dynamic_cast<SoLoud::BiquadResonantFilter*>(m_filters[filterIndex].get()))
		{
			p->setParams(SoLoud::BiquadResonantFilter::HIGHPASS,
				static_cast<float>(cutoffFrequency),
				static_cast<float>(resonance));

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::BiquadResonantFilter::TYPE,
				SoLoud::BiquadResonantFilter::HIGHPASS);

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::BiquadResonantFilter::FREQUENCY,
				static_cast<float>(cutoffFrequency));

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::BiquadResonantFilter::RESONANCE,
				static_cast<float>(resonance));
		}
		else
		{
			m_bus.setFilter(static_cast<uint32>(filterIndex), nullptr);

			auto filter = std::make_unique<SoLoud::BiquadResonantFilter>();
			filter->setParams(SoLoud::BiquadResonantFilter::HIGHPASS,
				static_cast<float>(cutoffFrequency),
				static_cast<float>(resonance));
			m_filters[filterIndex] = std::move(filter);
			m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());
		}

		m_pSoloud->setFilterParameter(m_handle,
			static_cast<uint32>(filterIndex),
			SoLoud::BiquadResonantFilter::WET,
			static_cast<float>(wet));
	}

	void AudioBus::setEchoFilter(const size_t filterIndex, double delay, const double decay, const double wet)
	{
		delay = Max(delay, 0.0001);

		if (not m_filters[filterIndex])
		{
			auto filter = std::make_unique<SoLoud::EchoFilter>();
			filter->setParams(
				static_cast<float>(delay),
				static_cast<float>(decay));
			m_filters[filterIndex] = std::move(filter);
		}
		else if (auto p = dynamic_cast<SoLoud::EchoFilter*>(m_filters[filterIndex].get()))
		{
			p->setParams(
				static_cast<float>(delay),
				static_cast<float>(decay));
		}
		else
		{
			m_bus.setFilter(static_cast<uint32>(filterIndex), nullptr);

			auto filter = std::make_unique<SoLoud::EchoFilter>();
			filter->setParams(
				static_cast<float>(delay),
				static_cast<float>(decay));
			m_filters[filterIndex] = std::move(filter);
		}

		m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());

		m_pSoloud->setFilterParameter(m_handle,
			static_cast<uint32>(filterIndex),
			SoLoud::EchoFilter::WET,
			static_cast<float>(wet));
	}

	void AudioBus::setReverbFilter(const size_t filterIndex, const bool freeze, const double roomSize, const double damp, const double width, const double wet)
	{
		if (not m_filters[filterIndex])
		{
			auto filter = std::make_unique<SoLoud::FreeverbFilter>();
			filter->setParams(
				static_cast<float>(freeze),
				static_cast<float>(roomSize),
				static_cast<float>(damp),
				static_cast<float>(width));
			m_filters[filterIndex] = std::move(filter);
			m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());
		}
		else if (auto p = dynamic_cast<SoLoud::FreeverbFilter*>(m_filters[filterIndex].get()))
		{
			p->setParams(
				static_cast<float>(freeze),
				static_cast<float>(roomSize),
				static_cast<float>(damp),
				static_cast<float>(width));

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::FreeverbFilter::FREEZE,
				static_cast<float>(freeze));

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::FreeverbFilter::ROOMSIZE,
				static_cast<float>(roomSize));

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::FreeverbFilter::DAMP,
				static_cast<float>(damp));

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				SoLoud::FreeverbFilter::WIDTH,
				static_cast<float>(width));
		}
		else
		{
			m_bus.setFilter(static_cast<uint32>(filterIndex), nullptr);

			auto filter = std::make_unique<SoLoud::FreeverbFilter>();
			filter->setParams(
				static_cast<float>(freeze),
				static_cast<float>(roomSize),
				static_cast<float>(damp),
				static_cast<float>(width));
			m_filters[filterIndex] = std::move(filter);
			m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());
		}

		m_pSoloud->setFilterParameter(m_handle,
			static_cast<uint32>(filterIndex),
			SoLoud::FreeverbFilter::WET,
			static_cast<float>(wet));
	}

	void AudioBus::setPitchShiftFilter(size_t filterIndex, double pitchShift)
	{
		if (not m_filters[filterIndex])
		{
			auto filter = std::make_unique<CustomFilter>();
			filter->setParams(
				static_cast<float>(pitchShift));
			m_filters[filterIndex] = std::move(filter);
			m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());
		}
		else if (auto p = dynamic_cast<CustomFilter*>(m_filters[filterIndex].get()))
		{
			p->setParams(
				static_cast<float>(pitchShift));

			m_pSoloud->setFilterParameter(m_handle,
				static_cast<uint32>(filterIndex),
				CustomFilter::PITCH,
				static_cast<float>(pitchShift));
		}
		else
		{
			m_bus.setFilter(static_cast<uint32>(filterIndex), nullptr);

			auto filter = std::make_unique<CustomFilter>();
			filter->setParams(
				static_cast<float>(pitchShift));
			m_filters[filterIndex] = std::move(filter);
			m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());
		}

		m_pSoloud->setFilterParameter(m_handle,
			static_cast<uint32>(filterIndex),
			CustomFilter::WET,
			1.0f);
	}
}
