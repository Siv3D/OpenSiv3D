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

# include <Siv3D/AudioFormat/MP3Decoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AudioCodec/IAudioCodec.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	StringView MP3Decoder::name() const
	{
		return U"MP3"_sv;
	}

	bool MP3Decoder::isHeader(const uint8(&bytes)[48]) const
	{
		static constexpr uint8 MPEG1_SIGN[] = { 0xFF, 0xFB };
		static constexpr uint8 MP3_SIGN[] = { 0x49, 0x44, 0x33 };

		return (std::memcmp(bytes, MPEG1_SIGN, sizeof(MPEG1_SIGN)) == 0)
			|| (std::memcmp(bytes, MP3_SIGN, sizeof(MP3_SIGN)) == 0);
	}

	const Array<String>& MP3Decoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"mp3" };

		return extensions;
	}

	AudioFormat MP3Decoder::audioFormat() const noexcept
	{
		return AudioFormat::MP3;
	}

	Wave MP3Decoder::decode(const FilePathView path) const
	{
		return IAudioDecoder::decode(path);
	}

	Wave MP3Decoder::decode(IReader& reader, const FilePathView pathHint) const
	{
		if (not reader.isOpen())
		{
			return{};
		}

		return SIV3D_ENGINE(AudioCodec)->decode(reader, AudioFormat::MP3);
	}
}
