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

# include <Siv3D/ScopedColorMul2D.hpp>
# include <Siv3D/Graphics2D.hpp>

namespace s3d
{
	ScopedColorMul2D::ScopedColorMul2D(const ColorF& color)
		: m_oldColor{ Graphics2D::GetColorMul() }
	{
		Graphics2D::Internal::SetColorMul(color.toFloat4());
	}

	ScopedColorMul2D::ScopedColorMul2D(const double rgb, const double a)
		: ScopedColorMul2D{ ColorF{rgb, a} }
	{

	}

	ScopedColorMul2D::ScopedColorMul2D(const double r, const double g, const double b, const double a)
		: ScopedColorMul2D{ ColorF{ r, g, b, a } }
	{

	}

	ScopedColorMul2D::ScopedColorMul2D(ScopedColorMul2D&& other) noexcept
	{
		m_oldColor = other.m_oldColor;
		other.clear();
	}

	ScopedColorMul2D::~ScopedColorMul2D()
	{
		m_oldColor.then(Graphics2D::Internal::SetColorMul);
	}

	void ScopedColorMul2D::clear() noexcept
	{
		m_oldColor.reset();
	}
}
