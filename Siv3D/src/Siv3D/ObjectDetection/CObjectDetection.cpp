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

# include "CObjectDetection.hpp"
# include <Siv3D/Image.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Compression.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Logger.hpp>
# include "../EngineDirectory/EngineDirectory.hpp"

namespace s3d
{
	namespace detail
	{
		static void ToGrayScale(const Image& from, cv::Mat_<uint8>& to)
		{
			assert(from.width() == to.cols);
			assert(from.height() == to.rows);

			const Color* pSrc = from.data();
			const int32 height = from.height(), width = from.width();

			for (int32 y = 0; y < height; ++y)
			{
				uint8* line = &to(y, 0);

				for (int32 x = 0; x < width; ++x)
				{
					line[x] = pSrc->grayscale0_255();
					++pSrc;
				}
			}
		}

		static const FilePath CascadeNames[5] =
		{
			U"frontal_face_alt2.xml",
			U"eye.xml",
			U"eye_eyeglasses.xml",
			U"face_anime.xml",
			U"frontal_catface.xml",
		};
	}

	CObjectDetection::CObjectDetection()
	{
		m_unavailable.fill(false);
	}

	CObjectDetection::~CObjectDetection()
	{

	}

	bool CObjectDetection::init()
	{
		const FilePath cascadeDirectory = EngineDirectory::CurrectVersionCommon() + U"objdetect/haarcascade/";

		for (const auto& cascadeName : detail::CascadeNames)
		{
			const FilePath fontResourcePath = Resource(U"engine/objdetect/haarcascade/" + cascadeName + U".zst");

			if (!FileSystem::Exists(cascadeDirectory + cascadeName)
				&& FileSystem::Exists(fontResourcePath))
			{
				Compression::DecompressFileToFile(fontResourcePath, cascadeDirectory + cascadeName);
			}
		}

		LOG_INFO(U"ℹ️ ObjectDetection initialized");

		return true;
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

		detail::ToGrayScale(image, m_mat);

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

		detail::ToGrayScale(image, m_mat);

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
