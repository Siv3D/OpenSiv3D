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

# pragma once
# include <Siv3D/Common.hpp>

namespace s3d
{
# pragma pack (push, 1)

	struct RiffHeader
	{
		uint8 riff[4];
		uint32 fileSizeWithoutHead8;
		uint8 type[4];
	};

	struct ChunkHeader
	{
		uint8 chunkID[4];
		uint32 chunkSize;
	};

	struct FormatHeader
	{
		uint16 formatID;
		uint16 channels;
		uint32 samplerate;
		uint32 bytePerSec;
		uint16 blockAlign;
		uint16 bitsWidth;
	};

	struct WS8bit
	{
		uint8 left;
		uint8 right;
	};

	struct WaveSmaple24S_Mono
	{
		uint8 mono[3];
	};

	struct WaveSmaple24S_Stereo
	{
		uint8 left[3];
		uint8 right[3];
	};

# pragma pack ( pop )

# define WAVE_FORMAT_IEEE_FLOAT 0x0003

	namespace detail
	{
		inline constexpr uint8 RIFF_SIGN[] = { 'R', 'I', 'F', 'F' };
		inline constexpr uint8 WAVE_SIGN[] = { 'W', 'A', 'V', 'E' };
		inline constexpr uint8 FMT_CHUNK[] = { 'f', 'm', 't', ' ' };
		inline constexpr uint8 DATA_CHUNK[] = { 'd', 'a', 't', 'a' };

		template <size_t Size>
		inline bool MemEqual(const uint8(&s1)[Size], const uint8(&s2)[Size])
		{
			return std::memcmp(s1, s2, Size) == 0;
		}
	}
}
