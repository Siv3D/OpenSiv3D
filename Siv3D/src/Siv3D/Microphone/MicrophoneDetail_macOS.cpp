//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "MicrophoneDetail_macOS.hpp"
# include <Siv3D/Logger.hpp>

namespace s3d
{
	int Microphone::MicrophoneDetail::InputCallback(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data)
	{
		Microphone::MicrophoneDetail* iData = static_cast<Microphone::MicrophoneDetail*>(data);
		
		if (iData->onRead(static_cast<const WaveSampleS16*>(inputBuffer), nBufferFrames))
		{
			return 0;
		}
		else
		{
			return 2; // abort
		}
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
		const uint32 num_devices = m_device.getDeviceCount();
		
		if (num_devices < 1 )
		{
			LOG_FAIL(U"❌ Microphone: No audio devices found");
			return false;
		}
		
		m_samplingRate = detail::ToSamplingRate(format);
		m_loop = loop;
		
		m_device.showWarnings(true);
		
		if (bufferLength < 256)
		{
			LOG_FAIL(U"❌ Microphone: bufferLength is too short");
			return false;
		}
		
		RtAudio::StreamParameters iParams;
		iParams.deviceId		= static_cast<uint32>(deviceID.value_or(m_device.getDefaultInputDevice()));
		iParams.nChannels		= 2;
		iParams.firstChannel	= 0;
		
		uint32 bufferFrames = 256;

		try
		{
			m_device.openStream(nullptr, &iParams, RTAUDIO_SINT16, m_samplingRate, &bufferFrames, InputCallback, this);
		}
		catch (RtAudioError& e)
		{
			LOG_FAIL(U"❌ Microphone: {}"_fmt(Unicode::Widen(e.getMessage())));
			if (m_device.isStreamOpen()) m_device.closeStream();
			return false;
		}
		
		m_buffer.assign(bufferLength, WaveSampleS16::Zero());
		m_writePos = 0;
		
		m_initialized = true;
		
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
		
		if (m_device.isStreamRunning())
		{
			m_device.abortStream();
		}
		
		if (m_device.isStreamOpen())
		{
			m_device.closeStream();
		}
		
		m_initialized = false;
	}

	bool Microphone::MicrophoneDetail::start()
	{
		if (!m_initialized || m_isRecording)
		{
			return false;
		}
		
		try
		{
			m_device.startStream();
		}
		catch (RtAudioError& e)
		{
			LOG_FAIL(U"❌ Microphone: {}"_fmt(Unicode::Widen(e.getMessage())));
			if (m_device.isStreamOpen()) m_device.closeStream();
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
		
		m_device.abortStream();

		m_writePos = 0;
		
		m_buffer.fill(WaveSampleS16::Zero());
		
		m_isRecording = false;
	}

	bool Microphone::MicrophoneDetail::isRecording() const
	{
		return m_isRecording;
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
		return m_writePos;
	}
	
	bool Microphone::MicrophoneDetail::onRead(const WaveSampleS16* pSrc, size_t samples)
	{
		if (m_loop)
		{
			while (samples)
			{
				size_t write_samples = std::min(samples, m_buffer.size() - m_writePos);
				::memcpy(m_buffer.data() + m_writePos, pSrc, write_samples * (2 * sizeof(int16)));
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
				samples = m_buffer.size() - m_writePos;
			}
		
			const size_t write_bytes = samples * (2 * sizeof(int16));
		
			::memcpy(m_buffer.data() + m_writePos, pSrc, write_bytes);
		
			m_writePos += samples;
		
			if (m_writePos >= m_buffer.size())
			{
				m_isRecording = false;
				
				return false;
			}
		
			return true;
		}
	}
}

# endif
