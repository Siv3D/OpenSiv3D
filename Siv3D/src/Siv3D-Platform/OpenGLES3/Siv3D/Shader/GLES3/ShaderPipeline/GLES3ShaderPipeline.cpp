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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/SamplerState.hpp>
# include "GLES3ShaderPipeline.hpp"

namespace s3d
{
    static GLuint LinkShaders(GLuint vs, GLuint ps)
    {
        if (vs == 0 || ps == 0)
        {
            return 0;
        }

        GLuint program = ::glCreateProgram();

        ::glAttachShader(program, vs);
        ::glAttachShader(program, ps);

        ::glLinkProgram(program);

        ::glDetachShader(program, vs);
        ::glDetachShader(program, ps);

        return program;
    }

    ShaderPipeline::~ShaderPipeline()
    {
        for (auto [shaderSet, program] : m_programs)
		{
			::glDeleteProgram(program);
		}
    }

    bool ShaderPipeline::hasCachedShaderProgram(ShaderType vertexShader, ShaderType pixelShader) const
    {
        return m_programs.contains({ vertexShader, pixelShader });
    }

    ShaderPipeline::LinkedProgramState ShaderPipeline::linkShaders(ShaderType vertexShader, ShaderType pixelShader) 
    {
        ShaderSet shaderSet = { vertexShader, pixelShader };
        bool cacheExists = hasCachedShaderProgram(vertexShader, pixelShader);

        if (!cacheExists)
        {
            auto newProgram = s3d::LinkShaders(vertexShader, pixelShader);
            m_programs.emplace(shaderSet, newProgram);
        } 
       
        LinkedProgramState state;

        state.shaderProgram = m_programs[shaderSet];
        state.cacheHit = cacheExists;
        
        return state;
    }
}