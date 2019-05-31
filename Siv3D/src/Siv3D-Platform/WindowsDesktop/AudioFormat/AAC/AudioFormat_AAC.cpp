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
# include "AudioFormat_AAC.hpp"

namespace s3d
{
	AudioFormat AudioFormat_AAC::format() const
	{
		return AudioFormat::AAC;
	}

	const Array<String>& AudioFormat_AAC::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"m4a" };

		return extensions;
	}

	bool AudioFormat_AAC::isHeader(const uint8(&bytes)[16], const IReader&) const
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

	Wave AudioFormat_AAC::decodeFromFile(const FilePath& path) const
	{
		BinaryReader reader(path);

		return decode(reader);
	}

	Wave AudioFormat_AAC::decode(IReader& reader) const
	{
		return Siv3DEngine::Get<ISiv3DCodec>()->decode(reader);
	}
}
