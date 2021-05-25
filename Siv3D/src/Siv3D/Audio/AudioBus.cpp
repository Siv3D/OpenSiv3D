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

# include "AudioBus.hpp"
# include <ThirdParty/soloud/include/soloud_bus.h>
# include <ThirdParty/soloud/include/soloud_biquadresonantfilter.h>
# include <ThirdParty/soloud/include/soloud_echofilter.h>
# include <ThirdParty/soloud/include/soloud_freeverbfilter.h>

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
		}
		else if (auto p = dynamic_cast<SoLoud::BiquadResonantFilter*>(m_filters[filterIndex].get()))
		{
			p->setParams(SoLoud::BiquadResonantFilter::LOWPASS,
				static_cast<float>(cutoffFrequency),
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
		}

		m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());

		m_pSoloud->setFilterParameter(m_handle,
			static_cast<uint32>(filterIndex),
			SoLoud::FreeverbFilter::WET,
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
		}
		else if (auto p = dynamic_cast<SoLoud::BiquadResonantFilter*>(m_filters[filterIndex].get()))
		{
			p->setParams(SoLoud::BiquadResonantFilter::HIGHPASS,
				static_cast<float>(cutoffFrequency),
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
		}

		m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());

		m_pSoloud->setFilterParameter(m_handle,
			static_cast<uint32>(filterIndex),
			SoLoud::FreeverbFilter::WET,
			static_cast<float>(wet));
	}

	void AudioBus::setEchoFilter(const size_t filterIndex, const double delay, const double decay, const double wet)
	{
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
			SoLoud::FreeverbFilter::WET,
			static_cast<float>(wet));
	}

	void AudioBus::setReverbFilter(const size_t filterIndex, const bool freeze, const double roomSize, const double damp, const double width, const double wet)
	{
		if (not m_filters[filterIndex])
		{
			auto filter = std::make_unique<SoLoud::FreeverbFilter>();
			filter->setParams(
				freeze,
				static_cast<float>(roomSize),
				static_cast<float>(damp),
				static_cast<float>(width));
			m_filters[filterIndex] = std::move(filter);
		}
		else
		{
			m_bus.setFilter(static_cast<uint32>(filterIndex), nullptr);

			auto filter = std::make_unique<SoLoud::FreeverbFilter>();
			filter->setParams(
				freeze,
				static_cast<float>(roomSize),
				static_cast<float>(damp),
				static_cast<float>(width));
			m_filters[filterIndex] = std::move(filter);
		}

		m_bus.setFilter(static_cast<uint32>(filterIndex), m_filters[filterIndex].get());

		m_pSoloud->setFilterParameter(m_handle,
			static_cast<uint32>(filterIndex),
			SoLoud::FreeverbFilter::WET,
			static_cast<float>(wet));
	}
}
