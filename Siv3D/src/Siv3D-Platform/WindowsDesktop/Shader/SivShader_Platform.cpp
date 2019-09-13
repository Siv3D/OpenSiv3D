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

# include <Siv3D/Shader.hpp>
# include <Siv3DEngine.hpp>
# include <Shader/D3D11/CShader_D3D11.hpp>

namespace s3d
{
	namespace Platform::Windows::Shader
	{
		bool IsHLSLCompilerAvailable() noexcept
		{
			// CShader_D3D11 を取得
			CShader_D3D11* const pShader = dynamic_cast<CShader_D3D11*>(Siv3DEngine::Get<ISiv3DShader>());

			if (!pShader) // 取得に失敗
			{
				return false;
			}

			return pShader->hasHLSLCompiler();
		}

		bool CompileHLSLToFile(const FilePath& hlslFilePath, const FilePath& toFilePath, const ShaderStage stage, const String& entryPoint, const uint32 flags)
		{
			// CShader_D3D11 を取得
			CShader_D3D11* const pShader = dynamic_cast<CShader_D3D11*>(Siv3DEngine::Get<ISiv3DShader>());

			if (!pShader) // 取得に失敗
			{
				return false;
			}

			return pShader->compileHLSLToFile(hlslFilePath, toFilePath, stage, entryPoint, flags);
		}
	}
}
