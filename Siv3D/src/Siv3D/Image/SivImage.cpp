//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Image.hpp>
# include <Siv3D/ImageROI.hpp>
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/MultiPolygon.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/ImageDecoder.hpp>
# include <Siv3D/ImageEncoder.hpp>
# include <Siv3D/Dialog.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ImageFormat/PNGEncoder.hpp>
# include <Siv3D/ImageFormat/JPEGEncoder.hpp>
# include <Siv3D/ImageFormat/PPMEncoder.hpp>
# include <Siv3D/ImageFormat/WebPEncoder.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>
# include "ImagePainting.hpp"

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
		static Color MakeSepia(Color color) noexcept
		{
			const double tr = Min(((0.393 * color.r) + (0.769 * color.g) + (0.189 * color.b)), 255.0);
			const double tg = Min(((0.349 * color.r) + (0.686 * color.g) + (0.168 * color.b)), 255.0);
			const double tb = Min(((0.272 * color.r) + (0.534 * color.g) + (0.131 * color.b)), 255.0);

			color.r = static_cast<uint8>(tr);
			color.g = static_cast<uint8>(tg);
			color.b = static_cast<uint8>(tb);
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

		static Color GetAverage(const Image& src, const Rect& rect)
		{
			const int32 count = rect.area();

			if (count == 0)
			{
				return Color{ 0 };
			}

			int32 sumR = 0, sumG = 0, sumB = 0, sumA = 0;

			const size_t imgWidth = src.width();
			const int32 height = rect.h;
			const int32 width = rect.w;

			const Color* pLine = &src[rect.y][rect.x];

			for (int32 y = 0; y < height; ++y)
			{
				const Color* pDst = pLine;

				for (int32 x = 0; x < width; ++x)
				{
					sumR += pDst->r;
					sumG += pDst->g;
					sumB += pDst->b;
					sumA += pDst->a;
					++pDst;
				}

				pLine += imgWidth;
			}

			return{
				static_cast<uint8>(sumR / count),
				static_cast<uint8>(sumG / count),
				static_cast<uint8>(sumB / count),
				static_cast<uint8>(sumA / count) };
		}

		static void FillRect(Image& dst, const Rect& rect, const Color& color)
		{
			const size_t imgWidth = dst.width();
			const int32 height = rect.h;
			const int32 width = rect.w;

			Color* pLine = &dst[rect.y][rect.x];

			for (int32 y = 0; y < height; ++y)
			{
				Color* pDst = pLine;

				for (int32 x = 0; x < width; ++x)
				{
					(*pDst++) = color;
				}

				pLine += imgWidth;
			}
		}

		[[nodiscard]]
		static Polygon SelectLargestPolygon(const MultiPolygon& polygons)
		{
			if (not polygons)
			{
				return{};
			}
			else if (polygons.size() == 1)
			{
				return polygons.front();
			}

			double maxArea = 0.0;
			size_t index = 0;

			for (size_t i = 0; i < polygons.size(); ++i)
			{
				const double area = polygons[i].area();

				if (area > maxArea)
				{
					maxArea = area;
					index = i;
				}
			}

			return polygons[index];
		}

		[[nodiscard]]
		static MultiPolygon ToPolygonsWithoutHoles(const cv::Mat_<uint8>& gray)
		{
			MultiPolygon polygons;
			std::vector<std::vector<cv::Point>> contours;

			try
			{
				cv::findContours(gray, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, { 0, 0 });
			}
			catch (cv::Exception&)
			{
				return polygons;
			}

			for (const auto& contour : contours)
			{
				const size_t externalSize = contour.size();

				if (externalSize < 3)
				{
					continue;
				}

				Array<Vec2> external(externalSize);
				{
					Vec2* pDst = external.data();
					const Vec2* const pDstEnd = pDst + externalSize;
					const cv::Point* pSrc = contour.data() + (externalSize - 1);

					while (pDst != pDstEnd)
					{
						pDst->set(pSrc->x, pSrc->y);
						++pDst; --pSrc;
					}
				}

				for (auto& polygon : Polygon::Correct(external))
				{
					if (polygon)
					{
						polygons.push_back(std::move(polygon));
					}
				}
			}

			return polygons;
		}

		[[nodiscard]]
		static MultiPolygon ToPolygons(const cv::Mat_<uint8>& gray)
		{
			MultiPolygon polygons;
			std::vector<std::vector<cv::Point>> contours;
			std::vector<cv::Vec4i> hierarchy;

			try
			{
				cv::findContours(gray, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE, { 0, 0 });
			}
			catch (cv::Exception&)
			{
				return polygons;
			}

			for (size_t i = 0; i < contours.size(); i = hierarchy[i][0])
			{
				const auto& contour = contours[i];
				const size_t externalSize = contour.size();

				if (externalSize < 3)
				{
					continue;
				}

				Array<Vec2> external(externalSize);
				{
					{
						Vec2* pDst = external.data();
						const Vec2* const pDstEnd = pDst + externalSize;
						const cv::Point* pSrc = contour.data() + (externalSize - 1);

						while (pDst != pDstEnd)
						{
							pDst->set(pSrc->x, pSrc->y);
							++pDst; --pSrc;
						}
					}

					for (size_t k = 0; k < externalSize; ++k)
					{
						const Vec2& a = external[k];

						for (size_t m = k + 1; m < externalSize; ++m)
						{
							if (Vec2& b = external[m]; a == b)
							{
								b += ((external[m - 1] - b).normalized() * 0.5).rotated(90_deg);
							}
						}
					}

					//{
					//	Vec2* pDst = external.data();
					//	const Vec2* pDstEnd = external.data() + externalSize - 1;

					//	while (pDst != pDstEnd)
					//	{
					//		*pDst += ((*(pDst + 1) - *pDst).normalized() * 0.01);
					//		++pDst;
					//	}
					//}
				}

				Array<Array<Vec2>> holes;
				{
					for (int32 k = hierarchy[i][2]; k != -1; k = hierarchy[k][0])
					{
						const auto& holeContour = contours[k];
						const size_t holeSize = holeContour.size();

						Array<Vec2> hole(holeSize);
						{
							Vec2* pDst = hole.data();
							const Vec2* const pDstEnd = pDst + holeSize;
							const cv::Point* pSrc = holeContour.data() + (holeSize - 1);

							while (pDst != pDstEnd)
							{
								pDst->set(pSrc->x, pSrc->y);
								++pDst; --pSrc;
							}
						}

						holes.push_back(std::move(hole));
					}
				}

				for (auto& polygon : Polygon::Correct(external, holes))
				{
					if (polygon)
					{
						polygons.push_back(std::move(polygon));
					}
				}
			}

			return polygons;
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
		const ColorF* const pSrcEnd = (pSrc + grid.num_elements());
		Color* pDst = m_data.data();

		while (pSrc != pSrcEnd)
		{
			*pDst++ = *pSrc++;
		}
	}

	void Image::fill(const Color color) noexcept
	{
		std::fill(m_data.begin(), m_data.end(), color);
	}

	void Image::resize(const size_t width, const size_t height)
	{
		resize(Size(width, height));
	}

	void Image::resize(const Size size)
	{
		if (not detail::IsValidImageSize(size))
		{
			return clear();
		}

		if (size == Size(m_width, m_height))
		{
			return;
		}

		m_data.resize(size.x * size.y);
		m_width = static_cast<uint32>(size.x);
		m_height = static_cast<uint32>(size.y);
	}

	void Image::resize(const size_t width, const size_t height, const Color fillColor)
	{
		resize(Size(width, height), fillColor);
	}

	void Image::resize(const Size size, const Color fillColor)
	{
		if (not detail::IsValidImageSize(size))
		{
			return clear();
		}

		if (size == Size(m_width, m_height))
		{
			return;
		}

		m_data.assign(size.x * size.y, fillColor);
		m_width = static_cast<uint32>(size.x);
		m_height = static_cast<uint32>(size.y);
	}

	void Image::resizeRows(const size_t rows, const Color fillColor)
	{
		if (rows == m_height)
		{
			return;
		}

		if (not detail::IsValidImageSize(Size(m_width, rows)))
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

	Color Image::getPixel(const int32 x, const int32 y, const ImageAddressMode addressMode) const
	{
		return getPixel(Size{ x, y }, addressMode);
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

	ColorF Image::samplePixel(const double x, const double y, const ImageAddressMode addressMode) const
	{
		return samplePixel(Vec2{ x, y }, addressMode);
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
			const uint8 t = p->r;
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

	Blob Image::encode(const ImageFormat format) const
	{
		return ImageEncoder::Encode(*this, format);
	}

	bool Image::saveWithDialog() const
	{
		if (isEmpty())
		{
			LOG_FAIL(U"Image::saveWithDialog(): Image is empty");
			return false;
		}

		if (const auto path = Dialog::SaveImage())
		{
			return save(*path);
		}
		else
		{
			return false;
		}
	}

	bool Image::savePNG(const FilePathView path, const PNGFilter filter) const
	{
		return PNGEncoder{}.save(*this, path, filter);
	}

	Blob Image::encodePNG(const PNGFilter filter) const
	{
		return PNGEncoder{}.encode(*this, filter);
	}

	bool Image::saveJPEG(const FilePathView path, const int32 quality) const
	{
		return JPEGEncoder{}.save(*this, path, quality);
	}

	Blob Image::encodeJPEG(const int32 quality) const
	{
		return JPEGEncoder{}.encode(*this, quality);
	}

	bool Image::savePPM(const FilePathView path, const PPMType format) const
	{
		return PPMEncoder{}.save(*this, path, format);
	}

	Blob Image::encodePPM(const PPMType format) const
	{
		return PPMEncoder{}.encode(*this, format);
	}

	bool Image::saveWebP(const FilePathView path, const Lossless lossless, const double quality, const WebPMethod method) const
	{
		return WebPEncoder{}.save(*this, path, lossless, quality, method);
	}

	Blob Image::encodeWebP(const Lossless lossless, const double quality, const WebPMethod method) const
	{
		return WebPEncoder{}.encode(*this, lossless, quality, method);
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

	Image& Image::sepia()
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
				pixel = detail::MakeSepia(pixel);
			}
		}

		return *this;
	}

	Image Image::sepiaed() const
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
				pixel = detail::MakeSepia(pixel);
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
					pixel.r = static_cast<uint8>(Max(static_cast<int32>(pixel.r) + level, 0));
					pixel.g = static_cast<uint8>(Max(static_cast<int32>(pixel.g) + level, 0));
					pixel.b = static_cast<uint8>(Max(static_cast<int32>(pixel.b) + level, 0));
				}
			}
			else if (level > 0)
			{
				for (auto& pixel : m_data)
				{
					pixel.r = static_cast<uint8>(Min(static_cast<int32>(pixel.r) + level, 255));
					pixel.g = static_cast<uint8>(Min(static_cast<int32>(pixel.g) + level, 255));
					pixel.b = static_cast<uint8>(Min(static_cast<int32>(pixel.b) + level, 255));
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
					pixel.r = static_cast<uint8>(Max(static_cast<int32>(pixel.r) + level, 0));
					pixel.g = static_cast<uint8>(Max(static_cast<int32>(pixel.g) + level, 0));
					pixel.b = static_cast<uint8>(Max(static_cast<int32>(pixel.b) + level, 0));
				}
			}
			else if (level > 0)
			{
				for (auto& pixel : image)
				{
					pixel.r = static_cast<uint8>(Min(static_cast<int32>(pixel.r) + level, 255));
					pixel.g = static_cast<uint8>(Min(static_cast<int32>(pixel.g) + level, 255));
					pixel.b = static_cast<uint8>(Min(static_cast<int32>(pixel.b) + level, 255));
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
			const size_t imageWidth = m_width;
			Color* p = m_data.data();

			for (uint32 y = 0; y < m_height; ++y)
			{
				std::reverse(p, p + imageWidth);
				p += imageWidth;
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

		// 2. 処理A
		{
			const size_t imageWidth = m_width;
			Color* pLineFrom = data();
			Color* pLineTo = pLineFrom + (imageWidth * (m_height - 1));

			for (uint32 y = 0; y < (m_height / 2); ++y)
			{
				std::swap_ranges(pLineFrom, pLineFrom + imageWidth, pLineTo);
				pLineFrom += imageWidth;
				pLineTo -= imageWidth;
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
						pDst->setRGB(0);
					}
					else
					{
						pDst->setRGB(255);
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
						pDst->setRGB(255);
					}
					else
					{
						pDst->setRGB(0);
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
						pDst->setRGB(0);
					}
					else
					{
						pDst->setRGB(255);
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
						pDst->setRGB(255);
					}
					else
					{
						pDst->setRGB(0);
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

	Image& Image::mosaic(const int32 size)
	{
		return mosaic(size, size);
	}

	Image& Image::mosaic(const int32 horizontal, const int32 vertical)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 1) || (vertical <= 1))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const uint32 xPiece = (m_width / horizontal);
			const uint32 yPiece = (m_height / vertical);
			uint32 yP = 0, xP = 0;

			for (yP = 0; yP < yPiece; ++yP)
			{
				for (xP = 0; xP < xPiece; ++xP)
				{
					const Rect rc(xP * horizontal, yP * vertical, horizontal, vertical);
					detail::FillRect(*this, rc, detail::GetAverage(*this, rc));
				}

				const Rect rc(xP * horizontal, yP * vertical, m_width - xP * horizontal, vertical);
				detail::FillRect(*this, rc, detail::GetAverage(*this, rc));
			}

			if (yP * vertical < m_height)
			{
				const int32 tY = m_height - yP * vertical;

				for (xP = 0; xP < xPiece; ++xP)
				{
					const Rect rc(xP * horizontal, yP * vertical, horizontal, tY);
					detail::FillRect(*this, rc, detail::GetAverage(*this, rc));
				}

				const Rect rc(xP * horizontal, yP * vertical, m_width - xP * horizontal, tY);
				detail::FillRect(*this, rc, detail::GetAverage(*this, rc));
			}
		}

		return *this;
	}

	Image Image::mosaiced(const int32 size) const
	{
		return mosaiced(size, size);
	}

	Image Image::mosaiced(const int32 horizontal, const int32 vertical) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 1) || (vertical <= 1))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image image{ *this };

			const uint32 xPiece = (m_width / horizontal);
			const uint32 yPiece = (m_height / vertical);
			uint32 yP = 0, xP = 0;

			for (yP = 0; yP < yPiece; ++yP)
			{
				for (xP = 0; xP < xPiece; ++xP)
				{
					const Rect rc(xP * horizontal, yP * vertical, horizontal, vertical);
					detail::FillRect(image, rc, detail::GetAverage(image, rc));
				}

				const Rect rc(xP * horizontal, yP * vertical, m_width - xP * horizontal, vertical);
				detail::FillRect(image, rc, detail::GetAverage(image, rc));
			}

			if (yP * vertical < m_height)
			{
				const int32 tY = m_height - yP * vertical;

				for (xP = 0; xP < xPiece; ++xP)
				{
					const Rect rc(xP * horizontal, yP * vertical, horizontal, tY);
					detail::FillRect(image, rc, detail::GetAverage(image, rc));
				}

				const Rect rc(xP * horizontal, yP * vertical, m_width - xP * horizontal, tY);
				detail::FillRect(image, rc, detail::GetAverage(image, rc));
			}

			return image;
		}
	}

	Image& Image::spread(const int32 size)
	{
		return spread(size, size);
	}

	Image& Image::spread(const int32 horizontal, const int32 vertical)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0) || (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image tmp{ m_width, m_height };
			DefaultRNG rng{ 12345 };

			UniformIntDistribution<int32> hu{ -horizontal, horizontal };
			UniformIntDistribution<int32> vu{ -vertical, vertical };

			Color* pDst = tmp.data();

			for (int32 y = 0; y < static_cast<int32>(m_height); ++y)
			{
				for (int32 x = 0; x < static_cast<int32>(m_width); ++x)
				{
					const int32 xOffset = hu(rng);
					const int32 yOffset = vu(rng);
					*pDst++ = getPixel(x + xOffset, y + yOffset, ImageAddressMode::Mirror);
				}
			}

			swap(tmp);
		}

		return *this;
	}

	Image Image::spreaded(const int32 size) const
	{
		return spreaded(size, size);
	}

	Image Image::spreaded(const int32 horizontal, const int32 vertical) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0) || (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image image{ m_width, m_height };
			DefaultRNG rng{ 12345 };

			UniformIntDistribution<int32> hu{ -horizontal, horizontal };
			UniformIntDistribution<int32> vu{ -vertical, vertical };

			Color* pDst = image.data();

			for (int32 y = 0; y < static_cast<int32>(m_height); ++y)
			{
				for (int32 x = 0; x < static_cast<int32>(m_width); ++x)
				{
					const int32 xOffset = hu(rng);
					const int32 yOffset = vu(rng);
					*pDst++ = getPixel(x + xOffset, y + yOffset, ImageAddressMode::Mirror);
				}
			}

			return image;
		}
	}

	Image& Image::blur(const int32 size, const BorderType borderType)
	{
		return blur(size, size, borderType);
	}

	Image& Image::blur(const int32 horizontal, const int32 vertical, const BorderType borderType)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0) || (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(*this);
			cv::blur(matSrc, matSrc, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), cv::Point(-1, -1), OpenCV_Bridge::ConvertBorderType(borderType));
		}

		return *this;
	}

	Image Image::blurred(const int32 size, const BorderType borderType) const
	{
		return blurred(size, size, borderType);
	}

	Image Image::blurred(const int32 horizontal, const int32 vertical, const BorderType borderType) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 0) || (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image image{ m_width, m_height };
			const cv::Mat matSrc(cv::Size(m_width, m_height), CV_8UC4, const_cast<uint8*>(dataAsUint8()), stride());
			cv::Mat matDst = OpenCV_Bridge::GetMatView(image);

			cv::blur(matSrc, matDst, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), cv::Point(-1, -1), OpenCV_Bridge::ConvertBorderType(borderType));
			return image;
		}
	}

	Image& Image::medianBlur(int32 apertureSize)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (apertureSize < 1)
			{
				return *this;
			}

			if (IsEven(apertureSize))
			{
				++apertureSize;
			}
		}

		// 2. 処理
		{
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(*this);
			cv::medianBlur(matSrc, matSrc, apertureSize);
		}

		return *this;
	}

	Image Image::medianBlurred(int32 apertureSize) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (apertureSize < 1)
			{
				return *this;
			}

			if (IsEven(apertureSize))
			{
				++apertureSize;
			}
		}

		// 2. 処理
		{
			Image image{ m_width, m_height };
			const cv::Mat matSrc(cv::Size(m_width, m_height), CV_8UC4, const_cast<uint8*>(dataAsUint8()), stride());
			cv::Mat matDst = OpenCV_Bridge::GetMatView(image);

			cv::medianBlur(matSrc, matDst, apertureSize);
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

			if ((horizontal <= 0) || (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(*this);
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

			if ((horizontal <= 0) || (vertical <= 0))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image image{ m_width, m_height };
			const cv::Mat matSrc(cv::Size(m_width, m_height), CV_8UC4, const_cast<uint8*>(dataAsUint8()), stride());
			cv::Mat matDst = OpenCV_Bridge::GetMatView(image);

			cv::GaussianBlur(matSrc, matDst, cv::Size(horizontal * 2 + 1, vertical * 2 + 1), 0.0, 0.0, OpenCV_Bridge::ConvertBorderType(borderType));
			return image;
		}
	}

	Image& Image::bilateralFilter(const int32 d, const double sigmaColor, const double sigmaSpace, const BorderType borderType)
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
			cv::Mat_<cv::Vec3b> matSrc = OpenCV_Bridge::ToMatVec3bBGR(*this);
			cv::Mat_<cv::Vec3b> matDst(m_height, m_width);
			cv::bilateralFilter(matSrc, matDst, d, sigmaColor, sigmaSpace, OpenCV_Bridge::ConvertBorderType(borderType));
			OpenCV_Bridge::FromMatVec3b(matDst, *this, OverwriteAlpha::No);
		}

		return *this;
	}

	Image Image::bilateralFiltered(const int32 d, const double sigmaColor, const double sigmaSpace, const BorderType borderType) const
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
			cv::Mat_<cv::Vec3b> matSrc = OpenCV_Bridge::ToMatVec3bBGR(*this);
			cv::Mat_<cv::Vec3b> matDst(m_height, m_width);
			cv::bilateralFilter(matSrc, matDst, d, sigmaColor, sigmaSpace, OpenCV_Bridge::ConvertBorderType(borderType));
		
			Image image{ *this };
			OpenCV_Bridge::FromMatVec3b(matDst, image, OverwriteAlpha::No);
			return image;
		}
	}

	Image& Image::dilate(const int32 iterations)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (iterations <= 0)
			{
				return *this;
			}
		}

		// 2. 処理
		{
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(*this);
			cv::dilate(matSrc, matSrc, cv::Mat(), cv::Point(-1, -1), iterations);
		}

		return *this;
	}

	Image Image::dilated(const int32 iterations) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (iterations <= 0)
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image image{ m_width, m_height };
			const cv::Mat matSrc(cv::Size(m_width, m_height), CV_8UC4, const_cast<uint8*>(dataAsUint8()), stride());
			cv::Mat matDst = OpenCV_Bridge::GetMatView(image);

			cv::dilate(matSrc, matDst, cv::Mat(), cv::Point(-1, -1), iterations);
			return image;
		}
	}

	Image& Image::erode(const int32 iterations)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (iterations <= 0)
			{
				return *this;
			}
		}

		// 2. 処理
		{
			cv::Mat matSrc = OpenCV_Bridge::GetMatView(*this);
			cv::erode(matSrc, matSrc, cv::Mat(), cv::Point(-1, -1), iterations);
		}

		return *this;
	}

	Image Image::eroded(const int32 iterations) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if (iterations <= 0)
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image image{ m_width, m_height };
			const cv::Mat matSrc(cv::Size(m_width, m_height), CV_8UC4, const_cast<uint8*>(dataAsUint8()), stride());
			cv::Mat matDst = OpenCV_Bridge::GetMatView(image);

			cv::erode(matSrc, matDst, cv::Mat(), cv::Point(-1, -1), iterations);
			return image;
		}
	}

	Image& Image::floodFill(const Point& pos, const Color& color, const FloodFillConnectivity connectivity, const int32 lowerDifference, const int32 upperDifference)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((not InRange(pos.x, 0, static_cast<int32>(m_width) - 1))
				|| (not InRange(pos.y, 0, static_cast<int32>(m_height) - 1)))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			cv::Mat_<cv::Vec3b> mat = OpenCV_Bridge::ToMatVec3bBGR(*this);

			cv::floodFill(
				mat,
				{ pos.x, pos.y },
				cv::Scalar(color.b, color.g, color.r),
				nullptr,
				cv::Scalar::all(lowerDifference),
				cv::Scalar::all(upperDifference),
				static_cast<int32>(connectivity) | cv::FLOODFILL_FIXED_RANGE | (255 << 8)
			);

			OpenCV_Bridge::FromMatVec3b(mat, *this, OverwriteAlpha::No);
		}

		return *this;
	}

	Image Image::floodFilled(const Point& pos, const Color& color, const FloodFillConnectivity connectivity, const int32 lowerDifference, const int32 upperDifference) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((not InRange(pos.x, 0, static_cast<int32>(m_width) - 1))
				|| (not InRange(pos.y, 0, static_cast<int32>(m_height) - 1)))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			cv::Mat_<cv::Vec3b> mat = OpenCV_Bridge::ToMatVec3bBGR(*this);

			cv::floodFill(
				mat,
				{ pos.x, pos.y },
				cv::Scalar(color.b, color.g, color.r),
				nullptr,
				cv::Scalar::all(lowerDifference),
				cv::Scalar::all(upperDifference),
				static_cast<int32>(connectivity) | cv::FLOODFILL_FIXED_RANGE
			);

			Image image{ *this };
			OpenCV_Bridge::FromMatVec3b(mat, image, OverwriteAlpha::No);
			return image;
		}
	}

	Image& Image::scale(int32 width, int32 height, InterpolationAlgorithm interpolation)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			width	= Clamp<int32>(width, 1, Image::MaxWidth);
			height	= Clamp<int32>(height, 1, Image::MaxHeight);

			if ((static_cast<int32>(m_width) == width)
				&& (static_cast<int32>(m_height) == height))
			{
				return *this;
			}
		}

		const uint32 targetWidth = width;
		const uint32 targetHeight = height;

		// 2. 処理
		{
			if (interpolation == InterpolationAlgorithm::Auto)
			{
				if ((m_width <= targetWidth) && (m_height <= targetHeight))
				{
					interpolation = InterpolationAlgorithm::Lanczos;
				}
				else if ((targetWidth <= m_width / 2) || (targetHeight <= m_height / 2))
				{
					interpolation = InterpolationAlgorithm::Area;
				}
				else
				{
					interpolation = InterpolationAlgorithm::Lanczos;
				}
			}

			Image tmp(targetWidth, targetHeight);
			const cv::Mat matSrc = OpenCV_Bridge::GetMatView(*this);
			cv::Mat matDst = OpenCV_Bridge::GetMatView(tmp);
			
			cv::resize(matSrc, matDst, matDst.size(), 0, 0, static_cast<int32>(interpolation));
			swap(tmp);
		}

		return *this;
	}

	Image Image::scaled(int32 width, int32 height, InterpolationAlgorithm interpolation) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			width	= Clamp<int32>(width, 1, Image::MaxWidth);
			height	= Clamp<int32>(height, 1, Image::MaxHeight);

			if ((static_cast<int32>(m_width) == width)
				&& (static_cast<int32>(m_height) == height))
			{
				return *this;
			}
		}

		const uint32 targetWidth = width;
		const uint32 targetHeight = height;

		// 2. 処理
		{
			if (interpolation == InterpolationAlgorithm::Auto)
			{
				if ((m_width <= targetWidth) && (m_height <= targetHeight))
				{
					interpolation = InterpolationAlgorithm::Lanczos;
				}
				else if ((targetWidth <= m_width / 2) || (targetHeight <= m_height / 2))
				{
					interpolation = InterpolationAlgorithm::Area;
				}
				else
				{
					interpolation = InterpolationAlgorithm::Lanczos;
				}
			}

			Image image(targetWidth, targetHeight);
			const cv::Mat matSrc(cv::Size(m_width, m_height), CV_8UC4, const_cast<uint8*>(dataAsUint8()), stride());
			cv::Mat matDst = OpenCV_Bridge::GetMatView(image);

			cv::resize(matSrc, matDst, matDst.size(), 0, 0, static_cast<int32>(interpolation));
			return image;
		}
	}

	Image& Image::scale(const Size& size, const InterpolationAlgorithm interpolation)
	{
		return scale(size.x, size.y, interpolation);
	}

	Image Image::scaled(const Size& size, const InterpolationAlgorithm interpolation) const
	{
		return scaled(size.x, size.y, interpolation);
	}

	Image& Image::scale(const double scaling, const InterpolationAlgorithm interpolation)
	{
		return scale(static_cast<int32>(m_width * scaling), static_cast<int32>(m_height * scaling), interpolation);
	}

	Image Image::scaled(const double scaling, const InterpolationAlgorithm interpolation) const
	{
		return scaled(static_cast<int32>(m_width * scaling), static_cast<int32>(m_height * scaling), interpolation);
	}

	Image& Image::fit(int32 width, int32 height, const AllowScaleUp allowScaleUp, const InterpolationAlgorithm interpolation)
	{
		if (not allowScaleUp)
		{
			width	= Min(width, static_cast<int32>(m_width));
			height	= Min(height, static_cast<int32>(m_height));
		}

		const int32 w = m_width;
		const int32 h = m_height;
		double ws = (static_cast<double>(width) / w); // 何 % scalingするか
		double hs = (static_cast<double>(height) / h);

		int32 targetWidth, targetHeight;

		if (ws < hs)
		{
			targetWidth		= width;
			targetHeight	= Max(static_cast<int32>(h * ws), 1);
		}
		else
		{
			targetWidth		= Max(static_cast<int32>(w * hs), 1);
			targetHeight	= height;
		}

		return scale(targetWidth, targetHeight, interpolation);
	}

	Image Image::fitted(int32 width, int32 height, const AllowScaleUp allowScaleUp, const InterpolationAlgorithm interpolation) const
	{
		if (not allowScaleUp)
		{
			width	= Min(width, static_cast<int32>(m_width));
			height	= Min(height, static_cast<int32>(m_height));
		}

		const int32 w = m_width;
		const int32 h = m_height;
		double ws = (static_cast<double>(width) / w); // 何% scalingするか
		double hs = (static_cast<double>(height) / h);

		int32 targetWidth, targetHeight;

		if (ws < hs)
		{
			targetWidth		= width;
			targetHeight	= Max(static_cast<int32>(h * ws), 1);
		}
		else
		{
			targetWidth		= Max(static_cast<int32>(w * hs), 1);
			targetHeight	= height;
		}

		return scaled(targetWidth, targetHeight, interpolation);
	}

	Image& Image::fit(const Size& size, const AllowScaleUp allowScaleUp, const InterpolationAlgorithm interpolation)
	{
		return fit(size.x, size.y, allowScaleUp, interpolation);
	}

	Image Image::fitted(const Size& size, const AllowScaleUp allowScaleUp, const InterpolationAlgorithm interpolation) const
	{
		return fitted(size.x, size.y, allowScaleUp, interpolation);
	}

	Image& Image::border(const int32 thickness, const Color& color)
	{
		return border(thickness, thickness, thickness, thickness, color);
	}

	Image Image::bordered(const int32 thickness, const Color& color) const
	{
		return bordered(thickness, thickness, thickness, thickness, color);
	}

	Image& Image::border(int32 top, int32 right, int32 bottom, int32 left, const Color& color)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			top		= Max(0, top);
			right	= Max(0, right);
			bottom	= Max(0, bottom);
			left	= Max(0, left);

			if (top == 0 && right == 0 && bottom == 0 && left == 0)
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image tmp(left + m_width + right, top + m_height + bottom, color);

			const Color* pSrc = data();
			const size_t srcStride = stride();
			Color* pDst = tmp.data() + tmp.width() * top + left;
			const size_t srcStep = m_width;
			const size_t dstStep = tmp.width();

			for (uint32 y = 0; y < m_height; ++y)
			{
				std::memcpy(pDst, pSrc, srcStride);
				pSrc += srcStep;
				pDst += dstStep;
			}

			swap(tmp);
		}

		return *this;
	}

	Image Image::bordered(int32 top, int32 right, int32 bottom, int32 left, const Color& color) const
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			top		= Max(0, top);
			right	= Max(0, right);
			bottom	= Max(0, bottom);
			left	= Max(0, left);

			if (top == 0 && right == 0 && bottom == 0 && left == 0)
			{
				return *this;
			}
		}

		// 2. 処理
		{
			Image image(left + m_width + right, top + m_height + bottom, color);

			const Color* pSrc = data();
			const size_t srcStride = stride();
			Color* pDst = image.data() + image.width() * top + left;
			const size_t srcStep = m_width;
			const size_t dstStep = image.width();

			for (uint32 y = 0; y < m_height; ++y)
			{
				std::memcpy(pDst, pSrc, srcStride);
				pSrc += srcStep;
				pDst += dstStep;
			}

			return image;
		}
	}

	Image Image::warpAffine(const Mat3x2& mat, const Color& background) const
	{
		if (isEmpty())
		{
			return{};
		}

		const Quad quad{
			mat.transformPoint(Point{ 0, 0 }),
			mat.transformPoint(Point{ m_width, 0 }),
			mat.transformPoint(Point{ m_width, m_height }),
			mat.transformPoint(Point{ 0, m_height })
		};
		const RectF boundingRect = Geometry2D::BoundingRect(&quad.p0, 4);
		const Mat3x2 m = mat.translated(-boundingRect.pos);
		const Size dstSize = Math::Ceil(boundingRect.size).asPoint();

		const cv::Matx23f transform{ m._11, m._21, m._31, m._12, m._22, m._32 };
		const cv::Mat matSrc(cv::Size(m_width, m_height), CV_8UC4, const_cast<uint8*>(dataAsUint8()), stride());
		cv::Mat_<cv::Vec4b> matDst;

		const ColorF bg{ background };
		cv::warpAffine(matSrc, matDst, transform, cv::Size(dstSize.x, dstSize.y), cv::INTER_LINEAR, cv::BORDER_CONSTANT,
			cv::Scalar(background.r, background.g, background.b, background.a));

		Image image;
		OpenCV_Bridge::FromMatVec4bRGBA(matDst, image);
		return image;
	}

	Image Image::rotated(const double angle, const Color& background) const
	{
		return warpAffine(Mat3x2::Rotate(angle, size() * 0.5), background);
	}

	Image Image::warpPerspective(const Quad& quad, const Color& background) const
	{
		if (isEmpty())
		{
			return{};
		}

		const RectF boundingRect = Geometry2D::BoundingRect(&quad.p0, 4);
		const Quad q = quad.movedBy(-boundingRect.pos);
		const Size dstSize = Math::Ceil(boundingRect.size).asPoint();

		const std::array<cv::Point2f, 4> from = {
			cv::Point2f(0, 0),
			cv::Point2f(static_cast<float>(m_width), 0),
			cv::Point2f(static_cast<float>(m_width), static_cast<float>(m_height)),
			cv::Point2f(0, static_cast<float>(m_height))
		};

		const std::array<cv::Point2f, 4> to = {
			cv::Point2f(static_cast<float>(q.p0.x), static_cast<float>(q.p0.y)),
			cv::Point2f(static_cast<float>(q.p1.x), static_cast<float>(q.p1.y)),
			cv::Point2f(static_cast<float>(q.p2.x), static_cast<float>(q.p2.y)),
			cv::Point2f(static_cast<float>(q.p3.x), static_cast<float>(q.p3.y)),
		};

		const cv::Mat transform = cv::getPerspectiveTransform(from, to);
		const cv::Mat matSrc(cv::Size(m_width, m_height), CV_8UC4, const_cast<uint8*>(dataAsUint8()), stride());
		cv::Mat_<cv::Vec4b> matDst;

		const ColorF bg{ background };
		cv::warpPerspective(matSrc, matDst, transform, cv::Size(dstSize.x, dstSize.y), cv::INTER_LINEAR, cv::BORDER_CONSTANT,
			cv::Scalar(background.r, background.g, background.b, background.a));

		Image image;
		OpenCV_Bridge::FromMatVec4bRGBA(matDst, image);
		return image;
	}

	void Image::paint(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		paint(dst, Point{ x, y }, color);
	}

	void Image::paint(Image& dst, const Point& pos, const Color& color) const
	{
		if (this == &dst)
		{
			return;
		}

		const Image& src = *this;
		const int32 dstXBegin	= Max(pos.x, 0);
		const int32 dstYBegin	= Max(pos.y, 0);
		const int32 dstXEnd		= Min(pos.x + src.width(), dst.width());
		const int32 dstYEnd		= Min(pos.y + src.height(), dst.height());
		const int32 writeWidth	= (dstXEnd - dstXBegin);
		const int32 writeHeight	= (dstYEnd - dstYBegin);

		if ((writeWidth <= 0) || (writeHeight <= 0))
		{
			return;
		}

		const int32 srcXBegin = Max(0, -pos.x);
		const int32 srcYBegin = Max(0, -pos.y);

		const Color* pSrc = &src[srcYBegin][srcXBegin];
		Color* pDst = &dst[dstYBegin][dstXBegin];

		const int32 srcWidth = src.width();
		const int32 dstWidth = dst.width();
		ImagePainting::Paint(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
	}

	void Image::stamp(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		stamp(dst, Point{ x, y }, color);
	}

	void Image::stamp(Image& dst, const Point& pos, const Color& color) const
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
		const int32 writeWidth = (dstXEnd - dstXBegin);
		const int32 writeHeight = (dstYEnd - dstYBegin);

		if ((writeWidth <= 0) || (writeHeight <= 0))
		{
			return;
		}

		const int32 srcXBegin = Max(0, -pos.x);
		const int32 srcYBegin = Max(0, -pos.y);

		const Color* pSrc = &src[srcYBegin][srcXBegin];
		Color* pDst = &dst[dstYBegin][dstXBegin];

		const int32 srcWidth = src.width();
		const int32 dstWidth = dst.width();
		ImagePainting::Stamp(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth, color);
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
		const int32 srcWidth = src.width();
		const int32 dstWidth = dst.width();

		ImagePainting::Overwrite(pSrc, pDst, writeWidth, writeHeight, srcWidth, dstWidth);
	}

	void Image::paintAt(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		paintAt(dst, Point{ x, y, }, color);
	}

	void Image::paintAt(Image& dst, const Point& pos, const Color& color) const
	{
		paint(dst, (pos - (size() / 2)), color);
	}

	void Image::stampAt(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		stampAt(dst, Point{ x, y, }, color);
	}

	void Image::stampAt(Image& dst, const Point& pos, const Color& color) const
	{
		stamp(dst, (pos - (size() / 2)), color);
	}

	void Image::overwriteAt(Image& dst, const int32 x, const int32 y) const
	{
		overwriteAt(dst, Point{ x, y, });
	}

	void Image::overwriteAt(Image& dst, const Point pos) const
	{
		overwrite(dst, (pos - (size() / 2)));
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

	Polygon Image::alphaToPolygon(const uint32 threshold, const AllowHoles allowHoles) const
	{
		return detail::SelectLargestPolygon(alphaToPolygons(threshold, allowHoles));
	}

	Polygon Image::alphaToPolygonCentered(const uint32 threshold, const AllowHoles allowHoles) const
	{
		return alphaToPolygon(threshold, allowHoles).movedBy(-size() * 0.5);
	}

	MultiPolygon Image::alphaToPolygons(const uint32 threshold, const AllowHoles allowHoles) const
	{
		if (isEmpty())
		{
			return{};
		}

		cv::Mat_<uint8> gray(height() * 2, width() * 2);
		OpenCV_Bridge::AlphaToBinary2x(*this, gray, threshold);

		if (allowHoles)
		{
			return detail::ToPolygons(gray).scale(0.5);
		}
		else
		{
			return detail::ToPolygonsWithoutHoles(gray).scale(0.5);
		}
	}

	MultiPolygon Image::alphaToPolygonsCentered(const uint32 threshold, const AllowHoles allowHoles) const
	{
		return alphaToPolygons(threshold, allowHoles).movedBy(-size() * 0.5);
	}

	Polygon Image::grayscaleToPolygon(const uint32 threshold, const AllowHoles allowHoles) const
	{
		return detail::SelectLargestPolygon(grayscaleToPolygons(threshold, allowHoles));
	}

	Polygon Image::grayscaleToPolygonCentered(const uint32 threshold, const AllowHoles allowHoles) const
	{
		return grayscaleToPolygon(threshold, allowHoles).movedBy(-size() * 0.5);
	}

	MultiPolygon Image::grayscaleToPolygons(const uint32 threshold, const AllowHoles allowHoles) const
	{
		if (isEmpty())
		{
			return{};
		}

		cv::Mat_<uint8> gray(height() * 2, width() * 2);
		OpenCV_Bridge::RedToBinary2x(*this, gray, threshold);

		if (allowHoles)
		{
			return detail::ToPolygons(gray).scale(0.5);
		}
		else
		{
			return detail::ToPolygonsWithoutHoles(gray).scale(0.5);
		}
	}

	MultiPolygon Image::grayscaleToPolygonsCentered(const uint32 threshold, const AllowHoles allowHoles) const
	{
		return grayscaleToPolygons(threshold, allowHoles).movedBy(-size() * 0.5);
	}

	ImageROI& ImageROI::sepia()
	{
		if (isEmpty())
		{
			return *this;
		}

		const size_t imageWidth = imageRef.width();
		Color* pLine = &imageRef[region.y][region.x];

		for (int32 y = 0; y < region.h; ++y)
		{
			Color* p = pLine;

			for (int32 x = 0; x < region.w; ++x)
			{
				*p = detail::MakeSepia(*p);
				++p;
			}

			pLine += imageWidth;
		}

		return *this;
	}

	ImageROI& ImageROI::posterize(const int32 level)
	{
		if (isEmpty())
		{
			return *this;
		}

		uint8 colorTable[256];
		detail::InitPosterizeTable(level, colorTable);

		const size_t imageWidth = imageRef.width();
		Color* pLine = &imageRef[region.y][region.x];

		for (int32 y = 0; y < region.h; ++y)
		{
			Color* p = pLine;

			for (int32 x = 0; x < region.w; ++x)
			{
				p->r = colorTable[p->r];
				p->g = colorTable[p->g];
				p->b = colorTable[p->b];
				++p;
			}

			pLine += imageWidth;
		}

		return *this;
	}

	ImageROI& ImageROI::gammaCorrect(const double gamma)
	{
		if (isEmpty())
		{
			return *this;
		}

		uint8 colorTable[256];
		detail::InitGammmaTable(gamma, colorTable);

		const size_t imageWidth = imageRef.width();
		Color* pLine = &imageRef[region.y][region.x];

		for (int32 y = 0; y < region.h; ++y)
		{
			Color* p = pLine;

			for (int32 x = 0; x < region.w; ++x)
			{
				p->r = colorTable[p->r];
				p->g = colorTable[p->g];
				p->b = colorTable[p->b];
				++p;
			}

			pLine += imageWidth;
		}

		return *this;
	}

	ImageROI& ImageROI::mosaic(const int32 horizontal, const int32 vertical)
	{
		// 1. パラメータチェック
		{
			if (isEmpty())
			{
				return *this;
			}

			if ((horizontal <= 1) || (vertical <= 1))
			{
				return *this;
			}
		}

		// 2. 処理
		{
			const int32 xPiece = (region.w / horizontal);
			const int32 yPiece = (region.h / vertical);
			int32 yP = 0, xP = 0;

			for (yP = 0; yP < yPiece; ++yP)
			{
				for (xP = 0; xP < xPiece; ++xP)
				{
					const Rect rc(region.x + xP * horizontal, region.y + yP * vertical, horizontal, vertical);
					detail::FillRect(imageRef, rc, detail::GetAverage(imageRef, rc));
				}

				const Rect rc(region.x + xP * horizontal, region.y + yP * vertical, region.w - xP * horizontal, vertical);
				detail::FillRect(imageRef, rc, detail::GetAverage(imageRef, rc));
			}

			if (yP * vertical < region.h)
			{
				const int32 tY = region.h - yP * vertical;

				for (xP = 0; xP < xPiece; ++xP)
				{
					const Rect rc(region.x + xP * horizontal, region.y + yP * vertical, horizontal, tY);
					detail::FillRect(imageRef, rc, detail::GetAverage(imageRef, rc));
				}

				const Rect rc(region.x + xP * horizontal, region.y + yP * vertical, region.w - xP * horizontal, tY);
				detail::FillRect(imageRef, rc, detail::GetAverage(imageRef, rc));
			}
		}

		return *this;
	}
}
