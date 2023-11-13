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
# include "CAudioCodec.hpp"
# include "MFRenderStream.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Wave WriteWaveData(IMFSourceReader* pReader, IMFMediaType* pAudioType)
		{
			const uint32 channel = ::MFGetAttributeUINT32(pAudioType, MF_MT_AUDIO_NUM_CHANNELS, 0);
			const uint32 sampleRate = ::MFGetAttributeUINT32(pAudioType, MF_MT_AUDIO_SAMPLES_PER_SECOND, 0);

			Wave wave;
			wave.setSampleRate(sampleRate);

			HRESULT hr = S_OK;
			ComPtr<IMFSample> pSample;
			ComPtr<IMFMediaBuffer> pBuffer;

			for (;;)
			{
				DWORD dwFlags = 0;

				hr = pReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &dwFlags, nullptr, &pSample);

				if (FAILED(hr))
				{
					break;
				}

				if (dwFlags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
				{
					break;
				}

				if (dwFlags & MF_SOURCE_READERF_ENDOFSTREAM)
				{
					break;
				}

				if (pSample == nullptr)
				{
					continue;
				}

				// Get a pointer to the audio data in the sample.
				hr = pSample->ConvertToContiguousBuffer(&pBuffer);

				if (FAILED(hr))
				{
					break;
				}

				BYTE* pAudioData = nullptr;
				DWORD cbBuffer = 0;
				hr = pBuffer->Lock(&pAudioData, nullptr, &cbBuffer);

				if (FAILED(hr))
				{
					break;
				}

				if (channel == 1)
				{
					const size_t newSize = cbBuffer / sizeof(float);
					const size_t offset = wave.lengthSample();
					wave.resize(offset + newSize);

					WaveSample* pDst = &(wave[offset]);
					const float* pSrc = static_cast<const float*>(static_cast<const void*>(pAudioData));

					for (size_t i = 0; i < newSize; ++i)
					{
						(pDst++)->set(*pSrc++);
					}
				}
				else
				{
					const size_t length = cbBuffer / sizeof(WaveSample);
					const WaveSample* pSrc = static_cast<const WaveSample*>(static_cast<const void*>(pAudioData));
					wave.insert(wave.end(), pSrc, pSrc + length);
				}

				// Unlock the buffer.
				hr = pBuffer->Unlock();

				pAudioData = nullptr;

				if (FAILED(hr))
				{
					break;
				}
			}

			if (FAILED(hr))
			{
				return{};
			}

			return wave;
		}
	}

	CAudioCodec::CAudioCodec() {}

	CAudioCodec::~CAudioCodec()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::~CAudioCodec()");

		if (m_functions.p_MFShutdown)
		{
			m_functions.p_MFShutdown();
		}

		DLL::Unload(m_MFRW);
		//DLL::Unload(m_MF);
		DLL::Unload(m_MFplat);
	}

	void CAudioCodec::init()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::init()");

		//
		//	Mfplat
		//
		m_MFplat	= DLL::LoadSystemLibrary(L"Mfplat.dll");
		m_functions.p_MFStartup							= DLL::GetFunction(m_MFplat, "MFStartup");
		m_functions.p_MFShutdown						= DLL::GetFunction(m_MFplat, "MFShutdown");
		//m_functions.p_MFCreateSourceResolver			= DLL::GetFunction(m_MFplat, "MFCreateSourceResolver");
		m_functions.p_MFCreateAttributes				= DLL::GetFunction(m_MFplat, "MFCreateAttributes");
		m_functions.p_MFCreateMediaType					= DLL::GetFunction(m_MFplat, "MFCreateMediaType");
		m_functions.p_MFCreateAsyncResult				= DLL::GetFunction(m_MFplat, "MFCreateAsyncResult");
		m_functions.p_MFInvokeCallback					= DLL::GetFunction(m_MFplat, "MFInvokeCallback");
		//m_functions.p_MFCreateMemoryBuffer				= DLL::GetFunction(m_MFplat, "MFCreateMemoryBuffer");
		//m_functions.p_MFCreateSample					= DLL::GetFunction(m_MFplat, "MFCreateSample");
		//m_functions.p_MFFrameRateToAverageTimePerFrame	= DLL::GetFunction(m_MFplat, "MFFrameRateToAverageTimePerFrame");

		//
		//	Mf
		//
		//m_MF = DLL::LoadSystemLibrary(L"Mf.dll");
		//m_functions.p_MFCreateTranscodeTopology					= DLL::GetFunction(m_MF, "MFCreateTranscodeTopology");
		//m_functions.p_MFCreateMediaSession						= DLL::GetFunction(m_MF, "MFCreateMediaSession");
		//m_functions.p_MFCreateTranscodeProfile					= DLL::GetFunction(m_MF, "MFCreateTranscodeProfile");
		//m_functions.p_MFTranscodeGetAudioOutputAvailableTypes	= DLL::GetFunction(m_MF, "MFTranscodeGetAudioOutputAvailableTypes");
		//m_functions.p_MFGetService								= DLL::GetFunction(m_MF, "MFGetService");
		//m_functions.p_MFCreateTopology							= DLL::GetFunction(m_MF, "MFCreateTopology");
		//m_functions.p_MFCreateTopologyNode						= DLL::GetFunction(m_MF, "MFCreateTopologyNode");
		//m_functions.p_MFCreateAudioRendererActivate				= DLL::GetFunction(m_MF, "MFCreateAudioRendererActivate");
		//m_functions.p_MFCreateVideoRendererActivate				= DLL::GetFunction(m_MF, "MFCreateVideoRendererActivate");

		//
		//	Mfreadwrite
		//
		m_MFRW = DLL::LoadSystemLibrary(L"Mfreadwrite.dll");
		//m_functions.p_MFCreateSourceReaderFromURL			= DLL::GetFunction(m_MFRW, "MFCreateSourceReaderFromURL");
		m_functions.p_MFCreateSourceReaderFromByteStream	= DLL::GetFunction(m_MFRW, "MFCreateSourceReaderFromByteStream");
		//m_functions.p_MFCreateSinkWriterFromURL				= DLL::GetFunction(m_MFRW, "MFCreateSinkWriterFromURL");

		if (FAILED(m_functions.p_MFStartup(MF_VERSION, 0)))
		{
			throw EngineError{ U"MFStartup() failed" };
		}
	}

	Wave CAudioCodec::decode(IReader& reader, AudioFormat)
	{
		if (not reader.isOpen())
		{
			return{};
		}

		MFReaderStream::p_MFCreateAttributes = m_functions.p_MFCreateAttributes;
		MFReaderStream::p_MFCreateAsyncResult = m_functions.p_MFCreateAsyncResult;
		MFReaderStream::p_MFInvokeCallback = m_functions.p_MFInvokeCallback;
		MFReaderStream* pMFReaderStream = new MFReaderStream(&reader);

		if (FAILED(pMFReaderStream->Open()))
		{
			pMFReaderStream->Release();
			return{};
		}

		IMFByteStream* bs = nullptr;

		HRESULT hr = pMFReaderStream->QueryInterface(IID_PPV_ARGS(&bs));
		pMFReaderStream->Release();

		if (FAILED(hr))
		{
			return{};
		}

		ComPtr<IMFSourceReader> pSourceReader;

		if (FAILED(m_functions.p_MFCreateSourceReaderFromByteStream(bs, nullptr, &pSourceReader)))
		{
			LOG_FAIL(U"✖ CAudioCodec::decode(): MFCreateSourceReaderFromByteStream");
			return{};
		}

		ComPtr<IMFMediaType> pAudioType;

		if (FAILED(configureAudioStream(pSourceReader, pAudioType)))
		{
			LOG_FAIL(U"✖ CAudioCodec::decode(): configureAudioStream (対応していないオーディオフォーマットです)");
			pMFReaderStream->Release();
			return{};
		}

		pMFReaderStream->Release();

		return detail::WriteWaveData(pSourceReader.Get(), pAudioType.Get());
	}

	bool CAudioCodec::encode(const Wave& , IWriter&, AudioFormat)
	{
		// do nothing
		return(false);
	}

	HRESULT CAudioCodec::configureAudioStream(ComPtr<IMFSourceReader>& pReader, ComPtr<IMFMediaType>& ppPCMAudio)
	{
		ComPtr<IMFMediaType> pUncompressedAudioType;
		ComPtr<IMFMediaType> pPartialType;

		// Select the first audio stream, and deselect all other streams.
		HRESULT hr = pReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, FALSE);

		if (SUCCEEDED(hr))
		{
			hr = pReader->SetStreamSelection((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, TRUE);
		}

		// Create a partial media type that specifies uncompressed PCM audio.
		if (SUCCEEDED(hr))
		{
			hr = m_functions.p_MFCreateMediaType(&pPartialType);
		}

		if (SUCCEEDED(hr))
		{
			hr = pPartialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		}

		if (SUCCEEDED(hr))
		{
			hr = pPartialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_Float);
		}

		// Set this type on the source reader. The source reader will
		// load the necessary decoder.
		if (SUCCEEDED(hr))
		{
			hr = pReader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, pPartialType.Get());
		}

		// Get the complete uncompressed format.
		if (SUCCEEDED(hr))
		{
			hr = pReader->GetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, &pUncompressedAudioType);
		}

		// Ensure the stream is selected.
		if (SUCCEEDED(hr))
		{
			hr = pReader->SetStreamSelection((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, TRUE);
		}

		// Return the PCM format to the caller.
		if (SUCCEEDED(hr))
		{
			ppPCMAudio = pUncompressedAudioType;
		}

		return hr;
	}
}
