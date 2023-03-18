//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	/// @brief シェーダステージ
	enum class ShaderStage : uint8
	{
		/// @brief 頂点シェーダ
		Vertex,

		/// @brief ピクセルシェーダ
		Pixel,
	};

	namespace Shader
	{
		namespace Internal
		{
			[[nodiscard]]
			constexpr uint32 MakeSamplerSlot(ShaderStage stage, uint32 index) noexcept;

			[[nodiscard]]
			constexpr uint32 MakeUniformBlockBinding(ShaderStage stage, uint32 index) noexcept;
		}
	}
}

# include "detail/ShaderStage.ipp"
