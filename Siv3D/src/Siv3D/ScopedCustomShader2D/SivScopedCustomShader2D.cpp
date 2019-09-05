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

# include <Siv3D/ScopedCustomShader2D.hpp>

namespace s3d
{
	ScopedCustomShader2D::ScopedCustomShader2D(const Optional<PixelShader>& ps)
		: m_oldPS(Graphics2D::GetCustomPixelShader())
	{
		Graphics2D::Internal::SetCustomPixelShader(ps);
	}

	ScopedCustomShader2D::ScopedCustomShader2D(ScopedCustomShader2D&& other) noexcept
	{
		m_oldPS = other.m_oldPS;

		other.clear();
	}

	ScopedCustomShader2D::~ScopedCustomShader2D()
	{
		m_oldPS.then(Graphics2D::Internal::SetCustomPixelShader);
	}

	ScopedCustomShader2D& ScopedCustomShader2D::operator =(ScopedCustomShader2D&& other) noexcept
	{
		if (!m_oldPS && other.m_oldPS)
		{
			m_oldPS = other.m_oldPS;
		}

		other.clear();

		return *this;
	}

	void ScopedCustomShader2D::clear() noexcept
	{
		m_oldPS.reset();
	}
}
