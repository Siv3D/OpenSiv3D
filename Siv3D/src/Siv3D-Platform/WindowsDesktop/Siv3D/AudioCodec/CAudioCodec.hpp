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

# pragma once
# include <Siv3D/AudioCodec/IAudioCodec.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include "MF_Functions.hpp"

namespace s3d
{
	class CAudioCodec final : public ISiv3DAudioCodec
	{
	public:

		CAudioCodec();

		~CAudioCodec() override;

		void init() override;
	
		Wave decode(IReader& reader, AudioFormat audioFormat) override;
		
		bool encode(const Wave& wave, IWriter& writer, AudioFormat audioFormat) override;

	private:

		HINSTANCE m_MF = nullptr;

		HINSTANCE m_MFRW = nullptr;

		HINSTANCE m_MFplat = nullptr;

		MF_Functions m_functions;

		HRESULT configureAudioStream(ComPtr<IMFSourceReader>& pReader, ComPtr<IMFMediaType>& ppPCMAudio);
	};
}
