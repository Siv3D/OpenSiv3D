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
# include "Common.hpp"
# include "2DShapes.hpp"
# include "Image.hpp"

namespace s3d
{
	struct ImageROI
	{
		Image& imageRef;

		Rect region;

		SIV3D_NODISCARD_CXX20
		ImageROI(Image& image, const Rect& rect) noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		ImageROI& gaussianBlur(int32 size, BorderType borderType = BorderType::Reflect_101);

		ImageROI& gaussianBlur(int32 horizontal, int32 vertical, BorderType borderType = BorderType::Reflect_101);
	};

	struct ImageConstROI
	{
		const Image& imageRef;

		Rect region;

		SIV3D_NODISCARD_CXX20
		explicit ImageConstROI(const ImageROI& imageROI) noexcept;

		SIV3D_NODISCARD_CXX20
		ImageConstROI(const Image& image, const Rect& rect) noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;
	};
}
