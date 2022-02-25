//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Uncopyable.hpp"
# include "Optional.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	class ScopedViewport3D : Uncopyable
	{
	public:

		SIV3D_NODISCARD_CXX20
		ScopedViewport3D() = default;

		SIV3D_NODISCARD_CXX20
		explicit ScopedViewport3D(const Optional<Rect>& viewport);

		SIV3D_NODISCARD_CXX20
		ScopedViewport3D(int32 w, int32 h);

		SIV3D_NODISCARD_CXX20
		ScopedViewport3D(Size size);

		SIV3D_NODISCARD_CXX20
		ScopedViewport3D(int32 x, int32 y, int32 w, int32 h);

		SIV3D_NODISCARD_CXX20
		ScopedViewport3D(Point pos, int32 w, int32 h);

		SIV3D_NODISCARD_CXX20
		ScopedViewport3D(int32 x, int32 y, Size size);

		SIV3D_NODISCARD_CXX20
		ScopedViewport3D(Point pos, Size size);

		SIV3D_NODISCARD_CXX20
		ScopedViewport3D(ScopedViewport3D&& other) noexcept;

		~ScopedViewport3D();

		//ScopedViewport3D& operator =(ScopedViewport3D && other) noexcept;

	private:

		Optional<Optional<Rect>> m_oldViewport;

		void clear() noexcept;
	};
}
