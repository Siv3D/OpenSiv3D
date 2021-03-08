//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Image.hpp>
# include <Siv3D/ImageROI.hpp>
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/ImageDecoder.hpp>
# include <Siv3D/ImageEncoder.hpp>
# include <Siv3D/ImageFormat/PNGEncoder.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

# include <opencv2/imgproc.hpp>

namespace s3d
{
	namespace detail
	{
		static_assert((int32)AdaptiveThresholdMethod::Mean == cv::ADAPTIVE_THRESH_MEAN_C);
		static_assert((int32)AdaptiveThresholdMethod::Gaussian == cv::ADAPTIVE_THRESH_GAUSSIAN_C);

		[[nodiscard]]
		inline constexpr int32 ImageMod(int32 x, int32 y) noexcept
		{
			return (0 <= x) ? (x % y) : (y - ((-x - 1) % y) - 1);
		}

		[[nodiscard]]
		inline constexpr int32 ImageMir(int32 x, int32 y) noexcept
		{
			const int32 t = ImageMod(x, y * 2);

			return (t < y) ? t : (y * 2 - 1) - t;
		}

		[[nodiscard]]
		static constexpr double Biliner(double c1, double c2, double c3, double c4, double px, double py) noexcept
		{
			return (px * py * (c1 - c2 - c3 + c4) + px * (c2 - c1) + py * (c3 - c1) + c1);
		}

		[[nodiscard]]
		static Color MakeSepia(Color color, const double levr, const double levg, const double levb) noexcept
		{
			const double y = ((0.299 * color.r) + (0.587 * color.g) + (0.114 * color.b));
			color.r = Color::ToUint8(levr + y);
			color.g = Color::ToUint8(levg + y);
			color.b = Color::ToUint8(levb + y);
			return color;
		}

		static void InitPosterizeTable(const int32 level, uint8 table[256]) noexcept
		{
			const int32 levN = Clamp(level, 2, 256) - 1;

			for (size_t i = 0; i < 256; ++i)
			{
				table[i] = static_cast<uint8>(std::floor(i / 255.0 * levN + 0.5) / levN * 255);
			}
		}

		static void InitGammmaTable(const double gamma, uint8 table[256])
		{
			const double gammaInv = (1.0 / gamma);

			for (size_t i = 0; i < 256; ++i)
			{
				table[i] = static_cast<uint8>(std::pow(i / 255.0, gammaInv) * 255.0);
			}
		}
	}

	Image::Image(const FilePathView path, const ImageFormat format)
	{
		*this = ImageDecoder::Decode(path, format);
	}

	Image::Image(IReader&& reader, const ImageFormat format)
	{
		*this = ImageDecoder::Decode(reader, format);
	}

	Image::Image(const FilePathView rgb, const FilePathView alpha)
		: Image{ rgb }
	{
		applyAlphaFromRChannel(alpha);
	}

	Image::Image(const Color rgb, const FilePathView alpha)
		: Image{ alpha }
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
		: Image{ Emoji::CreateImage(emoji.codePoints) } {}

	Image::Image(const Icon& icon, const int32 size)
		: Image{ Icon::CreateImage(icon.type, icon.code, size) } {}

	Image::Image(const Grid<Color>& grid)
		: Image{ grid.size() }
	{
		if (m_data.empty())
		{
			return;
		}

		std::memcpy(m_data.data(), grid.data(), grid.size_bytes());
	}

	Image::Image(const Grid<ColorF>& grid)
		: Image{ grid.size() }
	{
		if (m_data.empty())
		{
			return;
		}

		const ColorF* pSrc = grid.data();
		const ColorF* const pSrcEnd = (pSrc + grid.size_elements());
		Color* pDst = m_data.data();

		while (pSrc != pSrcEnd)
		{
			*pDst++ = *pSrc++;
		}
	}

	Color Image::getPixel(const Point pos, const ImageAddressMode addressMode) const
	{
		switch (addressMode)
		{
		case ImageAddressMode::Repeat:
			return m_data[static_cast<size_t>(m_width) * detail::ImageMod(pos.y, m_height) + detail::ImageMod(pos.x, m_width)];
		case ImageAddressMode::Mirror:
			return m_data[static_cast<size_t>(m_width) * detail::ImageMir(pos.y, m_height) + detail::ImageMir(pos.x, m_width)];
		case ImageAddressMode::Clamp:
			return m_data[static_cast<size_t>(m_width) * Clamp(pos.y, 0, (static_cast<int32>(m_height) - 1)) + Clamp(pos.x, 0, (static_cast<int32>(m_width) - 1))];
		default:
			{
				if (InRange(pos.x, 0, static_cast<int32>(m_width) - 1)
					&& InRange(pos.y, 0, static_cast<int32>(m_height) - 1))
				{
					return m_data[static_cast<size_t>(m_width) * pos.y + pos.x];
				}

				if (addressMode == ImageAddressMode::BorderBlack)
				{
					return Color{ 0 };
				}
				else
				{
					return Color{ 255 };
				}
			}
		}
	}

	ColorF Image::samplePixel(const Vec2 pos, const ImageAddressMode addressMode) const
	{
		const int32 ix = static_cast<int32>(pos.x);
		const int32 iy = static_cast<int32>(pos.y);

		const Color c1 = getPixel(ix, iy, addressMode);
		const Color c2 = getPixel((ix + 1), iy, addressMode);
		const Color c3 = getPixel(ix, (iy + 1), addressMode);
		const Color c4 = getPixel((ix + 1), (iy + 1), addressMode);

		const double xr1 = (pos.x - ix);
		const double yr1 = (pos.y - iy);

		const double r = detail::Biliner(c1.r, c2.r, c3.r, c4.r, xr1, yr1);
		const double g = detail::Biliner(c1.g, c2.g, c3.g, c4.g, xr1, yr1);
		const double b = detail::Biliner(c1.b, c2.b, c3.b, c4.b, xr1, yr1);
		const double a = detail::Biliner(c1.a, c2.a, c3.a, c4.a, xr1, yr1);

		return{ (r / 255.0), (g / 255.0), (b / 255.0), (a / 255.0) };
	}

	Image Image::clipped(const Rect& rect) const
	{
		if (not detail::IsValidImageSize(rect.size))
		{
			return{};
		}

		Image tmp(rect.size, Color{ 0, 0 });

		const int32 h = static_cast<int32>(m_height);
		const int32 w = static_cast<int32>(m_width);

		// [Siv3D ToDo] 最適化
		for (int32 y = 0; y < rect.h; ++y)
		{
			const int32 sy = y + rect.y;

			if (0 <= sy && sy < h)
			{
				for (int32 x = 0; x < rect.w; ++x)
				{
					const int32 sx = x + rect.x;

					if (0 <= sx && sx < w)
					{
						tmp[y][x] = operator[](sy)[sx];
					}
				}
			}
		}

		return tmp;
	}

	Image Image::clipped(const int32 x, const int32 y, const int32 w, const int32 h) const
	{
		return clipped(Rect{ x, y, w, h });
	}

	Image Image::clipped(const Point& pos, const int32 w, const int32 h) const
	{
		return clipped(Rect{ pos, w, h });
	}

	Image Image::clipped(const int32 x, const int32 y, const Size& size) const
	{
		return clipped(Rect{ x, y, size });
	}

	Image Image::clipped(const Point& pos, const Size& size) const
	{
		return clipped(Rect{ pos, size });
	}

	Image Image::squareClipped() const
	{
		const int32 size = Min(m_width, m_height);

		return clipped(((m_width - size) / 2), ((m_height - size) / 2), size, size);
	}

	Image& Image::RGBAtoBGRA()
	{
		Color* p = m_data.data();
		const Color* pEnd = (p + num_pixels());

		while (p != pEnd)
		{
			const uint32 t = p->r;
			p->r = p->b;
			p->b = t;
			++p;
		}

		return *this;
	}

	bool Image::applyAlphaFromRChannel(const FilePathView alpha)
	{
		if (isEmpty())
		{
			return false;
		}

		const Image alphaImage{ alpha };

		if (not alphaImage)
		{
			return false;
		}

		Color* pDst = data();
		const size_t dstStep = m_width;

		const Color* pSrc = alphaImage.data();
		const size_t srcStep = alphaImage.m_width;

		const uint32 w = Min(m_width, alphaImage.m_width);
		const uint32 h = Min(m_height, alphaImage.m_height);

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

	bool Image::save(const FilePathView path, const ImageFormat format) const
	{
		return ImageEncoder::Save(*this, format, path);
	}

	bool Image::savePNG(const FilePathView path, const PNGFilter filter) const
	{
		return PNGEncoder{}.save(*this, path, filter);
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

		// 2. 処理
		{
			Image image{ *this };

			for (auto& pixel : image)
			{
				pixel = ~pixel;
			}

			return image;
		}
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
				const uint8 gray = pixel.grayscale0_255();
				pixel.r = gray;
				pixel.g = gray;
				pixel.b = gray;
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

		// 2. 処理
		{
			Image image{ *this };

			for (auto& pixel : image)
			{
				const uint8 gray = pixel.grayscale0_255();
				pixel.r = gray;
				pixel.g = gray;
				pixel.b = gray;
			}

			return image;
		}
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
			const double levr = 0.956 * levn;
			const double levg = 0.274 * levn;
			const double levb = -1.108 * levn;

			for (auto& pixel : m_data)
			{
				pixel = detail::MakeSepia(pixel, levr, levg, levb);
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

		// 2. 処理
		{
			Image image{ *this };

			const double levn = Clamp(level, 0, 255);
			const double levr = 0.956 * levn;
			const double levg = 0.274 * levn;
			const double levb = -1.108 * levn;

			for (auto& pixel : image)
			{
				pixel = detail::MakeSepia(pixel, levr, levg, levb);
			}

			return image;
		}
	}

	Image& Image::posterize(const int32 level)
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
			detail::InitPosterizeTable(level, colorTable);

			for (auto& pixel : m_data)
			{
				pixel.r = colorTable[pixel.r];
				pixel.g = colorTable[pixel.g];
				pixel.b = colorTable[pixel.b];
			}
		}

		return *this;
	}

	Image Image::posterized(const int32 level) const
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
			Image image{ *this };

			uint8 colorTable[256];
			detail::InitPosterizeTable(level, colorTable);

			for (auto& pixel : image)
			{
				pixel.r = colorTable[pixel.r];
				pixel.g = colorTable[pixel.g];
				pixel.b = colorTable[pixel.b];
			}

			return image;
		}
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
					pixel.r = Max(static_cast<int32>(pixel.r) + level, 0);
					pixel.g = Max(static_cast<int32>(pixel.g) + level, 0);
					pixel.b = Max(static_cast<int32>(pixel.b) + level, 0);
				}
			}
			else if (level > 0)
			{
				for (auto& pixel : m_data)
				{
					pixel.r = Min(static_cast<int32>(pixel.r) + level, 255);
					pixel.g = Min(static_cast<int32>(pixel.g) + level, 255);
					pixel.b = Min(static_cast<int32>(pixel.b) + level, 255);
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

		// 2. 処理
		{
			Image image{ *this };

			if (level < 0)
			{
				for (auto& pixel : image)
				{
					pixel.r = Max(static_cast<int32>(pixel.r) + level, 0);
					pixel.g = Max(static_cast<int32>(pixel.g) + level, 0);
					pixel.b = Max(static_cast<int32>(pixel.b) + level, 0);
				}
			}
			else if (level > 0)
			{
				for (auto& pixel : image)
				{
					pixel.r = Min(static_cast<int32>(pixel.r) + level, 255);
					pixel.g = Min(static_cast<int32>(pixel.g) + level, 255);
					pixel.b = Min(static_cast<int32>(pixel.b) + level, 255);
				}
			}

			return image;
		}
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
			const int32 h = m_height;
			const int32 w = m_width;
			const int32 wHalf = (m_width / 2);
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

	Image Image::mirrored() const
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
			Image image{ m_width, m_height };

			const Color* pSrc = data();
			Color* pDst = image.data();
			const size_t width = m_width;

			for (size_t y = 0; y < m_height; ++y)
			{
				const Color* pSrcLine = (pSrc + width * y + width - 1);
				Color* pDstLine = (pDst + width * y);

				for (size_t x = 0; x < m_width; ++x)
				{
					*(pDstLine + x) = *(pSrcLine - x);
				}
			}

			return image;
		}
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
			const int32 h = m_height;
			const size_t stride_bytes = stride();

			Array<Color> line(m_width);
			Color* lineU = m_data.data();
			Color* lineB = lineU + m_width * (h - 1);

			for (int32 y = 0; y < h / 2; ++y)
			{
				std::memcpy(line.data(), lineU, stride_bytes);
				std::memcpy(lineU, lineB, stride_bytes);
				std::memcpy(lineB, line.data(), stride_bytes);

				lineU += m_width;
				lineB -= m_width;
			}
		}

		return *this;
	}

	Image Image::flipped() const
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
			Image image{ m_width, m_height };

			const size_t stride_bytes = stride();
			const Color* pSrc = data() + (m_height - 1) * m_width;
			Color* pDst = image.data();

			for (size_t y = 0; y < m_height; ++y)
			{
				std::memcpy(pDst, pSrc, stride_bytes);
				pDst += m_width;
				pSrc -= m_width;
			}

			return image;
		}
	}

	Image& Image::rotate90()
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
			// [Siv3D ToDo] 最適化
			Image tmp{ m_height, m_width };

			for (size_t y = 0; y < m_height; ++y)
			{
				const Color* pSrc = data() + y * m_width;
				const size_t dstX = m_height - y - 1;

				for (size_t x = 0; x < m_width; ++x)
				{
					tmp[x][dstX] = pSrc[x];
				}
			}

			swap(tmp);
		}

		return *this;
	}

	Image Image::rotated90() const
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
			Image image{ m_height, m_width };

			// [Siv3D ToDo] 最適化
			for (size_t y = 0; y < m_height; ++y)
			{
				const Color* pSrc = data() + y * m_width;
				const size_t dstX = m_height - y - 1;

				for (size_t x = 0; x < m_width; ++x)
				{
					image[x][dstX] = pSrc[x];
				}
			}

			return image;
		}
	}

	Image& Image::rotate180()
	{
		std::reverse(begin(), end());

		return *this;
	}

	Image Image::rotated180() const
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
			Image image{ m_width, m_height };

			const Color* pSrc = data() + num_pixels() - 1;
			Color* pDst = image.data();
			const Color* const pDstEnd = pDst + image.num_pixels();

			while (pDst != pDstEnd)
			{
				*pDst++ = *pSrc--;
			}

			return image;
		}
	}

	Image& Image::rotate270()
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
			// [Siv3D ToDo] 最適化
			Image tmp{ m_height, m_width };

			for (size_t y = 0; y < m_height; ++y)
			{
				const Color* pSrc = (data() + y * m_width);

				for (size_t x = 0; x < m_width; ++x)
				{
					tmp[m_width - x - 1][y] = pSrc[x];
				}
			}

			swap(tmp);
		}

		return *this;
	}

	Image Image::rotated270() const
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
			Image image{ m_height, m_width };

			for (size_t y = 0; y < m_height; ++y)
			{
				const Color* pSrc = (data() + y * m_width);

				for (size_t x = 0; x < m_width; ++x)
				{
					image[m_width - x - 1][y] = pSrc[x];
				}
			}

			return image;
		}
	}

	Image& Image::gammaCorrect(const double gamma)
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
			detail::InitGammmaTable(gamma, colorTable);

			for (auto& pixel : m_data)
			{
				pixel.r = colorTable[pixel.r];
				pixel.g = colorTable[pixel.g];
				pixel.b = colorTable[pixel.b];
			}
		}

		return *this;
	}

	Image Image::gammaCorrected(const double gamma) const
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
			Image image{ *this };

			uint8 colorTable[256];
			detail::InitGammmaTable(gamma, colorTable);

			for (auto& pixel : image)
			{
				pixel.r = colorTable[pixel.r];
				pixel.g = colorTable[pixel.g];
				pixel.b = colorTable[pixel.b];
			}

			return image;
		}
	}

	Image& Image::threshold(const uint8 threshold, const InvertColor invertColor)
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
			Color* pDst = data();
			const Color* pDstEnd = pDst + num_pixels();
			const double thresholdF = (threshold / 255.0);

			if (invertColor)
			{
				while (pDst != pDstEnd)
				{
					if (thresholdF < pDst->grayscale())
					{
						pDst->setRGB(255);
					}
					else
					{
						pDst->setRGB(0);
					}

					++pDst;
				}
			}
			else
			{
				while (pDst != pDstEnd)
				{
					if (thresholdF < pDst->grayscale())
					{
						pDst->setRGB(0);
					}
					else
					{
						pDst->setRGB(255);
					}

					++pDst;
				}
			}
		}

		return *this;
	}

	Image Image::thresholded(const uint8 threshold, const InvertColor invertColor) const
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
			Image image{ *this };

			Color* pDst = image.data();
			const Color* pDstEnd = pDst + num_pixels();
			const double thresholdF = (threshold / 255.0);

			if (invertColor)
			{
				while (pDst != pDstEnd)
				{
					if (thresholdF < pDst->grayscale())
					{
						pDst->setRGB(255);
					}
					else
					{
						pDst->setRGB(0);
					}

					++pDst;
				}
			}
			else
			{
				while (pDst != pDstEnd)
				{
					if (thresholdF < pDst->grayscale())
					{
						pDst->setRGB(0);
					}
					else
					{
						pDst->setRGB(255);
					}

					++pDst;
				}
			}

			return image;
		}
	}

	Image& Image::threshold_Otsu(const InvertColor invertColor)
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
			const int32 thresholdType = 
				((invertColor ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY) | cv::THRESH_OTSU);

			cv::Mat_<uint8> gray = OpenCV_Bridge::ToGrayScale(*this);

			cv::threshold(gray, gray, 0, 255, thresholdType);

			OpenCV_Bridge::FromGrayScale(gray, *this, OverwriteAlpha::No);
		}

		return *this;
	}

	Image Image::thresholded_Otsu(const InvertColor invertColor) const
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
			const int32 thresholdType =
				((invertColor ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY) | cv::THRESH_OTSU);

			cv::Mat_<uint8> gray = OpenCV_Bridge::ToGrayScale(*this);

			cv::threshold(gray, gray, 0, 255, thresholdType);

			Image image{ *this };

			OpenCV_Bridge::FromGrayScale(gray, image, OverwriteAlpha::No);

			return image;
		}
	}

	Image& Image::adaptiveThreshold(const AdaptiveThresholdMethod method, int32 blockSize, const double c, const InvertColor invertColor)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (IsEven(blockSize))
			{
				++blockSize;
			}
		}

		// 2. 処理
		{
			const cv::ThresholdTypes thresholdType = (invertColor ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY);

			cv::Mat_<uint8> gray = OpenCV_Bridge::ToGrayScale(*this);

			cv::adaptiveThreshold(gray, gray, 255, static_cast<int32>(method), thresholdType, blockSize, c);

			OpenCV_Bridge::FromGrayScale(gray, *this, OverwriteAlpha::No);
		}

		return *this;
	}

	Image Image::adaptiveThresholded(const AdaptiveThresholdMethod method, int32 blockSize, const double c, const InvertColor invertColor) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (blockSize % 2 == 0)
			{
				++blockSize;
			}
		}

		// 2. 処理
		{
			const cv::ThresholdTypes thresholdType = (invertColor ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY);

			cv::Mat_<uint8> gray = OpenCV_Bridge::ToGrayScale(*this);

			cv::adaptiveThreshold(gray, gray, 255, static_cast<int32>(method), thresholdType, blockSize, c);

			Image image{ *this };

			OpenCV_Bridge::FromGrayScale(gray, image, OverwriteAlpha::No);

			return image;
		}
	}









	Image& Image::gaussianBlur(const int32 size, const BorderType borderType)
	{
		return gaussianBlur(size, size, borderType);
	}

	Image& Image::gaussianBlur(const int32 horizontal, const int32 vertical, const BorderType borderType)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0)
				|| (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			cv::Mat_<cv::Vec4b> matSrc = OpenCV_Bridge::GetMatView(*this);

			cv::GaussianBlur(matSrc, matSrc, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), 0.0, 0.0, OpenCV_Bridge::ConvertBorderType(borderType));
		}

		return *this;
	}

	Image Image::gaussianBlurred(const int32 size, const BorderType borderType) const
	{
		return gaussianBlurred(size, size, borderType);
	}

	Image Image::gaussianBlurred(const int32 horizontal, const int32 vertical, const BorderType borderType) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0)
				|| (vertical <= 0))
			{
				return *this;
			}
		}

		Image image{ m_width, m_height };

		cv::Mat_<cv::Vec4b> matSrc(m_height, m_width, const_cast<cv::Vec4b*>(static_cast<const cv::Vec4b*>(static_cast<const void*>(data()))), stride());

		cv::Mat_<cv::Vec4b> matDst = OpenCV_Bridge::GetMatView(image);

		cv::GaussianBlur(matSrc, matDst, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), 0.0, 0.0, OpenCV_Bridge::ConvertBorderType(borderType));

		return image;
	}










	void Image::overwrite(Image& dst, const int32 x, const int32 y) const
	{
		overwrite(dst, Point{ x, y });
	}

	void Image::overwrite(Image& dst, const Point pos) const
	{
		if (this == &dst)
		{
			return;
		}

		const Image& src = *this;

		const int32 dstXBegin = Max(pos.x, 0);
		const int32 dstYBegin = Max(pos.y, 0);
		const int32 dstXEnd = Min(pos.x + src.width(), dst.width());
		const int32 dstYEnd = Min(pos.y + src.height(), dst.height());
		const int32 writeWidth = ((dstXEnd - dstXBegin) > 0 ? (dstXEnd - dstXBegin) : 0);
		const int32 writeHeight = ((dstYEnd - dstYBegin) > 0 ? (dstYEnd - dstYBegin) : 0);

		if ((writeWidth * writeHeight) == 0)
		{
			return;
		}

		const int32 srcXBegin = Max(0, -pos.x);
		const int32 srcYBegin = Max(0, -pos.y);

		const Color* pSrc = &src[srcYBegin][srcXBegin];
		Color* pDst = &dst[dstYBegin][dstXBegin];
		{
			const int32 srcWidth = src.width();
			const int32 dstWidth = dst.width();
			const size_t stride_bytes = (writeWidth * sizeof(Color));

			for (int32 y = 0; y < writeHeight; ++y)
			{
				std::memcpy(pDst, pSrc, stride_bytes);
				pSrc += srcWidth;
				pDst += dstWidth;
			}
		}
	}

	ImageROI Image::operator ()(const int32 x, const int32 y, const int32 w, const int32 h)
	{
		return operator()(Rect{ x, y, w, h });
	}

	ImageROI Image::operator ()(const Point& pos, const int32 w, const int32 h)
	{
		return operator()(Rect{ pos, w, h });
	}

	ImageROI Image::operator ()(const int32 x, const int32 y, const Size& size)
	{
		return operator()(Rect{ x, y, size });
	}

	ImageROI Image::operator ()(const Point& pos, const Size& size)
	{
		return operator()(Rect{ pos, size });
	}

	ImageROI Image::operator ()(const Rect& rect)
	{
		return{ *this, rect };
	}

	ImageConstROI Image::operator ()(const int32 x, const int32 y, const int32 w, const int32 h) const
	{
		return operator()(Rect{ x, y, w, h });
	}

	ImageConstROI Image::operator ()(const Point& pos, const int32 w, const int32 h) const
	{
		return operator()(Rect{ pos, w, h });
	}

	ImageConstROI Image::operator ()(const int32 x, const int32 y, const Size& size) const
	{
		return operator()(Rect{ x, y, size });
	}

	ImageConstROI Image::operator ()(const Point& pos, const Size& size) const
	{
		return operator()(Rect{ pos, size });
	}

	ImageConstROI Image::operator ()(const Rect& rect) const
	{
		return{ *this, rect };
	}
}
