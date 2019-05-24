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
# include <Siv3D/AudioFormat.hpp>
# include <Siv3D/BinaryReader.hpp>
# include "IAudioFormat.hpp"

namespace s3d
{
	namespace AudioProcessing
	{
		AudioFormat GetFormat(const FilePath& path)
		{
			return Siv3DEngine::Get<ISiv3DAudioFormat>()->getFormatFromReader(BinaryReader(path), path);
		}

		AudioFormat GetFormat(const IReader& reader)
		{
			return Siv3DEngine::Get<ISiv3DAudioFormat>()->getFormatFromReader(reader, String());
		}

		AudioFormat GetFormatFromFilePath(const FilePath& path)
		{
			return Siv3DEngine::Get<ISiv3DAudioFormat>()->getFormatFromFilePath(path);
		}
	}
}
