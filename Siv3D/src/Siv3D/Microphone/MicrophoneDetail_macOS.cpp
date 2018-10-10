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
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "MicrophoneDetail_macOS.hpp"

namespace s3d
{
	Microphone::MicrophoneDetail::MicrophoneDetail()
	{
		// [Siv3D ToDo]
	}

	Microphone::MicrophoneDetail::~MicrophoneDetail()
	{
		// [Siv3D ToDo]
	}

	bool Microphone::MicrophoneDetail::init(const Optional<size_t> deviceID, const RecordingFormat format, const size_t bufferLength, const bool loop)
	{
		// [Siv3D ToDo]
		return false;
	}

	bool Microphone::MicrophoneDetail::isAvailable() const
	{
		// [Siv3D ToDo]
		return false;
	}

	void Microphone::MicrophoneDetail::release()
	{
		// [Siv3D ToDo]
	}

	bool Microphone::MicrophoneDetail::start()
	{
		// [Siv3D ToDo]
		return false;
	}

	void Microphone::MicrophoneDetail::stop()
	{
		// [Siv3D ToDo]
	}

	bool Microphone::MicrophoneDetail::isRecording() const
	{
		// [Siv3D ToDo]
		return false;
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
		// [Siv3D ToDo]
		return 0;
	}
}

# endif
