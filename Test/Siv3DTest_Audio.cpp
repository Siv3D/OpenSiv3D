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

# include "Siv3DTest.hpp"

TEST_CASE("Audio")
{
	SECTION("Decoder WAVE")
	{
		const FilePathView path = U"test/audio/sample.wav";
		const auto format = AudioDecoder::GetAudioFormat(path);
		REQUIRE(format == AudioFormat::WAVE);

		const Wave wave(path);
		REQUIRE(wave.sampleRate() == 44100);
		REQUIRE(wave.samples() == 87813);
	}

	SECTION("Decoder OggVorbis")
	{
		const FilePathView path = U"test/audio/sample.ogg";
		const auto format = AudioDecoder::GetAudioFormat(path);
		REQUIRE(format == AudioFormat::OggVorbis);

		const Wave wave(path);
		REQUIRE(wave.sampleRate() == 44100);
		REQUIRE(wave.samples() == 83968);
	}

	SECTION("Decoder MP3")
	{
		const FilePathView path = U"test/audio/sample.mp3";
		const auto format = AudioDecoder::GetAudioFormat(path);
		REQUIRE(format == AudioFormat::MP3);

		const Wave wave(path);
		REQUIRE(wave.sampleRate() == 48000);
		REQUIRE(wave.samples() == 63999);
	}

	SECTION("Decoder AAC")
	{
		const FilePathView path = U"test/audio/sample.aac";
		const auto format = AudioDecoder::GetAudioFormat(path);
		REQUIRE(format == AudioFormat::AAC);

		const Wave wave(path);
		REQUIRE(wave.sampleRate() == 44100);
		REQUIRE(wave.samples() == 87813);
	}
}
