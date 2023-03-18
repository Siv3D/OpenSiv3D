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

# include <Siv3D/ScopedRenderTarget3D.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Graphics3D.hpp>

namespace s3d
{
	ScopedRenderTarget3D::ScopedRenderTarget3D(const Optional<RenderTexture>& rt)
		: m_oldRenderTarget{ Graphics3D::GetRenderTarget() }
		, m_oldViewport{ Graphics3D::GetViewport() }
	{
		Graphics3D::Internal::SetRenderTarget(rt);
		Graphics3D::Internal::SetViewport(rt ? Rect{ rt->size() } : Scene::Rect());
	}

	ScopedRenderTarget3D::ScopedRenderTarget3D(ScopedRenderTarget3D&& other) noexcept
	{
		m_oldRenderTarget = std::move(other.m_oldRenderTarget);
		m_oldViewport = std::move(other.m_oldViewport);

		other.clear();
	}

	ScopedRenderTarget3D::~ScopedRenderTarget3D()
	{
		m_oldRenderTarget.then(Graphics3D::Internal::SetRenderTarget);
		m_oldViewport.then(Graphics3D::Internal::SetViewport);
	}

	void ScopedRenderTarget3D::clear() noexcept
	{
		m_oldRenderTarget.reset();
		m_oldViewport.reset();
	}
}
