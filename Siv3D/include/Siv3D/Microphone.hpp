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

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Optional.hpp"
# include "Wave.hpp"
# include "FFT.hpp"

namespace s3d
{
	enum class RecordingFormat
	{
		/// <summary>
		/// ステレオ 11,025 Hz
		/// </summary>
		S11025 = 0x00000008,

		/// <summary>
		/// ステレオ 22,050 Hz
		/// </summary>
		S22050 = 0x00000080,

		/// <summary>
		/// ステレオ 44,100 Hz
		/// </summary>
		S44100 = 0x00000800,

		/// <summary>
		/// ステレオ 48,000 Hz
		/// </summary>
		S48000 = 0x00008000,

		/// <summary>
		/// ステレオ 96,000 Hz
		/// </summary>
		S96000 = 0x00080000,

		/// <summary>
		/// デフォルト [ステレオ 44,100 Hz]
		/// </summary>
		Default = S44100,
	};

	namespace detail
	{
		inline constexpr uint32 ToSamplingRate(RecordingFormat format) noexcept
		{
			switch (format)
			{
			case RecordingFormat::S11025:
				return 11025;
			case RecordingFormat::S22050:
				return 22050;
			default:
			case RecordingFormat::S44100:
				return 44100;
			case RecordingFormat::S48000:
				return 48000;
			case RecordingFormat::S96000:
				return 96000;
			}
		}
	}

	class Microphone
	{
	private:

		class MicrophoneDetail;

		std::shared_ptr<MicrophoneDetail> pImpl;

	public:

		static constexpr size_t DefaultBuffreLength = Wave::DefaultSamplingRate * 5;

		Microphone();

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		explicit Microphone(const Optional<size_t> deviceID, RecordingFormat format = RecordingFormat::Default, size_t bufferLength = DefaultBuffreLength, bool loop = true);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Microphone();

		bool init(const Optional<size_t> deviceID, RecordingFormat format = RecordingFormat::Default, size_t bufferLength = DefaultBuffreLength, bool loop = true);

		[[nodiscard]] bool isAvailable() const;

		[[nodiscard]] explicit operator bool() const;

		void release();

		bool start();

		void stop();

		[[nodiscard]] bool isRecording() const;

		[[nodiscard]] uint32 samplingRate() const;

		[[nodiscard]] const Array<WaveSampleS16>& getBuffer() const;

		[[nodiscard]] size_t posSample() const;

		[[nodiscard]] double mean(const Duration& duration = SecondsF(0.02)) const;

		[[nodiscard]] double rootMeanSquare(const Duration& duration = SecondsF(0.02)) const;

		[[nodiscard]] double peak(const Duration& duration = SecondsF(0.02)) const;

		void fft(FFTResult& result, FFTSampleLength sampleLength = FFTSampleLength::Default) const;

		bool saveBuffer(const FilePath& path) const;
	};
}
