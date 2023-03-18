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

# include <Siv3D/Wave.hpp>
# include <Siv3D/AudioDecoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AsyncTask.hpp>

namespace s3d::Platform::Web::AudioDecoder
{
    namespace detail
    {
        using DecodeAudioCallBack = void(*)(struct AsyncDecodedAudioData*);

        struct AsyncDecodedAudioData
        {
            float* leftChannelData;
            float* rightChannelData;
            uint32 samplingRate;
            std::size_t dataLength;
            std::promise<Wave> audioPromise;

            AsyncDecodedAudioData(std::promise<Wave>&& p) : 
                audioPromise(std::move(p))
            {}
        };

        __attribute__((import_name("siv3dDecodeAudioFromFileAsync")))
        void siv3dDecodeAudioFromFileAsync(const char* filePath, DecodeAudioCallBack callback, AsyncDecodedAudioData* arg);

        void OnDecodeAudioFromFile(AsyncDecodedAudioData* data)
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

    void DecodeFromFile(const FilePathView path, std::promise<Wave> promise)
    {
        auto data = new detail::AsyncDecodedAudioData(std::move(promise));
        siv3dDecodeAudioFromFileAsync(path.toUTF8().c_str(), detail::OnDecodeAudioFromFile, data);

        LOG_TRACE(U"DecodeAudioFromFile: falling back to Browser-Supported Decoding");
    }

    AsyncTask<Wave> DecodeFromFile(const FilePathView path)
    {
        std::promise<Wave> promise;
        AsyncTask<Wave> future { promise.get_future() };

        DecodeFromFile(path, std::move(promise));
        return future;
    }
}