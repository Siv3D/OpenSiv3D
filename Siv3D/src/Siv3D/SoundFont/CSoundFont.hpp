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

		Wave render(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity, Arg::sampleRate_<uint32> sampleRate) override;

		Wave renderMIDI(FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, Arg::sampleRate_<uint32> sampleRate, const Duration& tail) override;

		Wave renderMIDI(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, Arg::sampleRate_<uint32> sampleRate, const Duration& tail) override;

	private:

		bool m_hasGMGSx = false;
	};
}
