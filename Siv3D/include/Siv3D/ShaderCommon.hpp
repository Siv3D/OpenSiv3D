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

# if SIV3D_PLATFORM(WINDOWS)

# define SIV3D_VERTEX_SHADER_EXTENSION U".hlsl"
# define SIV3D_PIXEL_SHADER_EXTENSION U".hlsl"
# define SIV3D_SELECT_SHADER(HLSL_SHADER_EXTENSION, GLSL_SHADER_EXTENSION) HLSL_SHADER_EXTENSION

# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

# define SIV3D_VERTEX_SHADER_EXTENSION U".vert"
# define SIV3D_PIXEL_SHADER_EXTENSION U".frag"
# define SIV3D_SELECT_SHADER(HLSL_SHADER_EXTENSION, GLSL_SHADER_EXTENSION) GLSL_SHADER_EXTENSION

# else

# error Unimplemented

# endif

namespace s3d
{
	enum class ShaderStage
	{
		Vertex,

		Pixel,
	};

	struct ConstantBufferBinding
	{
		String name;
		
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
