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

namespace s3d
{
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

		enum class D3D11Driver
		{
			Hardware,

			Hardware_FavorIntegrated,

			WARP,

			Reference
		};
	};

	struct ApplicationOptions
	{
		EngineOption::DebugHeap debugHeap		= EngineOption::DebugHeap::Yes;

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
