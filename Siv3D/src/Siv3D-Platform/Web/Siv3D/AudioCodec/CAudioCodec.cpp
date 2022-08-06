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

# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/BinaryWriter.hpp>
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

		__attribute__((import_name("siv3dDecodeAudioFromFile")))
        void siv3dDecodeAudioFromFile(const char* filePath, DecodedAudioData* data);
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

	Wave CAudioCodec::decode(const FilePathView path, const AudioFormat audioFormat)
	{
		detail::DecodedAudioData data;
		detail::siv3dDecodeAudioFromFile(path.toUTF8().c_str(), &data);

		if (data.dataLength > 0)
		{
			Wave wave { data.dataLength, data.samplingRate };

			for (uint32 i = 0; i < data.dataLength; i++)
			{
				wave[i].set(data.leftChannelData[i], data.rightChannelData[i]);
			}

			if (data.leftChannelData != data.rightChannelData) 
			{
				::free(data.rightChannelData);
			}

			::free(data.leftChannelData);

			return wave;
		}
		else
		{
			return{};
		}
	}	
}
