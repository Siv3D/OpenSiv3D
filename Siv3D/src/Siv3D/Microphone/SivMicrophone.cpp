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

# include <Siv3D/Microphone.hpp>
# include <Siv3D/Microphone/MicrophoneDetail.hpp>

namespace s3d
{
	Microphone::Microphone()
		: pImpl{ std::make_shared<MicrophoneDetail>() } {}

	Microphone::Microphone(const Optional<size_t>& deviceIndex, const Optional<uint32>& sampleRate, size_t bufferLength, Loop loop, StartImmediately startImmediately)
		: Microphone{}
	{
		if (not pImpl->open(deviceIndex, sampleRate, bufferLength, loop, startImmediately))
		{
			return;
		}

		if (startImmediately)
		{
			pImpl->start();
		}
	}

	Microphone::~Microphone()
	{
		// do nothing
	}

	Optional<Microphone::Permission> Microphone::getPermission() const
	{
		// [Siv3D ToDo]
		return Microphone::Permission::Allowed;
	}

	bool Microphone::open(const Optional<size_t>& deviceIndex, const Optional<uint32>& sampleRate, const size_t bufferLength, const Loop loop, const StartImmediately startImmediately)
	{
		return pImpl->open(deviceIndex, sampleRate, bufferLength, loop, startImmediately);
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

	bool Microphone::isActive() const
	{
		return pImpl->isActive();
	}

	size_t Microphone::microphoneIndex() const
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
}
