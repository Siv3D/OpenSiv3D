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

# include "MicrophoneDetail.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	int Microphone::MicrophoneDetail::InputCallback_S16_1ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data)
	{
		Microphone::MicrophoneDetail* iData = static_cast<Microphone::MicrophoneDetail*>(data);
		
		if (iData->onRead_S16_1ch(static_cast<const int16*>(inputBuffer), nBufferFrames))
		{
			return 0;
		}
		else
		{
			return 2; // abort
		}
	}

	int Microphone::MicrophoneDetail::InputCallback_S16_2ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data)
	{
		Microphone::MicrophoneDetail* iData = static_cast<Microphone::MicrophoneDetail*>(data);
		
		if (iData->onRead_S16_2ch(static_cast<const WaveSampleS16*>(inputBuffer), nBufferFrames))
		{
			return 0;
		}
		else
		{
			return 2; // abort
		}
	}

	int Microphone::MicrophoneDetail::InputCallback_F32_1ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data)
	{
		Microphone::MicrophoneDetail* iData = static_cast<Microphone::MicrophoneDetail*>(data);
		
		if (iData->onRead_F32_1ch(static_cast<const float*>(inputBuffer), nBufferFrames))
		{
			return 0;
		}
		else
		{
			return 2; // abort
		}
		
		return 0;
	}

	int Microphone::MicrophoneDetail::InputCallback_F32_2ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data)
	{
		Microphone::MicrophoneDetail* iData = static_cast<Microphone::MicrophoneDetail*>(data);
		
		if (iData->onRead_F32_2ch(static_cast<const WaveSample*>(inputBuffer), nBufferFrames))
		{
			return 0;
		}
		else
		{
			return 2; // abort
		}
		
		return 0;
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
		
		LOG_INFO(U"Audio device count: {}"_fmt(num_devices));
		
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
		
		const uint32 deviceIndex = static_cast<uint32>(deviceID.value_or(m_device.getDefaultInputDevice()));
		const RtAudio::DeviceInfo deviceInfo = m_device.getDeviceInfo(deviceIndex);
		const String deviceName = Unicode::Widen(deviceInfo.name);
		const uint32 nChannels = deviceInfo.inputChannels;
		const bool isF32 = !!(deviceInfo.nativeFormats & RTAUDIO_FLOAT32);
		const bool isS16 = !!(deviceInfo.nativeFormats & RTAUDIO_SINT16);
		
		if (nChannels == 0)
		{
			LOG_FAIL(U"❌ Microphone: deviceID [{}] has no input channels"_fmt(deviceIndex));
			return false;
		}
		
		if (!isF32 && !isS16)
		{
			LOG_FAIL(U"❌ Microphone: OpenSiv3D does not support nativeFormats `{}`"_fmt(deviceInfo.nativeFormats));
			return false;
		}
		
		if (nChannels != 1 && nChannels != 2)
		{
			LOG_FAIL(U"❌ Microphone: OpenSiv3D does not support {} ch input"_fmt(nChannels));
			return false;
		}

		RtAudio::StreamParameters iParams;
		iParams.deviceId		= deviceIndex;
		iParams.nChannels		= nChannels;
		iParams.firstChannel	= 0;
		
		LOG_INFO(U"ℹ️ Microphone: deviceIndex: {}, name: {}, nChannels: {}, F32: {}, S16: {}"_fmt(deviceIndex, deviceName, nChannels, isF32, isS16));
	
		uint32 bufferFrames = 256;
		
		try
		{
			if (nChannels == 1)
			{
				if (isF32)
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_FLOAT32, m_samplingRate, &bufferFrames, InputCallback_F32_1ch, this);
				}
				else
				{
					// [Siv3D ToDo]
				}
			}
			else
			{
				if (isF32)
				{
					// [Siv3D ToDo]
				}
				else
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_SINT16, m_samplingRate, &bufferFrames, InputCallback_S16_2ch, this);
				}
			}
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
		LOG_TRACE(U"Microphone::MicrophoneDetail::release()");
		
		if (!m_initialized)
		{
			return;
		}
		
		if (m_device.isStreamOpen())
		{
			LOG_TRACE(U"m_device.closeStream()");
			
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

	bool Microphone::MicrophoneDetail::onRead_S16_1ch(const int16* pSrc, size_t samples)
	{
		if (m_loop)
		{
			while (samples)
			{
				const size_t write_samples = std::min(samples, m_buffer.size() - m_writePos);
				
				for (size_t i = 0; i < write_samples; ++i)
				{
					m_buffer[m_writePos + i].set(pSrc[i]);
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
				samples = m_buffer.size() - m_writePos;
			}

			for (size_t i = 0; i < samples; ++i)
			{
				m_buffer[m_writePos + i].set(pSrc[i]);
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
	
	bool Microphone::MicrophoneDetail::onRead_S16_2ch(const WaveSampleS16* pSrc, size_t samples)
	{
		if (m_loop)
		{
			while (samples)
			{
				const size_t write_samples = std::min(samples, m_buffer.size() - m_writePos);
				std::memcpy(m_buffer.data() + m_writePos, pSrc, write_samples * (2 * sizeof(int16)));
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
			
			std::memcpy(m_buffer.data() + m_writePos, pSrc, write_bytes);
			
			m_writePos += samples;
			
			if (m_writePos >= m_buffer.size())
			{
				m_isRecording = false;
				
				return false;
			}
			
			return true;
		}
	}

	bool Microphone::MicrophoneDetail::onRead_F32_1ch(const float* pSrc, size_t samples)
	{
		if (m_loop)
		{
			while (samples)
			{
				const size_t write_samples = std::min(samples, m_buffer.size() - m_writePos);
				
				for (size_t i = 0; i < write_samples; ++i)
				{
					m_buffer[m_writePos + i] = WaveSampleS16::FromF32(pSrc[i]);
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
				samples = m_buffer.size() - m_writePos;
			}
			
			for (size_t i = 0; i < samples; ++i)
			{
				m_buffer[m_writePos + i] = WaveSampleS16::FromF32(pSrc[i]);
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

	bool Microphone::MicrophoneDetail::onRead_F32_2ch(const WaveSample* pSrc, size_t samples)
	{
		if (m_loop)
		{
			while (samples)
			{
				const size_t write_samples = std::min(samples, m_buffer.size() - m_writePos);
				
				for (size_t i = 0; i < write_samples; ++i)
				{
					m_buffer[m_writePos + i] = pSrc[i].asWaveSampleS16();
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
				samples = m_buffer.size() - m_writePos;
			}
			
			for (size_t i = 0; i < samples; ++i)
			{
				m_buffer[m_writePos + i] = pSrc[i].asWaveSampleS16();
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
}
