//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Wave.hpp"
# include "GMInstrument.hpp"
# include "MIDINote.hpp"

namespace s3d
{
	/// @brief サウンドフォント
	class SoundFont
	{
	public:

		SIV3D_NODISCARD_CXX20
		SoundFont() = default;

		SIV3D_NODISCARD_CXX20
		explicit SoundFont(FilePathView path);

		SIV3D_NODISCARD_CXX20
		explicit SoundFont(IReader&& reader);

		bool open(FilePathView path);

		bool open(IReader&& reader);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		Wave render(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff = SecondsF{ 1.0 }, double velocity = 1.0, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		[[nodiscard]]
		Wave renderMIDI(FilePathView path, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate, const Duration& tail = SecondsF{ 0.5 });

		[[nodiscard]]
		Wave renderMIDI(FilePathView path, const Duration& tail, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		[[nodiscard]]
		Wave renderMIDI(FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate, const Duration& tail = SecondsF{ 0.5 });

		[[nodiscard]]
		Wave renderMIDI(FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, const Duration& tail, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		[[nodiscard]]
		Wave renderMIDI(IReader& reader, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate, const Duration& tail = SecondsF{ 0.5 });

		[[nodiscard]]
		Wave renderMIDI(IReader& reader, const Duration& tail, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

		[[nodiscard]]
		Wave renderMIDI(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate, const Duration& tail = SecondsF{ 0.5 });

		[[nodiscard]]
		Wave renderMIDI(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, const Duration& tail, Arg::sampleRate_<uint32> sampleRate = Wave::DefaultSampleRate);

	private:

		class SoundFontDetail;

		std::shared_ptr<SoundFontDetail> pImpl;
	};
}
