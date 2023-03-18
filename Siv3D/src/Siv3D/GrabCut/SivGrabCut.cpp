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

# include <Siv3D/Image.hpp>
# include <Siv3D/GrabCut.hpp>
# include <Siv3D/GrabCut/GrabCutDetail.hpp>

namespace s3d
{
	GrabCut::GrabCut()
		: pImpl{ std::make_shared<GrabCutDetail>() } {}

	GrabCut::GrabCut(const Image& image, const GrabCutClass defaultMask)
		: GrabCut{}
	{
		pImpl->init(image, defaultMask);
	}

	GrabCut::GrabCut(const Image& image, const Rect& backgroundRect, const size_t iterations)
		: GrabCut{}
	{
		pImpl->initWithRect(image, backgroundRect, iterations);
	}

	void GrabCut::update(const Image& maskImage, const Color& foreground, const Color& background, const size_t iterations)
	{
		pImpl->update(maskImage, foreground, background, iterations);
	}

	void GrabCut::getResult(Grid<GrabCutClass>& result)
	{
		pImpl->getResult(result);
	}
}
