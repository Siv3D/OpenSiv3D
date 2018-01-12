//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "IAudioFormat.hpp"
# include <Siv3D/AudioFormat.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	namespace AudioProcessing
	{
		AudioFormat GetFormat(const FilePath& path)
		{
			return Siv3DEngine::GetAudioFormat()->getFormatFromReader(BinaryReader(path), path);
		}

		AudioFormat GetFormat(const IReader& reader)
		{
			return Siv3DEngine::GetAudioFormat()->getFormatFromReader(reader, String());
		}

		AudioFormat GetFormatFromFilePath(const FilePath& path)
		{
			return Siv3DEngine::GetAudioFormat()->getFormatFromFilePath(path);
		}
	}
}
