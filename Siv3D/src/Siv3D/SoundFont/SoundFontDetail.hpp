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
# include <Siv3D/SoundFont.hpp>

struct tsf;

namespace s3d
{
	class SoundFont::SoundFontDetail
	{
	public:

		~SoundFontDetail();

		bool open(const FilePathView path);

		bool open(IReader& reader);

		void close();

		bool isOpen() const noexcept;

		Wave render(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity, Arg::samplingRate_<uint32> samplingRate, double globalGain);

		Wave renderMIDI(FilePathView path, Arg::samplingRate_<uint32> _samplingRate, const Duration& tail, std::array<Array<MIDINote>, 16>& midiScore);

		Wave renderMIDI(IReader& reader, Arg::samplingRate_<uint32> _samplingRate, const Duration& tail, std::array<Array<MIDINote>, 16>& midiScore);

	private:

		bool load(const Blob& blob);

		tsf* m_font = nullptr;
	};
}
