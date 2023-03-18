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

# include <Siv3D/AudioFormat/FLACDecoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AudioCodec/IAudioCodec.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	StringView FLACDecoder::name() const
	{
		return U"FLAC"_sv;
	}

	bool FLACDecoder::isHeader(const uint8(&bytes)[48]) const
	{
		static constexpr uint8 FLAC_MARKER[] = { 0x66, 0x4C, 0x61, 0x43 };

		return (std::memcmp(bytes, FLAC_MARKER, sizeof(FLAC_MARKER)) == 0);
	}

	const Array<String>& FLACDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"flac" };

		return extensions;
	}

	AudioFormat FLACDecoder::audioFormat() const noexcept
	{
		return AudioFormat::FLAC;
	}

	Wave FLACDecoder::decode(const FilePathView path) const
	{
		return IAudioDecoder::decode(path);
	}

	Wave FLACDecoder::decode(IReader& reader, [[maybe_unused]] const FilePathView pathHint) const
	{
		if (not reader.isOpen())
		{
			return{};
		}

		return SIV3D_ENGINE(AudioCodec)->decode(reader, AudioFormat::FLAC);
	}
}
