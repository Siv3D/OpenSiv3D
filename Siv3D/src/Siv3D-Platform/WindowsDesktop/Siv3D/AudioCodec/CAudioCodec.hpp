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
# include <Siv3D/AudioCodec/IAudioCodec.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/DLL.hpp>
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

		LibraryHandle m_MFplat = nullptr;

		//LibraryHandle m_MF = nullptr;

		LibraryHandle m_MFRW = nullptr;

		MF_Functions m_functions;

		HRESULT configureAudioStream(ComPtr<IMFSourceReader>& pReader, ComPtr<IMFMediaType>& ppPCMAudio);
	};
}
