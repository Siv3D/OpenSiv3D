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

# pragma once
# include <Siv3D/Windows/Windows.hpp>
# include <mfapi.h>
# include <mfidl.h>
# include <Mfreadwrite.h>

namespace s3d
{
	struct MF_Functions
	{
		// Mpflat
		decltype(MFStartup)* p_MFStartup = nullptr;
		decltype(MFShutdown)* p_MFShutdown = nullptr;
		//decltype(MFCreateSourceResolver)* p_MFCreateSourceResolver = nullptr;
		decltype(MFCreateAttributes)* p_MFCreateAttributes = nullptr;
		decltype(MFCreateMediaType)* p_MFCreateMediaType = nullptr;
		decltype(MFCreateAsyncResult)* p_MFCreateAsyncResult = nullptr;
		decltype(MFInvokeCallback)* p_MFInvokeCallback = nullptr;
		//decltype(MFCreateMemoryBuffer)* p_MFCreateMemoryBuffer = nullptr;
		//decltype(MFCreateSample)* p_MFCreateSample = nullptr;
		//decltype(MFFrameRateToAverageTimePerFrame)* p_MFFrameRateToAverageTimePerFrame = nullptr;

		// Mf
		//decltype(MFCreateTranscodeTopology)* p_MFCreateTranscodeTopology = nullptr;
		//decltype(MFCreateMediaSession)* p_MFCreateMediaSession = nullptr;
		//decltype(MFCreateTranscodeProfile)* p_MFCreateTranscodeProfile = nullptr;
		//decltype(MFTranscodeGetAudioOutputAvailableTypes)* p_MFTranscodeGetAudioOutputAvailableTypes = nullptr;
		//decltype(MFGetService)* p_MFGetService = nullptr;
		//decltype(MFCreateTopology)* p_MFCreateTopology = nullptr;
		//decltype(MFCreateTopologyNode)* p_MFCreateTopologyNode = nullptr;
		//decltype(MFCreateAudioRendererActivate)* p_MFCreateAudioRendererActivate = nullptr;
		//decltype(MFCreateVideoRendererActivate)* p_MFCreateVideoRendererActivate = nullptr;

		// Mfreadwrite
		//decltype(MFCreateSourceReaderFromURL)* p_MFCreateSourceReaderFromURL = nullptr;
		decltype(MFCreateSourceReaderFromByteStream)* p_MFCreateSourceReaderFromByteStream = nullptr;
		//decltype(MFCreateSinkWriterFromURL)* p_MFCreateSinkWriterFromURL = nullptr;
	};
}
