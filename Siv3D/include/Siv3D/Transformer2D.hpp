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
# include "Mat3x2.hpp"
# include "Graphics2D.hpp"
# include "Cursor.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief 2D 座標変換スコープオブジェクト
	/// @remark このオブジェクトが存在するスコープでは、2D 描画とマウスカーソル座標に、指定した座標変換行列が適用されます。
	class Transformer2D : Uncopyable
	{
	public:

		/// @brief 座標変換の適用方法
		enum class Target : uint8
		{
			/// @brief ローカル座標変換行列スタックにプッシュ
			PushLocal,
			
			/// @brief カメラ座標変換行列スタックにプッシュ
			PushCamera,
			
			/// @brief ローカル座標変換行列を上書き
			SetLocal,
			
			/// @brief カメラ座標変換行列を上書き
			SetCamera,
		};

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Transformer2D() = default;

		/// @brief 2D 座標変換スコープオブジェクトを作成します。
		/// @param transform 2D 描画に適用する座標変換行列
		/// @param target 適用方法
		SIV3D_NODISCARD_CXX20
		Transformer2D(const Mat3x2& transform, Target target);

		/// @brief 2D 座標変換スコープオブジェクトを作成します。
		/// @param transform 2D 描画に適用する座標変換行列
		/// @param transformCursor transform をマウスカーソル座標にも適用する場合 `TransformCursor::Yes`, それ以外の場合は `TransformCursor::No`
		/// @param target 適用方法
		SIV3D_NODISCARD_CXX20
		explicit Transformer2D(const Mat3x2& transform, TransformCursor transformCursor = TransformCursor::No, Target target = Target::PushLocal);

		/// @brief 2D 座標変換スコープオブジェクトを作成します。
		/// @param graphics2DTransform 2D 描画に適用する座標変換行列
		/// @param cursorTransform マウスカーソル座標に適用する座標変換行列
		/// @param target 適用方法
		SIV3D_NODISCARD_CXX20
		Transformer2D(const Mat3x2& graphics2DTransform, const Mat3x2& cursorTransform, Target target = Target::PushLocal);

		/// @brief ムーブコンストラクタ
		/// @param other 別の 2D 座標変換スコープオブジェクト
		SIV3D_NODISCARD_CXX20
		Transformer2D(Transformer2D&& other) noexcept;

		/// @brief デストラクタ
		~Transformer2D();

	private:

		Target m_target = Target::PushLocal;

		Optional<Mat3x2> m_oldTransform;
		
		Optional<Mat3x2> m_oldCursorTransform;

		void clear() noexcept;

		bool isPush() const noexcept;

		bool isLocal() const noexcept;

		bool isCamera() const noexcept;

		const Mat3x2& getGraphics2DTransform() const noexcept;

		const Mat3x2& getCursorTransform() const noexcept;

		void setGraphics2DTransform(const Mat3x2& transform) const;

		void setCursorTransform(const Mat3x2& transform) const;
	};
}

# include "detail/Transformer2D.ipp"
