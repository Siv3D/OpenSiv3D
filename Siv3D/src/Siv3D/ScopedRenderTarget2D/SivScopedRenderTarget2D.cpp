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

# include <Siv3D/ScopedRenderTarget2D.hpp>
# include <Siv3D/Scene.hpp>

namespace s3d
{
	ScopedRenderTarget2D::ScopedRenderTarget2D(const Optional<RenderTexture>& rt)
		: m_oldRenderTarget(Graphics2D::Internal::GetRenderTarget())
		, m_oldViewport(Graphics2D::Internal::GetViewport())
	{
		Graphics2D::Internal::SetRenderTarget(rt);
		Graphics2D::Internal::SetViewport(rt ? Rect(rt->size()) : Scene::Rect());
	}

	ScopedRenderTarget2D::ScopedRenderTarget2D(ScopedRenderTarget2D&& other) noexcept
	{
		m_oldRenderTarget = other.m_oldRenderTarget;
		m_oldViewport = other.m_oldViewport;

		other.clear();
	}

	ScopedRenderTarget2D::~ScopedRenderTarget2D()
	{
		m_oldRenderTarget.then(Graphics2D::Internal::SetRenderTarget);
		m_oldViewport.then(Graphics2D::Internal::SetViewport);
	}

	ScopedRenderTarget2D& ScopedRenderTarget2D::operator =(ScopedRenderTarget2D&& other) noexcept
	{
		if (!m_oldRenderTarget && other.m_oldRenderTarget)
		{
			m_oldRenderTarget = other.m_oldRenderTarget;
		}

		if (!m_oldViewport && other.m_oldViewport)
		{
			m_oldViewport = other.m_oldViewport;
		}

		other.clear();

		return *this;
	}

	void ScopedRenderTarget2D::clear() noexcept
	{
		m_oldRenderTarget.reset();
		m_oldViewport.reset();
	}
}
