//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include "MicrophoneDetail.hpp"

namespace s3d
{
	void Microphone::MicrophoneDetail::WaveInCallback(const HWAVEIN, const UINT uMsg, const DWORD_PTR dwInstance, const DWORD_PTR dwParam1, const DWORD_PTR)
	{
		if (uMsg != WIM_DATA)
		{
			return;
		}

		LPWAVEHDR pwh = reinterpret_cast<LPWAVEHDR>(dwParam1);
		const WaveSampleS16* pSrc = reinterpret_cast<const WaveSampleS16*>(pwh->lpData);
		const size_t samples = (pwh->dwBytesRecorded) / (sizeof(short) * 2);

		MicrophoneDetail* pAudioInput = reinterpret_cast<MicrophoneDetail*>(dwInstance);
		pAudioInput->onRead(pSrc, samples);
	}

	Microphone::MicrophoneDetail::MicrophoneDetail()
	{
		
	}

	Microphone::MicrophoneDetail::~MicrophoneDetail()
	{
		release();
	}

	bool Microphone::MicrophoneDetail::init(const Optional<size_t> deviceID, const RecordingFormat format, const size_t bufferLength, const bool loop)
	{
		if (m_initialized)
		{
			release();
		}

		if (const size_t num_devices = ::waveInGetNumDevs(); num_devices == 0)
		{
			LOG_FAIL(U"❌ Microphone: No waveform-audio input device found");
		}
		else if (deviceID >= num_devices)
		{
			LOG_FAIL(U"❌ Microphone: Waveform-audio input device index out of range");
			return false;
		}

		if (deviceID)
		{
			if (WAVEINCAPSW caps; MMSYSERR_NOERROR != ::waveInGetDevCapsW(deviceID.value(), &caps, sizeof(caps)))
			{
				LOG_FAIL(U"❌ Microphone: waveInGetDevCapsW() failed");
				return false;
			}
			else if (!(static_cast<uint32>(format) & caps.dwFormats))
			{
				LOG_FAIL(U"❌ Microphone: waveIn device({}) does not support RecordingFormat({})"_fmt(deviceID.value(), static_cast<uint32>(format)));
				return false;
			}
		}

		m_samplingRate	= detail::ToSamplingRate(format);
		m_loop			= loop;

		constexpr uint32 num_channels	= 2;
		WAVEFORMATEX waveform;
		waveform.wFormatTag			= WAVE_FORMAT_PCM;
		waveform.nChannels			= num_channels;
		waveform.nSamplesPerSec		= m_samplingRate;
		waveform.nAvgBytesPerSec	= m_samplingRate * (sizeof(short) * num_channels);
		waveform.nBlockAlign		= (sizeof(short) * num_channels);
		waveform.wBitsPerSample		= 16;
		waveform.cbSize				= 0;

		if (MMSYSERR_NOERROR != ::waveInOpen(&m_hWaveIn, static_cast<UINT>(deviceID.value_or(WAVE_MAPPER)), &waveform,
			reinterpret_cast<DWORD_PTR>(WaveInCallback),
			reinterpret_cast<DWORD_PTR>(this), CALLBACK_FUNCTION))
		{
			LOG_FAIL(U"❌ Microphone: waveInOpen() failed");
			return false;
		}

		m_buffer.assign(bufferLength, WaveSampleS16::Zero());
		m_wh.lpData				= static_cast<char*>(static_cast<void*>(m_buffer.data()));
		m_wh.dwBufferLength		= static_cast<uint32>(bufferLength * (sizeof(short) * num_channels));
		m_wh.dwBytesRecorded	= 0;
		m_wh.dwUser				= 0;
		m_wh.dwFlags			= 0;
		m_wh.dwLoops			= 1;
		m_wh.lpNext				= nullptr;
		m_wh.reserved			= 0;

		if (MMSYSERR_NOERROR != ::waveInPrepareHeader(m_hWaveIn, &m_wh, sizeof(WAVEHDR)))
		{
			::waveInClose(m_hWaveIn);
			LOG_FAIL(U"❌ Microphone: waveInPrepareHeader() failed");
			return false;
		}

		m_initialized = true;
		m_reachedEnd = false;

		return true;
	}

	bool Microphone::MicrophoneDetail::isAvailable() const
	{
		return m_initialized;
	}

	void Microphone::MicrophoneDetail::release()
	{
		if (!m_initialized)
		{
			return;
		}

		stop();

		::waveInUnprepareHeader(m_hWaveIn, &m_wh, sizeof(WAVEHDR));
		::waveInClose(m_hWaveIn);

		m_hWaveIn = nullptr;
		m_initialized = false;
		m_reachedEnd = false;
	}

	bool Microphone::MicrophoneDetail::start()
	{
		if (!m_initialized || m_isRecording)
		{
			return false;
		}

		::waveInAddBuffer(m_hWaveIn, &m_wh, sizeof(WAVEHDR));

		if (::waveInStart(m_hWaveIn) != MMSYSERR_NOERROR)
		{
			LOG_FAIL(U"❌ Microphone: waveInStart() failed");
			return false;
		}

		m_isRecording = true;

		return true;
	}

	void Microphone::MicrophoneDetail::stop()
	{
		if (!m_initialized || !m_isRecording)
		{
			return;
		}

		::waveInStop(m_hWaveIn);
		::waveInReset(m_hWaveIn);

		m_buffer.fill(WaveSampleS16::Zero());

		m_isRecording = false;
		m_reachedEnd = false;
	}

	bool Microphone::MicrophoneDetail::isRecording() const
	{
		return m_isRecording && !m_reachedEnd;
	}

	uint32 Microphone::MicrophoneDetail::samplingRate() const
	{
		return m_samplingRate;
	}

	const Array<WaveSampleS16>& Microphone::MicrophoneDetail::getBuffer() const
	{
		return m_buffer;
	}

	size_t Microphone::MicrophoneDetail::posSample() const
	{
		return (m_wh.dwBytesRecorded) / (sizeof(short) * 2);
	}

	void Microphone::MicrophoneDetail::onRead(const WaveSampleS16*, const size_t samples)
	{
		if (m_loop && samples > 0)
		{
			::waveInAddBuffer(m_hWaveIn, &m_wh, sizeof(WAVEHDR));
		}

		if (!m_loop)
		{
			m_reachedEnd = true;
		}
	}
}
