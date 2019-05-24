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

# include <Siv3D/DynamicTexture.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/System.hpp>
# include "WebcamDetail.hpp"

namespace s3d
{
	Webcam::WebcamDetail::WebcamDetail()
	{

	}

	Webcam::WebcamDetail::WebcamDetail(const size_t index)
		: m_index(static_cast<int32>(index))
	{
		m_initialized = open();
	}

	Webcam::WebcamDetail::~WebcamDetail()
	{
		if (!m_initialized)
		{
			return;
		}

		stop();
	}

	bool Webcam::WebcamDetail::isAvailable()
	{
		return m_initialized;
	}

	bool Webcam::WebcamDetail::start()
	{
		if (!m_initialized)
		{
			return false;
		}

		if (m_state != WebcamState::None)
		{
			return true;
		}

		if (!m_capture.isOpened())
		{
			if (!open())
			{
				return false;
			}
		}

		m_thread = std::thread(OnRunning, std::ref(*this));

		for (;;)
		{
			const WebcamState state = m_state;

			if (state == WebcamState::HasError)
			{
				return false;
			}
			
			if (state != WebcamState::None)
			{
				return true;
			}

			System::Sleep(5);
		}
	}

	void Webcam::WebcamDetail::stop()
	{
		if (!m_initialized)
		{
			return;
		}

		if (!m_thread.joinable())
		{
			return;
		}

		m_state = WebcamState::Stop;

		m_thread.join();

		m_state = WebcamState::None;
	}

	bool Webcam::WebcamDetail::isActive() const
	{
		if (!m_initialized)
		{
			return false;
		}

		return (m_state != WebcamState::None);
	}

	size_t Webcam::WebcamDetail::index() const
	{
		if (!m_initialized)
		{
			return 0;
		}

		return m_index;
	}

	Size Webcam::WebcamDetail::getResolution() const
	{
		if (!m_initialized)
		{
			return Size(0, 0);
		}

		return m_currentResolution;
	}

	bool Webcam::WebcamDetail::setResolution(const Size& resolution)
	{
		if (!m_initialized)
		{
			return false;
		}

		if (isActive())
		{
			return false;
		}

		if (m_currentResolution == resolution)
		{
			return true;
		}

		if (!open())
		{
			return false;
		}

		if (!m_capture.set(cv::CAP_PROP_FRAME_WIDTH, resolution.x)
			|| !m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, resolution.y))
		{
			m_capture.set(cv::CAP_PROP_FRAME_WIDTH, m_currentResolution.x);
			m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, m_currentResolution.y);
			return false;
		}
		else
		{
			m_capture >> m_frame;
			m_currentResolution.set(m_frame.cols, m_frame.rows);
			return (m_currentResolution == resolution);
		}
	}

	bool Webcam::WebcamDetail::hasNewFrame() const
	{
		if (!m_initialized)
		{
			return false;
		}

		return (m_state == WebcamState::Active) && (m_newFrameCount > 0);
	}

	bool Webcam::WebcamDetail::getFrame(Image& image)
	{
		if (!m_initialized)
		{
			return false;
		}

		if (m_state != WebcamState::Active)
		{
			return false;
		}

		image.resize(m_currentResolution);

		{
			std::lock_guard lock(m_imageMutex);

			std::memcpy(image.data(), m_image.data(), image.size_bytes());

			m_newFrameCount = 0;
		}

		return true;
	}

	bool Webcam::WebcamDetail::getFrame(DynamicTexture& texture)
	{
		if (!m_initialized)
		{
			return false;
		}

		if (m_state != WebcamState::Active)
		{
			return false;
		}

		{
			std::lock_guard lock(m_imageMutex);

			const bool result = texture.fill(m_image);

			m_newFrameCount = 0;

			return result;
		}
	}

	bool Webcam::WebcamDetail::open()
	{
		LOG_TRACE(U"Webcam::WebcamDetail::open()");

		if (m_capture.isOpened())
		{
			return true;
		}

		if (!m_capture.open(m_index))
		{
			LOG_ERROR(U"cv::VideoCapture::oepn({}) failed"_fmt(m_index));
			return false;
		}

		LOG_INFO(U"cv::VideoCapture::oepn({}) succeeded"_fmt(m_index));

		m_currentResolution.set(
			static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_WIDTH)),
			static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_HEIGHT)));

		return true;
	}

	void Webcam::WebcamDetail::OnRunning(WebcamDetail& webcam)
	{
		auto& capture = webcam.m_capture;
		assert(capture.isOpened());

		if (const Size targetResolution = webcam.getResolution();
			!webcam.setResolution(targetResolution))
		{
			webcam.m_state = WebcamState::HasError;
			return;
		}

		webcam.m_state = WebcamState::Ready;

		{
			std::lock_guard lock(webcam.m_imageMutex);
			webcam.m_image.resize(webcam.getResolution(), Color(255));
		}

		LOG_DEBUG(U"ℹ️ Initializing Webcam...");

		{
			int32 frameCount = 0;

			for (int32 i = 0; i < 8; ++i)
			{
				if (capture.grab() && capture.retrieve(webcam.m_frame))
				{
					++frameCount;
				}

				System::Sleep(100);

				if (frameCount >= 5)
				{
					break;
				}
			}
		}

		LOG_DEBUG(U"ℹ️ Webcam setup completed");

		webcam.m_state = WebcamState::Active;

		while (webcam.m_state != WebcamState::Stop)
		{
			if (!capture.grab() || !capture.retrieve(webcam.m_frame))
			{
				System::Sleep(5);
				continue;
			}

			{
				std::lock_guard lock(webcam.m_imageMutex);

				const size_t num_pixels	= webcam.m_image.num_pixels();
				const uint8* pSrc		= webcam.m_frame.data;
				uint8* pDst				= webcam.m_image.dataAsUint8();

				if (num_pixels % 4 == 0)
				{
					const size_t count = num_pixels / 4;

					for (size_t i = 0; i < count; ++i)
					{
						pDst[2] = pSrc[0];
						pDst[1] = pSrc[1];
						pDst[0] = pSrc[2];

						pDst[6] = pSrc[3];
						pDst[5] = pSrc[4];
						pDst[4] = pSrc[5];

						pDst[10] = pSrc[6];
						pDst[9] = pSrc[7];
						pDst[8] = pSrc[8];

						pDst[14] = pSrc[9];
						pDst[13] = pSrc[10];
						pDst[12] = pSrc[11];

						pDst += 16;
						pSrc += 12;
					}
				}
				else
				{
					for (size_t i = 0; i < num_pixels; ++i)
					{
						pDst[2] = pSrc[0];
						pDst[1] = pSrc[1];
						pDst[0] = pSrc[2];

						pDst += 4;
						pSrc += 3;
					}
				}

				++webcam.m_newFrameCount;
			}
		}

		capture.release();
	}
}
