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

# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
# include "MicrophoneDetail.hpp"

namespace s3d
{
	Microphone::MicrophoneDetail::MicrophoneDetail() {}

	Microphone::MicrophoneDetail::~MicrophoneDetail()
	{
		close();
	}

	//bool Microphone::MicrophoneDetail::open(const Optional<size_t>& deviceIndex, const Optional<uint32>& sampleRate, const size_t bufferLength, const Loop loop, const StartImmediately startImmediately)
	//{

	//}

	//void Microphone::MicrophoneDetail::close()
	//{

	//}

	//bool Microphone::MicrophoneDetail::isOpen()
	//{

	//}

	//bool Microphone::MicrophoneDetail::start()
	//{

	//}

	//bool Microphone::MicrophoneDetail::isActive() const
	//{

	//}

	//size_t Microphone::MicrophoneDetail::microphoneIndex() const
	//{

	//}

	//uint32 Microphone::MicrophoneDetail::getSampleRate() const
	//{

	//}

	//size_t Microphone::MicrophoneDetail::getBufferLength() const
	//{

	//}

	//bool Microphone::MicrophoneDetail::isLoop() const
	//{

	//}

	//const Wave& Microphone::MicrophoneDetail::getBuffer() const
	//{

	//}

	//size_t Microphone::MicrophoneDetail::posSample() const
	//{

	//}
}
