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
# include "BlendState.hpp"
# include "RasterizerState.hpp"
# include "SamplerState.hpp"
# include "Rectangle.hpp"
# include "Mat3x2.hpp"

namespace s3d
{
	/// <summary>
	/// 2D グラフィックス
	/// </summary>
	/// <remarks>
	/// 2D　グラフィックスに関連する機能を提供します。
	/// </remarks>
	namespace Graphics2D
	{
		/// <summary>
		/// 2D 描画のブレンドステートを設定します。
		/// </summary>
		/// <param name="blendState">
		/// ブレンドステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetBlendState(const BlendState& blendState);

		/// <summary>
		/// 現在の 2D 描画のブレンドステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のブレンドステート
		/// </returns>
		[[nodiscard]] BlendState GetBlendState();

		/// <summary>
		/// 2D 描画のラスタライザーステートを設定します。
		/// </summary>
		/// <param name="rasterizerState">
		/// ラスタライザーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetRasterizerState(const RasterizerState& rasterizerState);

		/// <summary>
		/// 現在の 2D 描画のラスタライザーステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のラスタライザーステート
		/// </returns>
		[[nodiscard]] RasterizerState GetRasterizerState();



		void SetSamplerState(uint32 slot, const SamplerState& samplerState);

		/// <summary>
		/// 2D 描画のサンプラーステートを設定します。
		/// </summary>
		/// <param name="rasterizerState">
		/// サンプラーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		inline void SetSamplerState(const SamplerState& samplerState)
		{
			SetSamplerState(0, samplerState);
		}

		/// <summary>
		/// 現在の 2D 描画のサンプラーステートを取得します。
		/// </summary>
		/// <param name="slot">
		/// スロット
		/// </param>
		/// <returns>
		/// 現在の 2D 描画のサンプラーステート
		/// </returns>
		[[nodiscard]] SamplerState GetSamplerState(uint32 slot);

		[[nodiscard]] inline SamplerState GetSamplerState()
		{
			return GetSamplerState(0);
		}

		/// <summary>
		/// 現在の 2D 描画のサンプラーステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のサンプラーステート
		/// </returns>
		[[nodiscard]] SamplerState GetSamplerState();

		void SetScissorRect(const Rect& rect);

		[[nodiscard]] Rect GetScissorRect();

		void SetViewport(const Optional<Rect>& viewport);

		[[nodiscard]] Optional<Rect> GetViewport();
		
		void SetTransformLocal(const Mat3x2& matrix);

		void SetTransformCamera(const Mat3x2& matrix);

		void SetTransformScreen(const Mat3x2& matrix);
		
		[[nodiscard]] const Mat3x2& GetTransformLocal();

		[[nodiscard]] const Mat3x2& GetTransformCamera();

		[[nodiscard]] const Mat3x2& GetTransformScreen();

		[[nodiscard]] double GetMaxScaling();
	}
}
