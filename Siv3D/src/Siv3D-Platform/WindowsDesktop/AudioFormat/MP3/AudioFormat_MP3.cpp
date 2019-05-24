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


# include <Siv3DEngine.hpp>
# include <Codec/ICodec.hpp>
# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include "AudioFormat_MP3.hpp"

namespace s3d
{
	AudioFormat AudioFormat_MP3::format() const
	{
		return AudioFormat::MP3;
	}

	const Array<String>& AudioFormat_MP3::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"mp3" };

		return extensions;
	}

	bool AudioFormat_MP3::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 MPEG1_SIGN[] = { 0xFF, 0xFB };
		static constexpr uint8 MP3_SIGN[] = { 0x49, 0x44, 0x33 };

		return (std::memcmp(bytes, MPEG1_SIGN, sizeof(MPEG1_SIGN)) == 0)
		|| (std::memcmp(bytes, MP3_SIGN, sizeof(MP3_SIGN)) == 0);
	}

	Wave AudioFormat_MP3::decodeFromFile(const FilePath& path) const
	{
		BinaryReader reader(path);

		return decode(reader);
	}

	Wave AudioFormat_MP3::decode(IReader& reader) const
	{
		return Siv3DEngine::Get<ISiv3DCodec>()->decode(reader);
	}
}
