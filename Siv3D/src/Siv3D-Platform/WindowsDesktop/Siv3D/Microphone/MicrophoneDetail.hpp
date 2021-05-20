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

# pragma once
# include <Siv3D/Microphone.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	class Microphone::MicrophoneDetail
	{
	public:

		MicrophoneDetail();

		~MicrophoneDetail();

		[[nodiscard]]
		bool open(const Optional<size_t>& deviceIndex, const Optional<uint32>& sampleRate, size_t bufferLength, Loop loop, StartImmediately startImmediately);

		void close();

		[[nodiscard]]
		bool isOpen();

		bool start();

		[[nodiscard]]
		bool isActive() const;

		[[nodiscard]]
		size_t microphoneIndex() const;

		[[nodiscard]]
		uint32 getSampleRate() const;

		[[nodiscard]]
		size_t getBufferLength() const;

		[[nodiscard]]
		bool isLoop() const;

		[[nodiscard]]
		const Wave& getBuffer() const;

		[[nodiscard]]
		size_t posSample() const;

	private:

		HWAVEIN m_hWaveIn = nullptr;

		Wave m_buffer;

		WAVEHDR m_wh = {};

		uint32 m_sampleRate = Wave::DefaultSampleRate;

		bool m_initialized = false;

		bool m_isRecording = false;

		bool m_reachedEnd = false;

		bool m_loop = true;
	};
}
