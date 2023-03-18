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

# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/HashTable.hpp>
# include <tuple>

namespace s3d
{
	class ShaderPipeline
	{
	public:

		using ShaderType = GLuint;
		using ShaderProgramType = GLuint;

		struct LinkedProgramState
		{	
			ShaderProgramType shaderProgram;
			bool cacheHit;
		};

		struct ShaderSet
		{
			ShaderType vertexShader;
			ShaderType pixelShader;

			[[nodiscard]]
			friend constexpr bool operator==(ShaderSet lhs, ShaderSet rhs)
			{
				return lhs.vertexShader == rhs.vertexShader && lhs.pixelShader == rhs.pixelShader;
			}

			[[nodiscard]]
			friend constexpr bool operator!=(ShaderSet lhs, ShaderSet rhs)
			{
				return !(lhs == rhs);
			}
		};

	private:
		
		HashTable<ShaderSet, ShaderProgramType> m_programs;

		bool hasCachedShaderProgram(ShaderType vertexShader, ShaderType pixelShader) const;

	public:
		
		~ShaderPipeline();

		LinkedProgramState linkShaders(ShaderType vertexShader, ShaderType pixelShader);
	};
}

template <>
struct std::hash<s3d::ShaderPipeline::ShaderSet>
{
	[[nodiscard]]
	size_t operator()(const s3d::ShaderPipeline::ShaderSet& value) const noexcept
	{
		return s3d::Hash::FNV1a(value);
	}
};