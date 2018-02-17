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

# include "../Siv3DEngine.hpp"
# include "../ImageFormat/IImageFormat.hpp"

# include <opencv2/imgproc.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/Number.hpp>
# include <Siv3D/Logger.hpp>
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr bool IsValidSize(const size_t width, const size_t height)
		{
			return width <= Image::MaxWidth && height <= Image::MaxHeight;
		}

		static constexpr int32 ConvertBorderType(const BorderType borderType)
		{
			switch (borderType)
			{
			case BorderType::Replicate:
				return cv::BORDER_REPLICATE;
			//case BorderType::Wrap:
			//	return cv::BORDER_WRAP;
			case BorderType::Reflect:
				return cv::BORDER_REFLECT;
			case BorderType::Reflect_101:
				return cv::BORDER_REFLECT101;
			default:
				return cv::BORDER_DEFAULT;
			}
		}

		static void MakeSepia(const double levr, const double levg, const double levb, Color& pixel)
		{
			const double y = (0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);
			const double r = levr + y;
			const double g = levg + y;
			const double b = levb + y;
			pixel.r = r >= 255.0 ? 255 : r <= 0.0 ? 0 : static_cast<uint8>(r);
			pixel.g = g >= 255.0 ? 255 : g <= 0.0 ? 0 : static_cast<uint8>(g);
			pixel.b = b >= 255.0 ? 255 : b <= 0.0 ? 0 : static_cast<uint8>(b);
		}

		static void SetupPostarizeTable(const int32 level, uint8 table[256])
		{
			const int32 levN = Clamp(level, 2, 256) - 1;

			for (size_t i = 0; i < 256; ++i)
			{
				table[i] = static_cast<uint8>(std::floor(i / 255.0 * levN + 0.5) / levN * 255);
			}
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

	Image::Image(const Emoji& emoji)
	{
		*this = Emoji::LoadImage(emoji.codePoints);
	}

	Image::Image(const Icon& icon)
	{
		*this = Icon::LoadImage(icon.code, icon.size);
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

	void Image::resizeRows(const size_t rows, const Color& fillColor)
	{
		if (rows == m_height)
		{
			return;
		}

		if (!detail::IsValidSize(m_width, rows))
		{
			return clear();
		}

		if (rows < m_height)
		{
			m_data.resize(m_width * rows);
		}
		else
		{
			m_data.insert(m_data.end(), m_width * (rows - m_height), fillColor);
		}

		m_height = static_cast<uint32>(rows);
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

	bool Image::savePNG(const FilePath& path, const PNGFilter::Flag filterFlag) const
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

		return Siv3DEngine::GetImageFormat()->encodePNG(writer, *this, filterFlag);
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

	bool Image::savePPM(const FilePath& path, const PPMType format) const
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

		return Siv3DEngine::GetImageFormat()->encodePPM(writer, *this, format);
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

	Image& Image::negate()
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		// 2. 処理
		{
			for (auto& pixel : m_data)
			{
				pixel = ~pixel;
			}
		}

		return *this;
	}

	Image Image::negated() const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		Image image(*this);

		for (auto& pixel : image)
		{
			pixel = ~pixel;
		}

		return image;
	}

	Image& Image::grayscale()
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		// 2. 処理
		{
			for (auto& pixel : m_data)
			{
				pixel.r = pixel.g = pixel.b = pixel.grayscale0_255();
			}
		}

		return *this;
	}

	Image Image::grayscaled() const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		Image image(*this);

		for (auto& pixel : image)
		{
			pixel.r = pixel.g = pixel.b = pixel.grayscale0_255();
		}

		return image;
	}

	Image& Image::sepia(const int32 level)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const double levn = Clamp(level, 0, 255);
			const double levr = 0.956*levn;
			const double levg = 0.274*levn;
			const double levb = -1.108*levn;

			for (auto& pixel : m_data)
			{
				detail::MakeSepia(levr, levg, levb, pixel);
			}
		}

		return *this;
	}

	Image Image::sepiaed(const int32 level) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		Image image(*this);

		const double levn = Clamp(level, 0, 255);
		const double levr = 0.956*levn;
		const double levg = 0.274*levn;
		const double levb = -1.108*levn;

		for (auto& pixel : image)
		{
			detail::MakeSepia(levr, levg, levb, pixel);
		}

		return image;
	}

	Image& Image::postarize(const int32 level)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		// 2. 処理
		{
			uint8 colorTable[256];

			detail::SetupPostarizeTable(level, colorTable);

			for (auto& pixel : m_data)
			{
				pixel.r = colorTable[pixel.r];
				pixel.g = colorTable[pixel.g];
				pixel.b = colorTable[pixel.b];
			}
		}

		return *this;
	}

	Image Image::postarized(const int32 level) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		Image image(*this);

		uint8 colorTable[256];

		detail::SetupPostarizeTable(level, colorTable);

		for (auto& pixel : image)
		{
			pixel.r = colorTable[pixel.r];
			pixel.g = colorTable[pixel.g];
			pixel.b = colorTable[pixel.b];
		}

		return image;
	}

	Image& Image::brighten(const int32 level)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		// 2. 処理
		{
			if (level < 0)
			{
				for (auto& pixel : m_data)
				{
					pixel.r = std::max(static_cast<int>(pixel.r) + level, 0);
					pixel.g = std::max(static_cast<int>(pixel.g) + level, 0);
					pixel.b = std::max(static_cast<int>(pixel.b) + level, 0);
				}
			}
			else if (level > 0)
			{
				for (auto& pixel : m_data)
				{
					pixel.r = std::min(static_cast<int>(pixel.r) + level, 255);
					pixel.g = std::min(static_cast<int>(pixel.g) + level, 255);
					pixel.b = std::min(static_cast<int>(pixel.b) + level, 255);
				}
			}
		}

		return *this;
	}

	Image Image::brightened(const int32 level) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		Image image(*this);

		if (level < 0)
		{
			for (auto& pixel : image)
			{
				pixel.r = std::max(static_cast<int>(pixel.r) + level, 0);
				pixel.g = std::max(static_cast<int>(pixel.g) + level, 0);
				pixel.b = std::max(static_cast<int>(pixel.b) + level, 0);
			}
		}
		else if (level > 0)
		{
			for (auto& pixel : image)
			{
				pixel.r = std::min(static_cast<int>(pixel.r) + level, 255);
				pixel.g = std::min(static_cast<int>(pixel.g) + level, 255);
				pixel.b = std::min(static_cast<int>(pixel.b) + level, 255);
			}
		}

		return image;
	}










	Image& Image::mirror()
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const int32 h = m_height, w = m_width, wHalf = m_width / 2;
			Color* line = m_data.data();

			for (int32 y = 0; y < h; ++y)
			{
				Color* lineA = line;
				Color* lineB = line + w - 1;;

				for (int32 x = 0; x < wHalf; ++x)
				{
					std::swap(*lineA, *lineB);
					++lineA;
					--lineB;
				}

				line += w;
			}
		}

		return *this;
	}

	Image& Image::flip()
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const int32 h = m_height, s = stride();
			Array<Color> line(m_width);
			Color* lineU = m_data.data();
			Color* lineB = lineU + m_width * (h - 1);

			for (int32 y = 0; y < h / 2; ++y)
			{
				::memcpy(line.data(), lineU, s);
				::memcpy(lineU, lineB, s);
				::memcpy(lineB, line.data(), s);

				lineU += m_width;
				lineB -= m_width;
			}
		}

		return *this;
	}



	Image& Image::gaussianBlur(const int32 horizontal, const int32 vertical, const BorderType borderType)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal < 0 || vertical < 0) || (horizontal == 0 && vertical == 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image tmp(m_width, m_height);

			cv::Mat_<cv::Vec4b> matSrc(m_height, m_width, static_cast<cv::Vec4b*>(static_cast<void*>(data())), stride());

			cv::Mat_<cv::Vec4b> matDst(tmp.height(), tmp.width(), static_cast<cv::Vec4b*>(static_cast<void*>(tmp.data())), tmp.stride());

			cv::GaussianBlur(matSrc, matDst, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), 0.0, 0.0, detail::ConvertBorderType(borderType));

			swap(tmp);
		}

		return *this;
	}

	Image Image::gaussianBlurred(const int32 horizontal, const int32 vertical, const BorderType borderType) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal < 0 || vertical < 0) || (horizontal == 0 && vertical == 0))
			{
				return *this;
			}
		}

		Image image(m_width, m_height);

		cv::Mat_<cv::Vec4b> matSrc(m_height, m_width, const_cast<cv::Vec4b*>(static_cast<const cv::Vec4b*>(static_cast<const void*>(data()))), stride());

		cv::Mat_<cv::Vec4b> matDst(image.height(), image.width(), static_cast<cv::Vec4b*>(static_cast<void*>(image.data())), image.stride());

		cv::GaussianBlur(matSrc, matDst, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), 0.0, 0.0, detail::ConvertBorderType(borderType));

		return image;
	}
}
