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
# include "RenderTexture.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	class ScopedRenderTarget3D : Uncopyable
	{
	public:

		SIV3D_NODISCARD_CXX20
		ScopedRenderTarget3D() = default;

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderTarget3D(const Optional<RenderTexture>& rt);

		SIV3D_NODISCARD_CXX20
		ScopedRenderTarget3D(ScopedRenderTarget3D&& other) noexcept;

		~ScopedRenderTarget3D();

		//ScopedRenderTarget3D& operator =(ScopedRenderTarget3D && other) noexcept;

	private:
		
		Optional<Optional<RenderTexture>> m_oldRenderTarget;

		Optional<Optional<Rect>> m_oldViewport;

		void clear() noexcept;
	};
}
