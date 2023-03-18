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

# include <Siv3D/Webcam.hpp>
# include "WebcamDetail.hpp"

namespace s3d
{
	Webcam::Webcam()
		: pImpl{ std::make_shared<WebcamDetail>() } {}

	Webcam::Webcam(const uint32 cameraIndex, const StartImmediately startImmediately)
		: Webcam{}
	{
		if (not pImpl->open(cameraIndex))
		{
			return;
		}

		if (startImmediately)
		{
			pImpl->start();
		}
	}

	Webcam::Webcam(const uint32 cameraIndex, const Size& targetResolution, const StartImmediately startImmediately)
		: Webcam{}
	{
		pImpl->setResolution(targetResolution);

		if (not pImpl->open(cameraIndex))
		{
			return;
		}

		if (startImmediately)
		{
			pImpl->start();
		}
	}
	
	Webcam::~Webcam()
	{
		// do nothing
	}

	Optional<Webcam::Permission> Webcam::getPermission() const
	{
		return pImpl->getPermission();
	}

	bool Webcam::open(const uint32 cameraIndex)
	{
		return pImpl->open(cameraIndex);
	}

	void Webcam::close()
	{
		pImpl->close();
	}

	bool Webcam::isOpen() const
	{
		return pImpl->isOpen();
	}
	
	Webcam::operator bool() const
	{
		return isOpen();
	}

	bool Webcam::start()
	{
		return pImpl->start();
	}

	bool Webcam::isActive() const
	{
		return pImpl->isActive();
	}

	uint32 Webcam::cameraIndex() const
	{
		return pImpl->cameraIndex();
	}

	Size Webcam::getResolution() const
	{
		return pImpl->getResolution();
	}

	bool Webcam::setResolution(const int32 width, const int32 height)
	{
		return pImpl->setResolution(Size{ width, height });
	}

	bool Webcam::setResolution(const Size resolution)
	{
		return pImpl->setResolution(resolution);
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
