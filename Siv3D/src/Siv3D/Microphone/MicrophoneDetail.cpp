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
		LOG_TRACE(U"Microphone::MicrophoneDetail::open()");

		close();

		m_microphoneIndex = deviceIndex.value_or(m_device.getDefaultInputDevice());
		const RtAudio::DeviceInfo info = m_device.getDeviceInfo(m_microphoneIndex);

		if (info.inputChannels == 0)
		{
			LOG_FAIL(U"✖ Microphone: deviceIndex {} is not a microphone"_fmt(m_microphoneIndex));
			return false;
		}

		const Array<uint32> sampleRates(info.sampleRates.begin(), info.sampleRates.end());

		if (sampleRate)
		{
			if (not sampleRates.contains(*sampleRate))
			{
				LOG_FAIL(U"✖ Microphone: Device does not support sampleRate {}Hz"_fmt(*sampleRate));
				return false;
			}
			
			m_sampleRate = *sampleRate;
		}
		else
		{
			m_sampleRate = info.preferredSampleRate;
		}

		const size_t bufferLength = static_cast<size_t>(duration.count() * m_sampleRate);

		if (bufferLength < 256)
		{
			LOG_FAIL(U"✖ Microphone: bufferLength must be at least 256");
			return false;
		}

		const uint32 nChannels = Min(info.inputChannels, 2u);
		const bool isF32 = !!(info.nativeFormats & RTAUDIO_FLOAT32);
		const bool isS16 = !!(info.nativeFormats & RTAUDIO_SINT16);

		if ((not isF32) && (not isS16))
		{
			LOG_FAIL(U"❌ Microphone: OpenSiv3D does not support nativeFormats `{}`"_fmt(info.nativeFormats));
			return false;
		}

		//if ((nChannels != 1) && (nChannels != 2))
		//{
		//	LOG_FAIL(U"❌ Microphone: OpenSiv3D does not support {} ch input"_fmt(nChannels));
		//	return false;
		//}

		RtAudio::StreamParameters iParams;
		iParams.deviceId = m_microphoneIndex;
		iParams.nChannels = nChannels;
		iParams.firstChannel = 0;

		LOG_INFO(U"ℹ️ Microphone: deviceIndex: {}, name: {}, nChannels: {}, F32: {}, S16: {}"_fmt(deviceIndex, Unicode::FromUTF8(info.name), nChannels, isF32, isS16));

		uint32 bufferFrames = 256;

		try
		{
			if (nChannels == 1)
			{
				if (isF32)
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_FLOAT32, m_sampleRate, &bufferFrames, InputCallback_F32_1ch, this);
				}
				else
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_SINT16, m_sampleRate, &bufferFrames, InputCallback_S16_1ch, this);
				}
			}
			else
			{
				if (isF32)
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_FLOAT32, m_sampleRate, &bufferFrames, InputCallback_F32_2ch, this);
				}
				else
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_SINT16, m_sampleRate, &bufferFrames, InputCallback_S16_2ch, this);
				}
			}
		}
		catch (RtAudioError& e)
		{
			LOG_FAIL(U"❌ Microphone: {}"_fmt(Unicode::Widen(e.getMessage())));

			if (m_device.isStreamOpen())
			{
				m_device.closeStream();
			}

			return false;
		}

		m_buffer = Wave{ bufferLength, WaveSample::Zero(), Arg::sampleRate = m_sampleRate };
		m_loop = loop.getBool();
		m_writePos = 0;
		m_initialized = true;
		return true;
	}

	bool Microphone::MicrophoneDetail::open(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, const size_t bufferLength, const Loop loop)
	{
		LOG_TRACE(U"Microphone::MicrophoneDetail::open()");

		close();

		if (bufferLength < 256)
		{
			LOG_FAIL(U"✖ Microphone: bufferLength must be at least 256");
			return false;
		}

		m_microphoneIndex = deviceIndex.value_or(m_device.getDefaultInputDevice());
		const RtAudio::DeviceInfo info = m_device.getDeviceInfo(m_microphoneIndex);

		if (info.inputChannels == 0)
		{
			LOG_FAIL(U"✖ Microphone: deviceIndex {} is not a microphone"_fmt(m_microphoneIndex));
			return false;
		}

		const Array<uint32> sampleRates(info.sampleRates.begin(), info.sampleRates.end());

		if (sampleRate)
		{
			if (not sampleRates.contains(*sampleRate))
			{
				LOG_FAIL(U"✖ Microphone: Device does not support sampleRate {}Hz"_fmt(*sampleRate));
				return false;
			}

			m_sampleRate = *sampleRate;
		}
		else
		{
			m_sampleRate = info.preferredSampleRate;
		}

		const uint32 nChannels = Min(info.inputChannels, 2u);
		const bool isF32 = !!(info.nativeFormats & RTAUDIO_FLOAT32);
		const bool isS16 = !!(info.nativeFormats & RTAUDIO_SINT16);

		if ((not isF32) && (not isS16))
		{
			LOG_FAIL(U"❌ Microphone: OpenSiv3D does not support nativeFormats `{}`"_fmt(info.nativeFormats));
			return false;
		}

		//if ((nChannels != 1) && (nChannels != 2))
		//{
		//	LOG_FAIL(U"❌ Microphone: OpenSiv3D does not support {} ch input"_fmt(nChannels));
		//	return false;
		//}

		RtAudio::StreamParameters iParams;
		iParams.deviceId = m_microphoneIndex;
		iParams.nChannels = nChannels;
		iParams.firstChannel = 0;

		LOG_INFO(U"ℹ️ Microphone: deviceIndex: {}, name: {}, nChannels: {}, F32: {}, S16: {}"_fmt(deviceIndex, Unicode::FromUTF8(info.name), nChannels, isF32, isS16));

		uint32 bufferFrames = 256;

		try
		{
			if (nChannels == 1)
			{
				if (isF32)
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_FLOAT32, m_sampleRate, &bufferFrames, InputCallback_F32_1ch, this);
				}
				else
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_SINT16, m_sampleRate, &bufferFrames, InputCallback_S16_1ch, this);
				}
			}
			else
			{
				if (isF32)
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_FLOAT32, m_sampleRate, &bufferFrames, InputCallback_F32_2ch, this);
				}
				else
				{
					m_device.openStream(nullptr, &iParams, RTAUDIO_SINT16, m_sampleRate, &bufferFrames, InputCallback_S16_2ch, this);
				}
			}
		}
		catch (RtAudioError& e)
		{
			LOG_FAIL(U"❌ Microphone: {}"_fmt(Unicode::Widen(e.getMessage())));

			if (m_device.isStreamOpen())
			{
				m_device.closeStream();
			}

			return false;
		}

		m_buffer = Wave{ bufferLength, WaveSample::Zero(), Arg::sampleRate = m_sampleRate };
		m_loop = loop.getBool();
		m_writePos = 0;
		m_initialized = true;
		return true;
	}

	void Microphone::MicrophoneDetail::close()
	{
		LOG_TRACE(U"Microphone::MicrophoneDetail::close()");

		if (not m_initialized)
		{
			return;
		}

		if (m_device.isStreamOpen())
		{
			LOG_TRACE(U"m_device.closeStream()");

			m_device.closeStream();
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

		try
		{
			m_device.startStream();
		}
		catch (RtAudioError& e)
		{
			LOG_FAIL(U"❌ Microphone: {}"_fmt(Unicode::Widen(e.getMessage())));
			
			if (m_device.isStreamOpen())
			{
				m_device.closeStream();
			}

			return false;
		}

		m_isRecording = true;

		return true;
	}

	void Microphone::MicrophoneDetail::stop()
	{
		if ((not m_initialized)
			|| (not m_isRecording))
		{
			return;
		}

		m_device.abortStream();

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

	bool Microphone::MicrophoneDetail::onRead_S16_1ch(const int16* pSrc, size_t samples)
	{
		if (m_loop)
		{
			while (samples)
			{
				const size_t write_samples = Min(samples, (m_buffer.size() - m_writePos));

				for (size_t i = 0; i < write_samples; ++i)
				{
					m_buffer[m_writePos + i] = WaveSample::FromInt16(pSrc[i]);
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

			for (size_t i = 0; i < samples; ++i)
			{
				m_buffer[m_writePos + i] = WaveSample::FromInt16(pSrc[i]);
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
				const size_t write_samples = Min(samples, (m_buffer.size() - m_writePos));

				for (size_t i = 0; i < write_samples; ++i)
				{
					m_buffer[m_writePos + i] = pSrc[i];
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

			for (size_t i = 0; i < samples; ++i)
			{
				m_buffer[m_writePos + i] = pSrc[i];
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

	bool Microphone::MicrophoneDetail::onRead_F32_1ch(const float* pSrc, size_t samples)
	{
		if (m_loop)
		{
			while (samples)
			{
				const size_t write_samples = Min(samples, (m_buffer.size() - m_writePos));

				for (size_t i = 0; i < write_samples; ++i)
				{
					m_buffer[m_writePos + i] = pSrc[i];
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

			for (size_t i = 0; i < samples; ++i)
			{
				m_buffer[m_writePos + i] = pSrc[i];
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
				const size_t write_samples = Min(samples, (m_buffer.size() - m_writePos));

				std::memcpy(m_buffer.data() + m_writePos, pSrc, (write_samples * sizeof(WaveSample)));

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

			const size_t write_bytes = (samples * sizeof(WaveSample));

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

	int Microphone::MicrophoneDetail::InputCallback_S16_1ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data)
	{
		Microphone::MicrophoneDetail* pMicrophone = static_cast<Microphone::MicrophoneDetail*>(data);

		if (pMicrophone->onRead_S16_1ch(static_cast<const int16*>(inputBuffer), nBufferFrames))
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
		Microphone::MicrophoneDetail* pMicrophone = static_cast<Microphone::MicrophoneDetail*>(data);

		if (pMicrophone->onRead_S16_2ch(static_cast<const WaveSampleS16*>(inputBuffer), nBufferFrames))
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
		Microphone::MicrophoneDetail* pMicrophone = static_cast<Microphone::MicrophoneDetail*>(data);

		if (pMicrophone->onRead_F32_1ch(static_cast<const float*>(inputBuffer), nBufferFrames))
		{
			return 0;
		}
		else
		{
			return 2; // abort
		}
	}

	int Microphone::MicrophoneDetail::InputCallback_F32_2ch(void*, void* inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void* data)
	{
		Microphone::MicrophoneDetail* pMicrophone = static_cast<Microphone::MicrophoneDetail*>(data);

		if (pMicrophone->onRead_F32_2ch(static_cast<const WaveSample*>(inputBuffer), nBufferFrames))
		{
			return 0;
		}
		else
		{
			return 2; // abort
		}
	}
}
