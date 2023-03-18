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
# include <Siv3D/ImageInfo.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Grid.hpp>
# include <Siv3D/IImageDecoder.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DImageDecoder
	{
	public:

		static ISiv3DImageDecoder* Create();

		virtual ~ISiv3DImageDecoder() = default;

		virtual void init() = 0;

		virtual Optional<ImageInfo> getImageInfo(IReader& reader, FilePathView pathHint, ImageFormat imageFormat) = 0;

		virtual Image decode(IReader& reader, FilePathView pathHint, ImageFormat imageFormat) = 0;

		virtual Grid<uint16> decodeGray16(IReader& reader, FilePathView pathHint, ImageFormat imageFormat) = 0;

		virtual bool add(std::unique_ptr<IImageDecoder>&& decoder) = 0;

		virtual void remove(StringView name) = 0;

		virtual const Array<std::unique_ptr<IImageDecoder>>& enumDecoder() const noexcept = 0;
	};
}
