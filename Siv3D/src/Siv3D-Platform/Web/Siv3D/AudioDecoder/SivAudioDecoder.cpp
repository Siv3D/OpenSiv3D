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

# include <Siv3D/Wave.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d::Platform::Web::AudioDecoder
{
    namespace detail
    {
        using DecodeAudioCallBack = void(*)(struct DecodedAudioData*);

        struct DecodedAudioData
        {
            float* leftChannelData;
            float* rightChannelData;
            uint32 samplingRate;
            std::size_t dataLength;
            std::promise<Wave> audioPromise;

            DecodedAudioData(std::promise<Wave>&& p) : 
                audioPromise(std::move(p))
            {}
        };

        __attribute__((import_name("siv3dDecodeAudioFromFile")))
        void siv3dDecodeAudioFromFile(const char* filePath, DecodeAudioCallBack callback, DecodedAudioData* arg);

        void OnDecodeAudioFromFile(DecodedAudioData* data)
        {
            if (data->dataLength > 0)
            {
                Wave wave { data->dataLength, data->samplingRate };

                for (uint32 i = 0; i < data->dataLength; i++)
                {
                    wave[i].set(data->leftChannelData[i], data->rightChannelData[i]);
                }

                data->audioPromise.set_value(Wave(std::move(wave)));

                if (data->leftChannelData != data->rightChannelData) 
                {
                    ::free(data->rightChannelData);
                }

                ::free(data->leftChannelData);
            }
            else
            {
                data->audioPromise.set_value(Wave{});
            }
                  
            delete data;
        }
    }

    void DecodeFromFile(const FilePath& path, std::promise<Wave> promise)
    {
        if (Wave processedByEmbeddedCodec(path); !processedByEmbeddedCodec.isEmpty())
        {
            // Immediately resolve
            promise.set_value(processedByEmbeddedCodec);
        }
        else
        {
            auto data = new detail::DecodedAudioData(std::move(promise));
            siv3dDecodeAudioFromFile(path.toUTF8().c_str(), detail::OnDecodeAudioFromFile, data);

            LOG_TRACE(U"DecodeAudioFromFile: falling back to Browser-Supported Decoding");
        }
    }

    std::future<Wave> DecodeFromFile(const FilePath& path)
    {
        std::promise<Wave> promise;
        auto future = promise.get_future();

        DecodeFromFile(path, std::move(promise));
        return future;
    }
}