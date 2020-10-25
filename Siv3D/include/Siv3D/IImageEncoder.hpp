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
# include "Common.hpp"
# include "Fwd.hpp"
# include "Blob.hpp"
# include "ImageFormat.hpp"

namespace s3d
{
	class IImageEncoder
	{
	public:

		virtual ~IImageEncoder() = default;

		[[nodiscard]]
		virtual StringView name() const = 0;

		[[nodiscard]]
		virtual const Array<String>& possibleExtensions() const = 0;

		virtual bool save(const Image& image, FilePathView path) const = 0;

		virtual bool encode(const Image& image, IWriter& writer) const = 0;

		[[nodiscard]]
		virtual Blob encode(const Image& image) const = 0;
	};
}
