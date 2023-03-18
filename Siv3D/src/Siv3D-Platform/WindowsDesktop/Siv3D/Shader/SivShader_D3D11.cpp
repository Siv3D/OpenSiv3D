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

# include <Siv3D/Shader.hpp>
# include <Siv3D/Shader/D3D11/CShader_D3D11.hpp>

namespace s3d
{
	namespace Platform::Windows
	{
		bool IsHLSLCompilerAvailable() noexcept
		{
			// CShader_D3D11 を取得
			CShader_D3D11* const pShader = static_cast<CShader_D3D11*>(Siv3DEngine::Get<ISiv3DShader>());

			if (not pShader) // 取得に失敗
			{
				return false;
			}

			return pShader->hasHLSLCompiler();
		}

		bool CompileHLSLToFile(const FilePathView hlslFilePath, const FilePathView toFilePath, const ShaderStage stage, const StringView entryPoint, const HLSLCompileOption flags)
		{
			// CShader_D3D11 を取得
			CShader_D3D11* const pShader = static_cast<CShader_D3D11*>(Siv3DEngine::Get<ISiv3DShader>());

			if (not pShader) // 取得に失敗
			{
				return false;
			}

			return pShader->compileHLSLToFile(hlslFilePath, toFilePath, stage, entryPoint, flags);
		}
	}
}
