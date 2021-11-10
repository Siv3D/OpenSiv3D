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
# include "Common.hpp"
# include "Uncopyable.hpp"
# include "Optional.hpp"
# include "RenderTexture.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	class ScopedRenderTarget2D : Uncopyable
	{
	public:

		SIV3D_NODISCARD_CXX20
		ScopedRenderTarget2D() = default;

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderTarget2D(const Optional<RenderTexture>& rt);

		SIV3D_NODISCARD_CXX20
		ScopedRenderTarget2D(ScopedRenderTarget2D&& other) noexcept;

		~ScopedRenderTarget2D();

		//ScopedRenderTarget2D& operator =(ScopedRenderTarget2D && other) noexcept;

	private:
		
		Optional<Optional<RenderTexture>> m_oldRenderTarget;

		Optional<Optional<Rect>> m_oldViewport;

		void clear() noexcept;
	};
}
