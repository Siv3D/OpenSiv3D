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

		Wave render(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity, Arg::sampleRate_<uint32> sampleRate, double globalGain);

		Wave renderMIDI(FilePathView path, Arg::sampleRate_<uint32> _sampleRate, const Duration& tail, std::array<Array<MIDINote>, 16>& midiScore);

		Wave renderMIDI(IReader& reader, Arg::sampleRate_<uint32> _sampleRate, const Duration& tail, std::array<Array<MIDINote>, 16>& midiScore);

	private:

		bool load(const Blob& blob);

		tsf* m_font = nullptr;
	};
}
