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

# include <Siv3D/Microphone.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/FFTResult.hpp>
# include <Siv3D/FFT.hpp>
# include <Siv3D/Microphone/MicrophoneDetail.hpp>

namespace s3d
{
	Microphone::Microphone()
		: pImpl{ std::make_shared<MicrophoneDetail>() } {}

	Microphone::Microphone(const StartImmediately startImmediately)
		: Microphone{ unspecified, unspecified, DefaultBufferDuration, Loop::Yes, startImmediately } {}

	Microphone::Microphone(const Duration& duration, const StartImmediately startImmediately)
		: Microphone{ unspecified, unspecified, duration, Loop::Yes, startImmediately } {}

	Microphone::Microphone(const Duration& duration, const Loop loop, const StartImmediately startImmediately)
		: Microphone{ unspecified, unspecified, duration, loop, startImmediately } {}

	Microphone::Microphone(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, const Duration& duration, const Loop loop, const StartImmediately startImmediately)
		: Microphone{}
	{
		if (not pImpl->open(deviceIndex, sampleRate, duration, loop))
		{
			return;
		}

		if (startImmediately)
		{
			pImpl->start();
		}
	}

	Microphone::Microphone(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, const size_t bufferLength, const Loop loop, const StartImmediately startImmediately)
		: Microphone{}
	{
		if (not pImpl->open(deviceIndex, sampleRate, bufferLength, loop))
		{
			return;
		}

		if (startImmediately)
		{
			pImpl->start();
		}
	}

	Microphone::~Microphone() {}

	Optional<Microphone::Permission> Microphone::getPermission() const
	{
		// [Siv3D ToDo]
		return Microphone::Permission::Allowed;
	}

	bool Microphone::open(const StartImmediately startImmediately)
	{
		return open(unspecified, unspecified, DefaultBufferDuration, Loop::Yes, startImmediately);
	}

	bool Microphone::open(const Duration& duration, const StartImmediately startImmediately)
	{
		return open(unspecified, unspecified, duration, Loop::Yes, startImmediately);
	}

	bool Microphone::open(const Duration& duration, const Loop loop, const StartImmediately startImmediately)
	{
		return open(unspecified, unspecified, duration, loop, startImmediately);
	}

	bool Microphone::open(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, const Duration& duration, const Loop loop, const StartImmediately startImmediately)
	{
		if (not pImpl->open(deviceIndex, sampleRate, duration, loop))
		{
			return false;
		}

		if (startImmediately)
		{
			return pImpl->start();
		}
		else
		{
			return true;
		}
	}

	bool Microphone::open(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, const size_t bufferLength, const Loop loop, const StartImmediately startImmediately)
	{
		if (not pImpl->open(deviceIndex, sampleRate, bufferLength, loop))
		{
			return false;
		}

		if (startImmediately)
		{
			return pImpl->start();
		}
		else
		{
			return true;
		}
	}

	void Microphone::close()
	{
		pImpl->close();
	}

	bool Microphone::isOpen() const
	{
		return pImpl->isOpen();
	}
	
	Microphone::operator bool() const
	{
		return isOpen();
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

	uint32 Microphone::microphoneIndex() const
	{
		return pImpl->microphoneIndex();
	}

	uint32 Microphone::getSampleRate() const
	{
		return pImpl->getSampleRate();
	}

	size_t Microphone::getBufferLength() const
	{
		return pImpl->getBufferLength();
	}

	bool Microphone::isLoop() const
	{
		return pImpl->isLoop();
	}

	const Wave& Microphone::getBuffer() const
	{
		return pImpl->getBuffer();
	}

	size_t Microphone::posSample() const
	{
		return pImpl->posSample();
	}

	double Microphone::mean(const Duration& duration) const
	{
		if (not isRecording())
		{
			return 0.0;
		}

		const Wave& wave = getBuffer();
		const size_t writePos = posSample();
		const double lengthSec = Clamp(static_cast<double>(duration.count()), 0.001, 5.0);
		const size_t readLength = static_cast<size_t>(lengthSec * getSampleRate());
		double sum = 0.0;
		{
			const size_t headLength = Min(writePos, readLength);
			const size_t tailLength = (readLength - headLength);

			if (tailLength)
			{
				const WaveSample* pSrc = &wave[wave.size() - tailLength];

				for (size_t i = 0; i < tailLength; ++i)
				{
					sum += (Abs(pSrc->left) + Abs(pSrc->right));
					++pSrc;
				}
			}

			if (headLength)
			{
				const WaveSample* pSrc = &wave[writePos - headLength];

				for (size_t i = 0; i < headLength; ++i)
				{
					sum += (Abs(pSrc->left) + Abs(pSrc->right));
					++pSrc;
				}
			}
		}

		return (sum / (readLength * 2.0));
	}

	double Microphone::rootMeanSquare(const Duration& duration) const
	{
		if (not isRecording())
		{
			return 0.0;
		}

		const Wave& wave = getBuffer();
		const size_t writePos = posSample();
		const double lengthSec = Clamp(static_cast<double>(duration.count()), 0.001, 5.0);
		const size_t readLength = static_cast<size_t>(lengthSec * getSampleRate());
		double sum = 0.0;
		{
			const size_t headLength = Min(writePos, readLength);
			const size_t tailLength = (readLength - headLength);

			if (tailLength)
			{
				const WaveSample* pSrc = &wave[wave.size() - tailLength];

				for (size_t i = 0; i < tailLength; ++i)
				{
					sum += (Math::Square(pSrc->left) + Math::Square(pSrc->right));
					++pSrc;
				}
			}

			if (headLength)
			{
				const WaveSample* pSrc = &wave[writePos - headLength];

				for (size_t i = 0; i < headLength; ++i)
				{
					sum += (Math::Square(pSrc->left) + Math::Square(pSrc->right));
					++pSrc;
				}
			}
		}

		return Math::Sqrt(sum / (readLength * 2.0));
	}

	double Microphone::peak(const Duration& duration) const
	{
		if (not isRecording())
		{
			return 0.0;
		}

		const Wave& wave = getBuffer();
		const size_t writePos = posSample();
		const double lengthSec = Clamp(static_cast<double>(duration.count()), 0.001, 5.0);
		const size_t readLength = static_cast<size_t>(lengthSec * getSampleRate());
		float max = 0.0f;
		{
			const size_t headLength = Min(writePos, readLength);
			const size_t tailLength = (readLength - headLength);

			if (tailLength)
			{
				const WaveSample* pSrc = &wave[wave.size() - tailLength];

				for (size_t i = 0; i < tailLength; ++i)
				{
					max = Max(Abs(pSrc->left), max);
					max = Max(Abs(pSrc->right), max);
					++pSrc;
				}
			}

			if (headLength)
			{
				const WaveSample* pSrc = &wave[writePos - headLength];

				for (size_t i = 0; i < headLength; ++i)
				{
					max = Max(Abs(pSrc->left), max);
					max = Max(Abs(pSrc->right), max);
					++pSrc;
				}
			}
		}

		return max;
	}

	void Microphone::fft(FFTResult& result, const FFTSampleLength sampleLength) const
	{
		FFT::Analyze(result, getBuffer(), posSample(), sampleLength);
	}
}
