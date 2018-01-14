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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include <wrl.h>
# include <mfapi.h>
# include <mfidl.h>
# include <Mfreadwrite.h>
# include "../ICodec.hpp"

using namespace Microsoft::WRL;

namespace s3d
{
	struct MF_Functions
	{
		//using t_MFStartup = HRESULT(STDAPICALLTYPE*)(ULONG, DWORD);
		//t_MFStartup p_MFStartup = nullptr;
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

	class CCodec_MF : public ISiv3DCodec
	{
	private:

		HINSTANCE m_MF = nullptr;
		
		HINSTANCE m_MFRW = nullptr;
		
		HINSTANCE m_MFplat = nullptr;

		//using t_MFStartup = HRESULT(STDAPICALLTYPE*)(ULONG, DWORD);
		//t_MFStartup p_MFStartup = nullptr;

		decltype(MFStartup)* p_MFStartup = nullptr;

		decltype(MFShutdown)* p_MFShutdown = nullptr;

		MF_Functions m_functions;

		bool m_initialized = false;

		HRESULT configureAudioStream(ComPtr<IMFSourceReader>& pReader, ComPtr<IMFMediaType>& ppPCMAudio);

	public:

		CCodec_MF();

		~CCodec_MF() override;

		bool init() override;

		Wave decode(IReader& reader) override;
	};
}

# endif
