//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Webcam.hpp>
# include "WebcamDetail.hpp"

namespace s3d
{
	Webcam::Webcam()
		: pImpl(std::make_shared<WebcamDetail>())
	{

	}

	Webcam::Webcam(const size_t index)
		: pImpl(std::make_shared<WebcamDetail>(index))
	{

	}

	Webcam::~Webcam()
	{

	}

	bool Webcam::isAvailable() const
	{
		return pImpl->isAvailable();
	}

	Webcam::operator bool() const
	{
		return isAvailable();
	}

	bool Webcam::start()
	{
		return pImpl->start();
	}

	void Webcam::stop()
	{
		pImpl->stop();
	}

	bool Webcam::isActive() const
	{
		return pImpl->isActive();
	}

	size_t Webcam::index() const
	{
		return pImpl->index();
	}

	Size Webcam::getResolution() const
	{
		return pImpl->getResolution();
	}

	bool Webcam::setResolution(const Size& resolution)
	{
		return pImpl->setResolution(resolution);
	}
	
	bool Webcam::setResolution(const int32 width, const int32 height)
	{
		return setResolution(Size(width, height));
	}

	bool Webcam::hasNewFrame() const
	{
		return pImpl->hasNewFrame();
	}

	bool Webcam::getFrame(Image& image)
	{
		return pImpl->getFrame(image);
	}

	bool Webcam::getFrame(DynamicTexture& texture)
	{
		return pImpl->getFrame(texture);
	}
}
