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

# pragma once

namespace s3d
{
	inline ScopedCustomShader2D::ScopedCustomShader2D(const VertexShader& vs)
		: m_oldVS{ Graphics2D::GetCustomVertexShader() }
	{
		Graphics2D::Internal::SetCustomVertexShader(vs);
	}

	inline ScopedCustomShader2D::ScopedCustomShader2D(const PixelShader& ps)
		: m_oldPS{ Graphics2D::GetCustomPixelShader() }
	{
		Graphics2D::Internal::SetCustomPixelShader(ps);
	}

	inline ScopedCustomShader2D::ScopedCustomShader2D(const VertexShader& vs, const PixelShader& ps)
		: m_oldVS{ Graphics2D::GetCustomVertexShader() }
		, m_oldPS{ Graphics2D::GetCustomPixelShader() }
	{
		Graphics2D::Internal::SetCustomVertexShader(vs);
		Graphics2D::Internal::SetCustomPixelShader(ps);
	}

	inline ScopedCustomShader2D::ScopedCustomShader2D(const PixelShader& ps, const VertexShader& vs)
		: m_oldVS(Graphics2D::GetCustomVertexShader())
		, m_oldPS(Graphics2D::GetCustomPixelShader())
	{
		Graphics2D::Internal::SetCustomVertexShader(vs);
		Graphics2D::Internal::SetCustomPixelShader(ps);
	}

	inline ScopedCustomShader2D::ScopedCustomShader2D(ScopedCustomShader2D&& other) noexcept
	{
		m_oldVS = other.m_oldVS;
		m_oldPS = other.m_oldPS;
		other.clear();
	}

	inline ScopedCustomShader2D::~ScopedCustomShader2D()
	{
		m_oldVS.then(Graphics2D::Internal::SetCustomVertexShader);
		m_oldPS.then(Graphics2D::Internal::SetCustomPixelShader);
	}

	//inline ScopedCustomShader2D& ScopedCustomShader2D::operator =(ScopedCustomShader2D&& other) noexcept
	//{
	//	if ((not m_oldVS) && other.m_oldVS)
	//	{
	//		m_oldVS = other.m_oldVS;
	//	}

	//	if ((not m_oldPS) && other.m_oldPS)
	//	{
	//		m_oldPS = other.m_oldPS;
	//	}

	//	other.clear();
	//	
	//	return *this;
	//}

	inline void ScopedCustomShader2D::clear() noexcept
	{
		m_oldVS.reset();
		m_oldPS.reset();
	}
}
