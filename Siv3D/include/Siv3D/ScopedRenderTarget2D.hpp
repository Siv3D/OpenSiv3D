//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
	class ScopedRenderTarget2D : Uncopyable
	{
	private:

		Optional<Optional<RenderTexture>> m_oldRenderTarget;

		Optional<Optional<Rect>> m_oldViewport;

		void clear() noexcept;

	public:

		ScopedRenderTarget2D() = default;

		explicit ScopedRenderTarget2D(const Optional<RenderTexture>& rt);

		ScopedRenderTarget2D(ScopedRenderTarget2D&& other) noexcept;

		~ScopedRenderTarget2D();

		ScopedRenderTarget2D& operator =(ScopedRenderTarget2D&& other) noexcept;
	};
}
