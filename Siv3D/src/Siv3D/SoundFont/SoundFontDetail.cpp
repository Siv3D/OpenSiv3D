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

# include <Siv3D/Optional.hpp>
# include <Siv3D/EngineLog.hpp>
# include "SoundFontDetail.hpp"

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)
# define TSF_IMPLEMENTATION
# include <ThirdParty/TinySoundFont/tsf.h>
#define TML_IMPLEMENTATION
# include <ThirdParty/TinySoundFont/tml.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	SoundFont::SoundFontDetail::~SoundFontDetail()
	{
		close();
	}

	bool SoundFont::SoundFontDetail::open(const FilePathView path)
	{
		close();

		return load(Blob{ path });
	}

	bool SoundFont::SoundFontDetail::open(IReader& reader)
	{
		close();

		return load(Blob{ reader });
	}

	void SoundFont::SoundFontDetail::close()
	{
		if (not m_font)
		{
			return;
		}

		::tsf_close(m_font);
		m_font = nullptr;
	}

	bool SoundFont::SoundFontDetail::isOpen() const noexcept
	{
		return (m_font != nullptr);
	}

	Wave SoundFont::SoundFontDetail::render(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity, Arg::samplingRate_<uint32> samplingRate, double globalGain)
	{
		if (not m_font)
		{
			return{};
		}

		const size_t noteOnSamples = detail::CalculateSamples(noteOn, samplingRate);
		const size_t noteOffSamples = detail::CalculateSamples(noteOff, samplingRate);
		const size_t samples = (noteOnSamples + noteOffSamples);

		Wave wave{ samples, samplingRate };

		::tsf_set_output(m_font, TSF_STEREO_INTERLEAVED, static_cast<int32>(*samplingRate), static_cast<float>(globalGain));

		::tsf_note_on(m_font, FromEnum(instrument), key, static_cast<float>(velocity));

		::tsf_render_float(m_font, &wave[0].left, static_cast<int32>(noteOnSamples), 0);

		if (noteOffSamples)
		{
			::tsf_note_off(m_font, FromEnum(instrument), key);

			::tsf_render_float(m_font, &wave[noteOnSamples].left, static_cast<int32>(noteOffSamples), 0);

			const size_t fadeOutSamples = Min<size_t>((*samplingRate / 10), noteOffSamples);

			wave.fadeOut(fadeOutSamples);
		}

		::tsf_reset(m_font);

		wave.removeSilenceFromEnd();

		return wave;
	}

	Wave SoundFont::SoundFontDetail::renderMIDI(const FilePathView path, const Arg::samplingRate_<uint32> _samplingRate, const Duration& tail, std::array<Array<MIDINote>, 16>& midiScore)
	{
		if (not m_font)
		{
			return{};
		}

		const uint32 samplingRate = *_samplingRate;
		const size_t tailSamples = detail::CalculateSamples(tail, Arg::samplingRate = samplingRate);

		tml_message* midi = ::tml_load_filename(path.narrow().c_str());
		{
			if (not midi)
			{
				return{};
			}

			::tsf_channel_set_bank_preset(m_font, 9, 128, 0);
			::tsf_set_output(m_font, TSF_STEREO_INTERLEAVED, samplingRate, 0.0f);
		}

		Wave result(Arg::samplingRate = samplingRate);
		{
			size_t timeMillisec = 0;

			for (tml_message* currentMessage = midi; currentMessage; currentMessage = currentMessage->next)
			{
				timeMillisec = currentMessage->time;
			}

			const size_t reserveSamples = ((timeMillisec + tailSamples + 100) * samplingRate / 1000);
			result.reserve(reserveSamples);
		}

		{
			Array<std::array<Optional<int32>, 128>> tmpNotes(16);
			double timeMillisec = 0.0;
			int32 posSample = 0;

			for (tml_message* currentMessage = midi; currentMessage;)
			{
				constexpr int32 SampleBlock = TSF_RENDER_EFFECTSAMPLEBLOCK;

				for (timeMillisec += SampleBlock * (1000.0 / samplingRate); currentMessage && (timeMillisec >= currentMessage->time); currentMessage = currentMessage->next)
				{
					if ((currentMessage->type == 0x80) || (currentMessage->type == 0x90))
					{
						const uint32 ch = currentMessage->channel;
						const uint32 key = currentMessage->key & 0x7F;
						const bool on = ((currentMessage->type == 0x90) && (currentMessage->velocity != 0x00));

						if (on)
						{
							LOG_TRACE(U"on");
							if (not tmpNotes[ch][key])
							{
								tmpNotes[ch][key] = posSample;
							}
						}
						else
						{
							LOG_TRACE(U"off");
							if (tmpNotes[ch][key])
							{
								MIDINote midiNote;
								midiNote.key = key;
								midiNote.startMillisec = *tmpNotes[ch][key];
								midiNote.lengthMillisec = (posSample - *tmpNotes[ch][key]);
								midiScore[ch].push_back(midiNote);
								tmpNotes[ch][key].reset();
							}
						}
					}

					switch (currentMessage->type)
					{
					case TML_PROGRAM_CHANGE: //channel program (preset) change (special handling for 10th MIDI channel with drums)
						::tsf_channel_set_presetnumber(m_font, currentMessage->channel, currentMessage->program, (currentMessage->channel == 9));
						break;
					case TML_NOTE_ON: //play a note
						::tsf_channel_note_on(m_font, currentMessage->channel, currentMessage->key, currentMessage->velocity / 127.0f);
						break;
					case TML_NOTE_OFF: //stop a note
						::tsf_channel_note_off(m_font, currentMessage->channel, currentMessage->key);
						break;
					case TML_PITCH_BEND: //pitch wheel modification
						::tsf_channel_set_pitchwheel(m_font, currentMessage->channel, currentMessage->pitch_bend);
						break;
					case TML_CONTROL_CHANGE: //MIDI controller messages
						::tsf_channel_midi_control(m_font, currentMessage->channel, currentMessage->control, currentMessage->control_value);
						break;
					}

					posSample += SampleBlock;
				}

				// Render the block of audio samples in float format
				const size_t currentSize = result.size();
				result.resize(currentSize + SampleBlock);
				::tsf_render_float(m_font, &result[currentSize].left, SampleBlock, 0);
			}

			if (tailSamples)
			{
				const size_t currentSize = result.size();
				result.resize(currentSize + tailSamples);
				::tsf_render_float(m_font, &result[currentSize].left, static_cast<int32>(tailSamples), 0);
			}

			const size_t fadeOutSamples = (samplingRate / 10);
			result.fadeOut(fadeOutSamples);
		}

		::tml_free(midi);
		::tsf_reset(m_font);

		return result;
	}


	Wave SoundFont::SoundFontDetail::renderMIDI(IReader& reader, const Arg::samplingRate_<uint32> _samplingRate, const Duration& tail, std::array<Array<MIDINote>, 16>& midiScore)
	{
		if (not m_font)
		{
			return{};
		}

		const uint32 samplingRate = *_samplingRate;
		const size_t tailSamples = detail::CalculateSamples(tail, Arg::samplingRate = samplingRate);

		Blob blob{ reader };
		tml_message* midi = ::tml_load_memory(blob.data(), static_cast<int32>(blob.size()));
		{
			if (not midi)
			{
				return{};
			}

			::tsf_channel_set_bank_preset(m_font, 9, 128, 0);
			::tsf_set_output(m_font, TSF_STEREO_INTERLEAVED, samplingRate, 0.0f);
		}

		Wave result(Arg::samplingRate = samplingRate);
		{
			size_t timeMillisec = 0;

			for (tml_message* currentMessage = midi; currentMessage; currentMessage = currentMessage->next)
			{
				timeMillisec = currentMessage->time;
			}

			const size_t reserveSamples = ((timeMillisec + tailSamples + 100) * samplingRate / 1000);
			result.reserve(reserveSamples);
		}

		{
			Array<std::array<Optional<int32>, 128>> tmpNotes(16);
			double timeMillisec = 0.0;
			int32 posSample = 0;

			for (tml_message* currentMessage = midi; currentMessage;)
			{
				constexpr int32 SampleBlock = TSF_RENDER_EFFECTSAMPLEBLOCK;

				for (timeMillisec += SampleBlock * (1000.0 / samplingRate); currentMessage && (timeMillisec >= currentMessage->time); currentMessage = currentMessage->next)
				{
					if ((currentMessage->type == 0x80) || (currentMessage->type == 0x90))
					{
						const uint32 ch = currentMessage->channel;
						const uint32 key = currentMessage->key & 0x7F;
						const bool on = ((currentMessage->type == 0x90) && (currentMessage->control != 0x00));

						if (on)
						{
							if (not tmpNotes[ch][key])
							{
								tmpNotes[ch][key] = posSample;
							}
						}
						else
						{
							if (tmpNotes[ch][key])
							{
								MIDINote midiNote;
								midiNote.key = key;
								midiNote.startMillisec = *tmpNotes[ch][key];
								midiNote.lengthMillisec = (posSample - *tmpNotes[ch][key]);
								midiScore[ch].push_back(midiNote);
								tmpNotes[ch][key].reset();
							}
						}
					}

					switch (currentMessage->type)
					{
					case TML_PROGRAM_CHANGE: //channel program (preset) change (special handling for 10th MIDI channel with drums)
						::tsf_channel_set_presetnumber(m_font, currentMessage->channel, currentMessage->program, (currentMessage->channel == 9));
						break;
					case TML_NOTE_ON: //play a note
						::tsf_channel_note_on(m_font, currentMessage->channel, currentMessage->key, currentMessage->velocity / 127.0f);
						break;
					case TML_NOTE_OFF: //stop a note
						::tsf_channel_note_off(m_font, currentMessage->channel, currentMessage->key);
						break;
					case TML_PITCH_BEND: //pitch wheel modification
						::tsf_channel_set_pitchwheel(m_font, currentMessage->channel, currentMessage->pitch_bend);
						break;
					case TML_CONTROL_CHANGE: //MIDI controller messages
						::tsf_channel_midi_control(m_font, currentMessage->channel, currentMessage->control, currentMessage->control_value);
						break;
					}

					posSample += SampleBlock;
				}

				// Render the block of audio samples in float format
				const size_t currentSize = result.size();
				result.resize(currentSize + SampleBlock);
				::tsf_render_float(m_font, &result[currentSize].left, SampleBlock, 0);
			}

			if (tailSamples)
			{
				const size_t currentSize = result.size();
				result.resize(currentSize + tailSamples);
				::tsf_render_float(m_font, &result[currentSize].left, static_cast<int32>(tailSamples), 0);
			}

			const size_t fadeOutSamples = (samplingRate / 10);
			result.fadeOut(fadeOutSamples);
		}

		::tml_free(midi);
		::tsf_reset(m_font);

		return result;
	}

	bool SoundFont::SoundFontDetail::load(const Blob& blob)
	{
		m_font = ::tsf_load_memory(blob.data(), static_cast<int32>(blob.size()));

		return (m_font != nullptr);
	}
}
