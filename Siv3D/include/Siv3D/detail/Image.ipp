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

# pragma once

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline constexpr bool IsValidImageSize(const Size size) noexcept
		{
			return InRange(size.x, 0, Image::MaxWidth)
				&& InRange(size.y, 0, Image::MaxHeight);
		}
	}

	inline Image::Image(Image&& image) noexcept
		: m_data(std::move(image.m_data))
		, m_width{ image.m_width }
		, m_height{ image.m_height }
	{
		image.m_width = image.m_height = 0;
	}

	inline Image::Image(const size_t size)
		: Image{ size, size } {}

	inline Image::Image(const size_t size, const Color color)
		: Image{ size, size, color } {}

	template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>*>
	inline Image::Image(const size_t size, Arg::generator_<Fty> generator)
		: Image{ size, size, generator } {}

	template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>*>
	inline Image::Image(const size_t size, Arg::generator0_1_<Fty> generator)
		: Image{ size, size, generator } {}


	inline Image::Image(const size_t width, const size_t height)
		: Image{ Size{ width, height } } {}

	inline Image::Image(const size_t width, const size_t height, const Color color)
		: Image{ Size{ width, height }, color } {}

	template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>*>
	inline Image::Image(const size_t width, const size_t height, Arg::generator_<Fty> generator)
		: Image{ Size{ width, height }, generator } {}

	template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>*>
	inline Image::Image(const size_t width, const size_t height, Arg::generator0_1_<Fty> generator)
		: Image{ Size{ width, height }, generator } {}

	inline Image::Image(const Size size)
		: m_data(detail::IsValidImageSize(size) ? size.area() : 0)
		, m_width{ static_cast<uint32>(detail::IsValidImageSize(size) ? size.x : 0) }
		, m_height{ static_cast<uint32>(detail::IsValidImageSize(size) ? size.y : 0) } {}

	inline Image::Image(const Size size, const Color color)
		: m_data(detail::IsValidImageSize(size) ? size.area() : 0, color)
		, m_width{ static_cast<uint32>(detail::IsValidImageSize(size) ? size.x : 0) }
		, m_height{ static_cast<uint32>(detail::IsValidImageSize(size) ? size.y : 0) } {}

	template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>*>
	inline Image::Image(const Size size, Arg::generator_<Fty> generator)
	{
		*this = Generate(size, generator.value());
	}

	template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>*>
	inline Image::Image(const Size size, Arg::generator0_1_<Fty> generator)
	{
		*this = Generate0_1(size, generator.value());
	}

	inline Image& Image::operator =(Image&& image) noexcept
	{
		m_data		= std::move(image.m_data);
		m_width		= image.m_width;
		m_height	= image.m_height;

		image.m_width = 0;
		image.m_height = 0;

		return *this;
	}

	template <class Type, class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty, Type>>*>
	Image::Image(const Grid<Type>& grid, Fty converter)
		: Image{ grid.size() }
	{
		if (m_data.empty())
		{
			return;
		}

		const Type* pSrc = grid.data();
		const Type* const pSrcEnd = (pSrc + grid.num_elements());
		Color* pDst = m_data.data();

		while (pSrc != pSrcEnd)
		{
			*pDst++ = converter(*pSrc++);
		}
	}

	inline int32 Image::width() const noexcept
	{
		return m_width;
	}

	inline int32 Image::height() const noexcept
	{
		return m_height;
	}

	inline Size Image::size() const noexcept
	{
		return{ m_width, m_height };
	}

	inline uint32 Image::stride() const noexcept
	{
		return m_width * sizeof(Color);
	}

	inline uint32 Image::num_pixels() const noexcept
	{
		return m_width * m_height;
	}

	inline size_t Image::size_bytes() const noexcept
	{
		return (static_cast<size_t>(stride()) * m_height);
	}

	inline bool Image::isEmpty() const noexcept
	{
		return m_data.empty();
	}

	inline Image::operator bool() const noexcept
	{
		return (not m_data.empty());
	}

	template <class Type>
	inline Type Image::horizontalAspectRatio() const noexcept
	{
		return size().horizontalAspectRatio();
	}

	inline void Image::shrink_to_fit()
	{
		m_data.shrink_to_fit();
	}

	inline void Image::clear() noexcept
	{
		m_data.clear();

		m_width = m_height = 0;
	}

	inline void Image::release()
	{
		clear();

		shrink_to_fit();
	}

	inline void Image::swap(Image& image) noexcept
	{
		using std::swap;
		swap(m_data, image.m_data);
		swap(m_width, image.m_width);
		swap(m_height, image.m_height);
	}

	inline Image Image::cloned() const
	{
		return *this;
	}

	inline Color* Image::operator[](const size_t y)
	{
		return m_data.data() + (m_width * y);
	}

	inline Color& Image::operator[](const Point pos)
	{
		return *(m_data.data() + (static_cast<size_t>(m_width) * pos.y + pos.x));
	}

	inline const Color* Image::operator[](const size_t y) const
	{
		return m_data.data() + (m_width * y);
	}

	inline const Color& Image::operator[](const Point pos) const
	{
		return *(m_data.data() + (static_cast<size_t>(m_width) * pos.y + pos.x));
	}

	inline Color* Image::data()
	{
		return m_data.data();
	}

	inline const Color* Image::data() const
	{
		return m_data.data();
	}

	inline uint8* Image::dataAsUint8()
	{
		return static_cast<uint8*>(static_cast<void*>(m_data.data()));
	}
	
	inline const uint8* Image::dataAsUint8() const
	{
		return static_cast<const uint8*>(static_cast<const void*>(&m_data[0]));
	}

	inline const Array<Color>& Image::asArray() const&
	{
		return m_data;
	}

	inline Array<Color> Image::asArray()&&
	{
		return std::move(m_data);
	}

	inline Image::iterator Image::begin() noexcept
	{
		return m_data.begin();
	}

	inline Image::iterator Image::end() noexcept
	{
		return m_data.end();
	}

	inline Image::const_iterator Image::begin() const noexcept
	{
		return m_data.begin();
	}

	inline Image::const_iterator Image::end() const noexcept
	{
		return m_data.end();
	}

	inline Image::const_iterator Image::cbegin() const noexcept
	{
		return m_data.cbegin();
	}

	inline Image::const_iterator Image::cend() const noexcept
	{
		return m_data.cend();
	}

	inline Image::reverse_iterator Image::rbegin() noexcept
	{
		return m_data.rbegin();
	}

	inline Image::reverse_iterator Image::rend() noexcept
	{
		return m_data.rend();
	}

	inline Image::const_reverse_iterator Image::rbegin() const noexcept
	{
		return m_data.rbegin();
	}

	inline Image::const_reverse_iterator Image::rend() const noexcept
	{
		return m_data.rend();
	}

	inline Image::const_reverse_iterator Image::crbegin() const noexcept
	{
		return m_data.crbegin();
	}

	inline Image::const_reverse_iterator Image::crend() const noexcept
	{
		return m_data.crend();
	}

	inline void Image::fill(const Color color) noexcept
	{
		Color* pDst = m_data.data();
		Color* const pDstEnd = pDst + m_data.size();

		while (pDst != pDstEnd)
		{
			*pDst++ = color;
		}
	}

	inline void Image::resize(const size_t width, const size_t height)
	{
		resize(Size(width, height));
	}

	inline void Image::resize(const Size size)
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
		m_width		= static_cast<uint32>(size.x);
		m_height	= static_cast<uint32>(size.y);
	}

	inline void Image::resize(const size_t width, const size_t height, const Color fillColor)
	{
		resize(Size(width, height), fillColor);
	}

	inline void Image::resize(const Size size, const Color fillColor)
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
		m_width		= static_cast<uint32>(size.x);
		m_height	= static_cast<uint32>(size.y);
	}

	inline void Image::resizeRows(const size_t rows, const Color fillColor)
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

	inline Color Image::getPixel(const int32 x, const int32 y, const ImageAddressMode addressMode) const
	{
		return getPixel(Size{ x, y }, addressMode);
	}

	inline ColorF Image::samplePixel(const double x, const double y, const ImageAddressMode addressMode) const
	{
		return samplePixel(Vec2{ x, y }, addressMode);
	}

	template <class Fty>
	inline Image& Image::forEach(Fty f)
	{
		for (auto& pixel : m_data)
		{
			f(pixel);
		}

		return *this;
	}

	template <class Fty>
	inline const Image& Image::forEach(Fty f) const
	{
		for (const auto& pixel : m_data)
		{
			f(pixel);
		}

		return *this;
	}

	template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>*>
	inline Image Image::Generate(const Size size, Fty generator)
	{
		Image newImage(size);

		if (not newImage)
		{
			return newImage;
		}

		const int32 width = size.x;
		const int32 height = size.y;
		Color* pDst = newImage.data();

		for (int32 y = 0; y < height; ++y)
		{
			for (int32 x = 0; x < width; ++x)
			{
				if constexpr (std::is_invocable_r_v<Color, Fty, Point>)
				{
					(*pDst++) = generator({ x, y });
				}
				else if constexpr (std::is_invocable_r_v<Color, Fty, int32, int32>)
				{
					(*pDst++) = generator(x, y);
				}
				else // std::is_invocable_r_v<Color, Fty>
				{
					(*pDst++) = generator();
				}
			}
		}

		return newImage;
	}

	template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>*>
	inline Image Image::Generate0_1(const Size size, Fty generator)
	{
		Image newImage(size);

		if (not newImage)
		{
			return newImage;
		}

		const int32 width = size.x;
		const int32 height = size.y;
		const double sx = 1.0 / (width - 1);
		const double sy = 1.0 / (height - 1);
		Color* pDst = newImage.data();

		for (int32 y = 0; y < height; ++y)
		{
			for (int32 x = 0; x < width; ++x)
			{
				if constexpr (std::is_invocable_r_v<Color, Fty, Vec2>)
				{
					(*pDst++) = generator({ sx * x, sy * y });
				}
				else // std::is_invocable_r_v<Color, Fty, double, double>
				{
					(*pDst++) = generator(sx * x, sy * y);
				}
			}
		}

		return newImage;
	}

	inline void swap(Image& a, Image& b) noexcept
	{
		a.swap(b);
	}
}

template <>
void std::swap(s3d::Image& a, s3d::Image& b) noexcept
{
	a.swap(b);
}
