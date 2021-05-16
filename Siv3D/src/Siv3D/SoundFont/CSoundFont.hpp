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

# pragma once
# include "ISoundFont.hpp"
# include <Siv3D/SoundFont.hpp>

namespace s3d
{
	class CSoundFont final : public ISiv3DSoundFont
	{
	public:

		CSoundFont();

		~CSoundFont() override;

		void init() override;

		Wave render(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity, Arg::samplingRate_<uint32> samplingRate) override;

		Wave renderMIDI(FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, Arg::samplingRate_<uint32> samplingRate, const Duration& tail) override;

	private:

		bool m_hasGMGSx = false;

		std::unique_ptr<SoundFont> m_GMGSx;
	};
}
