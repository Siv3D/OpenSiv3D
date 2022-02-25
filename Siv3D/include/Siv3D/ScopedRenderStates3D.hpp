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
# include "Array.hpp"
# include "BlendState.hpp"
# include "RasterizerState.hpp"
# include "SamplerState.hpp"
# include "DepthStencilState.hpp"
# include "ShaderStage.hpp"

namespace s3d
{
	class ScopedRenderStates3D : Uncopyable
	{
	public:

		struct SamplerStateInfo
		{
			ShaderStage shaderStage;

			uint32 slot;

			SamplerState state;
		};

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D() = default;

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates3D(const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates3D(const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates3D(const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates3D(const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerState& samplerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerState& samplerState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerState& samplerState, const DepthStencilState& depthStencilState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const SamplerState& samplerState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const SamplerState& samplerState, const DepthStencilState& depthStencilState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const DepthStencilState& depthStencilState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerState& samplerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerState& samplerState, const RasterizerState& rasterizerState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerState& samplerState, const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerState& samplerState, const BlendState& blendState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerState& samplerState, const DepthStencilState& depthStencilState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerState& samplerState, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const SamplerStateInfo& samplerStateInfo, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const Array<SamplerStateInfo>& samplerStateInfos, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState);



		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(const BlendState& blendState, const RasterizerState& rasterizerState, const DepthStencilState& depthStencilState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates3D(ScopedRenderStates3D&& other) noexcept;

		~ScopedRenderStates3D();

		//ScopedRenderStates3D& operator =(ScopedRenderStates3D&& other) noexcept;

	private:

		Optional<BlendState> m_oldBlendState;
		
		Optional<RasterizerState> m_oldRasterizerState;

		Optional<DepthStencilState> m_oldDepthStencilState;

		Array<SamplerStateInfo> m_oldSamplerStateInfos;

		void clear() noexcept;
	};
}
