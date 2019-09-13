//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "ShaderCommon.hpp"

namespace s3d
{
	namespace Shader
	{
		void Copy(const TextureRegion& from, RenderTexture& to);

		void Downsample(const TextureRegion& from, RenderTexture& to);

		void GaussianBlurH(const TextureRegion& from, RenderTexture& to);

		void GaussianBlurV(const TextureRegion& from, RenderTexture& to);

		void GaussianBlur(const TextureRegion& from, RenderTexture& to, const Vec2& direction);

		void GaussianBlur(const TextureRegion& from, RenderTexture& internalBuffer, RenderTexture& to);
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows::Shader
	{
		// HLSL コンパイルオプション
		// HLSL compile options
		struct HLSLCompileOption
		{
			// see D3DCOMPILE Constants
			enum Flag
			{
				Debug				= (1 << 0),
				AvoidFlowControl	= (1 << 9),
				PreferFlowControl	= (1 << 10),
				EnableStrictness	= (1 << 11),
				OptimizationLevel3	= (1 << 15),
				WarningsAreErrors	= (1 << 18),
				Default				= EnableStrictness | OptimizationLevel3 | WarningsAreErrors,
			};
		};

		// HLSL コンパイラが利用可能かを調べる
		bool IsHLSLCompilerAvailable() noexcept;

		// HLSL ファイルをコンパイルしてコンパイル結果をファイルに保存
		bool CompileHLSLToFile(const FilePath& hlslFilePath, const FilePath& toFilePath, ShaderStage stage, const String& entryPoint, uint32 flags = HLSLCompileOption::Default);
	}

# endif
}
