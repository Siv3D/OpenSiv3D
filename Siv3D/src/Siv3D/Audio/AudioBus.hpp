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
# include <array>
# include <memory>
# include <Siv3D/Common.hpp>
# include <Siv3D/Duration.hpp>
# include <ThirdParty/soloud/include/soloud.h>

namespace s3d
{
	class AudioBus
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit AudioBus(SoLoud::Soloud* soloud);

		[[nodiscard]]
		SoLoud::Bus& getBus() noexcept;

		void annexSoundHandle(SoLoud::handle handle);

		double getVolume();

		void setVolume(double volume);

		void fadeVolume(double volume, const Duration& time);

		void clearFilter(size_t filterIndex);

		void setLowPassFilter(size_t filterIndex, double cutoffFrequency, double resonance, double wet);

		void setHighPassFilter(size_t filterIndex, double cutoffFrequency, double resonance, double wet);

		void setEchoFilter(size_t filterIndex, double delay, double decay, double wet);

		void setReverbFilter(size_t filterIndex, bool freeze, double roomSize, double damp, double width, double wet);

		void setPitchShiftFilter(size_t filterIndex, double pitchShift);

	private:

		SoLoud::Bus m_bus;

		SoLoud::Soloud* m_pSoloud = nullptr;

		SoLoud::handle m_handle = 0;

		std::array<std::unique_ptr<SoLoud::Filter>, 8> m_filters;
	};
}
