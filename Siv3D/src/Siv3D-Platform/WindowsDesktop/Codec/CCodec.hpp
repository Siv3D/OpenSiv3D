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
# include <wrl.h>
# include <mfapi.h>
# include <mfidl.h>
# include <Mfreadwrite.h>
# include <Codec/ICodec.hpp>

namespace s3d
{
	struct MF_Functions
	{
		decltype(MFStartup)* p_MFStartup = nullptr;
		decltype(MFShutdown)* p_MFShutdown = nullptr;

		decltype(MFCreateTranscodeTopology)* p_MFCreateTranscodeTopology = nullptr;

		// Mpflat
		decltype(MFCreateSourceResolver)* p_MFCreateSourceResolver = nullptr;
		decltype(MFCreateAttributes)* p_MFCreateAttributes = nullptr;
		decltype(MFCreateMediaType)* p_MFCreateMediaType = nullptr;
		decltype(MFCreateAsyncResult)* p_MFCreateAsyncResult = nullptr;
		decltype(MFInvokeCallback)* p_MFInvokeCallback = nullptr;
		decltype(MFCreateMemoryBuffer)* p_MFCreateMemoryBuffer = nullptr;
		decltype(MFCreateSample)* p_MFCreateSample = nullptr;
		decltype(MFFrameRateToAverageTimePerFrame)* p_MFFrameRateToAverageTimePerFrame = nullptr;

		// Mf
		decltype(MFCreateMediaSession)* p_MFCreateMediaSession = nullptr;
		decltype(MFCreateTranscodeProfile)* p_MFCreateTranscodeProfile = nullptr;
		decltype(MFTranscodeGetAudioOutputAvailableTypes)* p_MFTranscodeGetAudioOutputAvailableTypes = nullptr;
		decltype(MFGetService)* p_MFGetService = nullptr;
		decltype(MFCreateTopology)* p_MFCreateTopology = nullptr;
		decltype(MFCreateTopologyNode)* p_MFCreateTopologyNode = nullptr;
		decltype(MFCreateAudioRendererActivate)* p_MFCreateAudioRendererActivate = nullptr;
		decltype(MFCreateVideoRendererActivate)* p_MFCreateVideoRendererActivate = nullptr;

		// Mfreadwrite
		decltype(MFCreateSourceReaderFromURL)* p_MFCreateSourceReaderFromURL = nullptr;
		decltype(MFCreateSourceReaderFromByteStream)* p_MFCreateSourceReaderFromByteStream = nullptr;
		decltype(MFCreateSinkWriterFromURL)* p_MFCreateSinkWriterFromURL = nullptr;
	};

	class CCodec : public ISiv3DCodec
	{
	private:

		HINSTANCE m_MF = nullptr;
		
		HINSTANCE m_MFRW = nullptr;
		
		HINSTANCE m_MFplat = nullptr;

		MF_Functions m_functions;

		bool m_initialized = false;

		HRESULT configureAudioStream(ComPtr<IMFSourceReader>& pReader, ComPtr<IMFMediaType>& ppPCMAudio);

	public:

		CCodec();

		~CCodec() override;

		void init() override;

		Wave decode(IReader& reader) override;

		void getFunctions(MF_Functions& functions) const;
	};
}
