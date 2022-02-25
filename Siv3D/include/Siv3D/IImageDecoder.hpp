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
# include "String.hpp"
# include "Array.hpp"
# include "ImageInfo.hpp"
# include "Image.hpp"
# include "Optional.hpp"
# include "Grid.hpp"
# include "BinaryReader.hpp"

namespace s3d
{
	struct IImageDecoder
	{
		virtual ~IImageDecoder() = default;

		[[nodiscard]]
		virtual StringView name() const = 0;

		[[nodiscard]]
		virtual ImageFormat imageFormat() const noexcept = 0;

		[[nodiscard]]
		virtual bool isHeader(const uint8(&bytes)[16]) const = 0;

		[[nodiscard]]
		virtual const Array<String>& possibleExtensions() const = 0;

		[[nodiscard]]
		virtual Optional<ImageInfo> getImageInfo(FilePathView path) const;

		[[nodiscard]]
		virtual Optional<ImageInfo> getImageInfo(IReader& reader, FilePathView pathHint) const = 0;

		[[nodiscard]]
		virtual Image decode(FilePathView path) const;

		[[nodiscard]]
		virtual Image decode(IReader& reader, FilePathView pathHint) const = 0;

		[[nodiscard]]
		virtual Grid<uint16> decodeGray16(FilePathView path) const;

		[[nodiscard]]
		virtual Grid<uint16> decodeGray16(IReader&, FilePathView) const;
	};
}

# include "detail/IImageDecoder.ipp"
