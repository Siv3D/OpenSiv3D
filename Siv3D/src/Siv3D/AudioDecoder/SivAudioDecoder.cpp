//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/AudioDecoder.hpp>
# include <Siv3D/BinaryReader.hpp>
# include "IAudioDecoder.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	//namespace AudioDecoder
	//{
	//	Optional<AudioInfo> GetAudioInfo(const FilePathView path, const AudioFormat imageFormat)
	//	{
	//		BinaryReader reader(path);

	//		if (not reader)
	//		{
	//			return{};
	//		}

	//		return SIV3D_ENGINE(AudioDecoder)->getAudioInfo(reader, path, imageFormat);
	//	}

	//	Optional<AudioInfo> GetAudioInfo(IReader& reader, const AudioFormat imageFormat)
	//	{
	//		return SIV3D_ENGINE(AudioDecoder)->getAudioInfo(reader, {}, imageFormat);
	//	}

	//	Audio Decode(const FilePathView path, const AudioFormat imageFormat)
	//	{
	//		BinaryReader reader(path);

	//		if (not reader)
	//		{
	//			return{};
	//		}

	//		return SIV3D_ENGINE(AudioDecoder)->decode(reader, path, imageFormat);
	//	}

	//	Audio Decode(IReader& reader, const AudioFormat imageFormat)
	//	{
	//		return SIV3D_ENGINE(AudioDecoder)->decode(reader, {}, imageFormat);
	//	}

	//	Grid<uint16> DecodeGray16(FilePathView path, const AudioFormat imageFormat)
	//	{
	//		BinaryReader reader(path);

	//		if (not reader)
	//		{
	//			return{};
	//		}

	//		return SIV3D_ENGINE(AudioDecoder)->decodeGray16(reader, path, imageFormat);
	//	}

	//	Grid<uint16> DecodeGray16(IReader& reader, const AudioFormat imageFormat)
	//	{
	//		return SIV3D_ENGINE(AudioDecoder)->decodeGray16(reader, {}, imageFormat);
	//	}

	//	bool Add(std::unique_ptr<IAudioDecoder>&& decoder)
	//	{
	//		return SIV3D_ENGINE(AudioDecoder)->add(std::move(decoder));
	//	}

	//	void Remove(const StringView name)
	//	{
	//		return SIV3D_ENGINE(AudioDecoder)->remove(name);
	//	}

	//	const Array<std::unique_ptr<IAudioDecoder>>& Enum()
	//	{
	//		return SIV3D_ENGINE(AudioDecoder)->enumDecoder();
	//	}
	//}
}
