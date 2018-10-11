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

# include <Siv3D/Microphone.hpp>
# include <Siv3D/Math.hpp>
# include "MicrophoneDetail_Windows.hpp"
# include "MicrophoneDetail_macOS.hpp"
# include "MicrophoneDetail_Linux.hpp"

namespace s3d
{
	Microphone::Microphone()
		: pImpl(std::make_shared<MicrophoneDetail>())
	{

	}

	Microphone::Microphone(const Optional<size_t> deviceID, const RecordingFormat format, const size_t bufferLength, const bool loop)
		: Microphone()
	{
		pImpl->init(deviceID, format, bufferLength, loop);
	}

	Microphone::~Microphone()
	{

	}

	bool Microphone::init(const Optional<size_t> deviceID, const RecordingFormat format, const size_t bufferLength, const bool loop)
	{
		return pImpl->init(deviceID, format, bufferLength, loop);
	}

	bool Microphone::isAvailable() const
	{
		return pImpl->isAvailable();
	}

	Microphone::operator bool() const
	{
		return isAvailable();
	}

	void Microphone::release()
	{
		pImpl->release();
	}

	bool Microphone::start()
	{
		return pImpl->start();
	}

	void Microphone::stop()
	{
		pImpl->stop();
	}

	bool Microphone::isRecording() const
	{
		return pImpl->isRecording();
	}

	uint32 Microphone::samplingRate() const
	{
		return pImpl->samplingRate();
	}

	const Array<WaveSampleS16>& Microphone::getBuffer() const
	{
		return pImpl->getBuffer();
	}

	size_t Microphone::posSample() const
	{
		return pImpl->posSample();
	}

	double Microphone::mean(const Duration& duration) const
	{
		if (!isRecording())
		{
			return 0.0;
		}

		const Array<WaveSampleS16>& buffer = getBuffer();
		const double lengthSec = Clamp(static_cast<double>(duration.count()), 0.001, 1.0);
		const size_t readLength = static_cast<size_t>(lengthSec * samplingRate());
		int64 sum = 0;

		for (size_t samplesLeft = readLength, pos = posSample(); samplesLeft; --samplesLeft)
		{
			if (pos == 0)
			{
				pos = buffer.size();
			}

			const auto& sample = buffer[--pos];
			sum += std::abs(static_cast<int32>(sample.left));
			sum += std::abs(static_cast<int32>(sample.right));
		}

		return sum / (32768.0 * 2) / readLength;
	}

	double Microphone::rootMeanSquare(const Duration& duration) const
	{
		if (!isRecording())
		{
			return 0.0;
		}

		const Array<WaveSampleS16>& buffer = getBuffer();
		const double lengthSec = Clamp(static_cast<double>(duration.count()), 0.001, 1.0);
		const size_t readLength = static_cast<size_t>(lengthSec * samplingRate());
		double sum = 0;

		for (size_t samplesLeft = readLength, pos = posSample(); samplesLeft; --samplesLeft)
		{
			if (pos == 0)
			{
				pos = buffer.size();
			}

			const auto& sample = buffer[--pos];
			sum += Math::Square(sample.left / 32768.0);
			sum += Math::Square(sample.right / 32768.0);
		}

		return std::sqrt(sum / (readLength * 2));
	}

	double Microphone::peak(const Duration& duration) const
	{
		if (!isRecording())
		{
			return 0.0;
		}

		const Array<WaveSampleS16>& buffer = getBuffer();
		const double lengthSec = Clamp(static_cast<double>(duration.count()), 0.001, 1.0);
		const size_t readLength = static_cast<size_t>(lengthSec * samplingRate());
		int32 max = 0;

		for (size_t samplesLeft = readLength, pos = posSample(); samplesLeft; --samplesLeft)
		{
			if (pos == 0)
			{
				pos = buffer.size();
			}

			const auto& sample = buffer[--pos];
			max = std::max(std::abs(static_cast<int32>(sample.left)), max);
			max = std::max(std::abs(static_cast<int32>(sample.right)), max);
		}

		return max / 32768.0;
	}

	void Microphone::fft(FFTResult& result, const FFTSampleLength sampleLength) const
	{
		FFT::Analyze(result, getBuffer(), static_cast<uint32>(posSample()), samplingRate(), sampleLength);
	}

	bool Microphone::saveBuffer(const FilePath& path) const
	{
		if (!isAvailable())
		{
			return false;
		}

		const Array<WaveSampleS16>& buffer = getBuffer();
		Wave wave(buffer.size(), Arg::samplingRate = samplingRate());
		WaveSample* pDst = wave.data();
		const WaveSample* pDstEnd = pDst + wave.size();
		const WaveSampleS16* pSrc = buffer.data();

		while (pDst != pDstEnd)
		{
			*pDst++ = *pSrc++;
		}

		return wave.save(path);
	}
}
