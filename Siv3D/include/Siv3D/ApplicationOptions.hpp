//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	/// @brief エンジンの設定
	struct EngineOption
	{
		/// @brief デバッグヒープマネージャ (Windows のみ)
		enum class DebugHeap
		{
			/// @brief 有効
			Yes,

			/// @brief 無効
			No,
		};

		/// @brief レンダラー
		enum class Renderer
		{
			/// @brief デフォルト
			PlatformDefault = 0,

			/// @brief 非グラフィックスモード
			Headless = 1,

			/// @brief OpenGL
			OpenGL = 2,

			/// @brief Direc3D 11
			Direct3D11 = 3,

			/// @brief Metal
			Metal = 4,

			/// @brief WebGL
			WebGL2 = 5,
		};

		/// @brief Direct3D 11 ドライバーの種類 (Windows 版)
		enum class D3D11Driver
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

	struct ApplicationOptions
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

	extern ApplicationOptions g_applicationOptions;
}

# define SIV3D_COMBINE_(X,Y) X##Y
# define SIV3D_COMBINE(X,Y) SIV3D_COMBINE_(X,Y)
# define SIV3D_SET(value) const int SIV3D_COMBINE(siv3d_engine_otpion_,__LINE__) = s3d::detail::SetEngineOption(value);
