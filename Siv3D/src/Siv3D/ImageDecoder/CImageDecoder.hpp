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
# include <memory>
# include "IImageDecoder.hpp"
# include <Siv3D/IImageDecoder.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	class CImageDecoder final : public ISiv3DImageDecoder
	{
	private:

		Array<std::unique_ptr<IImageDecoder>> m_decoders;

		Array<std::unique_ptr<IImageDecoder>>::const_iterator findDecoder(ImageFormat imageFormat) const;

		Array<std::unique_ptr<IImageDecoder>>::const_iterator findDecoder(const IReader& reader, FilePathView pathHint) const;

	public:

		CImageDecoder() = default;

		~CImageDecoder() override;

		void init() override;

		Optional<ImageInfo> getImageInfo(IReader& reader, FilePathView pathHint, ImageFormat imageFormat) override;

		Image decode(IReader& reader, FilePathView pathHint, ImageFormat imageFormat) override;

		Grid<uint16> decodeGray16(IReader& reader, FilePathView pathHint, ImageFormat imageFormat) override;

		bool add(std::unique_ptr<IImageDecoder>&& decoder) override;

		void remove(StringView name) override;

		const Array<std::unique_ptr<IImageDecoder>>& enumDecoder() const noexcept override;
	};
}
