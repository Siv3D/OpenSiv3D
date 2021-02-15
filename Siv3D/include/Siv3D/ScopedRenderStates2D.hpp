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
# include "Graphics2D.hpp"

namespace s3d
{
	class ScopedRenderStates2D : Uncopyable
	{
	public:

		struct SamplerStateInfo
		{
			ShaderStage shaderStage;

			uint32 slot;

			SamplerState state;
		};

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D() = default;

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates2D(const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates2D(const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates2D(const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(ScopedRenderStates2D&& other) noexcept;

		~ScopedRenderStates2D();

		//ScopedRenderStates2D& operator =(ScopedRenderStates2D&& other) noexcept;

	private:

		Optional<BlendState> m_oldBlendState;
		
		Optional<RasterizerState> m_oldRasterizerState;
		
		Array<SamplerStateInfo> m_oldSamplerStateInfos;

		void clear() noexcept;
	};
}

# include "detail/ScopedRenderStates2D.ipp"
