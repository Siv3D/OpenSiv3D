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

# include <Siv3D/AudioFormat/AIFFDecoder.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AudioCodec/CAudioCodec.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	StringView AIFFDecoder::name() const
	{
		return U"AIFF"_sv;
	}

	bool AIFFDecoder::isHeader(const uint8(&bytes)[48]) const
	{
		static constexpr uint8 AIFF_HEAD1[] = { 0x46, 0x4F, 0x52, 0x4D };
		static constexpr uint8 AIFF_HEAD2[] = { 0x41, 0x49, 0x46, 0x46 };

		return (std::memcmp(bytes, AIFF_HEAD1, sizeof(AIFF_HEAD1)) == 0)
			&& (std::memcmp(bytes + 8, AIFF_HEAD2, sizeof(AIFF_HEAD2)) == 0);
	}

	const Array<String>& AIFFDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"aif", U"aiff", U"aifc" };

		return extensions;
	}

	AudioFormat AIFFDecoder::audioFormat() const noexcept
	{
		return AudioFormat::AIFF;
	}

	Wave AIFFDecoder::decode(const FilePathView path) const
	{
		if (auto p = dynamic_cast<CAudioCodec*>(SIV3D_ENGINE(AudioCodec)))
		{
			return p->decode(path, AudioFormat::AIFF);
		}
		
		return{};
	}

	Wave AIFFDecoder::decode(IReader& reader, const FilePathView path) const
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
