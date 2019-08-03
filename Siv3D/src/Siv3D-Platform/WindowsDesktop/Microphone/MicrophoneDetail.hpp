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

# pragma once
# include <Siv3D/Windows.hpp>
# include <Siv3D/Microphone.hpp>

namespace s3d
{
	class Microphone::MicrophoneDetail
	{
	private:

		HWAVEIN m_hWaveIn = nullptr;

		Array<WaveSampleS16> m_buffer;

		WAVEHDR m_wh = {};

		uint32 m_samplingRate = Wave::DefaultSamplingRate;

		bool m_initialized = false;

		bool m_isRecording = false;

		bool m_reachedEnd = false;

		bool m_loop = true;

		static void WaveInCallback(HWAVEIN, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR);

	public:

		MicrophoneDetail();

		~MicrophoneDetail();

		bool init(const Optional<size_t> deviceID, RecordingFormat format, size_t bufferLength, bool loop);

		bool isAvailable() const;

		void release();

		bool start();

		void stop();

		bool isRecording() const;

		uint32 samplingRate() const;

		const Array<WaveSampleS16>& getBuffer() const;

		size_t posSample() const;

		void onRead(const WaveSampleS16*, size_t samples);
	};
}
