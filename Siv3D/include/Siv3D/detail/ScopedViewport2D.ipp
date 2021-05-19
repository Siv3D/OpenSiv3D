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
	inline ScopedViewport2D::ScopedViewport2D(const Optional<Rect>& viewport)
		: m_oldViewport{ Graphics2D::GetViewport() }
	{
		Graphics2D::Internal::SetViewport(viewport);
	}

	inline ScopedViewport2D::ScopedViewport2D(const int32 w, const int32 h)
		: ScopedViewport2D{ Rect{ w, h } } {}

	inline ScopedViewport2D::ScopedViewport2D(const Size size)
		: ScopedViewport2D{ Rect{ size } } {}

	inline ScopedViewport2D::ScopedViewport2D(const int32 x, const int32 y, const int32 w, const int32 h)
		: ScopedViewport2D{ Rect{ x, y, w, h } } {}

	inline ScopedViewport2D::ScopedViewport2D(const Point pos, const int32 w, const int32 h)
		: ScopedViewport2D{ Rect{ pos, w, h } } {}

	inline ScopedViewport2D::ScopedViewport2D(const int32 x, const int32 y, const Size size)
		: ScopedViewport2D{ Rect{ x, y, size } } {}

	inline ScopedViewport2D::ScopedViewport2D(const Point pos, const Size size)
		: ScopedViewport2D{ Rect{ pos, size } } {}

	inline ScopedViewport2D::ScopedViewport2D(ScopedViewport2D&& other) noexcept
	{
		m_oldViewport = other.m_oldViewport;
		other.clear();
	}

	inline ScopedViewport2D::~ScopedViewport2D()
	{
		m_oldViewport.then(Graphics2D::Internal::SetViewport);
	}

	inline void ScopedViewport2D::clear() noexcept
	{
		m_oldViewport.reset();
	}
}
