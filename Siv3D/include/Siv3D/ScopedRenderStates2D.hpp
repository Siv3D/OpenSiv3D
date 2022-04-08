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
# include "ShaderStage.hpp"

namespace s3d
{
	/// @brief 2D 描画レンダーステート設定スコープオブジェクト
	/// @remark このオブジェクトが存在するスコープでは、2D 描画に、指定したレンダーステートが適用されます。
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
		explicit ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerState& samplerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerStateInfo& samplerStateInfo);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const Array<SamplerStateInfo>& samplerStateInfos);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerStateInfo& samplerStateInfo, const BlendState& blendState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const RasterizerState& rasterizerState, const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const BlendState& blendState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo, const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const SamplerStateInfo& samplerStateInfo, const RasterizerState& rasterizerState, const BlendState& blendState);


		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos, const BlendState& blendState, const RasterizerState& rasterizerState);

		SIV3D_NODISCARD_CXX20
		ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos, const RasterizerState& rasterizerState, const BlendState& blendState);


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
