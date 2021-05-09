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
# include <Siv3D/IImageEncoder.hpp>

namespace s3d
{
	class JPEGEncoder : public IImageEncoder
	{
	public:

		[[nodiscard]]
		StringView name() const override;

		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		bool save(const Image& image, FilePathView path) const override;

		bool save(const Image& image, FilePathView path, int32 quality) const;

		bool encode(const Image& image, IWriter& writer) const override;

		bool encode(const Image& image, IWriter& writer, int32 quality) const;

		[[nodiscard]]
		Blob encode(const Image& image) const override;

		[[nodiscard]]
		Blob encode(const Image& image, int32 quality) const;
	};
}
