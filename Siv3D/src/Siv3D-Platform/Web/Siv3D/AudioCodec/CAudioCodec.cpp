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

# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/AudioDecoder.hpp>
# include "CAudioCodec.hpp"

namespace s3d
{
	namespace detail
    {
        struct DecodedAudioData
        {
            float* leftChannelData;
            float* rightChannelData;
            uint32 samplingRate;
            std::size_t dataLength;
        };
	}

	CAudioCodec::CAudioCodec()
	{
		// do nothing
	}

	CAudioCodec::~CAudioCodec()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::~CAudioCodec()");
	}

	void CAudioCodec::init()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::init()");
	}

	Wave CAudioCodec::decode(IReader& reader, AudioFormat format)
	{
		String path{U"/tmp/audio"};
		BinaryWriter writer{path};
		Array<uint8> buffer;
		buffer.resize(4096);

		while (true)
		{
			auto size = reader.read(buffer.data(), buffer.size());

			if (size == 0)
			{
				break;
			}

			writer.write(buffer.data(), size);
		}

		return decode(path, format);
	}

	bool CAudioCodec::encode(const Wave& , IWriter&, AudioFormat)
	{
		// do nothing
		return(false);
	}

	Wave CAudioCodec::decode(const FilePathView path, const AudioFormat)
	{
		auto audioFuture = Platform::Web::AudioDecoder::DecodeFromFile(path);
		
		if (auto audio = Platform::Web::System::AwaitAsyncTask(audioFuture))
		{
			return *audio;
		}
		else
		{
			LOG_WARNING(U"cannot decode .mp3 or .aac files without Asyncify. Please confirm that linker option contains `-sASYNCIFY=1`");
			return{};
		}
	}	
}
