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
	inline ScopedRenderTarget2D::ScopedRenderTarget2D(const Optional<RenderTexture>& rt)
		: m_oldRenderTarget{ Graphics2D::GetRenderTarget() }
		, m_oldViewport{ Graphics2D::GetViewport() }
	{
		Graphics2D::Internal::SetRenderTarget(rt);
		Graphics2D::Internal::SetViewport(rt ? Rect{ rt->size() } : Scene::Rect());
	}

	inline ScopedRenderTarget2D::ScopedRenderTarget2D(ScopedRenderTarget2D&& other) noexcept
	{
		m_oldRenderTarget = std::move(other.m_oldRenderTarget);
		m_oldViewport = std::move(other.m_oldViewport);

		other.clear();
	}

	inline ScopedRenderTarget2D::~ScopedRenderTarget2D()
	{
		m_oldRenderTarget.then(Graphics2D::Internal::SetRenderTarget);
		m_oldViewport.then(Graphics2D::Internal::SetViewport);
	}

	inline void ScopedRenderTarget2D::clear() noexcept
	{
		m_oldRenderTarget.reset();
		m_oldViewport.reset();
	}
}
