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
# include "Common.hpp"

namespace s3d
{
	/// @brief エンジンの設定
	struct EngineOption
	{
		/// @brief デバッグヒープマネージャ (Windows のみ)
		enum class DebugHeap : uint8
		{
			/// @brief 有効
			Yes,

			/// @brief 無効
			No,
		};

		/// @brief レンダラー
		enum class Renderer : uint8
		{
			/// @brief デフォルト
			PlatformDefault = 0,

			/// @brief 非グラフィックスモード
			/// @remark 対応: Windows / macOS / Linux
			Headless = 1,

			/// @brief OpenGL 4.1
			/// @remark 対応: Windows / macOS / Linux
			OpenGL = 2,

			/// @brief Direc3D 11
			/// @remark 対応: Windows
			Direct3D11 = 3,

			/// @brief Metal (未完成のため現在使用できません)
			/// @remark 対応: なし
			Metal = 4,

			/// @brief OpenGL ES 3.0
			/// @remark 対応: Linux / Web
			OpenGLES = 5,

			/// @brief WebGL
			/// @remark 対応: Linux / Web
			WebGL2 = OpenGLES,

			/// @brief WebGPU
			/// @remark 対応: Web
			WebGPU = 6,
		};

		/// @brief Direct3D 11 ドライバーの種類 (Windows 版)
		enum class D3D11Driver : uint8
		{
			/// @brief ハードウェア
			Hardware,

			/// @brief ハードウェア (iGPU 優先)
			Hardware_FavorIntegrated,

			/// @brief WARP ドライバーを使用
			/// @remark やや実行が遅いですが、実行環境による影響を受けないドライバーです。
			WARP,

			/// @brief リファレンスドライバーを使用
			Reference
		};
	};

	struct EngineOptions
	{
		EngineOption::DebugHeap debugHeap		= EngineOption::DebugHeap::No;

		EngineOption::Renderer renderer			= EngineOption::Renderer::PlatformDefault;

		EngineOption::D3D11Driver d3d11Driver	= EngineOption::D3D11Driver::Hardware;
	};

	namespace detail
	{
		int SetEngineOption(EngineOption::DebugHeap) noexcept;
		int SetEngineOption(EngineOption::Renderer) noexcept;
		int SetEngineOption(EngineOption::D3D11Driver) noexcept;
	}

	extern EngineOptions g_engineOptions;
}

# define SIV3D_COMBINE_(X,Y) X##Y
# define SIV3D_COMBINE(X,Y) SIV3D_COMBINE_(X,Y)
# define SIV3D_SET(value) const int SIV3D_COMBINE(siv3d_engine_otpion_,__LINE__) = s3d::detail::SetEngineOption(value);
