//-----------------------------------------------
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
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>
# include "Common.hpp"

namespace s3d
{
# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows
	{
		// HLSL コンパイルオプション
		// HLSL compile options
		// see D3DCOMPILE Constants
		enum class HLSLCompileOption
		{
			Debug				= (1 << 0),
			AvoidFlowControl	= (1 << 9),
			PreferFlowControl	= (1 << 10),
			EnableStrictness	= (1 << 11),
			OptimizationLevel3	= (1 << 15),
			WarningsAreErrors	= (1 << 18),
			Default				= EnableStrictness | OptimizationLevel3 | WarningsAreErrors,
		};
		DEFINE_BITMASK_OPERATORS(HLSLCompileOption);

		//// HLSL コンパイラが利用可能かを調べる
		//bool IsHLSLCompilerAvailable() noexcept;

		//// HLSL ファイルをコンパイルしてコンパイル結果をファイルに保存
		//bool CompileHLSLToFile(const FilePath& hlslFilePath, const FilePath& toFilePath, ShaderStage stage, const String& entryPoint, uint32 flags = HLSLCompileOption::Default);
	}

# endif
}
