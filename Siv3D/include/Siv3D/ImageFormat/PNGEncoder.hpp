//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/IImageEncoder.hpp>
# include <Siv3D/PNGFilter.hpp>

namespace s3d
{
	class PNGEncoder : public IImageEncoder
	{
	public:

		StringView name() const override;

		const Array<String>& possibleExtensions() const override;

		bool save(const Image& image, FilePathView path) const override;

		bool save(const Image& image, FilePathView path, PNGFilter filter) const;

		bool encode(const Image& image, IWriter& writer) const override;

		bool encode(const Image& image, IWriter& writer, PNGFilter filter) const;

		Blob encode(const Image& image) const override;

		Blob encode(const Image& image, PNGFilter filter) const;
	};
}
