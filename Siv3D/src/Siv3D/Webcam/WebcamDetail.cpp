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

# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
# include "WebcamDetail.hpp"

namespace s3d
{
	namespace detail
	{
		void CopyFrame(const cv::Mat_<cv::Vec3b>& src, Image& dst)
		{
			const size_t num_pixels = dst.num_pixels();
			const uint8* pSrc = src.data;
			uint8* pDst = dst.dataAsUint8();

			if (num_pixels % 4 == 0)
			{
				const size_t count = (num_pixels / 4);

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
		}
	}

	Webcam::WebcamDetail::WebcamDetail() {}

	Webcam::WebcamDetail::~WebcamDetail()
	{
		close();
	}

	bool Webcam::WebcamDetail::open(const uint32 cameraIndex)
	{
		LOG_SCOPED_TRACE(U"Webcam::WebcamDetail::open(cameraIndex = {})"_fmt(cameraIndex));

		close();

		if (not m_capture.open(static_cast<int32>(cameraIndex)))
		{
			LOG_ERROR(U"cv::VideoCapture::oepn({}) failed"_fmt(cameraIndex));
			
			return false;
		}

		LOG_INFO(U"cv::VideoCapture::oepn({}) succeeded"_fmt(cameraIndex));

		m_cameraIndex = cameraIndex;

		{
			m_captureResolution.set(
				static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_WIDTH)),
				static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_HEIGHT)));
			
			m_image = Image{ m_captureResolution, Color{ 255 } };
		}

		return true;
	}

	void Webcam::WebcamDetail::close()
	{
		if (not m_capture.isOpened())
		{
			return;
		}

		if (not m_thread.joinable())
		{
			return;
		}

		m_abort = true;

		m_thread.join();
		{
			m_abort = false;
			m_capture.release();
			m_cameraIndex = 0;
			m_newFrameCount = 0;
			m_captureResolution.set(0, 0);
		}
	}

	bool Webcam::WebcamDetail::isOpen()
	{
		return m_capture.isOpened();
	}

	bool Webcam::WebcamDetail::start()
	{
		if (not m_capture.isOpened())
		{
			return false;
		}

		// すでに start 後の場合は何もしない
		if (m_thread.joinable())
		{
			return true;
		}

		// キャプチャスレッドを起動
		{
			m_thread = std::thread{ Run, std::ref(*this) };

			return true;
		}
	}

	bool Webcam::WebcamDetail::isActive() const
	{
		return m_thread.joinable();
	}

	uint32 Webcam::WebcamDetail::cameraIndex() const
	{
		return m_cameraIndex;
	}

	Size Webcam::WebcamDetail::getResolution() const
	{
		return m_captureResolution;
	}

	bool Webcam::WebcamDetail::setResolution(const Size& resolution)
	{
		if (not m_capture.isOpened())
		{
			return false;
		}

		// start 後は変更できない
		if (m_thread.joinable())
		{
			return false;
		}

		// すでに同じ解像度が設定されている
		if (resolution == m_captureResolution)
		{
			return true;
		}

		if ((not m_capture.set(cv::CAP_PROP_FRAME_WIDTH, resolution.x))
			|| (not m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, resolution.y)))
		{
			m_capture.set(cv::CAP_PROP_FRAME_WIDTH, m_captureResolution.x);
			m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, m_captureResolution.y);
			return false;
		}
		else
		{
			m_capture >> m_frame;
			m_captureResolution.set(m_frame.cols, m_frame.rows);
			m_image = Image{ m_captureResolution, Color{ 255 } };
			return (m_captureResolution == resolution);
		}
	}

	bool Webcam::WebcamDetail::hasNewFrame()
	{
		std::lock_guard lock{ m_imageMutex };

		return (0 < m_newFrameCount);
	}

	bool Webcam::WebcamDetail::getFrame(Image& image)
	{
		if (not isActive())
		{
			return false;
		}

		image.resize(m_captureResolution);
		{
			std::lock_guard lock{ m_imageMutex };

			std::memcpy(image.data(), m_image.data(), image.size_bytes());

			m_newFrameCount = 0;
		}

		return true;
	}

	bool Webcam::WebcamDetail::getFrame(DynamicTexture& texture)
	{
		if (not isActive())
		{
			return false;
		}

		{
			std::lock_guard lock{ m_imageMutex };

			const bool result = texture.fill(m_image);

			m_newFrameCount = 0;

			return result;
		}
	}
	
	void Webcam::WebcamDetail::Run(WebcamDetail& webcam)
	{
		auto& capture = webcam.m_capture;

		while (not webcam.m_abort)
		{
			if (not capture.grab())
			{
				System::Sleep(5);
				continue;
			}

			if (not capture.retrieve(webcam.m_frame))
			{
				continue;
			}

			{
				std::lock_guard lock{ webcam.m_imageMutex };

				detail::CopyFrame(webcam.m_frame, webcam.m_image);

				++webcam.m_newFrameCount;
			}
		}
	}
}
