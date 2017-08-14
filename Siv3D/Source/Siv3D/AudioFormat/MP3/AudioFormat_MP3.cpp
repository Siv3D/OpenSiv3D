//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "AudioFormat_MP3.hpp"
# include "../../Siv3DEngine.hpp"
# include "../../Codec/ICodec.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	AudioFormat AudioFormat_MP3::format() const
	{
		return AudioFormat::MP3;
	}

	const Array<String>& AudioFormat_MP3::possibleExtexsions() const
	{
		static const Array<String> extensions = { S3DSTR("mp3") };

		return extensions;
	}

	bool AudioFormat_MP3::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 MPEG1_SIGN[] = { 0xFF, 0xFB };
		static constexpr uint8 MP3_SIGN[] = { 0x49, 0x44, 0x33 };

		return ::memcmp(bytes, MPEG1_SIGN, sizeof(MPEG1_SIGN))
			|| ::memcmp(bytes, MP3_SIGN, sizeof(MP3_SIGN));
	}

	Wave AudioFormat_MP3::decode(IReader& reader) const
	{
		return Siv3DEngine::GetCodec()->decode(reader);
	}
}
