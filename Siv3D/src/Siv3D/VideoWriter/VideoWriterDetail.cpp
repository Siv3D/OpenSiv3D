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

# include "VideoWriterDetail.hpp"
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static int32 GetFourCC(const StringView extension)
		{
			if (extension == U"wmv")
			{
				return cv::VideoWriter::fourcc('W', 'M', 'V', '3');
			}
			else if (extension == U"webm")
			{
				return cv::VideoWriter::fourcc('V', 'P', '9', '0');
			}
			else
			{
				return cv::VideoWriter::fourcc('H', '2', '6', '4');
			}
		}
	}

	VideoWriter::VideoWriterDetail::VideoWriterDetail() {}

	VideoWriter::VideoWriterDetail::~VideoWriterDetail()
	{
		close();
	}

	bool VideoWriter::VideoWriterDetail::open(const FilePathView path, const Size& size, double fps)
	{
		LOG_SCOPED_TRACE(U"VideoWriterDetail::open()");

		close();

		if (FileSystem::Exists(path))
		{
			FileSystem::Remove(path);
		}

		const int32 fourCC = detail::GetFourCC(FileSystem::Extension(path));

		const bool result = m_writer.open(path.narrow(), fourCC, fps, cv::Size(size.x, size.y), true);
	
		if (not result)
		{
			FileSystem::Remove(path);
			return false;
		}

		m_info =
		{
			.fullPath	= FileSystem::FullPath(path),
			.resolution	= size,
			.fps		= fps,
			.isOpen		= true,
			.mat		= cv::Mat_<cv::Vec3b>(size.y, size.x),
		};

		LOG_INFO(U"ℹ️ VideoWriter: file `{0}` opened (resolution: {1}, fps: {2})"_fmt(
			path, m_info.resolution, m_info.fps));

		return true;
	}

	void VideoWriter::VideoWriterDetail::close()
	{
		LOG_SCOPED_TRACE(U"VideoWriterDetail::close()");

		m_writer.release();

		m_info = {};
	}

	bool VideoWriter::VideoWriterDetail::isOpen() const noexcept
	{
		return m_info.isOpen;
	}

	bool VideoWriter::VideoWriterDetail::writeFrame(const Image& image)
	{
		if (not m_info.isOpen)
		{
			return false;
		}

		if (image.size() != m_info.resolution)
		{
			return false;
		}

		OpenCV_Bridge::ToMatVec3bBGR(image, m_info.mat);
		m_writer.write(m_info.mat);

		return true;
	}

	const Size& VideoWriter::VideoWriterDetail::getSize() const noexcept
	{
		return m_info.resolution;
	}

	double VideoWriter::VideoWriterDetail::getFPS() const noexcept
	{
		return m_info.fps;
	}

	const FilePath& VideoWriter::VideoWriterDetail::path() const noexcept
	{
		return m_info.fullPath;
	}
}
