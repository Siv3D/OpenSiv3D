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

# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <emscripten/html5.h>
# include "MicrophoneDetail.hpp"

namespace s3d
{
	Microphone::MicrophoneDetail::MicrophoneDetail() {}

	Microphone::MicrophoneDetail::~MicrophoneDetail()
	{
		close();
	}

	bool Microphone::MicrophoneDetail::open(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, const Duration& duration, const Loop loop)
	{
		const size_t bufferLength = static_cast<size_t>(duration.count() * sampleRate.value_or(Wave::DefaultSampleRate));
		return open(deviceIndex, sampleRate, bufferLength, loop);
	}

	bool Microphone::MicrophoneDetail::open(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, const size_t bufferLength, const Loop loop)
	{
		LOG_TRACE(U"Microphone::MicrophoneDetail::open()");

		close();

		m_sampleRate = sampleRate.value_or(Wave::DefaultSampleRate);
		m_loop = loop.getBool();
		
		if (bufferLength < 256)
		{
			LOG_FAIL(U"❌ Microphone: bufferLength is too short");
			return false;
		}
		
		m_device = ::alcCaptureOpenDevice(NULL, m_sampleRate, AL_FORMAT_MONO16, bufferLength);
		
		m_buffer = Wave{ bufferLength, WaveSample::Zero(), Arg::sampleRate = m_sampleRate };
		m_nativeBuffer = Array<int16>( bufferLength );
		m_writePos = 0;
		
		m_initialized = true;
		
		return true;
	}

	void Microphone::MicrophoneDetail::close()
	{
		LOG_TRACE(U"Microphone::MicrophoneDetail::close()");

		if (!m_initialized)
		{
			return;
		}
		
		if (m_device)
		{
			LOG_TRACE(U"::alcCloseDevice");

			::alcCloseDevice(m_device);
		}

		m_writePos = 0;
		m_isRecording = false;
		m_initialized = false;
	}

	bool Microphone::MicrophoneDetail::isOpen() const
	{
		return m_initialized;
	}

	bool Microphone::MicrophoneDetail::start()
	{
		LOG_TRACE(U"Microphone::MicrophoneDetail::start()");

		if ((not m_initialized)
			|| (m_isRecording))
		{
			return false;
		}
		
		::alcCaptureStart(m_device);
		::emscripten_set_timeout(&Microphone::MicrophoneDetail::InputCallback_S16_1ch, 20.0, this);
		
		m_isRecording = true;
		
		return true;
	}

	void Microphone::MicrophoneDetail::stop()
	{
		if (not m_initialized || not m_isRecording)
		{
			return;
		}
		
		::alcCaptureStop(m_device);
		
		m_writePos = 0;
		
		m_buffer.fill(WaveSample::Zero());
		
		m_isRecording = false;
	}

	bool Microphone::MicrophoneDetail::isRecording() const
	{
		return m_isRecording;
	}

	uint32 Microphone::MicrophoneDetail::microphoneIndex() const
	{
		return m_microphoneIndex;
	}

	uint32 Microphone::MicrophoneDetail::getSampleRate() const
	{
		return m_sampleRate;
	}

	size_t Microphone::MicrophoneDetail::getBufferLength() const
	{
		return m_buffer.samples();
	}

	bool Microphone::MicrophoneDetail::isLoop() const
	{
		return m_loop;
	}

	const Wave& Microphone::MicrophoneDetail::getBuffer() const
	{
		return m_buffer;
	}

	size_t Microphone::MicrophoneDetail::posSample() const
	{
		return m_writePos;
	}

	bool Microphone::MicrophoneDetail::onRead_S16_1ch()
	{
		if (static_cast<char>(m_isRecording) != 1)
		{
			LOG_FAIL(U"{}"_fmt(static_cast<int>(m_isRecording)));
			return false;
		}

		ALCint samples;

		::alcGetIntegerv(m_device, ALC_CAPTURE_SAMPLES, sizeof(samples), &samples);

		if (m_loop)
		{
			while (samples)
			{
				const size_t write_samples = Min(static_cast<size_t>(samples), (m_buffer.size() - m_writePos));

				::alcCaptureSamples(m_device, (ALCvoid*)(m_nativeBuffer.data()), write_samples);

				for (size_t i = 0; i < write_samples; ++i)
				{
					m_buffer[m_writePos + i] = WaveSample::FromInt16(m_nativeBuffer[i]);
				}

				m_writePos += write_samples;

				if (m_writePos >= m_buffer.size())
				{
					m_writePos = 0;
				}

				samples -= write_samples;
			}

			return true;
		}
		else
		{
			if (m_writePos + samples > m_buffer.size())
			{
				samples = (m_buffer.size() - m_writePos);
			}

			::alcCaptureSamples(m_device, (ALCvoid*)(m_nativeBuffer.data()), samples);

			for (size_t i = 0; i < samples; ++i)
			{
				m_buffer[m_writePos + i] = WaveSample::FromInt16(m_nativeBuffer[i]);
			}

			m_writePos += samples;

			if (m_writePos >= m_buffer.size())
			{
				m_isRecording = false;

				return false;
			}

			return true;
		}
	}

	void Microphone::MicrophoneDetail::InputCallback_S16_1ch(void* data)
	{
		Microphone::MicrophoneDetail* that = static_cast<Microphone::MicrophoneDetail*>(data);
		
		if (that->onRead_S16_1ch())
		{
			::emscripten_set_timeout(&Microphone::MicrophoneDetail::InputCallback_S16_1ch, 20.0, data);
		}
	}
}
