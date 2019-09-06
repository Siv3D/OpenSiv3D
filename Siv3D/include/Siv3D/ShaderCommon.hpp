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
# include "String.hpp"

namespace s3d
{
	enum class ShaderStage
	{
		Vertex,

		Pixel,
	};

	struct BindingPoint
	{
		String bufferName;
		
		uint32 index;
	};
	
	namespace Shader
	{
		namespace Internal
		{
			constexpr uint32 MakeUniformBlockBinding(ShaderStage stage, uint32 index) noexcept
			{
				if (stage == ShaderStage::Vertex)
				{
					return index;
				}
				else
				{
					return index + 12;
				}
			}
		}
	}
}
