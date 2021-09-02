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
	inline ScopedViewport3D::ScopedViewport3D(const Optional<Rect>& viewport)
		: m_oldViewport{ Graphics3D::GetViewport() }
	{
		Graphics3D::Internal::SetViewport(viewport);
	}

	inline ScopedViewport3D::ScopedViewport3D(const int32 w, const int32 h)
		: ScopedViewport3D{ Rect{ w, h } } {}

	inline ScopedViewport3D::ScopedViewport3D(const Size size)
		: ScopedViewport3D{ Rect{ size } } {}

	inline ScopedViewport3D::ScopedViewport3D(const int32 x, const int32 y, const int32 w, const int32 h)
		: ScopedViewport3D{ Rect{ x, y, w, h } } {}

	inline ScopedViewport3D::ScopedViewport3D(const Point pos, const int32 w, const int32 h)
		: ScopedViewport3D{ Rect{ pos, w, h } } {}

	inline ScopedViewport3D::ScopedViewport3D(const int32 x, const int32 y, const Size size)
		: ScopedViewport3D{ Rect{ x, y, size } } {}

	inline ScopedViewport3D::ScopedViewport3D(const Point pos, const Size size)
		: ScopedViewport3D{ Rect{ pos, size } } {}

	inline ScopedViewport3D::ScopedViewport3D(ScopedViewport3D&& other) noexcept
	{
		m_oldViewport = std::move(other.m_oldViewport);
		other.clear();
	}

	inline ScopedViewport3D::~ScopedViewport3D()
	{
		m_oldViewport.then(Graphics3D::Internal::SetViewport);
	}

	inline void ScopedViewport3D::clear() noexcept
	{
		m_oldViewport.reset();
	}
}
