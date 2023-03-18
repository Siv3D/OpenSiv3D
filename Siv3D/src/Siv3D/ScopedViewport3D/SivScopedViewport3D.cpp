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

# include <Siv3D/ScopedViewport3D.hpp>
# include <Siv3D/Graphics3D.hpp>

namespace s3d
{
	ScopedViewport3D::ScopedViewport3D(const Optional<Rect>& viewport)
		: m_oldViewport{ Graphics3D::GetViewport() }
	{
		Graphics3D::Internal::SetViewport(viewport);
	}

	ScopedViewport3D::ScopedViewport3D(const int32 w, const int32 h)
		: ScopedViewport3D{ Rect{ w, h } } {}

	ScopedViewport3D::ScopedViewport3D(const Size size)
		: ScopedViewport3D{ Rect{ size } } {}

	ScopedViewport3D::ScopedViewport3D(const int32 x, const int32 y, const int32 w, const int32 h)
		: ScopedViewport3D{ Rect{ x, y, w, h } } {}

	ScopedViewport3D::ScopedViewport3D(const Point pos, const int32 w, const int32 h)
		: ScopedViewport3D{ Rect{ pos, w, h } } {}

	ScopedViewport3D::ScopedViewport3D(const int32 x, const int32 y, const Size size)
		: ScopedViewport3D{ Rect{ x, y, size } } {}

	ScopedViewport3D::ScopedViewport3D(const Point pos, const Size size)
		: ScopedViewport3D{ Rect{ pos, size } } {}

	ScopedViewport3D::ScopedViewport3D(ScopedViewport3D&& other) noexcept
	{
		m_oldViewport = std::move(other.m_oldViewport);
		other.clear();
	}

	ScopedViewport3D::~ScopedViewport3D()
	{
		m_oldViewport.then(Graphics3D::Internal::SetViewport);
	}

	void ScopedViewport3D::clear() noexcept
	{
		m_oldViewport.reset();
	}
}
