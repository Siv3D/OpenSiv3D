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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>
# include "CascadeClassifierDetail.hpp"

namespace s3d
{
	CascadeClassifier::CascadeClassifierDetail::CascadeClassifierDetail() {}

	CascadeClassifier::CascadeClassifierDetail::~CascadeClassifierDetail()
	{
		// do nothing
	}

	bool CascadeClassifier::CascadeClassifierDetail::open(const FilePathView path)
	{
		close();

	# if SIV3D_PLATFORM(WINDOWS)

		if (FileSystem::IsResource(path))
		{
			const FilePath tmpPath = FileSystem::UniqueFilePath();

			if (Blob{ path }.save(tmpPath))
			{
				const bool result = m_cascade.load(tmpPath.narrow());

				FileSystem::Remove(tmpPath);

				return result;
			}
		}

	# endif

		return m_cascade.load(path.narrow());
	}

	void CascadeClassifier::CascadeClassifierDetail::close()
	{
		m_cascade = cv::CascadeClassifier{};
	}

	bool CascadeClassifier::CascadeClassifierDetail::isOpen() const
	{
		return (not m_cascade.empty());
	}

	Array<Rect> CascadeClassifier::CascadeClassifierDetail::detectObjects(const Image& image, const Array<Rect>& regions, const int32 minNeighbors, const Size& minSize, const Size& maxSize)
	{
		OpenCV_Bridge::ToGrayScale(image, m_mat);

		Array<Rect> rects;

		for (const auto& region : regions)
		{
			std::vector<cv::Rect> faces;

			const cv::Rect roi{ region.x, region.y, region.w, region.h };

			m_cascade
				.detectMultiScale(m_mat(roi), faces, 1.1, minNeighbors, 0, cv::Size{ minSize.x, minSize.y }, cv::Size{ maxSize.x, maxSize.y });

			for (const auto& face : faces)
			{
				rects.emplace_back((face.x + region.x), (face.y + region.y), face.width, face.height);
			}
		}

		return rects;
	}
}
