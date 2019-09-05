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

# include <Siv3D/ScopedColor2D.hpp>

namespace s3d
{
	ScopedColorMul2D::ScopedColorMul2D(const ColorF& color)
		: m_oldColor(Graphics2D::Internal::GetColorMul())
	{
		Graphics2D::Internal::SetColorMul(color);
	}

	ScopedColorMul2D::ScopedColorMul2D(const double rgb, const double a)
		: ScopedColorMul2D(ColorF(rgb, a)) {}

	ScopedColorMul2D::ScopedColorMul2D(const double r, const double g, const double b, const double a)
		: ScopedColorMul2D(ColorF(r, g, b, a)) {}

	ScopedColorMul2D::ScopedColorMul2D(ScopedColorMul2D&& other) noexcept
	{
		m_oldColor = other.m_oldColor;
		other.clear();
	}

	ScopedColorMul2D::~ScopedColorMul2D()
	{
		m_oldColor.then(Graphics2D::Internal::SetColorMul);
	}

	ScopedColorMul2D& ScopedColorMul2D::operator =(ScopedColorMul2D&& other) noexcept
	{
		if (!m_oldColor && other.m_oldColor)
		{
			m_oldColor = other.m_oldColor;
		}

		other.clear();
		return *this;
	}

	void ScopedColorMul2D::clear() noexcept
	{
		m_oldColor.reset();
	}

	ScopedColorAdd2D::ScopedColorAdd2D(const ColorF& color)
		: m_oldColor(Graphics2D::Internal::GetColorAdd())
	{
		Graphics2D::Internal::SetColorAdd(color);
	}

	ScopedColorAdd2D::ScopedColorAdd2D(const double rgb, const double a)
		: ScopedColorAdd2D(ColorF(rgb, a)) {}

	ScopedColorAdd2D::ScopedColorAdd2D(const double r, const double g, const double b, const double a)
		: ScopedColorAdd2D(ColorF(r, g, b, a)) {}

	ScopedColorAdd2D::ScopedColorAdd2D(ScopedColorAdd2D&& other) noexcept
	{
		m_oldColor = other.m_oldColor;
		other.clear();
	}

	ScopedColorAdd2D::~ScopedColorAdd2D()
	{
		m_oldColor.then(Graphics2D::Internal::SetColorAdd);
	}

	ScopedColorAdd2D& ScopedColorAdd2D::operator =(ScopedColorAdd2D&& other) noexcept
	{
		if (!m_oldColor && other.m_oldColor)
		{
			m_oldColor = other.m_oldColor;
		}

		other.clear();
		return *this;
	}

	void ScopedColorAdd2D::clear() noexcept
	{
		m_oldColor.reset();
	}
}
