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

# include <Siv3D/AudioFormat/WMADecoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AudioCodec/IAudioCodec.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	StringView WMADecoder::name() const
	{
		return U"WMA"_sv;
	}

	bool WMADecoder::isHeader(const uint8(&bytes)[48]) const
	{
		// Object ID: 75B22630-668E-11CF-A6D9-00AA0062CE6C
		static constexpr uint8 ASF_GUID[] = { 0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11, 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C };

		return (std::memcmp(bytes, ASF_GUID, sizeof(ASF_GUID)) == 0);
	}

	const Array<String>& WMADecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"m4a" };

		return extensions;
	}

	AudioFormat WMADecoder::audioFormat() const noexcept
	{
		return AudioFormat::WMA;
	}

	Wave WMADecoder::decode(const FilePathView path) const
	{
		return IAudioDecoder::decode(path);
	}

	Wave WMADecoder::decode(IReader& reader, const FilePathView pathHint) const
	{
		if (not reader.isOpen())
		{
			return{};
		}

		return SIV3D_ENGINE(AudioCodec)->decode(reader, AudioFormat::WMA);
	}
}
