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

# include <Siv3D/AudioFormat/MIDIDecoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/SoundFont/ISoundFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	StringView MIDIDecoder::name() const
	{
		return U"MIDI"_sv;
	}

	bool MIDIDecoder::isHeader(const uint8(&bytes)[48]) const
	{
		static constexpr uint8 head[] = { 0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, 0x00 };

		return (std::memcmp(bytes, head, sizeof(head)) == 0)
			&& ((bytes[9] == 0x00) || (bytes[9] == 0x01) || (bytes[9] == 0x02));
	}

	const Array<String>& MIDIDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"mid" };

		return extensions;
	}

	AudioFormat MIDIDecoder::audioFormat() const noexcept
	{
		return AudioFormat::MIDI;
	}

	Wave MIDIDecoder::decode(const FilePathView path) const
	{
		std::array<Array<MIDINote>, 16> _unused;
		return SIV3D_ENGINE(SoundFont)->renderMIDI(path, _unused, Wave::DefaultSampleRate, SecondsF{ 0.5 });
	}

	Wave MIDIDecoder::decode(const FilePathView path, std::array<Array<MIDINote>, 16>& midiScore) const
	{
		return SIV3D_ENGINE(SoundFont)->renderMIDI(path, midiScore, Wave::DefaultSampleRate, SecondsF{ 0.5 });
	}

	Wave MIDIDecoder::decode(IReader& reader, [[maybe_unused]] const FilePathView pathHint) const
	{
		std::array<Array<MIDINote>, 16> _unused;
		return SIV3D_ENGINE(SoundFont)->renderMIDI(reader, _unused, Wave::DefaultSampleRate, SecondsF{ 0.5 });
	}

	Wave MIDIDecoder::decode(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, [[maybe_unused]] const FilePathView pathHint) const
	{
		return SIV3D_ENGINE(SoundFont)->renderMIDI(reader, midiScore, Wave::DefaultSampleRate, SecondsF{ 0.5 });
	}
}
