﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	/// @brief シェーダステージ
	enum class ShaderStage
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
			constexpr uint32 MakeUniformBlockBinding(ShaderStage stage, uint32 index) noexcept
			{
				if (stage == ShaderStage::Vertex)
				{
					return index;
				}
				else
				{
					return (index + 12);
				}
			}
		}
	}
}
