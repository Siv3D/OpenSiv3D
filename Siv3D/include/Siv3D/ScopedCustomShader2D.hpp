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
# include "VertexShader.hpp"
# include "PixelShader.hpp"

namespace s3d
{
	/// @brief 2D 描画カスタムシェーダ設定スコープオブジェクト
	/// @remark このオブジェクトが存在するスコープでは、2D 描画時に、指定したカスタムシェーダが使用されます。
	class ScopedCustomShader2D : Uncopyable
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		ScopedCustomShader2D();

		/// @brief 2D 描画カスタムシェーダ設定スコープオブジェクトを作成します。
		/// @param vs 設定するカスタム頂点シェーダ
		SIV3D_NODISCARD_CXX20
		explicit ScopedCustomShader2D(const VertexShader& vs);

		/// @brief 2D 描画カスタムシェーダ設定スコープオブジェクトを作成します。
		/// @param ps 設定するカスタムピクセルシェーダ
		SIV3D_NODISCARD_CXX20
		explicit ScopedCustomShader2D(const PixelShader& ps);

		/// @brief 2D 描画カスタムシェーダ設定スコープオブジェクトを作成します。
		/// @param vs 設定するカスタム頂点シェーダ
		/// @param ps 設定するカスタムピクセルシェーダ
		SIV3D_NODISCARD_CXX20
		ScopedCustomShader2D(const VertexShader& vs, const PixelShader& ps);

		/// @brief 2D 描画カスタムシェーダ設定スコープオブジェクトを作成します。
		/// @param ps 設定するカスタムピクセルシェーダ
		/// @param vs 設定するカスタム頂点シェーダ
		SIV3D_NODISCARD_CXX20
		ScopedCustomShader2D(const PixelShader& ps, const VertexShader& vs);

		/// @brief ムーブコンストラクタ
		/// @param other 別の2D 描画カスタムシェーダ設定スコープオブジェクト
		SIV3D_NODISCARD_CXX20
		ScopedCustomShader2D(ScopedCustomShader2D&& other) noexcept;

		/// @brief デストラクタ
		~ScopedCustomShader2D();

		//ScopedCustomShader2D& operator =(ScopedCustomShader2D&& other) noexcept;

	private:

		Optional<Optional<VertexShader>> m_oldVS;

		Optional<Optional<PixelShader>> m_oldPS;

		void clear() noexcept;
	};
}
