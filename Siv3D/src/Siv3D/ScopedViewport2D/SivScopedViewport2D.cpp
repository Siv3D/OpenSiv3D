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

# include <Siv3D/ScopedViewport2D.hpp>
# include <Siv3D/Graphics2D.hpp>

namespace s3d
{
	ScopedViewport2D::ScopedViewport2D(const Optional<Rect>& viewport)
		: m_oldViewport{ Graphics2D::GetViewport() }
	{
		Graphics2D::Internal::SetViewport(viewport);
	}

	ScopedViewport2D::ScopedViewport2D(const int32 w, const int32 h)
		: ScopedViewport2D{ Rect{ w, h } } {}

	ScopedViewport2D::ScopedViewport2D(const Size size)
		: ScopedViewport2D{ Rect{ size } } {}

	ScopedViewport2D::ScopedViewport2D(const int32 x, const int32 y, const int32 w, const int32 h)
		: ScopedViewport2D{ Rect{ x, y, w, h } } {}

	ScopedViewport2D::ScopedViewport2D(const Point pos, const int32 w, const int32 h)
		: ScopedViewport2D{ Rect{ pos, w, h } } {}

	ScopedViewport2D::ScopedViewport2D(const int32 x, const int32 y, const Size size)
		: ScopedViewport2D{ Rect{ x, y, size } } {}

	ScopedViewport2D::ScopedViewport2D(const Point pos, const Size size)
		: ScopedViewport2D{ Rect{ pos, size } } {}

	ScopedViewport2D::ScopedViewport2D(ScopedViewport2D&& other) noexcept
	{
		m_oldViewport = std::move(other.m_oldViewport);
		other.clear();
	}

	ScopedViewport2D::~ScopedViewport2D()
	{
		m_oldViewport.then(Graphics2D::Internal::SetViewport);
	}

	void ScopedViewport2D::clear() noexcept
	{
		m_oldViewport.reset();
	}
}
