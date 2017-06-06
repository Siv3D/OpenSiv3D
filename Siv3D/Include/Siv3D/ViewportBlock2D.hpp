//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Optional.hpp"
# include "Graphics2D.hpp"
# include "Uncopyable.hpp"

namespace s3d
{
	class ViewportBlock2D : Uncopyable
	{
	private:

		Optional<Optional<Rect>> m_oldViewport;

		void clear()
		{
			m_oldViewport.reset();
		}

	public:

		ViewportBlock2D() = default;

		explicit ViewportBlock2D(const Optional<Rect>& viewport)
			: m_oldViewport(Graphics2D::GetViewport())
		{
			Graphics2D::SetViewport(viewport);
		}

		ViewportBlock2D(int32 x, int32 y, int32 w, int32 h)
			: ViewportBlock2D(Rect(x, y, w, h)) {}

		ViewportBlock2D(const Point& pos, int32 w, int32 h)
			: ViewportBlock2D(Rect(pos, w, h)) {}

		ViewportBlock2D(int32 x, int32 y, const Size& size)
			: ViewportBlock2D(Rect(x, y, size)) {}

		ViewportBlock2D(const Point& pos, const Size& size)
			: ViewportBlock2D(Rect(pos, size)) {}

		ViewportBlock2D(ViewportBlock2D&& block)
		{
			m_oldViewport = block.m_oldViewport;

			block.clear();
		}

		~ViewportBlock2D()
		{
			m_oldViewport.then(Graphics2D::SetViewport);
		}

		ViewportBlock2D& operator =(ViewportBlock2D&& block)
		{
			if (!m_oldViewport && block.m_oldViewport)
			{
				m_oldViewport = block.m_oldViewport;
			}

			block.clear();

			return *this;
		}
	};
}
