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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "AudioFormat_AAC_macOS.hpp"
# include "../../Siv3DEngine.hpp"
# include "../../Codec/ICodec.hpp"
# include "../../EngineUtility.hpp"

namespace s3d
{
	AudioFormat_AAC::AudioFormat_AAC()
	{

	}

	AudioFormat_AAC::~AudioFormat_AAC()
	{

	}

	AudioFormat AudioFormat_AAC::format() const
	{
		return AudioFormat::AAC;
	}

	const Array<String>& AudioFormat_AAC::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"m4a" };

		return extensions;
	}

	bool AudioFormat_AAC::isHeader(const uint8(&bytes)[16]) const
	{
		// M4V MPEG-4 video/QuickTime file
		static constexpr uint8 M4V_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x6D, 0x70, 0x34, 0x32 };

		// M4A Apple Lossless Audio Codec file
		static constexpr uint8 M4A_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x4D, 0x34, 0x41, 0x20 };

		// MP4 ftypisom
		static constexpr uint8 MP4ISOM_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x69, 0x73, 0x6F, 0x6D };

		return (::memcmp(bytes + 4, M4V_SIGNx, sizeof(M4V_SIGNx)) == 0
			|| ::memcmp(bytes + 4, M4A_SIGNx, sizeof(M4A_SIGNx)) == 0
			|| ::memcmp(bytes + 4, MP4ISOM_SIGNx, sizeof(MP4ISOM_SIGNx)) == 0);
	}

	Wave AudioFormat_AAC::decode(IReader& reader) const
	{

	}
}

# endif
