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
# include <memory>
# include "Common.hpp"
# include "Wave.hpp"
# include "GMInstrument.hpp"
# include "MIDINote.hpp"

namespace s3d
{
	class SoundFont
	{
	public:

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
		Wave render(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff = SecondsF{ 1.0 }, double velocity = 1.0, Arg::samplingRate_<uint32> samplingRate = Wave::DefaultSamplingRate);

		[[nodiscard]]
		Wave renderMIDI(FilePathView path, Arg::samplingRate_<uint32> samplingRate = Wave::DefaultSamplingRate, const Duration& tail = SecondsF{ 0.5 });

		[[nodiscard]]
		Wave renderMIDI(FilePathView path, const Duration& tail, Arg::samplingRate_<uint32> samplingRate = Wave::DefaultSamplingRate);

		[[nodiscard]]
		Wave renderMIDI(FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, Arg::samplingRate_<uint32> samplingRate = Wave::DefaultSamplingRate, const Duration& tail = SecondsF{ 0.5 });

		[[nodiscard]]
		Wave renderMIDI(FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, const Duration& tail, Arg::samplingRate_<uint32> samplingRate = Wave::DefaultSamplingRate);

		[[nodiscard]]
		Wave renderMIDI(IReader& reader, Arg::samplingRate_<uint32> samplingRate = Wave::DefaultSamplingRate, const Duration& tail = SecondsF{ 0.5 });

		[[nodiscard]]
		Wave renderMIDI(IReader& reader, const Duration& tail, Arg::samplingRate_<uint32> samplingRate = Wave::DefaultSamplingRate);

		[[nodiscard]]
		Wave renderMIDI(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, Arg::samplingRate_<uint32> samplingRate = Wave::DefaultSamplingRate, const Duration& tail = SecondsF{ 0.5 });

		[[nodiscard]]
		Wave renderMIDI(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, const Duration& tail, Arg::samplingRate_<uint32> samplingRate = Wave::DefaultSamplingRate);

	private:

		class SoundFontDetail;

		std::shared_ptr<SoundFontDetail> pImpl;
	};
}
