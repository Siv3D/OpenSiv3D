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

# include <Siv3D/ScopedCustomShader2D.hpp>
# include <Siv3D/Graphics2D.hpp>

namespace s3d
{
	ScopedCustomShader2D::ScopedCustomShader2D() {}

	ScopedCustomShader2D::ScopedCustomShader2D(const VertexShader& vs)
		: m_oldVS{ Graphics2D::GetCustomVertexShader() }
	{
		Graphics2D::Internal::SetCustomVertexShader(vs);
	}

	ScopedCustomShader2D::ScopedCustomShader2D(const PixelShader& ps)
		: m_oldPS{ Graphics2D::GetCustomPixelShader() }
	{
		Graphics2D::Internal::SetCustomPixelShader(ps);
	}

	ScopedCustomShader2D::ScopedCustomShader2D(const VertexShader& vs, const PixelShader& ps)
		: m_oldVS{ Graphics2D::GetCustomVertexShader() }
		, m_oldPS{ Graphics2D::GetCustomPixelShader() }
	{
		Graphics2D::Internal::SetCustomVertexShader(vs);
		Graphics2D::Internal::SetCustomPixelShader(ps);
	}

	ScopedCustomShader2D::ScopedCustomShader2D(const PixelShader& ps, const VertexShader& vs)
		: m_oldVS(Graphics2D::GetCustomVertexShader())
		, m_oldPS(Graphics2D::GetCustomPixelShader())
	{
		Graphics2D::Internal::SetCustomVertexShader(vs);
		Graphics2D::Internal::SetCustomPixelShader(ps);
	}

	ScopedCustomShader2D::ScopedCustomShader2D(ScopedCustomShader2D&& other) noexcept
	{
		m_oldVS = other.m_oldVS;
		m_oldPS = other.m_oldPS;
		other.clear();
	}

	ScopedCustomShader2D::~ScopedCustomShader2D()
	{
		m_oldVS.then(Graphics2D::Internal::SetCustomVertexShader);
		m_oldPS.then(Graphics2D::Internal::SetCustomPixelShader);
	}

	//ScopedCustomShader2D& ScopedCustomShader2D::operator =(ScopedCustomShader2D&& other) noexcept
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

	void ScopedCustomShader2D::clear() noexcept
	{
		m_oldVS.reset();
		m_oldPS.reset();
	}
}
