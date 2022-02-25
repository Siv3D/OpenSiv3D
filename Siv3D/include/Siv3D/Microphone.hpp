//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "Duration.hpp"
# include "PredefinedYesNo.hpp"
# include "FFTSampleLength.hpp"

namespace s3d
{
	class Wave;
	struct FFTResult;

	/// @brief マイク
	class Microphone
	{
	public:

		static constexpr Duration DefaultBufferDuration = SecondsF{ 5.0 };

		enum class Permission
		{
			Allowed,

			Denied,
		};

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Microphone();

		/// @brief マイクによる録音を準備します。
		/// @param startImmediately 録音を即座に開始するか
		/// @remark デフォルトの音声入力デバイス、推奨サンプリングレート、5 秒間分のバッファを使用します。
		SIV3D_NODISCARD_CXX20
		explicit Microphone(StartImmediately startImmediately);

		/// @brief マイクによる録音を準備します。
		/// @param duration 録音した音声を格納するバッファの長さ（秒）
		/// @param startImmediately 録音を即座に開始するか
		/// @remark デフォルトの音声入力デバイス、推奨サンプリングレートを使用します。
		SIV3D_NODISCARD_CXX20
		explicit Microphone(const Duration& duration, StartImmediately startImmediately);

		SIV3D_NODISCARD_CXX20
		Microphone(const Duration& duration, Loop loop = Loop::Yes, StartImmediately startImmediately = StartImmediately::No);

		SIV3D_NODISCARD_CXX20
		explicit Microphone(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate = unspecified, const Duration& duration = DefaultBufferDuration, Loop loop = Loop::Yes, StartImmediately startImmediately = StartImmediately::No);

		SIV3D_NODISCARD_CXX20
		Microphone(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, size_t bufferLength, Loop loop = Loop::Yes, StartImmediately startImmediately = StartImmediately::No);

		~Microphone();

		[[nodiscard]]
		Optional<Permission> getPermission() const;

		bool open(StartImmediately startImmediately);

		bool open(const Duration& duration, StartImmediately startImmediately);

		bool open(const Duration& duration, Loop loop = Loop::Yes, StartImmediately startImmediately = StartImmediately::No);

		bool open(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate = unspecified, const Duration& duration = SecondsF{ 5.0 }, Loop loop = Loop::Yes, StartImmediately startImmediately = StartImmediately::No);

		bool open(const Optional<uint32>& deviceIndex, const Optional<uint32>& sampleRate, size_t bufferLength, Loop loop = Loop::Yes, StartImmediately startImmediately = StartImmediately::No);

		void close();

		/// @brief マイクが利用可能かを返します。
		/// @return マイクが利用可能な場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const;

		/// @brief マイクが利用可能かを返します。
		/// @remark `Microphone::isOpen()` と同じです。
		/// @return マイクが利用可能な場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const;

		/// @brief 録音を開始します。
		/// @return 録音の開始に成功した場合 true, それ以外の場合は false
		bool start();

		/// @brief 録音を終了します。
		void stop();

		/// @brief マイクが録音中であるかを返します。
		/// @return 録音中の場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isRecording() const;

		[[nodiscard]]
		uint32 microphoneIndex() const;

		/// @brief 録音時のサンプリングレートの設定を返します。
		/// @return 録音時のサンプリングレートの設定
		[[nodiscard]]
		uint32 getSampleRate() const;

		[[nodiscard]]
		size_t getBufferLength() const;

		[[nodiscard]]
		bool isLoop() const;

		/// @brief 録音した音声を格納しているバッファを返します。
		/// @return 録音した音声を格納しているバッファ
		[[nodiscard]]
		const Wave& getBuffer() const;

		/// @brief 音声を格納するバッファの現在の書き込み位置（サンプル）を返します。
		/// @return 音声を格納するバッファの現在の書き込み位置（サンプル）
		[[nodiscard]]
		size_t posSample() const;

		[[nodiscard]]
		double mean(const Duration& duration = SecondsF{ 0.02 }) const;

		[[nodiscard]]
		double rootMeanSquare(const Duration& duration = SecondsF{ 0.02 }) const;

		[[nodiscard]]
		double peak(const Duration& duration = SecondsF{ 0.02 }) const;

		void fft(FFTResult& result, FFTSampleLength sampleLength = FFTSampleLength::Default) const;

	private:

		class MicrophoneDetail;

		std::shared_ptr<MicrophoneDetail> pImpl;
	};
}
