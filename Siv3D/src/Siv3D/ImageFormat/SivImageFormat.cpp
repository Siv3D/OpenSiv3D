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
# include <Siv3D/ImageFormat.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/PointVector.hpp>
# include "IImageFormat.hpp"

namespace s3d
{
	namespace ImageProcessing
	{
		ImageFormat GetFormat(const FilePath& path)
		{
			return Siv3DEngine::Get<ISiv3DImageFormat>()->getFormatFromReader(BinaryReader(path), path);
		}

		ImageFormat GetFormat(const IReader& reader)
		{
			return Siv3DEngine::Get<ISiv3DImageFormat>()->getFormatFromReader(reader, String());
		}

		ImageFormat GetFormatFromFilePath(const FilePath& path)
		{
			return Siv3DEngine::Get<ISiv3DImageFormat>()->getFormatFromFilePath(path);
		}

		Size GetSize(const FilePath& path)
		{
			return Siv3DEngine::Get<ISiv3DImageFormat>()->getSize(BinaryReader(path), path);
		}

		Size GetSize(const IReader& reader)
		{
			return Siv3DEngine::Get<ISiv3DImageFormat>()->getSize(reader, String());
		}
	}
}
