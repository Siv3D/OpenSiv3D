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
# include "Common.hpp"
# include "ImageInfo.hpp"
# include "Image.hpp"
# include "IReader.hpp"
# include "IImageDecoder.hpp"
# include "Optional.hpp"
# include "Grid.hpp"

namespace s3d
{
	namespace ImageDecoder
	{
		[[nodiscard]]
		Optional<ImageInfo> GetImageInfo(FilePathView path, ImageFormat imageFormat = ImageFormat::Unspecified);

		[[nodiscard]]
		Optional<ImageInfo> GetImageInfo(IReader& reader, ImageFormat imageFormat = ImageFormat::Unspecified);

		[[nodiscard]]
		Image Decode(FilePathView path, ImageFormat imageFormat = ImageFormat::Unspecified);

		[[nodiscard]]
		Image Decode(IReader& reader, ImageFormat imageFormat = ImageFormat::Unspecified);

		[[nodiscard]]
		Grid<uint16> DecodeGray16(FilePathView path, ImageFormat imageFormat = ImageFormat::Unspecified);

		[[nodiscard]]
		Grid<uint16> DecodeGray16(IReader& reader, ImageFormat imageFormat = ImageFormat::Unspecified);

		template <class ImageDecoder>
		bool Add();

		bool Add(std::unique_ptr<IImageDecoder>&& decoder);

		void Remove(StringView name);

		const Array<std::unique_ptr<IImageDecoder>>& Enum();
	}
}

# include "detail/ImageDecoder.ipp"
