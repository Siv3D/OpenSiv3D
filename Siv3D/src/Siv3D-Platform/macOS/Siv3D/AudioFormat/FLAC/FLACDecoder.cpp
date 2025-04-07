//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/AudioFormat/FLACDecoder.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AudioCodec/CAudioCodec.hpp>
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
		if (auto p = dynamic_cast<CAudioCodec*>(SIV3D_ENGINE(AudioCodec)))
		{
			return p->decode(path, AudioFormat::FLAC);
		}
		
		return{};
	}

	Wave FLACDecoder::decode(IReader& reader, const FilePathView path) const
	{
		if (path)
		{
			return decode(path);
		}
		else
		{
			const FilePath tmpPath = FileSystem::UniqueFilePath();

			Blob blob{ reader };
			
			if (not blob.save(tmpPath))
			{
				return{};
			}
			
			const Wave result = decode(tmpPath);
			
			FileSystem::Remove(tmpPath);
			
			return result;
		}
	}
}
