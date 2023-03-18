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

# include <Siv3D/AudioFormat/OpusEncoder.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/ogg/ogg.h>
#	include <ThirdParty-prebuilt/opus/opus.h>
#	include <ThirdParty-prebuilt/opus/opus_multistream.h>
#	include <ThirdParty-prebuilt/opus/opusfile.h>
# else
#	include <ogg/ogg.h>
#	include <opus/opus.h>
#	include <opus/opus_multistream.h>
#	include <ThirdParty-prebuilt/opus/opusfile.h>
# endif

namespace s3d
{
	//StringView OpusEncoder::name() const
	//{
	//	return U"Opus"_sv;
	//}

	//const Array<String>& OpusEncoder::possibleExtensions() const
	//{
	//	static const Array<String> extensions = { U"opus" };

	//	return extensions;
	//}

	//bool OpusEncoder::save(const Wave& wave, const FilePathView path) const
	//{
	//	return save(wave, path, DefaultBitrate);
	//}

	//bool OpusEncoder::save(const Wave& wave, const FilePathView path, const int32 bitrate) const
	//{
	//	BinaryWriter writer{ path };

	//	if (not writer)
	//	{
	//		return false;
	//	}

	//	return encode(wave, writer, bitrate);
	//}

	//bool OpusEncoder::encode(const Wave& wave, IWriter& writer) const
	//{
	//	return encode(wave, writer, DefaultBitrate);
	//}

	//bool OpusEncoder::encode(const Wave& wave, IWriter& writer, const int32 bitrate) const
	//{
	//	if (!wave || !writer.isOpen())
	//	{
	//		return false;
	//	}

	//	//const int32 inputRate = wave.sampleRate();
	//	//int32 coding_rate;
	//	//if (inputRate > 24000)coding_rate = 48000;
	//	//else if (inputRate > 16000)coding_rate = 24000;
	//	//else if (inputRate > 12000)coding_rate = 16000;
	//	//else if (inputRate > 8000)coding_rate = 12000;
	//	//else coding_rate = 8000;

	//	return true;
	//}

	//Blob OpusEncoder::encode(const Wave& wave) const
	//{
	//	return encode(wave, DefaultBitrate);
	//}

	//Blob OpusEncoder::encode(const Wave& wave, const int32 bitrate) const
	//{
	//	MemoryWriter writer;

	//	if (not encode(wave, writer, bitrate))
	//	{
	//		return{};
	//	}

	//	return writer.retrieve();
	//}
}
