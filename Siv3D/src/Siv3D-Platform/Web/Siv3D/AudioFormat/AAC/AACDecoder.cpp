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

# include <Siv3D/AudioFormat/AACDecoder.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AudioCodec/CAudioCodec.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	StringView AACDecoder::name() const
	{
		return U"AAC"_sv;
	}

	bool AACDecoder::isHeader(const uint8(&bytes)[48]) const
	{
		// M4V MPEG-4 video/QuickTime file
		static constexpr uint8 M4V_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x6D, 0x70, 0x34, 0x32 };

		// M4A Apple Lossless Audio Codec file
		static constexpr uint8 M4A_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x4D, 0x34, 0x41, 0x20 };

		// MP4 ftypisom
		static constexpr uint8 MP4ISOM_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x69, 0x73, 0x6F, 0x6D };

		return (std::memcmp(bytes + 4, M4V_SIGNx, sizeof(M4V_SIGNx)) == 0
			|| std::memcmp(bytes + 4, M4A_SIGNx, sizeof(M4A_SIGNx)) == 0
			|| std::memcmp(bytes + 4, MP4ISOM_SIGNx, sizeof(MP4ISOM_SIGNx)) == 0);
	}

	const Array<String>& AACDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"m4a" };

		return extensions;
	}

	AudioFormat AACDecoder::audioFormat() const noexcept
	{
		return AudioFormat::AAC;
	}

	Wave AACDecoder::decode(const FilePathView path) const
	{
		auto p = static_cast<CAudioCodec*>(SIV3D_ENGINE(AudioCodec));
		{
			return p->decode(path, AudioFormat::AAC);
		}
	}

	Wave AACDecoder::decode(IReader& reader, const FilePathView path) const
	{
		if (path)
		{
			return decode(path);
		}
		else
		{
			const FilePath tmpPath = FileSystem::UniqueFilePath();

			Blob blob(reader);

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
