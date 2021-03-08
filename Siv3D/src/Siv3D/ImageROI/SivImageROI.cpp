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

# include <Siv3D/ImageROI.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Rect FitRect(const Size& size, Rect rect) noexcept
		{
			if (rect.w < 0 || rect.h < 0)
			{
				return{ 0, 0, 0, 0 };
			}

			if (rect.x < 0)
			{
				rect.w -= -rect.x;
				rect.x = 0;
			}
			else if (size.x <= rect.x)
			{
				return{ 0, 0, 0, 0 };
			}

			if (rect.y < 0)
			{
				rect.h -= -rect.y;
				rect.y = 0;
			}
			else if (size.y <= rect.y)
			{
				return{ 0, 0, 0, 0 };
			}

			if (size.x < (rect.x + rect.w))
			{
				rect.w = (size.x - rect.x);
			}
			else if ((rect.x + rect.w) <= 0)
			{
				return{ 0, 0, 0, 0 };
			}

			if (size.y < (rect.y + rect.h))
			{
				rect.h= (size.y - rect.y);
			}
			else if ((rect.y + rect.h) <= 0)
			{
				return{ 0, 0, 0, 0 };
			}

			return rect;
		}
	}

	ImageROI::ImageROI(Image& image, const Rect& rect) noexcept
		: imageRef{ image }
		, region{ detail::FitRect(image.size(), rect) } {}

	bool ImageROI::isEmpty() const noexcept
	{
		return (not region.hasArea());
	}

	ImageROI& ImageROI::gaussianBlur(const int32 size, const BorderType borderType)
	{
		return gaussianBlur(size, size, borderType);
	}

	ImageROI& ImageROI::gaussianBlur(const int32 horizontal, const int32 vertical, const BorderType borderType)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0)
				|| (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const cv::Rect roi = OpenCV_Bridge::ToCVRect(region);

			cv::Mat_<cv::Vec4b> matSrc = OpenCV_Bridge::GetMatView(imageRef);

			cv::Mat srcROI = matSrc(roi);

			cv::GaussianBlur(srcROI, srcROI, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), 0.0, 0.0, OpenCV_Bridge::ConvertBorderType(borderType));
		}

		return *this;
	}

	ImageConstROI::ImageConstROI(const ImageROI& imageROI) noexcept
		: imageRef{ imageROI.imageRef }
		, region{ imageROI.region } {}

	ImageConstROI::ImageConstROI(const Image& image, const Rect& rect) noexcept
		: imageRef{ image }
		, region{ detail::FitRect(image.size(), rect) } {}

	bool ImageConstROI::isEmpty() const noexcept
	{
		return (not region.hasArea());
	}
}
