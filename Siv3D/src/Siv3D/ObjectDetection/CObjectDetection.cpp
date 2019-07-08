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

# include <Siv3D/Image.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Compression.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <EngineDirectory/EngineDirectory.hpp>
# include "CObjectDetection.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr FilePathView CascadeNames[5] =
		{
			U"frontal_face_alt2.xml"_sv,
			U"eye.xml"_sv,
			U"eye_eyeglasses.xml"_sv,
			U"face_anime.xml"_sv,
			U"frontal_catface.xml"_sv,
		};
	}

	CObjectDetection::CObjectDetection()
	{
		m_unavailable.fill(false);
	}

	CObjectDetection::~CObjectDetection()
	{
		LOG_TRACE(U"CObjectDetection::~CObjectDetection()");
	}

	void CObjectDetection::init()
	{
		LOG_TRACE(U"CObjectDetection::init()");

		const FilePath cascadeDirectory = EngineDirectory::CurrectVersionCommon() + U"objdetect/haarcascade/";

		for (const auto& cascadeName : detail::CascadeNames)
		{
			const FilePath cascadeResourcePath = Resource(U"engine/objdetect/haarcascade/" + cascadeName + U".zstdcmp");

			if (!FileSystem::Exists(cascadeDirectory + cascadeName)
				&& FileSystem::Exists(cascadeResourcePath))
			{
				Compression::DecompressFileToFile(cascadeResourcePath, cascadeDirectory + cascadeName);
			}
		}

		m_initialized = true;

		LOG_INFO(U"ℹ️ CObjectDetection initialized");
	}

	Array<Rect> CObjectDetection::detect(const Image& image, const HaarCascade cascade, const int32 minNeighbors, const Size& minSize, const Size& maxSize)
	{
		if (!m_initialized)
		{
			init();
		}

		if (!image)
		{
			return{};
		}

		const size_t cascadeIndex = static_cast<size_t>(cascade);

		if (m_unavailable[cascadeIndex])
		{
			return{};
		}

		if (image.width() != m_mat.cols || image.height() != m_mat.rows)
		{
			m_mat.create(image.height(), image.width());
		}

		if (m_cascades[cascadeIndex].empty())
		{
			if (!load(cascadeIndex))
			{
				return{};
			}
		}

		OpenCV_Bridge::ToGrayScale(image, m_mat);

		std::vector<cv::Rect> faces;

		m_cascades[cascadeIndex].detectMultiScale(m_mat, faces, 1.1, minNeighbors, 0, cv::Size(minSize.x, minSize.y), cv::Size(maxSize.x, maxSize.y));

		Array<Rect> rects;

		for (const auto& face : faces)
		{
			rects.emplace_back(face.x, face.y, face.width, face.height);
		}

		return rects;
	}

	Array<Rect> CObjectDetection::detect(const Image& image, const HaarCascade cascade, const Array<Rect>& regions, const int32 minNeighbors, const Size& minSize, const Size& maxSize)
	{
		if (!m_initialized)
		{
			init();
		}

		if (!image)
		{
			return{};
		}

		const size_t cascadeIndex = static_cast<size_t>(cascade);

		if (m_unavailable[cascadeIndex])
		{
			return{};
		}

		if (image.width() != m_mat.cols || image.height() != m_mat.rows)
		{
			m_mat.create(image.height(), image.width());
		}

		if (m_cascades[cascadeIndex].empty())
		{
			if (!load(cascadeIndex))
			{
				return{};
			}
		}

		OpenCV_Bridge::ToGrayScale(image, m_mat);

		Array<Rect> rects;

		for (const auto& region : regions)
		{
			std::vector<cv::Rect> faces;

			const cv::Rect roi(region.x, region.y, region.w, region.h);

			m_cascades[cascadeIndex].detectMultiScale(m_mat(roi), faces, 1.1, minNeighbors, 0, cv::Size(minSize.x, minSize.y), cv::Size(maxSize.x, maxSize.y));

			for (const auto& face : faces)
			{
				rects.emplace_back(face.x + region.x, face.y + region.y, face.width, face.height);
			}
		}

		return rects;
	}

	bool CObjectDetection::load(const size_t cascadeIndex)
	{
		const FilePath cascadeDirectory = EngineDirectory::CurrectVersionCommon() + U"objdetect/haarcascade/";

		const FilePath path = cascadeDirectory + detail::CascadeNames[cascadeIndex];

		if (!m_cascades[cascadeIndex].load(path.narrow()))
		{
			m_unavailable[cascadeIndex] = true;

			return false;
		}

		return true;
	}
}
