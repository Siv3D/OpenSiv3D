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

# pragma once
# include <Siv3D/IImageDecoder.hpp>

namespace s3d
{
	class JPEGDecoder : public IImageDecoder
	{
	public:

		[[nodiscard]]
		StringView name() const override;

		[[nodiscard]]
		bool isHeader(const uint8(&bytes)[16]) const override;

		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		[[nodiscard]]
		ImageFormat imageFormat() const noexcept override;

		[[nodiscard]]
		Optional<ImageInfo> getImageInfo(FilePathView path) const override;

		[[nodiscard]]
		Optional<ImageInfo> getImageInfo(IReader& reader, FilePathView pathHint = {}) const override;

		[[nodiscard]]
		Image decode(FilePathView path) const override;

		[[nodiscard]]
		Image decode(IReader& reader, FilePathView pathHint = {}) const override;
	};
}
