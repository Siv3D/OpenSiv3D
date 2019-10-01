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

# pragma once
# include "Fwd.hpp"
# include "Graphics2D.hpp"
# include "Uncopyable.hpp"

namespace s3d
{
	class ScopedViewport2D : Uncopyable
	{
	private:

		Optional<Optional<Rect>> m_oldViewport;

		void clear() noexcept;

	public:

		ScopedViewport2D() = default;

		explicit ScopedViewport2D(const Optional<Rect>& viewport);

		ScopedViewport2D(int32 w, int32 h);

		ScopedViewport2D(const Size& size);

		ScopedViewport2D(int32 x, int32 y, int32 w, int32 h);

		ScopedViewport2D(const Point& pos, int32 w, int32 h);

		ScopedViewport2D(int32 x, int32 y, const Size& size);

		ScopedViewport2D(const Point& pos, const Size& size);

		ScopedViewport2D(ScopedViewport2D&& other) noexcept;

		~ScopedViewport2D();

		ScopedViewport2D& operator =(ScopedViewport2D&& other) noexcept;
	};
}
