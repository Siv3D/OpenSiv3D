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

# include <Siv3D/SoundFont.hpp>
# include "SoundFontDetail.hpp"

namespace s3d
{
	SoundFont::SoundFont(const FilePathView path)
		: pImpl{ std::make_shared<SoundFontDetail>() }
	{
		pImpl->open(path);
	}

	SoundFont::SoundFont(IReader&& reader)
		: pImpl{ std::make_shared<SoundFontDetail>() }
	{
		pImpl->open(reader);
	}

	bool SoundFont::open(const FilePathView path)
	{
		return pImpl->open(path);
	}

	bool SoundFont::open(IReader&& reader)
	{
		return pImpl->open(reader);
	}

	void SoundFont::close()
	{
		pImpl->close();
	}

	bool SoundFont::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	SoundFont::operator bool() const noexcept
	{
		return pImpl->isOpen();
	}

	Wave SoundFont::render(const GMInstrument instrument, const uint8 key, const Duration& noteOn, const Duration& noteOff, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
	{
		return pImpl->render(instrument, key, noteOn, noteOff, velocity, sampleRate, 0.0);
	}

	Wave SoundFont::renderMIDI(const FilePathView path, const Arg::sampleRate_<uint32> sampleRate, const Duration& tail)
	{
		std::array<Array<MIDINote>, 16> midiScore;
		return pImpl->renderMIDI(path, sampleRate, tail, midiScore);
	}

	Wave SoundFont::renderMIDI(const FilePathView path, const Duration& tail, const Arg::sampleRate_<uint32> sampleRate)
	{
		std::array<Array<MIDINote>, 16> midiScore;
		return pImpl->renderMIDI(path, sampleRate, tail, midiScore);
	}

	Wave SoundFont::renderMIDI(const FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, const Arg::sampleRate_<uint32> sampleRate, const Duration& tail)
	{
		midiScore.fill({});
		return pImpl->renderMIDI(path, sampleRate, tail, midiScore);
	}

	Wave SoundFont::renderMIDI(const FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, const Duration& tail, const Arg::sampleRate_<uint32> sampleRate)
	{
		midiScore.fill({});
		return pImpl->renderMIDI(path, sampleRate, tail, midiScore);
	}

	Wave SoundFont::renderMIDI(IReader& reader, const Arg::sampleRate_<uint32> sampleRate, const Duration& tail)
	{
		std::array<Array<MIDINote>, 16> midiScore;
		return pImpl->renderMIDI(reader, sampleRate, tail, midiScore);
	}

	Wave SoundFont::renderMIDI(IReader& reader, const Duration& tail, const Arg::sampleRate_<uint32> sampleRate)
	{
		std::array<Array<MIDINote>, 16> midiScore;
		return pImpl->renderMIDI(reader, sampleRate, tail, midiScore);
	}

	Wave SoundFont::renderMIDI(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, const Arg::sampleRate_<uint32> sampleRate, const Duration& tail)
	{
		midiScore.fill({});
		return pImpl->renderMIDI(reader, sampleRate, tail, midiScore);
	}

	Wave SoundFont::renderMIDI(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, const Duration& tail, const Arg::sampleRate_<uint32> sampleRate)
	{
		midiScore.fill({});
		return pImpl->renderMIDI(reader, sampleRate, tail, midiScore);
	}
}
