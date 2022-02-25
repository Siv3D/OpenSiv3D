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

namespace s3d
{
	namespace Shader
	{
		namespace Internal
		{
			constexpr uint32 MakeSamplerSlot(ShaderStage stage, uint32 index) noexcept
			{
				if (stage == ShaderStage::Vertex)
				{
					return (index + 8);
				}
				else
				{
					return index;
				}
			}

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
