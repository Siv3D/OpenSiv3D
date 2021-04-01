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
# include <Siv3D/WebPMethod.hpp>
# include <Siv3D/PredefinedYesNo.hpp>

namespace s3d
{
	class WebPEncoder : public IImageEncoder
	{
	public:

		StringView name() const override;

		const Array<String>& possibleExtensions() const override;

		bool save(const Image& image, FilePathView path) const override;
		
		bool save(const Image& image, FilePathView path, Lossless lossless, double quality, WebPMethod method) const;

		bool encode(const Image& image, IWriter& writer) const override;

		bool encode(const Image& image, IWriter& writer, Lossless lossless, double quality, WebPMethod method) const;

		Blob encode(const Image& image) const override;

		Blob encode(const Image& image, Lossless lossless, double quality, WebPMethod method) const;
	};
}
