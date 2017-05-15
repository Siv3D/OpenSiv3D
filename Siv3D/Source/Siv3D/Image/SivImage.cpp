//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "../ImageFormat/IImageFormat.hpp"
# include "../../ThirdParty/guetzli/processor.h"

S3D_DISABLE_MSVC_WARNINGS_PUSH(4100 4244)
# include "../../ThirdParty/butteraugli/butteraugli.h"
S3D_DISABLE_MSVC_WARNINGS_POP()

# include <Siv3D/Image.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/Number.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr bool IsValidSize(const size_t width, const size_t height)
		{
			return width <= MaxImageSize && height <= MaxImageSize;
		}

		static std::vector<uint8> ToRGBVector(const Image& image)
		{
			std::vector<uint8> rgb(image.num_pixels() * 3);

			if (image.isEmpty())
			{
				return rgb;
			}

			const Color* pSrc = image.data();
			const Color* const pSrcEnd = pSrc + image.num_pixels();
			uint8* pDst = rgb.data();

			while (pSrc != pSrcEnd)
			{
				*pDst++ = pSrc->r;
				*pDst++ = pSrc->g;
				*pDst++ = pSrc->b;
				++pSrc;
			}

			return rgb;
		}

		static std::vector<butteraugli::ImageF> ToImageFVector(const Image& image)
		{
			if (image.isEmpty())
			{
				return{};
			}

			std::vector<butteraugli::ImageF> rgb;			
			rgb.emplace_back(image.width(), image.height());
			rgb.emplace_back(image.width(), image.height());
			rgb.emplace_back(image.width(), image.height());

			double table[256];
			for (int i = 0; i < 256; ++i) {
				const double srgb = i / 255.0;
				table[i] =
					255.0 * (srgb <= 0.04045 ? srgb / 12.92
						: std::pow((srgb + 0.055) / 1.055, 2.4));
			}
		

			for (int32 y = 0; y < image.height(); ++y)
			{
				const Color* pSrc = image[y];
				const Color* const pSrcEnd = pSrc + image.width();
				float* pDstR = rgb[0].Row(y);
				float* pDstG = rgb[1].Row(y);
				float* pDstB = rgb[2].Row(y);

				while (pSrc != pSrcEnd)
				{
					//*pDstR++ = static_cast<float>(pSrc->r / 255.0);
					//*pDstG++ = static_cast<float>(pSrc->g / 255.0);
					//*pDstB++ = static_cast<float>(pSrc->b / 255.0);

					*pDstR++ = static_cast<float>(table[pSrc->r]);
					*pDstG++ = static_cast<float>(table[pSrc->g]);
					*pDstB++ = static_cast<float>(table[pSrc->b]);
					++pSrc;
				}
			}

			return rgb;
		}
	}

	Image Image::Generate(const size_t width, const size_t height, std::function<Color(void)> generator)
	{
		Image new_image(width, height);

		if (!new_image.isEmpty())
		{
			Color* pDst = new_image.data();
			const Color* pDstEnd = pDst + new_image.num_pixels();

			while (pDst != pDstEnd)
			{
				(*pDst++) = generator();
			}
		}

		return new_image;
	}

	Image Image::Generate0_1(const size_t width, const size_t height, std::function<Color(Vec2)> generator)
	{
		Image new_image(width, height);

		if (!new_image.isEmpty())
		{
			const double sx = 1.0 / (width - 1);
			const double sy = 1.0 / (height - 1);

			Color* pDst = new_image.data();

			for (uint32 y = 0; y < height; ++y)
			{
				for (uint32 x = 0; x < width; ++x)
				{
					(*pDst++) = generator({ sx * x, sy * y });
				}
			}
		}

		return new_image;
	}

	Image::Image(Image&& image) noexcept
		: m_data(std::move(image.m_data))
		, m_width(image.m_width)
		, m_height(image.m_height)
	{
		image.m_width = image.m_height = 0;
	}

	Image::Image(size_t width, size_t height)
		: m_data(detail::IsValidSize(width, height) ? width * height : 0)
		, m_width(detail::IsValidSize(width, height) ? static_cast<uint32>(width) : 0)
		, m_height(detail::IsValidSize(width, height) ? static_cast<uint32>(height) : 0)
	{
	
	}

	Image::Image(size_t width, size_t height, const Color& color)
		: m_data(detail::IsValidSize(width, height) ? width * height : 0, color)
		, m_width(detail::IsValidSize(width, height) ? static_cast<uint32>(width) : 0)
		, m_height(detail::IsValidSize(width, height) ? static_cast<uint32>(height) : 0)
	{
	
	}

	Image::Image(const FilePath& path)
		: Image(Siv3DEngine::GetImageFormat()->load(path))
	{

	}

	Image::Image(IReader&& reader, ImageFormat format)
		: Image(Siv3DEngine::GetImageFormat()->decode(std::move(reader), format))
	{

	}

	Image::Image(const FilePath& rgb, const FilePath& alpha)
		: Image(rgb)
	{
		applyAlphaFromRChannel(alpha);
	}

	Image::Image(const Color& rgb, const FilePath& alpha)
		: Image(alpha)
	{
		for (auto& pixel : *this)
		{
			pixel.a = pixel.r;
			pixel.r = rgb.r;
			pixel.g = rgb.g;
			pixel.b = rgb.b;
		}
	}

	Image::Image(const Grid<Color>& grid)
		: Image(grid.width(), grid.height())
	{
		if (m_data.empty())
		{
			return;
		}

		::memcpy(m_data.data(), grid.data(), grid.size_bytes());
	}

	Image::Image(const Grid<ColorF>& grid)
		: Image(grid.width(), grid.height())
	{
		if (m_data.empty())
		{
			return;
		}

		const ColorF* pSrc = grid.data();
		const ColorF* const pSrcEnd = pSrc + grid.size_elements();
		Color* pDst = m_data.data();

		while (pSrc != pSrcEnd)
		{
			*pDst++ = *pSrc++;
		}
	}

	Image& Image::operator =(Image&& image)
	{
		m_data = std::move(image.m_data);
		m_width = image.m_width;
		m_height = image.m_height;

		image.m_width = image.m_height = 0;

		return *this;
	}

	void Image::resize(const size_t width, const size_t height)
	{
		if (!detail::IsValidSize(width, height))
		{
			return clear();
		}

		if (width == m_width && height == m_height)
		{
			return;
		}

		m_data.resize(width * height);

		m_width = static_cast<uint32>(width);

		m_height = static_cast<uint32>(height);
	}

	void Image::resize(const size_t width, const size_t height, const Color& fillColor)
	{
		if (!detail::IsValidSize(width, height))
		{
			return clear();
		}

		if (width == m_width && height == m_height)
		{
			return;
		}

		m_data.assign(width * height, fillColor);

		m_width = static_cast<uint32>(width);

		m_height = static_cast<uint32>(height);
	}

	bool Image::applyAlphaFromRChannel(const FilePath& alpha)
	{
		if (isEmpty())
		{
			return false;
		}

		const Image alphaImage(alpha);

		if (alphaImage.isEmpty())
		{
			return false;
		}

		Color* pDst = data();
		const size_t dstStep = m_width;

		const Color* pSrc = alphaImage.data();
		const size_t srcStep = alphaImage.m_width;

		const uint32 w = std::min(m_width, alphaImage.m_width);
		const uint32 h = std::min(m_height, alphaImage.m_height);

		for (uint32 y = 0; y < h; ++y)
		{
			Color* pDstLine = pDst;
			const Color* pSrcLine = pSrc;

			for (uint32 x = 0; x < w; ++x)
			{
				(*pDstLine++).a = (*pSrcLine++).r;
			}

			pSrc += srcStep;
			pDst += dstStep;
		}

		return true;
	}

	bool Image::save(const FilePath& path, ImageFormat format) const
	{
		if (isEmpty())
		{
			return false;
		}

		if (format == ImageFormat::Unspecified)
		{
			format = Siv3DEngine::GetImageFormat()->getFormatFromFilePath(path);
		}

		return Siv3DEngine::GetImageFormat()->save(*this, format, path);
	}

	bool Image::saveJPEG(const FilePath& path, const int32 quality) const
	{
		if (isEmpty())
		{
			return false;
		}

		BinaryWriter writer(path);

		if (!writer)
		{
			return false;
		}

		return Siv3DEngine::GetImageFormat()->encodeJPEG(writer, *this, quality);
	}

	bool Image::savePerceptualJPEG(const FilePath& path, const double butteraugliTarget) const
	{
		if (isEmpty())
		{
			return false;
		}

		BinaryWriter writer(path);

		if (!writer)
		{
			return false;
		}

		guetzli::Params params;
		params.butteraugli_target = static_cast<float>(butteraugliTarget);

		guetzli::ProcessStats stats;
		std::string out_data;

		if (!guetzli::Process(params, &stats, detail::ToRGBVector(*this), m_width, m_height, &out_data))
		{
			return false;
		}
		
		writer.write(out_data.data(), out_data.length());

		return true;
	}

	MemoryWriter Image::encode(ImageFormat format) const
	{
		if (isEmpty())
		{
			return MemoryWriter();
		}

		if (format == ImageFormat::Unspecified)
		{
			format = ImageFormat::PNG;
		}

		return Siv3DEngine::GetImageFormat()->encode(*this, format);
	}

	namespace ImageProcessing
	{
		double PerceivedDifferences(const Image& a, const Image& b)
		{
			if (a.isEmpty() || a.size() != b.size())
			{
				return Infinity<double>();
			}

			butteraugli::ImageF diff;
			double diffValue;
			butteraugli::ButteraugliInterface(detail::ToImageFVector(a), detail::ToImageFVector(b), diff, diffValue);

			return diffValue;
		}

		double PerceivedDifferences(const Image& a, const Image& b, Grid<float>& diffMap)
		{
			if (a.isEmpty() || a.size() != b.size())
			{
				return Infinity<double>();
			}

			butteraugli::ImageF diff;
			double diffValue;
			butteraugli::ButteraugliInterface(detail::ToImageFVector(a), detail::ToImageFVector(b), diff, diffValue);

			diffMap.resize(diff.xsize(), diff.ysize());

			float* pDst = diffMap.data();

			for (size_t y = 0; y < diff.ysize(); ++y)
			{
				const float* line = diff.Row(y);

				for (size_t x = 0; x < diff.xsize(); ++x)
				{
					*pDst++ = (*line++);
				}
			}

			return diffValue;
		}
	}
}
