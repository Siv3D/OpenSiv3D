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

# include "WebcamDetail.hpp"
# include <Siv3D/DynamicTexture.hpp>
# include <Siv3D/Logger.hpp>
# include <Siv3D/System.hpp>

namespace s3d
{
	void WebcamData::OnRunning(WebcamData& webcam, const int32 index)
	{
		if (!webcam.open(index))
		{
			webcam.m_state = WebcamState::HasError;
			return;
		}

		if (const Size targetResolution = webcam.getResolution(); !webcam.setResolution(targetResolution))
		{
			webcam.release();
			webcam.m_state = WebcamState::HasError;
			return;
		}

		webcam.m_state = WebcamState::Ready;
			
		{
			std::lock_guard<std::mutex> lock(webcam.m_imageMutex);

			webcam.m_image.resize(webcam.getResolution(), Color(255));
		}

		LOG_DEBUG(U"ℹ️ Initializing Webcam...");

		{
			int32 frameCount = 0;

			for (int32 i = 0; i < 8; ++i)
			{
				if (webcam.retrieve())
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
			if (webcam.m_state == WebcamState::Pause)
			{
				System::Sleep(15);

				continue;
			}

			if (!webcam.retrieve())
			{
				System::Sleep(5);

				continue;
			}

			{
				std::lock_guard<std::mutex> lock(webcam.m_imageMutex);

				const uint8* pSrc = webcam.m_frame.data;
				uint8* pDst = webcam.m_image.dataAsUint8();
				const size_t num_pixels = webcam.m_image.num_pixels();

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

		webcam.release();
	}

	WebcamData::~WebcamData()
	{
		stop();
	}

	bool WebcamData::open(const size_t index)
	{
		return m_capture.open(static_cast<int32>(index));
	}

	void WebcamData::initResolution()
	{
		m_resolution.set(static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_WIDTH)),
			static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_HEIGHT)));
	}

	bool WebcamData::setResolution(const Size& resolution)
	{
		if (!m_capture.set(cv::CAP_PROP_FRAME_WIDTH, resolution.x)
			|| !m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, resolution.y))
		{
			m_capture.set(cv::CAP_PROP_FRAME_WIDTH, m_resolution.x);
			m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, m_resolution.y);
			return false;
		}
		else
		{
			m_capture >> m_frame;

			m_resolution.set(m_frame.cols, m_frame.rows);

			return (m_resolution == resolution);
		}
	}

	bool WebcamData::retrieve()
	{
		if (!m_capture.grab())
		{
			return false;
		}

		m_capture.retrieve(m_frame);

		return true;
	}

	void WebcamData::release()
	{
		if (m_capture.isOpened())
		{
			m_capture.release();
		}
	}

	const Size& WebcamData::getResolution() const
	{
		return m_resolution;
	}

	bool WebcamData::start(const int32 index)
	{
		m_thread = std::thread(OnRunning, std::ref(*this), index);

		for (;;)
		{
			const WebcamState state = m_state;

			if (state == WebcamState::HasError)
			{
				return false;
			}
			else if (state != WebcamState::None)
			{
				return true;
			}

			System::Sleep(5);
		}
	}

	void WebcamData::stop()
	{
		if (!m_thread.joinable())
		{
			return;
		}

		m_state = WebcamState::Stop;

		m_thread.join();

		m_state			= WebcamState::None;
		m_newFrameCount	= 0;
	}

	bool WebcamData::hasNewFrame() const
	{
		if (m_state != WebcamState::Active)
		{
			return false;
		}

		return m_newFrameCount > 0;
	}

	bool WebcamData::getFrame(Image& image)
	{
		if (m_state != WebcamState::Active)
		{
			return false;
		}

		image.resize(m_resolution);

		{
			std::lock_guard<std::mutex> lock(m_imageMutex);

			::memcpy(image.data(), m_image.data(), image.size_bytes());

			m_newFrameCount = 0;
		}

		return true;
	}

	bool WebcamData::getFrame(DynamicTexture& texture)
	{
		if (m_state != WebcamState::Active)
		{
			return false;
		}

		{
			std::lock_guard<std::mutex> lock(m_imageMutex);

			return texture.fill(m_image);
		}
	}


	Webcam::WebcamDetail::WebcamDetail(const size_t index)
		: m_index(index)
	{
		m_available = m_webcam.open(index);

		if (!m_available)
		{
			return;
		}

		m_webcam.initResolution();

		m_webcam.setResolution(Size(640, 480));

		m_webcam.release();
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
		if (!m_available)
		{
			return false;
		}

		if (m_isActive)
		{
			return true;
		}

		if (!m_webcam.start(static_cast<int32>(m_index)))
		{
			return false;
		}

		m_isActive = true;

		return true;
	}

	void Webcam::WebcamDetail::stop()
	{
		if (!m_isActive)
		{
			return;
		}

		m_webcam.stop();

		m_isActive = false;
	}

	bool Webcam::WebcamDetail::isActive() const
	{
		return m_isActive;
	}

	size_t Webcam::WebcamDetail::index() const
	{
		return m_index;
	}

	Size Webcam::WebcamDetail::getResolution() const
	{
		return m_webcam.getResolution();
	}

	bool Webcam::WebcamDetail::setResolution(const Size& resolution)
	{
		if (!m_available || isActive())
		{
			return false;
		}

		if (m_webcam.getResolution() == resolution)
		{
			return true;
		}

		m_available = m_webcam.open(m_index);

		if (!m_available)
		{
			return false;
		}

		const bool result = m_webcam.setResolution(resolution);

		m_webcam.release();

		return result;
	}

	bool Webcam::WebcamDetail::hasNewFrame() const
	{
		if (!m_isActive)
		{
			return false;
		}

		return m_webcam.hasNewFrame();
	}

	bool Webcam::WebcamDetail::getFrame(Image& image)
	{
		if (!m_isActive)
		{
			return false;
		}

		return m_webcam.getFrame(image);
	}

	bool Webcam::WebcamDetail::getFrame(DynamicTexture& texture)
	{
		if (!m_isActive)
		{
			return false;
		}

		return m_webcam.getFrame(texture);
	}
}
