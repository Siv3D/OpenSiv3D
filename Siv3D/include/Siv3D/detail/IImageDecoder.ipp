//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline Optional<ImageInfo> IImageDecoder::getImageInfo(const FilePathView path) const
	{
		BinaryReader reader{ path };

		if (not reader)
		{
			return{};
		}

		return getImageInfo(reader, path);
	}

	inline Image IImageDecoder::decode(const FilePathView path) const
	{
		BinaryReader reader{ path };

		if (not reader)
		{
			return{};
		}

		return decode(reader, path);
	}

	inline Grid<uint16> IImageDecoder::decodeGray16(const FilePathView path) const
	{
		BinaryReader reader{ path };

		if (not reader)
		{
			return{};
		}

		return decodeGray16(reader, path);
	}

	inline Grid<uint16> IImageDecoder::decodeGray16(IReader&, FilePathView) const
	{
		return{};
	}
}
