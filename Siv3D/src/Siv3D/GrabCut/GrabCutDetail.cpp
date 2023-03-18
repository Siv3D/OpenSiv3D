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

# include "GrabCutDetail.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr GrabCutClass ToGrabCutValue(const uint8 maskValue) noexcept
		{
			constexpr GrabCutClass table[4] =
			{
				GrabCutClass::Background,
				GrabCutClass::Foreground,
				GrabCutClass::PossibleBackground,
				GrabCutClass::PossibleForeground,
			};

			return table[maskValue];
		}

		inline constexpr cv::GrabCutClasses ToCVGrabCutClasses(const GrabCutClass value) noexcept
		{
			constexpr cv::GrabCutClasses table[4] =
			{
				cv::GC_FGD,
				cv::GC_PR_FGD,
				cv::GC_PR_BGD,
				cv::GC_BGD,
			};

			return table[FromEnum(value)];
		}
	}

	GrabCut::GrabCutDetail::GrabCutDetail() {}

	GrabCut::GrabCutDetail::~GrabCutDetail() {}

	void GrabCut::GrabCutDetail::init(const Image& image, const GrabCutClass defaultMask)
	{
		assert((defaultMask == GrabCutClass::PossibleForeground)
			|| (defaultMask == GrabCutClass::PossibleBackground));

		m_originalImage = OpenCV_Bridge::ToMatVec3bBGR(image);

		m_maskImage = cv::Mat_<uint8>(image.height(), image.width(), static_cast<uint8>(detail::ToCVGrabCutClasses(defaultMask)));

		if (defaultMask == GrabCutClass::PossibleForeground)
		{
			m_hasForegroundPixel = true;
		}
		else
		{
			m_hasBackgroundPixel = true;
		}
	}

	void GrabCut::GrabCutDetail::initWithRect(const Image& image, const Rect& rect, const size_t iterations)
	{
		m_originalImage = OpenCV_Bridge::ToMatVec3bBGR(image);

		cv::grabCut(m_originalImage, m_maskImage, cv::Rect(rect.x, rect.y, rect.w, rect.h),
			m_backgroundModel, m_foregroundModel, static_cast<int32>(iterations), cv::GC_INIT_WITH_RECT);
	}

	void GrabCut::GrabCutDetail::update(const Image& maskImage, const Color& foreground, const Color& background, const size_t iterations)
	{
		if (maskImage.size() != Size{ m_maskImage.cols, m_maskImage.rows })
		{
			return;
		}

		const uint32 fgd = foreground.asUint32();
		const uint32 bgd = background.asUint32();
		uint8* pDst = m_maskImage.data;

		for (const auto& pixel : maskImage)
		{
			const uint32 value = pixel.asUint32();

			if (value == fgd)
			{
				*pDst = cv::GC_FGD;
				m_hasForegroundPixel = true;
			}
			else if (value == bgd)
			{
				*pDst = cv::GC_BGD;
				m_hasBackgroundPixel = true;
			}

			++pDst;
		}

		if (m_hasForegroundPixel && m_hasBackgroundPixel)
		{
			cv::grabCut(m_originalImage, m_maskImage, cv::Rect(0, 0, 0, 0),
				m_backgroundModel, m_foregroundModel, static_cast<int32>(iterations), cv::GC_INIT_WITH_MASK);
		}
	}

	void GrabCut::GrabCutDetail::getResult(Grid<GrabCutClass>& result)
	{
		const uint32 width	= m_maskImage.cols;
		const uint32 height	= m_maskImage.rows;
		result.resize(width, height);

		GrabCutClass* pDst = result.data();
		const GrabCutClass* const pDstEnd = pDst + result.num_elements();
		const uint8* pSrc = m_maskImage.data;

		while (pDst != pDstEnd)
		{
			*pDst++ = detail::ToGrabCutValue(*pSrc++);
		}
	}
}
