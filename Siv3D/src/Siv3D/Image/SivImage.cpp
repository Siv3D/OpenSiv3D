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
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/ImageDecoder.hpp>
# include <Siv3D/ImageEncoder.hpp>
# include <Siv3D/ImageFormat/PNGEncoder.hpp>

namespace s3d
{
	namespace detail
	{
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
}
