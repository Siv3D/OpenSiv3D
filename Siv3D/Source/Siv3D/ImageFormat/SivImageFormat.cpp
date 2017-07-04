//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "IImageFormat.hpp"
# include <Siv3D/ImageFormat.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	namespace ImageProcessing
	{
		ImageFormat GetFormat(const FilePath& path)
		{
			return Siv3DEngine::GetImageFormat()->getFormatFromReader(BinaryReader(path), path);
		}

		ImageFormat GetFormat(const IReader& reader)
		{
			return Siv3DEngine::GetImageFormat()->getFormatFromReader(reader, String());
		}

		ImageFormat GetFormatFromFilePath(const FilePath& path)
		{
			return Siv3DEngine::GetImageFormat()->getFormatFromFilePath(path);
		}

		Size GetSize(const FilePath& path)
		{
			return Siv3DEngine::GetImageFormat()->getSize(BinaryReader(path), path);
		}

		Size GetSize(const IReader& reader)
		{
			return Siv3DEngine::GetImageFormat()->getSize(reader, String());
		}
	}
}
