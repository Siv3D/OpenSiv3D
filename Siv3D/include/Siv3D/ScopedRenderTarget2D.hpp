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
# include "Uncopyable.hpp"
# include "Optional.hpp"
# include "RenderTexture.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	/// @brief 2D 描画レンダーターゲット設定スコープオブジェクト
	/// @remark このオブジェクトが存在するスコープでは、2D 描画のレンダーターゲットとして、デフォルトのシーンではなく指定したレンダーテクスチャが使用されます。
	class ScopedRenderTarget2D : Uncopyable
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		ScopedRenderTarget2D() = default;

		/// @brief 2D 描画レンダーターゲット設定スコープオブジェクトを作成します。
		/// @param rt レンダーターゲットとして使用するテクスチャ。none の場合はデフォルトのシーンを使用
		SIV3D_NODISCARD_CXX20
		explicit ScopedRenderTarget2D(const Optional<RenderTexture>& rt);

		/// @brief ムーブコンストラクタ
		/// @param other 別の 2D 描画レンダーターゲット設定スコープオブジェクト
		SIV3D_NODISCARD_CXX20
		ScopedRenderTarget2D(ScopedRenderTarget2D&& other) noexcept;

		/// @brief デストラクタ
		~ScopedRenderTarget2D();

		//ScopedRenderTarget2D& operator =(ScopedRenderTarget2D && other) noexcept;

	private:
		
		Optional<Optional<RenderTexture>> m_oldRenderTarget;

		Optional<Optional<Rect>> m_oldViewport;

		void clear() noexcept;
	};
}
