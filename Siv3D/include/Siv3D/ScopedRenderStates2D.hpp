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
	class ScopedRenderStates2D : Uncopyable
	{
	private:

		Optional<BlendState> m_oldBlendState;
		Optional<RasterizerState> m_oldRasterizerState;
		Optional<SamplerState> m_oldSamplerState;

		void clear() noexcept;

	public:

		ScopedRenderStates2D() = default;

		explicit ScopedRenderStates2D(const BlendState& blendState);

		explicit ScopedRenderStates2D(const RasterizerState& rasterizerState);

		explicit ScopedRenderStates2D(const SamplerState& samplerState);

		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState);

		ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState);

		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState);

		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState);

		ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState);

		ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState);

		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerState& samplerState);

		ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState, const RasterizerState& rasterizerState);

		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerState& samplerState);

		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const BlendState& blendState);

		ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState, const RasterizerState& rasterizerState);

		ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const BlendState& blendState);

		ScopedRenderStates2D(ScopedRenderStates2D&& block) noexcept;

		~ScopedRenderStates2D();

		ScopedRenderStates2D& operator =(ScopedRenderStates2D&& block) noexcept;
	};
}
