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
# include <memory>
# include "Common.hpp"
# include "IImageEncoder.hpp"

namespace s3d
{
	namespace ImageEncoder
	{
		bool Save(const Image& image, ImageFormat format, FilePathView path);

		bool Save(const Image& image, const String& encoderName, FilePathView path);

		bool Encode(const Image& image, ImageFormat format, IWriter& writer);

		bool Encode(const Image& image, const String& encoderName, IWriter& writer);

		Blob Encode(const Image& image, ImageFormat format);

		Blob Encode(const Image& image, const String& encoderName);

		template <class ImageEncoder>
		bool Add();

		bool Add(std::unique_ptr<IImageEncoder>&& encoder);

		void Remove(StringView name);

		const Array<std::unique_ptr<IImageEncoder>>& Enum();
	}
}

# include "detail/ImageEncoder.ipp"
