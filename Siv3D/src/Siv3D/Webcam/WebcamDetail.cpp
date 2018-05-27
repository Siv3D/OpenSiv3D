//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "WebcamDetail.hpp"

namespace s3d
{
	Webcam::WebcamDetail::WebcamDetail(const size_t index)
		: m_index(index)
	{
		m_available = m_capture.open(static_cast<int32>(index));

		if (!m_available)
		{
			return;
		}

		m_resolution.set(m_capture.get(cv::CAP_PROP_FRAME_WIDTH), m_capture.get(cv::CAP_PROP_FRAME_HEIGHT));

		m_capture.release();
	}

	Webcam::WebcamDetail::~WebcamDetail()
	{
		stop();
	}

	bool Webcam::WebcamDetail::isAvailable() const
	{
		return m_available;
	}

	bool Webcam::WebcamDetail::start()
	{
		return false;
	}

	void Webcam::WebcamDetail::stop()
	{

	}

	bool Webcam::WebcamDetail::isActive() const
	{
		return false;
	}

	size_t Webcam::WebcamDetail::index() const
	{
		return m_index;
	}

	Size Webcam::WebcamDetail::getResolution() const
	{
		return m_resolution;
	}

	void Webcam::WebcamDetail::setResolution(const Size& size)
	{

	}
}
