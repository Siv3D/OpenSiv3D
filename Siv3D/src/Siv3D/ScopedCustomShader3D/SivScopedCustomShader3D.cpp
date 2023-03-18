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

# include <Siv3D/ScopedCustomShader3D.hpp>
# include <Siv3D/Graphics3D.hpp>

namespace s3d
{
	ScopedCustomShader3D::ScopedCustomShader3D() {}

	ScopedCustomShader3D::ScopedCustomShader3D(const VertexShader& vs)
		: m_oldVS{ Graphics3D::GetCustomVertexShader() }
	{
		Graphics3D::Internal::SetCustomVertexShader(vs);
	}

	ScopedCustomShader3D::ScopedCustomShader3D(const PixelShader& ps)
		: m_oldPS{ Graphics3D::GetCustomPixelShader() }
	{
		Graphics3D::Internal::SetCustomPixelShader(ps);
	}

	ScopedCustomShader3D::ScopedCustomShader3D(const VertexShader& vs, const PixelShader& ps)
		: m_oldVS{ Graphics3D::GetCustomVertexShader() }
		, m_oldPS{ Graphics3D::GetCustomPixelShader() }
	{
		Graphics3D::Internal::SetCustomVertexShader(vs);
		Graphics3D::Internal::SetCustomPixelShader(ps);
	}

	ScopedCustomShader3D::ScopedCustomShader3D(const PixelShader& ps, const VertexShader& vs)
		: m_oldVS(Graphics3D::GetCustomVertexShader())
		, m_oldPS(Graphics3D::GetCustomPixelShader())
	{
		Graphics3D::Internal::SetCustomVertexShader(vs);
		Graphics3D::Internal::SetCustomPixelShader(ps);
	}

	ScopedCustomShader3D::ScopedCustomShader3D(ScopedCustomShader3D&& other) noexcept
	{
		m_oldVS = other.m_oldVS;
		m_oldPS = other.m_oldPS;
		other.clear();
	}

	ScopedCustomShader3D::~ScopedCustomShader3D()
	{
		m_oldVS.then(Graphics3D::Internal::SetCustomVertexShader);
		m_oldPS.then(Graphics3D::Internal::SetCustomPixelShader);
	}

	//ScopedCustomShader3D& ScopedCustomShader3D::operator =(ScopedCustomShader3D&& other) noexcept
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

	void ScopedCustomShader3D::clear() noexcept
	{
		m_oldVS.reset();
		m_oldPS.reset();
	}
}
